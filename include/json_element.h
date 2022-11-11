#ifndef __ZSON_JSON_ELEMENT_H__
#define __ZSON_JSON_ELEMENT_H__

#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <sstream>

namespace zson {

class JsonElement;
using JsonObject = std::map<std::string, JsonElement*>;
using JsonArray = std::vector<JsonElement*>;

class JsonElement {
public:
    enum class Type {
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_NUMBER,
        JSON_BOOL,
        JSON_NULL
    };

    union Value {
        JsonObject* val_object;
        JsonArray* val_array;
        std::string* val_string;
        double val_number;
        bool val_bool;
    };

    JsonElement(): m_type(Type::JSON_NULL) {}
    JsonElement(Type type) : m_type(type) {
        switch (type) {
            case Type::JSON_OBJECT:
                m_value.val_object = new JsonObject();
                break;
            case Type::JSON_ARRAY:
                m_value.val_array = new JsonArray();
                break;
            case Type::JSON_STRING:
                m_value.val_string = new std::string;
                break;
            case Type::JSON_NUMBER:
                m_value.val_number = 0;
                break;
            case Type::JSON_BOOL:
                m_value.val_bool = false;
                break;
            case Type::JSON_NULL:
                break;
            default:
                break;
        }
    }

    JsonElement(JsonObject* val) { value(val); }
    JsonElement(JsonArray* val) { value(val); }
    JsonElement(std::string* val) { value(val); }
    JsonElement(double val) { value(val); }
    JsonElement(bool val) { value(val); }

    ~JsonElement() {
        if (m_type == Type::JSON_OBJECT) {
            JsonObject* obj = m_value.val_object;
            for (auto& [key, val] : *obj) {
                delete val;
            }
            delete obj;
        } else if (m_type == Type::JSON_ARRAY) {
            JsonArray* arr = m_value.val_array;
            for (auto& elem : *arr) {
                delete elem;
            }
            delete arr;
        } else if (m_type == Type::JSON_STRING) {
            delete m_value.val_string;
        }
    }

    Type type() { return m_type; }

    void value(JsonObject* val) {
        m_type = Type::JSON_OBJECT;
        m_value.val_object = val;
    }

    void value(JsonArray* val) {
        m_type = Type::JSON_ARRAY;
        m_value.val_array = val;
    }

    void value(std::string* val) {
        m_type = Type::JSON_STRING;
        m_value.val_string = val;
    }

    void value(double val) {
        m_type = Type::JSON_NUMBER;
        m_value.val_number = val;
    }

    void value(bool val) {
        m_type = Type::JSON_BOOL;
        m_value.val_bool = val;
    }

    JsonObject* asObject() {
        if (m_type == Type::JSON_OBJECT) 
            return m_value.val_object;
        throw std::logic_error("Type of JsonElement is not JsonObject");
    }

    JsonArray* asArray() {
        if (m_type == Type::JSON_ARRAY) 
            return m_value.val_array;
        throw std::logic_error("Type of JsonElement is not JsonArray");
    }

    std::string* asString() {
        if (m_type == Type::JSON_STRING) 
            return m_value.val_string;
        throw std::logic_error("Type of JsonElement is not JsonString");
    }

    double asDouble() {
        if (m_type == Type::JSON_NUMBER) 
            return m_value.val_number;
        throw std::logic_error("Type of JsonElement is not JsonNumber");
    }

    bool asBool() {
        if (m_type == Type::JSON_BOOL) 
            return m_value.val_bool;
        throw std::logic_error("Type of JsonElement is not JsonBool");
    }

    friend std::ostream& operator<<(std::ostream& os, const JsonObject& obj) {
        os << '{';
        for (auto it = obj.cbegin(); it != obj.end(); ++it) {
            os << '\"' << it->first << '\"' << ": " << it->second->dump();
            if (it != obj.cend()) {
                os << ", ";
            }
        }
        os << '}';
        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const JsonArray& array) {
        os << '[';
        for (size_t i = 0; i < array.size(); ++i) {
            os << array[i]->dump();
            if (i != array.size() - 1) {
                os << ", ";
            }
        }
        os << ']';
        return os;
    }

    std::string dump() {
        std::stringstream ss;
        switch (m_type) {
            case Type::JSON_OBJECT: {
                ss << *(m_value.val_object);
                break;
            }
            case Type::JSON_ARRAY: {
                ss << *(m_value.val_array);
                break;
            }
            case Type::JSON_STRING: {
                ss << '\"' << *(m_value.val_string) << '\"';
                break;
            }
            case Type::JSON_NUMBER: {
                ss << m_value.val_number;
                break;
            }
            case Type::JSON_BOOL: {
                ss << (m_value.val_bool ? "true" : "false");
                break;
            }
            case Type::JSON_NULL: {
                ss << "null";
                break;
            }
        }

        return ss.str();
    }
private:
    Value m_value;
    Type m_type;
};

} // namespace zson

#endif // __ZSON_JSON_ELEMENT_H__