#pragma once
#include "cnf.hpp"
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

struct TPTPParseError : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

// 0-ary function symbol needed to model predicate atoms as equalities
const Term &tptpTrue();

// Parse a TPTP problem consisting only of cnf formulas
// Supported language elements:
//   comments: `% ... \n` and `/* ... */`
//   cnf(name, role, <literal_disjunction>).
//   literals: atom | ~atom | term = term | term != term
//   atoms:    lower_word | lower_word(term, ...)
//   terms:    variable (upper-case or _-leading) | function application
//
// Unsupported constructs (fof/tff/thf/selective include/distinct objects/numbers/...)
// = everything else triggers a TPTPParseError. Non-selective includes
// (include('file').) are supported when a base directory is available.

// This function is only used for testing, since it has no base directory to
// resolve includes against.
std::vector<Clause> parseTPTPCNF(std::string_view input);

// read a problem file and parse it
std::vector<Clause> parseTPTPCNFFromFile(const std::string &path, const std::string &base_dir,
                                         Signature &signature);
