# C++ and Javascript Interoperability though WASM with Emscripten

## Deployment

[`🚀 Launch`](https://idyllic-medovik-3ebc4f.netlify.app/)

[![Netlify Status](https://api.netlify.com/api/v1/badges/e970c529-8c7c-4244-b11a-b6363491f6fa/deploy-status)](https://app.netlify.com/sites/idyllic-medovik-3ebc4f/deploys)

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

```shell
npm start
```

or

```shell
npm build:react
serve -s build
```
