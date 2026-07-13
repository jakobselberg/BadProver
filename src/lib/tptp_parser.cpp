#include "tptp_parser.hpp"

#include <cctype>
#include <fstream>
#include <sstream>
#include <string>

namespace
{

// Implementation for our 0-ary "$true" function symbol
// separate implementation so we can keep details inside anonymous namespace
const Term &tptpTrueImpl()
{
    static const Term t = makeFunctionApplication(FunctionSymbol{0, "$true"}, {});
    return t;
}

class Parser
{

    std::string baseDir_;

  public:
    explicit Parser(std::string_view src) : src_(src)
    {
    }

    explicit Parser(std::string_view src, std::string baseDir)
        : src_(src), baseDir_(std::move(baseDir))
    {
    }

    std::vector<Clause> parseFile()
    {
        std::vector<Clause> clauses;
        skipWhitespaceAndComments();
        int nextId = 0;
        while (!atEnd())
        {
            clauses.push_back(parseCNFBody(nextId++));
            skipWhitespaceAndComments();
        }
        return clauses;
    }

  private:
    std::string_view src_;
    std::size_t pos_ = 0;

    [[noreturn]] void error(const std::string &msg) const
    {
        // compute 1-based line:column for the current position
        std::size_t line = 1;
        std::size_t col = 1;
        for (std::size_t i = 0; i < pos_ && i < src_.size(); ++i)
        {
            if (src_[i] == '\n')
            {
                ++line;
                col = 1;
            }
            else
            {
                ++col;
            }
        }
        std::ostringstream oss;
        oss << "TPTP parse error at line " << line << ", column " << col << ": " << msg;
        throw TPTPParseError(oss.str());
    }

    bool atEnd() const
    {
        return pos_ >= src_.size();
    }

    char peek() const
    {
        return atEnd() ? '\0' : src_[pos_];
    }

    char peekAt(std::size_t offset) const
    {
        return (pos_ + offset >= src_.size()) ? '\0' : src_[pos_ + offset];
    }

    char advance()
    {
        if (atEnd())
            error("unexpected end of input");
        return src_[pos_++];
    }

    bool match(char c)
    {
        if (peek() == c)
        {
            ++pos_;
            return true;
        }
        return false;
    }

    void expect(char c, const std::string &what)
    {
        if (!match(c))
            error("expected '" + std::string(1, c) + "' " + what);
    }

    void skipWhitespaceAndComments()
    {
        while (!atEnd())
        {
            char c = peek();
            if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                ++pos_;
            }
            else if (c == '%')
            {
                // line comment
                while (!atEnd() && src_[pos_] != '\n')
                    ++pos_;
            }
            else if (c == '/' && peekAt(1) == '*')
            {
                pos_ += 2;
                while (!atEnd() && !(src_[pos_] == '*' && peekAt(1) == '/'))
                    ++pos_;
                if (atEnd())
                    error("unterminated block comment");
                pos_ += 2; // skip */
            }
            else
            {
                break;
            }
        }
    }

    // token helpers

