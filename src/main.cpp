#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#endif // __EMSCRIPTEN__
#include <string>

std::string HelloWorld(std::string name) { return "Greetings " + name + "!"; }

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("HelloWorld", &HelloWorld);
}
#endif // __EMSCRIPTEN__
