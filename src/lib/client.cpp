#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cxxopts.hpp>
#include <exception>
#include <future>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include "client.hpp"
#include "config.hpp"
#include "saturation.hpp"
#include "tptp_parser.hpp"
#include "util.hpp"
int runClient(int argc, char *argv[])
{
    // STEP 0: grab timestamp at beginning of program
    const auto beginning = std::chrono::steady_clock::now();
    // STEP 1: parse command line args
    cxxopts::Options options("atp",
                             "automated theorem prover accepting TPTP cnf problemfiles as input.");

    options.add_options()("h, help", "Print usage information");
    options.add_options()("f, file", "Path to the input file", cxxopts::value<std::string>());
    options.add_options()("t, timeout",
                          "Set the maximum wall-clock time allowed for the solver to finish, in "
                          "seconds. Setting 0 disables the timeout. Default: 0",
                          cxxopts::value<unsigned long long>()->default_value("0"));
    options.add_options()("v, verbose",
                          "Print the parsed signature and input clauses before saturation starts",
                          cxxopts::value<bool>()->default_value("false"));
    options.add_options()(
        "p, proof-log-path",
        "If set, enable the logging of TPTP-compatible unsatisfiability proof to the file "
        "specified. The proof will be output only if the formula turned out to be unsat. "
        "The file at the specified path will be overwritten or newly created if it does not "
        "exist. ",
        cxxopts::value<std::string>());
    options.add_options()("b, base_dir",
                          "Set the base directory for resolving includes in TPTP files. (has to "
                          "include Axiom folder) Default: inputs",
                          cxxopts::value<std::string>()->default_value("inputs/TPTP-v9.2.1"));
    options.add_options()(
        "demodulation-index",
        "Index used to look up demodulation rewrite rules: none, fingerprint, or tree. "
        "Default: tree",
        cxxopts::value<std::string>()->default_value("tree"));
    options.add_options()(
        "feature-vector-indexing",
        "Use feature vector indexing for subsumption candidate lookup instead of a linear "
        "scan. Default: true",
        cxxopts::value<bool>()->default_value("true"));
    options.add_options()("subsumption",
                          "Eliminate clauses subsumed by an active clause. Disabling this keeps "
                          "redundant clauses around. Default: true",
                          cxxopts::value<bool>()->default_value("true"));

    try
    {
        cxxopts::ParseResult result = options.parse(argc, argv);

        if (result.count("help"))
        {
            std::printf("%s", options.help().c_str());
            return EXIT_SUCCESS;
        }

        if (result.count("file"))
        {
            set_config_file_path(result["file"].as<std::string>());
        }
        else
        {
            // file is required!
            std::printf("%s", options.help().c_str());
            return EXIT_FAILURE;
        }

        set_config_base_dir(result["base_dir"].as<std::string>());

        if (result.count("proof-log-path"))
        {
            set_config_output_path(result["proof-log-path"].as<std::string>());
        }
        else
        {
            set_config_output_path("");
        }
        set_config_timeout(result["timeout"].as<unsigned long long>());
        set_config_verbose(result["verbose"].as<bool>());

        std::string demodulationIndex = result["demodulation-index"].as<std::string>();
        if (demodulationIndex == "none")
            set_config_demodulation_index(DemodulationIndexKind::None);
        else if (demodulationIndex == "fingerprint")
            set_config_demodulation_index(DemodulationIndexKind::Fingerprint);
        else if (demodulationIndex == "tree")
            set_config_demodulation_index(DemodulationIndexKind::DiscriminationTree);
        else
        {
            std::cerr << "Error: invalid value for --demodulation-index: " << demodulationIndex
                      << std::endl;
            return EXIT_FAILURE;
        }
        set_config_feature_vector_indexing(result["feature-vector-indexing"].as<bool>());
        set_config_subsumption(result["subsumption"].as<bool>());
    }
    catch (cxxopts::exceptions::exception e)
    {
        std::cerr << "Error parsing command line arguments: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Define a task which runs the solver and handles in- and output
    std::packaged_task<int()> solver_task([] {
        // STEP 2: parse input file into a formula
        Signature signature;
        std::vector<Clause> formula =
            parseTPTPCNFFromFile(get_config_file_path(), get_config_base_dir(), signature);
        if (get_config_verbose())
        {
            printSignature(signature);
            for (const Clause &clause : formula)
            {
                printC(clause);
            }
        }
        ProofState proof;
        proof.passive = std::move(formula);

        proof.next_id = static_cast<int>(proof.passive.size());
        // STEP 3 prove it
        SaturationResult result = saturate(proof);

        // Step 4 output result
        if (result == SaturationResult::Unsatisfiable)
        {
            std::cout << "c UNSATISFIABLE" << std::endl;
            return EXIT_UNSAT;
        }
        else if (result == SaturationResult::Saturated)
        {
            std::cout << "c Saturated" << std::endl;
            return EXIT_SAT;
        }
        else
        {
            std::cout << "c UNKNOWN" << std::endl;
            std::cout << "Iteration Budget reached" << std::endl;

            return EXIT_UNKNOWN;
        }
    });

    // Now, start a worker thread for executing the actual Prover, and just wait in the main
    // thread for the result with a timeout

    // get a future / "ticket" to redeem the solver task result
    std::future<int> solver_future = solver_task.get_future();

    // start worker thread working on the solver task
    std::thread solver_worker(std::move(solver_task));

    if (get_config_timeout() == 0)
    {
        // if timeout is disabled, wait indefinitely until Prover is finished
        solver_future.wait();
        // wait until the worker has properly terminated
        solver_worker.join();
        try
        {
            // redeem future to get return value; rethrows any exception the solver threw
            return solver_future.get();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        // else, wait at most until the deadline
        const auto deadline = beginning + std::chrono::seconds(get_config_timeout());
        if ((solver_future.wait_until(deadline) == std::future_status::ready))
        {
            // Prover finished in time: return the exit value of the worker thread
            // wait until the worker has properly terminated
            solver_worker.join();
            try
            {
                // redeem future to get return value; rethrows any exception the solver threw
                return solver_future.get();
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            // timeout was reached: abandon worker thread and exit with an error
            solver_worker.detach();
            std::cout << "c UNKNOWN" << std::endl;
            std::cout << "Timeout reached" << std::endl;

            return EXIT_UNKNOWN;
        }
    }
}
