#!/bin/bash

echo "Script begin"

g++ -o executable main.cpp universe.cpp particle.cpp box.cpp -lsfml-graphics -lsfml-window -lsfml-system
./executable

echo "CleanUp"

rm executable
rm data.csv

echo "Script end"
