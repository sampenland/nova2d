/*
 * Copyright 2021 The Emscripten Authors.  All rights reserved.
 * Emscripten is available under two separate licenses, the MIT license and the
 * University of Illinois/NCSA Open Source License.  Both these licenses can be
 * found in the LICENSE file.
 */

#pragma once

#include <stdint.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Backend* backend_t;

// Obtains the backend_t of a specified path.
backend_t wasmfs_get_backend_by_path(char* path);

// Obtains the backend_t of a specified fd.
backend_t wasmfs_get_backend_by_fd(int fd);

// Creates and opens a new file in the new file system under a specific backend.
// Returns the file descriptor for the new file like `open`. Returns a negative
// value on error. TODO: It might be worth returning a more specialized type
// like __wasi_fd_t here.
int wasmfs_create_file(const char* pathname, mode_t mode, backend_t backend);

// Creates a new directory in the new file system under a specific backend.
// Returns 0 on success like `mkdir`, or a negative value on error.
int wasmfs_create_directory(const char* path, long mode, backend_t backend);

// Backend creation

// Creates a JSFile Backend in the new file system.
backend_t wasmfs_create_js_file_backend();

// A function that receives a void* and returns a backend.
typedef backend_t (*backend_constructor_t)(void*);

// Creates a Proxied Backend in the new file system.
backend_t wasmfs_create_proxied_backend(backend_constructor_t create_backend,
                                        void* arg);

backend_t wasmfs_create_fetch_backend(const char* base_url);

backend_t wasmfs_create_node_backend(const char* root);

#ifdef __cplusplus
}
#endif
