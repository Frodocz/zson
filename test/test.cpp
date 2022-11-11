#include <iostream>

#include "include/scanner.h"
#include "include/parser.h"

int main() {
    using namespace zson;
    auto source = R"(
                {
                    "glossary" : {
                        "test": true,
                        "hello": null,
                        "hello2": "miao\nmiao"
                    }
                }
                )";

    auto source2 = "[1, 2, 3, 4, 5, \"Hello\"]";

    Scanner scanner(source);
    Parser parser(scanner);

    JsonElement* res = parser.parse();
    JsonObject* obj = res->asObject();

    obj->insert({"tes", new JsonElement(20.0f)});

    std::cout << res->dump()  << '\n';

    delete res;
    return 0;
}