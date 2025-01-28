#!/bin/bash

g++ -std=c++17 -g -fsanitize=address CircularLinkedListTests.cpp CircularLinkedList.cpp -o tests
./tests