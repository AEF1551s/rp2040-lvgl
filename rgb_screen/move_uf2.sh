#!/bin/bash

# Default values
BUILD_DIR="./build"
UF2_NAME="rgb_screen.uf2"
TARGET_MOUNT="/media/$USER/RPI-RP2"

# Usage message
usage() {
    echo "Usage: $0 [-b build_dir] [-f filename.uf2] [-t target_mount_dir]"
    echo ""
    echo "  -b    Path to build directory (default: ./build)"
    echo "  -f    .uf2 filename (default: my_project.uf2)"
    echo "  -t    Target mount point (default: /media/roboros/RPI-RP2)"
    exit 1
}

# Parse flags
while getopts "b:f:t:h" opt; do
    case ${opt} in
        b ) BUILD_DIR="$OPTARG" ;;
        f ) UF2_NAME="$OPTARG" ;;
        t ) TARGET_MOUNT="$OPTARG" ;;
        h ) usage ;;
        * ) usage ;;
    esac
done

SOURCE_UF2="${BUILD_DIR}/${UF2_NAME}"

# Check if file exists
if [ ! -f "$SOURCE_UF2" ]; then
    echo "Error: File not found: $SOURCE_UF2"
    exit 1
fi

# Check if mount point exists
if [ ! -d "$TARGET_MOUNT" ]; then
    echo "Error: Target mount not found: $TARGET_MOUNT"
    exit 1
fi

# Copy the file
echo "Copying $SOURCE_UF2 to $TARGET_MOUNT ..."
cp "$SOURCE_UF2" "$TARGET_MOUNT"

if [ $? -eq 0 ]; then
    echo "[SUCCESS]: Copied successful"
else
    echo "[ERROR]: Failed]"
    exit 1
fi
