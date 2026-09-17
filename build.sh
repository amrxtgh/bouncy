#!/bin/bash
set -e
g++ -std=c++23 main.cpp glad-build/src/gl.c -Iglad-build/include -lglfw -lGL -ldl -o bouncy
./bouncy
