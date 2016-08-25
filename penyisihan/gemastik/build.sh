#!/usr/bin/env bash
set -e

g++ -std=c++11 -o solution solution.cpp
g++ -I../tcframe/include -std=c++11 -o runner runner.cpp


./runner --solution-command=./solution



