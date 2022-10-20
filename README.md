# C++ and Javascript Interoperability though WASM with Emscripten

## Installation

Follow [these steps](https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install) to install Emscripten.

> This is what we use to compile C|C++ into WebAssembly and create an API for JavaScript and C++ to communicate.

from project root

```shell
npm i
npm build:wasm
```

Assuming you've installed Emscripten, and followed the steps to add the binaries to your PATH, the compilation _should_ be successful.

## Execution

Usual React stuff...

```
npm start
```

## Interoperability

### Javascript

I created a simple hook to make calling `c++` functions as easy as possible.

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

Which makes calling functions quite elegant ( although, we do have to wait for the module to load first... ). Might be best to invoke it in a `useContext` hook and `provide` it where needed.

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

On the `C++` side, I use the Emscripten bind header to allow javascript to call the functions, It seems much easier than wrapping the functions with `cwrap`. Binding doesn't seem to require defining the signature too ( at least, not for primitive types ).

We provide a function pointer and the name we'll use to invoke the function in `JavaScript` to an Emscripten function. This also allows use of c++ standard library types like `std::string`

```c++
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <string>

std::string HelloWorld(std::string name) { return "Greetings " + name + "!"; }

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("HelloWorld", &HelloWorld);
}
```

## Running

![image](https://user-images.githubusercontent.com/83677410/196879973-ed08f239-f61a-4314-840e-0b43e67f2778.png)
