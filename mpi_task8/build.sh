#!/bin/bash
mpicxx -o ./target/task8 ./src/main.cpp
mpiexec -l -n 5 ./target/task8
