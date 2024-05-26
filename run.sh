#!/bin/bash

echo "Script begin"

g++ -o compute_simu main.cpp universe.cpp particle.cpp box.cpp
./compute_simu
g++ -o watch_simu SFML_example.cpp box.cpp -lsfml-graphics -lsfml-window -lsfml-system
./watch_simu

echo "CleanUp"

rm compute_simu
rm data.csv
rm watch_simu

echo "Script end"
