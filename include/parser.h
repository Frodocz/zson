#ifndef __ZSON_PARSER_H__
#define __ZSON_PARSER_H__

#include "scanner.h"

namespace zson {

class Parser {
public:
    Parser(Scanner scanner);
    JsonElement* parse();
private:
};

} // namespace zson

#endif // __ZSON_PARSER_H__