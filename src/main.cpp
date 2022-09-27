#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <string>

std::string HelloWorld(std::string name) { return "Greetings " + name + "!"; }

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("HelloWorld", &HelloWorld);
}
