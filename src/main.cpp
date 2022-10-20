#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#endif // __EMSCRIPTEN__
#include "../include/SDL2/include/SDL.h"
#include <string>
#include <iostream>

// Complex types can be used internally.
// 
// As in, we dont need to declare the `name` class to emscripten, even 
// though we instanciate it with a function emscripten has a binding 
// for.

class name {
private:
    const std::string first;
    const std::string last;
    name() = delete;
public:
    name(const std::string& first, const std::string& last) : first(first), last(last) {  }
    inline std::string fullName() const { return first + " " + last; }
};

std::string Greeting(std::string first, std::string last) {
    const name greeting{ first, last };
    return "Hello there, " + greeting.fullName() + "!";
}

// Standard output is redirected to the JS console

void Log(std::string message) { std::cout << message << std::endl; }

// We can write SDL2, and provide our gameloop to Emscripten.
// the renderer is redirected to an HTML Canvas we provide client-side

int vx = 1;
int vy = 5;
SDL_Rect rect{ 0, 0, 100, 100 };

SDL_Window* window;
SDL_Renderer* renderer;
	
void mainLoop() {
    // simple bounce logic
    if (rect.x + vx > 1600 - 100 || rect.x + vx < 0) vx *= -1;
    if (rect.y + vy > 900 - 100 || rect.y + vy < 0) vy *= -1;
    rect.x += vx;
    rect.y += vy;

    // clear then render the rect
    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

// Emscripten will call this `once` at load time, ( every page load + subsequent refresh )
// We're using React.js, so this works fine.

int main() {
    // initalize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(1600, 900, 0, &window, &renderer);
	
    // bind loop
    emscripten_set_main_loop(mainLoop, -1, true);

    // cleanup 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

// bind pointers to the functions we want to call frontend

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("Greeting", &Greeting);
    emscripten::function("Log", &Log);
}
#endif // __EMSCRIPTEN__
