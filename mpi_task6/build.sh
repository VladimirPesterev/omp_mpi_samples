#!/bin/bash
mpicxx -o ./target/task6 ./src/main.cpp
mpiexec -l -n 4 ./target/task6
