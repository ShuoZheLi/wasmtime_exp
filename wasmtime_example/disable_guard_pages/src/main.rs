//! Example of instantiating a wasm module which uses WASI imports.
use wasi_common::sync::WasiCtxBuilder;
use wasmtime::*;

fn main() -> Result<()> {
    // Define the WASI functions globally on the `Config`.

    // let mut config = Config::new();
    // config.memory_guard_size(0);
    // let engine = Engine::new(&config)?;

    let engine = Engine::default();

    // get memory guard size of the engine
    println!("Memory guard size: {}", engine.config());
    
    let mut linker = Linker::new(&engine);
    wasi_common::sync::add_to_linker(&mut linker, |s| s)?;

    // Create a WASI context and put it in a Store; all instances in the store
    // share this context. `WasiCtxBuilder` provides a number of ways to
    // configure what the target program will have access to.
    let wasi = WasiCtxBuilder::new()
        .inherit_stdio()
        .inherit_args()?
        .build();
    let mut store = Store::new(&engine, wasi);

    // Instantiate our module with the imports we've created, and run it.
    let module = Module::from_file(&engine, "/home/shuozhe/Documents/wasmtime_exp/example.wasm")?;
    linker.module(&mut store, "", &module)?;

    // time the execution
    let start = std::time::Instant::now();
    linker
        .get_default(&mut store, "")?
        .typed::<(), ()>(&store)?
        .call(&mut store, ())?;
    println!("Elapsed time: {:?}", start.elapsed());

    Ok(())
}