    static bool isAlpha(char c)
    {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
    static bool isDigit(char c)
    {
        return c >= '0' && c <= '9';
    }
    static bool isWordChar(char c)
    {
        return isAlpha(c) || isDigit(c) || c == '_';
    }

    // Read a maximal run of word characters (lowercase/upper/digit/_).
    // Does *not* skip leading whitespace.
    std::string readWord()
    {
        std::size_t start = pos_;
        while (!atEnd() && isWordChar(src_[pos_]))
            ++pos_;
        return std::string(src_.substr(start, pos_ - start));
    }

    // Lower-word: starts with [a-z] then word chars. Used for predicate/function
    // names, clause names, roles.
    std::string parseLowerWord(const std::string &what)
    {
        skipWhitespaceAndComments();
        if (atEnd() || !(peek() >= 'a' && peek() <= 'z'))
            error("expected " + what + " (a lower-case word)");
        return readWord();
    }

    // Upper-word: starts with [A-Z] or '_' then word chars. Used for variables.
    std::string parseUpperWord(const std::string &what)
    {
        skipWhitespaceAndComments();
        char c = peek();
        if (atEnd() || !((c >= 'A' && c <= 'Z') || c == '_'))
            error("expected " + what + " (a variable starting with upper-case or _)");
        return readWord();
    }

    std::string parseSingleQuotedString()
    {
        skipWhitespaceAndComments();
        expect('\'', "single-quoted string");
        std::string result;
        while (!atEnd() && peek() != '\'')
            result += advance();
        expect('\'', "closing single quote");
        return result;
    }

    // Integer name (used for cnf(123, ...)).
    std::string parseIntegerName()
    {
        std::size_t start = pos_;
        while (!atEnd() && isDigit(src_[pos_]))
            ++pos_;
        return std::string(src_.substr(start, pos_ - start));
    }

    // -- TPTP grammar -----------------------------------------------------

    // annotated_formula := language '(' name ',' role ',' body ')' '.'
    Clause parseCNFBody(int id)
    {
        skipWhitespaceAndComments();
        expect('(', "after 'cnf'");

        // name: lower word or integer (we accept and discard)
        skipWhitespaceAndComments();
        if (atEnd())
            error("expected clause name");
        char nc = peek();
        if (nc >= 'a' && nc <= 'z')
            (void)readWord();
        else if (isDigit(nc))
            (void)parseIntegerName();
        else
            error("expected clause name (lower-case word or integer)");

        skipWhitespaceAndComments();
        expect(',', "after clause name");

        // role: lower word (accepted and discarded for now)
        (void)parseLowerWord("clause role");

        skipWhitespaceAndComments();
        expect(',', "after clause role");

        // body: a (parenthesized) disjunction of literals
        std::set<Literal> lits = parseClauseBody();

        skipWhitespaceAndComments();
        expect(')', "to close cnf(...)");

        skipWhitespaceAndComments();
        expect('.', "to terminate cnf(...) formula");

        Clause c{id, std::move(lits)};
        return c;
    }

    std::vector<Clause> parseIncludeDirective()
    {
        skipWhitespaceAndComments();
        expect('(', "after 'include'");
        std::string path = parseSingleQuotedString();

        skipWhitespaceAndComments();
        if (match(','))
        {
            skipWhitespaceAndComments();
            expect('[', "include name list");
            int depth = 1;
            while (!atEnd() && depth > 0)
            {
                char c = advance();
                if (c == '[')
                    ++depth;
                else if (c == ']')
                    --depth;
            }
        }

        skipWhitespaceAndComments();
        expect(')', "to close include(...)");
        skipWhitespaceAndComments();
        expect('.', "to terminate include directive");

        if (baseDir_.empty())
            error("cannot resolve include directive without a file path context");

        std::string fullPath = baseDir_ + "/" + path;
        std::ifstream in(fullPath);
        if (!in)
            error("could not open included file: " + fullPath);
        std::ostringstream oss;
        oss << in.rdbuf();
        std::string contents = oss.str();

        std::string includedDir = fullPath.substr(0, fullPath.rfind('/'));
        Parser sub(contents, includedDir);
        return sub.parseFile();
    }

    // clause_body := '(' disjunction ')' | disjunction
    std::set<Literal> parseClauseBody()
    {
        skipWhitespaceAndComments();
        bool wrapped = false;
        if (peek() == '(')
        {
            ++pos_;
            wrapped = true;
        }

        std::set<Literal> lits = parseDisjunction();

        if (wrapped)
        {
            skipWhitespaceAndComments();
            expect(')', "to close clause body");
        }
        return lits;
    }

    // disjunction := literal ('|' literal)*
    std::set<Literal> parseDisjunction()
    {
        std::set<Literal> lits;
        lits.insert(parseLiteral());
        while (true)
        {
            skipWhitespaceAndComments();
            if (peek() != '|')
                break;
            ++pos_;
            lits.insert(parseLiteral());
        }
        return lits;
    }

    // literal := '~' atom | term '=' term | term '!=' term | atom
    Literal parseLiteral()
    {
        skipWhitespaceAndComments();
        if (peek() == '~')
        {
            ++pos_;
            Literal a = parsePlainAtom();
            return Literal{a.left, a.right, false};
        }

        // Otherwise: parse a term first, then look for '=' / '!=' to decide
        // between an equality literal and a reified predicate literal.
        Term t = parseTerm();
        skipWhitespaceAndComments();
        char c = peek();
        if (c == '=')
        {
            ++pos_;
            Term r = parseTerm();
            return Literal{std::move(t), std::move(r), true};
        }
        if (c == '!' && peekAt(1) == '=')
        {
            pos_ += 2;
            Term r = parseTerm();
            return Literal{std::move(t), std::move(r), false};
        }
        // No equality follows: the term we just parsed must in fact be a
        // predicate application (a lower-word-headed term), which we reify
        // as `t = $true`.
        if (std::holds_alternative<Variable>(t))
            error("a bare variable cannot be a literal");
        return Literal{std::move(t), tptpTrueImpl(), true};
    }

    // After '~', the next thing must be a predicate atom (not an equality and
    // not a bare variable): we therefore parse a term that must be a function
    // application, then optionally accept '=' / '!=' (TPTP also allows
    // `~(s = t)` to mean `s != t`, but we only allow the simple `~p(...)` form
    // here for simplicity).
    Literal parsePlainAtom()
    {
        skipWhitespaceAndComments();
        Term t = parseTerm();
        if (std::holds_alternative<Variable>(t))
            error("a bare variable cannot be an atom");
        // Disallow `~ s = t` to keep the grammar unambiguous.
        skipWhitespaceAndComments();
        char c = peek();
        if (c == '=' || (c == '!' && peekAt(1) == '='))
            error("'~' may not be followed by an equality literal; "
                  "use '!=' instead");
        return Literal{std::move(t), tptpTrueImpl(), true};
    }

    // term := variable | function_application
    Term parseTerm()
    {
        skipWhitespaceAndComments();
        if (atEnd())
            error("expected a term");
        char c = peek();
        if ((c >= 'A' && c <= 'Z') || c == '_')
        {
            std::string name = readWord();
            return Variable{std::move(name)};
        }
        if (c >= 'a' && c <= 'z')
        {
            std::string name = readWord();
            std::vector<Term> args;
            skipWhitespaceAndComments();
            if (peek() == '(')
            {
                ++pos_;
                skipWhitespaceAndComments();
                if (peek() != ')')
                {
                    args.push_back(parseTerm());
                    while (true)
                    {
                        skipWhitespaceAndComments();
                        if (peek() != ',')
                            break;
                        ++pos_;
                        args.push_back(parseTerm());
                    }
                }
                skipWhitespaceAndComments();
                expect(')', "to close function argument list");
            }
            int arity = static_cast<int>(args.size());
            return makeFunctionApplication(FunctionSymbol{arity, std::move(name)}, std::move(args));
        }
        if (isDigit(c))
            error("numeric terms are not supported");
        if (c == '"' || c == '\'')
            error("quoted/distinct-object terms are not supported");
        if (c == '$')
            error("built-in $-prefixed symbols are not supported");
        error(std::string("unexpected character '") + c + "' while parsing a term");
    }
};

} // namespace

const Term &tptpTrue()
{
    return tptpTrueImpl();
}

std::vector<Clause> parseTPTPCNF(std::string_view input)
{
    Parser p(input);
    return p.parseFile();
}

std::vector<Clause> parseTPTPCNFFromFile(const std::string &path)
{
    std::ifstream in(path);
    if (!in)
        throw TPTPParseError("could not open file: " + path);
    std::ostringstream oss;
    oss << in.rdbuf();
    std::string contents = oss.str();
    return parseTPTPCNF(contents);
}
