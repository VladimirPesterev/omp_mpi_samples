#!/bin/bash
mpicxx -o ./target/task1 ./src/main.cpp
mpiexec -l -n 2 ./target/task1
