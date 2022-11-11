#include <stdexcept>
#include <string>

#include "include/parser.h"

namespace zson {

using JsonTokenType = Scanner::JsonTokenType;

JsonObject* Parser::parseObject() {
    JsonObject* res = new JsonObject();
    JsonTokenType next = m_scanner.scan();
    if (next == JsonTokenType::END_OBJECT) {
        return res;
    }
    m_scanner.rollback();

    while (true) {
        next = m_scanner.scan();
        if (next != JsonTokenType::VALUE_STRING) {
            throw std::logic_error("Key must be a string");
        }
        std::string key = m_scanner.getValueString();
        next = m_scanner.scan();
        if (next != JsonTokenType::NAME_SEPARATOR) {
            throw std::logic_error("Expected ':' as separator");
        }
        (*res)[key] = parse();
        next = m_scanner.scan();
        if (next == JsonTokenType::END_OBJECT) {
            break;
        }
        if (next != JsonTokenType::VALUE_SEPARATOR) {
            throw std::logic_error("Expected ',' as separator");
        }
    }
    return res;
}

JsonArray* Parser::parseArray() {
    JsonArray* res = new JsonArray();
    JsonTokenType next = m_scanner.scan();
    if (next == JsonTokenType::END_ARRAY) {
        return res;
    }
    
    m_scanner.rollback();
    while (true) {
        res->push_back(parse());
        next = m_scanner.scan();
        if (next == JsonTokenType::END_ARRAY) {
            break;
        }

        if (next != JsonTokenType::VALUE_SEPARATOR) {
            throw std::logic_error("Expected ',' as separator");
        }
    }
    return res;
}

JsonElement* Parser::parse() {
    JsonElement* element = new JsonElement();
    JsonTokenType type = m_scanner.scan();

    switch (type) {
        case JsonTokenType::END_OF_SOURCE: {
            break;
        }
        case JsonTokenType::BEGIN_OBJECT: {
            JsonObject* obj = parseObject();
            element->value(obj);
            break;
        }
        case JsonTokenType::BEGIN_ARRAY: {
            JsonArray* arr = parseArray();
            element->value(arr);
            break;
        }
        case JsonTokenType::VALUE_STRING: {
            std::string* str = new std::string(m_scanner.getValueString());
            element->value(str);
            break;
        }
        case JsonTokenType::VALUE_NUMBER: {
            double val = m_scanner.getValueNumber();
            element->value(val);
            break;
        }
        case JsonTokenType::LITERAL_TRUE: {
            element->value(true);
            break;
        }
        case JsonTokenType::LITERAL_FALSE: {
            element->value(false);
            break;
        }
        case JsonTokenType::LITERAL_NULL: {
            break;
        }
    }
    return element;
}

} // namespace zson