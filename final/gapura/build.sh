#!/usr/bin/env bash
set -e

g++ -I../tcframe/include -std=c++11 -o runner runner.cpp
g++ -std=c++11 -o a solution.cpp
javac BF.java


./runner --solution-command=./a
./runner submit --solution-command='java BF'

