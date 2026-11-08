// --pre-js of the "emscripten" preset: createIec2c({wasmModule, wasmBinary})
// instantiates the WebAssembly.Module given as wasmModule, compiled once by
// the embedder, so that each run gets a fresh instance (iec2c keeps global
// state, and exits on errors) synchronously, without compiling again.
// wasmBinary must be given too (an empty Uint8Array does), the synchronous
// path of emscripten's glue compiles it otherwise.
var WebAssembly = Object.create(globalThis.WebAssembly, {
  Module: { value: function (binary) { return Module["wasmModule"] || new globalThis.WebAssembly.Module(binary); } }
});
