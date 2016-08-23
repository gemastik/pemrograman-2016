#!/usr/bin/env bash
set -e

g++ -std=c++11 -o solution_aji solution_aji.cpp
g++ -I../tcframe/include -std=c++11 -o runner runner.cpp

./runner --solution-command=./solution_aji
