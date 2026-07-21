#include "config.hpp"

std::string get_config_file_path() noexcept
{
    return global_config.file_path;
}

void set_config_file_path(std::string file_path) noexcept
{
    global_config.file_path = file_path;
}

std::string get_config_output_path() noexcept
{
    return global_config.output_path;
}

void set_config_output_path(std::string output_path) noexcept
{
    global_config.output_path = output_path;
}

unsigned long long get_config_timeout() noexcept
{
    return global_config.timeout;
}

void set_config_timeout(unsigned long long timeout)
{
    global_config.timeout = timeout;
}

bool get_config_verbose() noexcept
{
    return global_config.verbose;
}

void set_config_verbose(bool verbose) noexcept
{
    global_config.verbose = verbose;
}
