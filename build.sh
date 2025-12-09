#!/bin/bash

# Build script for WareHouse Simulation

echo "Compiling WareHouse Simulation..."
g++ -o warehouse src/main.cpp src/Order.cpp src/Simulation.cpp src/Event.cpp -I src

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Running simulation..."
    echo "----------------------------------------"
    ./warehouse.exe src/input.txt
else
    echo "Build failed!"
    exit 1
fi
