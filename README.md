# mod_solod

A FreeSWITCH module built with [So](https://github.com/solod-dev/solod/).

This module is mostly an experiment with So and C interop — it doesn't do anything useful.

## Build and Run

This repo includes pre-generated C code in the `generated` directory, so no So installation is required to build:

```
make c       # build with gcc
make install # install to /usr/local/freeswitch/mod (override in Makefile if needed)
```

If you have So installed, build natively:

```
make
make install
```

To regenerate the C code:

```
make gen
```

### Running in FreeSWITCH

```
load mod_solod                # load the module
solod                         # API command
originate null/1234 &solod    # dialplan application
```

## So/C Interop Notes

### Constants and Enums

C constants and enums must be redefined in So. See `core.go` for examples.

### Variadic Functions

FreeSWITCH uses variadic functions like `switch_log_printf` and `stream->write_function`. So cannot call a variadic function from within another variadic function, so helper macros in `embed.h` are used to bridge this gap.

### Types

So can use C types directly, but to export a type from a package it must be capitalized (like Go). For example:

```go
//so:extern
type switch_core_session_t struct {}
type Session switch_core_session_t
```

### Struct Members

So can access C struct members, but you only need to define the members you intend to use.

To export a member for external access, define a getter/setter function. See `frame.go` for an example.

### Embed C

`.h` and `.c` files can be embedded using the `so:embed` directive. `//go:build ignore` needs to be added to `.c` files at the very begining to prevent Go build errors.

### FreeSWITCH Module Conventions

FreeSWITCH requires a `mod_solod_module_interface` to be present, which can be defined using `SWITCH_MODULE_DEFINITION`. So doesn't support exposing structs, so `mod_solod.c` is used for that purpose.

Also, So doesn't support symbol visibility control — symbols exposed to FreeSWITCH must be in C for now.

### Visibility

It's good practice to hide symbols from the shared library and only expose public APIs. This helps prevent symbol conflicts when you have two or more shared libraries that might use different versions of `so_` functions.

So doesn't support visibility control, so you must use a C function marked with `__attribute__((visibility("default")))` or `__declspec(dllexport)`, etc., to make it visible.

`-f visibility=hidden` can be used to hide all symbols.
