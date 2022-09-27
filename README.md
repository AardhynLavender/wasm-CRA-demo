# C++ and Javascript Interoperability though WASM with Emscripten

## Installation

```plaintext
Emscripten installation explaination here...
```

from project root

```shell
npm i
npm build:wasm
```

Assuming you've installed Emscripten, and followed the steps to add the binaries to your PATH, the compilation should be successfull

## Execution

Usual React stuff...

```
npm start
```

## Interoperability

### Javascript

I created a simple hook to make calling `c++` functions as simple as possible.

```js
function useWebAssembly() {
  const [loading, setLoading] = useState(true);
  const [module, setModule] = useState();
  useEffect(
    () =>
      createModule().then((module) => {
        setModule(module);
        setLoading(false);
      }),
    []
  );
  return [module, loading];
}
```

Which makes calling functions quite elegant ( although, we do have to wait for the module to load first... )

```js
function App() {
  const [module, loading] = useWebAssembly();
  if (loading) return "WebAssembly is loading...";
  return (
    <div className="App">
        {!loading ? module.HelloWorld("Aardhyn Lavender") : "Loading..."}
    </div>
  );
}
```

### C++

On the `C++` side, I use the EMSCIPTEN bind header to allow javascript to call the functions, It seems much easier than wrapping the functions with `cwrap`. Binding doesn't seem to require defining the signature too.

We can pass a function pointer to an emscipten function, and provide the name well use to invoke the function in `JavaScript`

This also allows use of c++ standard library types like `std::string`

```c++
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <string>

std::string HelloWorld(std::string name) { return "Greetings " + name + "!"; }

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("HelloWorld", &HelloWorld);
}
```
