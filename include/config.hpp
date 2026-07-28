#pragma once
#include <cxxopts.hpp>

// index backing demodulation rewrite-rule lookup, from least to most optimized
enum class DemodulationIndexKind
{
    None,
    Fingerprint,
    DiscriminationTree
};

struct Config
{
    std::string file_path;
    std::string output_path;
    std::string base_dir;

    unsigned long long timeout;
    bool verbose = false;

    DemodulationIndexKind demodulation_index = DemodulationIndexKind::DiscriminationTree;
    bool feature_vector_indexing = true;
    bool subsumption = true;
};

static Config global_config = Config{};

std::string get_config_file_path() noexcept;
void set_config_file_path(std::string file_path) noexcept;

std::string get_config_output_path() noexcept;
void set_config_output_path(std::string output_path) noexcept;

std::string get_config_base_dir() noexcept;
void set_config_base_dir(std::string base_dir) noexcept;

unsigned long long get_config_timeout() noexcept;
void set_config_timeout(unsigned long long timeout);

bool get_config_verbose() noexcept;
void set_config_verbose(bool verbose) noexcept;

DemodulationIndexKind get_config_demodulation_index() noexcept;
void set_config_demodulation_index(DemodulationIndexKind kind) noexcept;

bool get_config_feature_vector_indexing() noexcept;
void set_config_feature_vector_indexing(bool enabled) noexcept;

bool get_config_subsumption() noexcept;
void set_config_subsumption(bool enabled) noexcept;
