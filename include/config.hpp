#include <cxxopts.hpp>

struct Config
{
    std::string file_path;
    // std::string output_path;
    unsigned long long timeout;
    bool verbose = false;
};

static Config global_config = Config{};

std::string get_config_file_path() noexcept;
void set_config_file_path(std::string file_path) noexcept;

// std::string get_config_output_path() noexcept;
// void set_config_output_path(std::string output_path) noexcept;

unsigned long long get_config_timeout() noexcept;
void set_config_timeout(unsigned long long timeout);

bool get_config_verbose() noexcept;
void set_config_verbose(bool verbose) noexcept;
