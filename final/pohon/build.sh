#!/usr/bin/env bash
set -e

g++ -I../tcframe/include -std=c++11 -o runner runner.cpp
g++ -std=c++11 -o a solution_aji.cpp
g++ -std=c++11 -o b solution_ashar.cpp


./runner --solution-command=./a
./runner submit --solution-command=./b

