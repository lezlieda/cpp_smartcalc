#!/bin/bash

make
valgrind --tool=memcheck --leak-check=yes ./test
