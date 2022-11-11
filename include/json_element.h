#ifndef __ZSON_JSON_ELEMENT_H__
#define __ZSON_JSON_ELEMENT_H__

#include <string>
#include <map>
#include <vector>

namespace zson {

class JsonElement {
public:
    using JsonObject = std::map<std::string, JsonElement>;
    using JsonArray = std::vector<JsonElement>;
    
    enum class Type {
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_NUMBER,
        JSON_BOOL,
        JSON_NULL
    };

    JsonElement(JsonObject* val);
    JsonElement(JsonArray* val);
    JsonElement(const std::string& val);
    JsonElement(double val);
    JsonElement(bool val);

    JsonObject* asObject();
    JsonArray* asArray();
    std::string asString();
    double asDouble();
    bool asBool();

    std::string dump();
private:
    union Value {
        JsonObject* val_object;
        JsonArray* val_array;
        std::string val_string;
        double val_number;
        bool val_bool;
    };
};

} // namespace zson

#endif // __ZSON_JSON_ELEMENT_H__