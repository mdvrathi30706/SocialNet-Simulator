#!/bin/bash
# ----------------------------------------
# SocialNet Simulator - Run Script
# Author: Madhav Rathi
# ----------------------------------------

# Step 1: Clear previous build
clear
echo "========================================="
echo "     🚀 Compiling SocialNet Simulator"
echo "========================================="

# Step 2: Compile the code
g++ -std=c++17 main.cpp -o socialnet 2> compile_log.txt

# Step 3: Check for compilation errors
if [ $? -ne 0 ]; then
    echo "❌ Compilation failed. Check compile_log.txt for details."
    exit 1
fi

echo "✅ Compilation successful."

# Step 4: Run the program
echo
echo "========================================="
echo "     🌐 Starting SocialNet Simulator"
echo "========================================="
echo

# If an input file is provided as argument, use it
if [ $# -eq 1 ]; then
    if [ -f "$1" ]; then
        echo "Running commands from: $1"
        echo
        ./socialnet < "$1"
    else
        echo "❌ File '$1' not found. Starting in interactive mode."
        echo
        ./socialnet
    fi
else
    echo "Starting in interactive mode..."
    echo
    ./socialnet
fi

echo
echo "========================================="
echo "     ✅ Program terminated successfully"
echo "========================================="
