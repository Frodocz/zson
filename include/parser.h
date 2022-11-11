#ifndef __ZSON_PARSER_H__
#define __ZSON_PARSER_H__

#include "scanner.h"
#include "json_element.h"

namespace zson {

class Parser {
public:
    Parser(Scanner scanner): m_scanner(scanner) {}
    JsonElement* parse();
private:
    JsonObject* parseObject();
    JsonArray* parseArray();
private:
    Scanner m_scanner;
};

} // namespace zson

#endif // __ZSON_PARSER_H__