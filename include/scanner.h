#ifndef __ZSON_SCANNER_H__
#define __ZSON_SCANNER_H__

#include <string>
#include <cstddef>

namespace zson {

class Scanner {
public:
    enum class JsonTokenType {
        BEGIN_OBJECT,       // {
        END_OBJECT,         // }

        VALUE_SEPARATOR,    // ,
        NAME_SEPARATOR,     // :

        VALUE_STRING,       // "string"
        VALUE_NUMBER,       // 1, 2, 2e10

        LITERAL_TRUE,       // true
        LITERAL_FALSE,      // false
        LITERAL_NULL,       // null

        BEGIN_ARRAY,        // [
        END_ARRAY,          // ]

        END_OF_SOURCE,      // EOF

        VALUE_ERROR,        // Unsupport Token
    };

    Scanner(const char* source): m_source{source}, m_curIdx{0}, m_prevIdx{0} {}
    JsonTokenType scan();
    const std::string& getValueString() const { return m_val_string; }
    double getValueNumber() const { return m_val_number; }
    void rollback() { m_curIdx = m_prevIdx; }
private:
    bool isAtEnd() const { return m_curIdx >= m_source.size(); }
    char advance() { return m_source[m_curIdx++]; }
    char peek() { return isAtEnd() ? '\0' : m_source[m_curIdx]; }
    char peekNext() { return ((m_curIdx + 1) >= m_source.size()) ? '\0' : m_source[m_curIdx + 1]; }

    void scanTrue();
    void scanFalse();
    void scanNull();
    void scanString();
    void scanNumber();

private:
    std::string m_source;       // JSON source string
    size_t m_curIdx;            // current index pos when scanning the JSON string
    size_t m_prevIdx;           // previous index pos for rollback
    std::string m_val_string;   // store string value
    double m_val_number;        // store number value
};

} // namespace zson

#endif // __ZSON_SCANNER_H__