#!/bin/bash
mpicxx -o ./target/task9 ./src/main.cpp
mpiexec -l -n 5 ./target/task9
