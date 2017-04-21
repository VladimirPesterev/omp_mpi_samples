#!/bin/bash
mpicxx -o ./target/task5 ./src/main.cpp
mpiexec -l -n 4 ./target/task5
