extern crate bindgen;

use std::env;
use std::path::PathBuf;
use std::process::Command;

fn main() {
    println!("cargo:rustc-link-search=./libe4/build/all/lib/");
    println!("cargo:rustc-link-lib=static=e4");
    println!("cargo:rerun-if-changed=libe4/build/all/lib/libe4.a");


    Command::new("make")
            .current_dir("libe4/")
            .env("CONF", "all")
            .env("STORE", "none")
            .spawn()
            .expect("failed to update libe4");

    let bindings = bindgen::Builder::default()
        .header("libe4/build/all/include/e4/e4.h")
        .clang_arg("-I./libe4/build/all/include")
        .whitelist_function("e4c_pubkey_configure_storage")
        .whitelist_function("e4c_pubkey_init")
        .whitelist_function("e4c_pubkey_protect_message")
        .whitelist_function("e4c_pubkey_set_id")
        .whitelist_function("e4c_pubkey_set_idkey")
        .whitelist_function("e4c_pubkey_set_topickey")
        .whitelist_function("e4c_pubkey_sync")
        .whitelist_function("e4c_pubkey_unprotect_message")
        .whitelist_function("e4c_symkey_configure_storage")
        .whitelist_function("e4c_symkey_init")
        .whitelist_function("e4c_symkey_load")
        .whitelist_function("e4c_symkey_protect_message")
        .whitelist_function("e4c_symkey_set_id")
        .whitelist_function("e4c_symkey_set_idkey")
        .whitelist_function("e4c_symkey_set_topickey")
        .whitelist_function("e4c_symkey_sync")
        .whitelist_function("e4c_symkey_unprotect_message")
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
