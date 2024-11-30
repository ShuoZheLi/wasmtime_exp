#include <wasm.h>
#include <wasmtime.h>
#include <stdio.h>

int main() {
    // Create a new configuration object
    wasm_config_t *config = wasm_config_new();

    // Set the static memory guard size to 0 bytes
    wasmtime_config_memory_guard_size_set(config, 0);

    // Set the dynamic memory guard size to 0 bytes
    wasmtime_config_memory_guard_size_set(config, 0);

    // Create an engine with the specified configuration
    wasm_engine_t *engine = wasm_engine_new_with_config(config);

    // Rest of your Wasmtime setup...
    // For example, creating a store, loading, and executing a WebAssembly module

    // Clean up
    wasm_engine_delete(engine);

    return 0;
}
