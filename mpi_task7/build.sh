#!/bin/bash
mpicxx -o ./target/task7 ./src/main.cpp
mpiexec -l -n 4 ./target/task7
