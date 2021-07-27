#!/bin/bash
g++ -std=c++14  -o MachineReassignment MachineReassignment.cpp
chmod a+x MachineReassignment
chmod a+x script.run
nohup ./script.run > ../result/data/outT1.log &
