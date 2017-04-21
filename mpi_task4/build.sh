#!/bin/bash
mpicxx -o ./target/task4 ./src/main.cpp
mpiexec -l -n 4 ./target/task4
