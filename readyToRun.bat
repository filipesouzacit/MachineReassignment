#!/bin/bash
g++ -std=c++14  -o MachineReassignment MachineReassignment.cpp
chmod a+x MachineReassignment
chmod a+x script.run
nohup ./script1.run > ../result/data/out03-09-S1.log &

git stash push --include-untracked
git stash drop

./MachineReassignment typeSearch=2 instance=a2_1 test=007 selectProcesses=4 subProblemSizeInit=10 subProblemSizeMax=10 improvementThreshold=9999999 runTime=10 failuresMax=400 discrepancyMax=5 seed=1 printFreq=1
