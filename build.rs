extern crate bindgen;

use std::env;
use std::path::PathBuf;

fn main() {
    println!("cargo:rustc-link-search=./");
    println!("cargo:rustc-link-lib=static=e4");

    let bindings = bindgen::Builder::default()
        .header("include/e4/e4.h")
        .clang_arg("-I./include")
        .whitelist_function("e4c_protect_message")
        .whitelist_function("e4c_unprotect_message")
        .whitelist_function("e4c_init")
        .whitelist_function("e4c_set_storagelocation")
        .whitelist_function("e4c_load")
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
