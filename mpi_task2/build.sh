#!/bin/bash
mpicxx -o ./target/task2 ./src/main.cpp
mpiexec -l -n 2 ./target/task2
