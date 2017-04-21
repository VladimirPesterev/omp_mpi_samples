#!/bin/bash
mpicxx -o ./target/task10 ./src/main.cpp
mpiexec -l -n 3 ./target/task10
