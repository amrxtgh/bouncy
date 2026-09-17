#!/bin/bash
set -e
g++ main.cpp glad-build/src/gl.c -Iglad-build/include -lglfw -lGL -ldl -o bouncy
./bouncy
