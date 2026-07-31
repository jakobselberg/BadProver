cmake_minimum_required(VERSION 3.20)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Important for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# library
add_library(atp_lib
    src/lib/terms.cpp
    src/lib/unification.cpp
    src/lib/cnf.cpp
    src/lib/tptp_parser.cpp
    src/lib/inference.cpp
    src/lib/ordering.cpp
    src/lib/saturation.cpp
    src/lib/util.cpp
    src/lib/config.cpp
    src/lib/client.cpp
    src/lib/simplification.cpp
    src/lib/subsumption.cpp
    src/lib/selection.cpp
    src/lib/discrimination_tree.cpp
    src/lib/feature_vector.cpp
    src/lib/fingerprint.cpp
    src/lib/superposition_index.cpp

)
target_include_directories(atp_lib PUBLIC
    include
)

# define the executable
add_executable(atp
    src/main.cpp
)
target_link_libraries(atp PRIVATE
    atp_lib
)


# testing
enable_testing()

function(add_doctest TEST_NAME)
    add_executable(${TEST_NAME}
        tests/${TEST_NAME}.cpp
    )

    target_link_libraries(${TEST_NAME} PRIVATE
        atp_lib
    )

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_doctest(terms_test)
add_doctest(tptp_parser_test)
add_doctest(inference_test)
add_doctest(discrimination_tree_test)
add_doctest(feature_vector_test)


# set compiler options to enable more warnings and errors
target_compile_options(
    atp_lib PRIVATE -O3 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -Wfloat-conversion -Wcast-align -Wcast-qual -Wold-style-cast
)

target_compile_options(
    atp PRIVATE -O3 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -Wfloat-conversion -Wcast-align -Wcast-qual -Wold-style-cast
)