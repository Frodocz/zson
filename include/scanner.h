#ifndef __ZSON_SCANNER_H__
#define __ZSON_SCANNER_H__

#include <string>

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

        END_OF_SOURCE       // EOF
    };

    JsonTokenType scan();
private:
    std::string m_source;   // json source string
};

} // namespace zson

#endif // __ZSON_SCANNER_H__