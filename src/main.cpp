#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#endif // __EMSCRIPTEN__
#include <string>
#include <iostream>

class name {
private:
    const std::string first;
    const std::string last;
    name() = delete;
public:
    name(const std::string& first, const std::string& last) : first(first), last(last) {  }
    inline std::string fullName() const { return first + " " + last; }
};

std::string SimpleGreeting(std::string name) { return "Greetings " + name + "!"; }

std::string Greeting(std::string first, std::string last) {
    const name greeting{ first, last };
    return "Hello there, " + greeting.fullName() + "!";
}

void Log(std::string message) { std::cout << message << std::endl; }

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("SimpleGreeting", &SimpleGreeting);
    emscripten::function("Greeting", &Greeting);
    emscripten::function("Log", &Log);
}
#endif // __EMSCRIPTEN__
