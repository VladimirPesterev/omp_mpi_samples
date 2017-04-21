#!/bin/bash
mpicxx -o ./target/task3 ./src/main.cpp
mpiexec -l -n 4 ./target/task3
