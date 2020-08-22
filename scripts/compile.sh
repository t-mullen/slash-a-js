#!/bin/bash

em++ --bind -O3 -s WASM=1 \
    -s EXPORT_NAME="'SlashA'" \
    -s NO_EXIT_RUNTIME=1 \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall"]' \
    -I lib/slash-a \
    lib/bindings.cpp \
    lib/slash-a/lib/*.cpp \
    -o build/slash-a.js