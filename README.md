# E4 Rust crate [WIP]

Rust bindings to [libe4](https://github.com/teserakt-io/libe4),
generated using `bindgen`, from the E4 headers in [include](./include):


TODO:

* Test and write unit tests
* Clean exposed functions/constants (see `cargo doc --open`)
* Document API in README
* Publish crate (`cargo publish`)

## Usage

```
pub struct _e4storage {
    pub id: [u8; 16],
    pub key: [u8; 32],
    pub topiccount: u16,
    pub topics: [topic_key; 100],
    pub filepath: [c_char; 256],
    pub ctrltopic: [u8; 16],
}
```

```
pub unsafe extern "C" fn e4c_protect_message(
    ciphertext: *mut u8, 
    ciphertext_max_len: usize, 
    ciphertext_len: *mut usize, 
    message: *const u8, 
    message_len: usize, 
    topic_name: *const c_char, 
    storage: *mut e4storage, 
    proto_opts: u32
) -> c_int
```

```
pub unsafe extern "C" fn e4c_unprotect_message(
    message: *mut u8, 
    message_max_len: usize, 
    message_len: *mut usize, 
    ciphertext: *const u8, 
    ciphertext_len: usize, 
    topic_name: *const c_char, 
    storage: *mut e4storage, 
    proto_opts: u32
) -> c_int
```




