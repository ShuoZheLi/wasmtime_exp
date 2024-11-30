#include <stdio.h>
#include <wasmtime.h>

int main() {
    // Initialize the Wasmtime engine configuration
    wasm_config_t *config = wasm_config_new();
    wasmtime_context_t *wasmtime_config = wasmtime_config_get(config);

    // Disable guard pages
    wasmtime_config_memory_guard_size_set(wasmtime_config, 0); // Static memory guard size = 0 bytes
    // wasmtime_config_dynamic_memory_guard_size_set(wasmtime_config, 0); // Dynamic memory guard size = 0 bytes

    // Create the Wasmtime engine and store
    wasm_engine_t *engine = wasm_engine_new_with_config(config);
    wasm_store_t *store = wasm_store_new(engine);

    // Load the WebAssembly module
    FILE *file = fopen("example.wasm", "rb");
    if (!file) {
        printf("Error: Unable to open WebAssembly module\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size_t wasm_size = ftell(file);
    rewind(file);

    uint8_t *wasm_bytes = malloc(wasm_size);
    fread(wasm_bytes, 1, wasm_size, file);
    fclose(file);

    wasm_byte_vec_t wasm;
    wasm_byte_vec_new_uninitialized(&wasm, wasm_size);
    memcpy(wasm.data, wasm_bytes, wasm_size);
    free(wasm_bytes);
    
    // Compile the module
    wasm_module_t *module = wasm_module_new(engine, &wasm);
    if (!module) {
        printf("Error: Failed to compile module\n");
        return 1;
    }

    // Instantiate the module
    wasm_trap_t *trap = NULL;
    wasm_instance_t *instance = wasm_instance_new(store, module, NULL, &trap);
    if (trap) {
        printf("Error: Failed to instantiate module\n");
        return 1;
    }

    wasm_byte_vec_delete(&wasm);

    printf("WebAssembly module instantiated successfully with guard pages disabled!\n");

    // Clean up
    wasm_instance_delete(instance);
    wasm_module_delete(module);
    wasm_store_delete(store);
    wasm_engine_delete(engine);

    return 0;
}
