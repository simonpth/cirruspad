#!/bin/bash

# Configuration
SOURCE_DIR="build/WebAssembly_Qt_6_10_1_single_threaded-Release"
TARGET_DIR="docs"

# Ensure target directory exists
mkdir -p "$TARGET_DIR"

if [ ! -d "$SOURCE_DIR" ]; then
    echo "Error: Source directory $SOURCE_DIR not found."
    echo "Please ensure you have built the single-threaded WebAssembly target."
    exit 1
fi

echo "Deploying WebAssembly files from $SOURCE_DIR to $TARGET_DIR..."

# List of important WASM files to copy
FILES_TO_COPY=(
    "appcirruspad.js"
    "appcirruspad.wasm"
)

for file in "${FILES_TO_COPY[@]}"; do
    if [ -f "$SOURCE_DIR/$file" ]; then
        cp "$SOURCE_DIR/$file" "$TARGET_DIR/"
        echo "Copied $file"
    else
        echo "Warning: $file not found in $SOURCE_DIR"
    fi
done

echo "Deployment complete."
