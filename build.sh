#!/bin/bash

g++ -o submit main.cpp handler.cpp -std=c++17 -O2 -lboost_system -lcpprest -lcrypto -lssl
