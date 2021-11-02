#!/bin/bash
set -e
g++ -Iinclude -Wall -g src/* -o a.out
./a.out