#!/bin/bash
g++ -std=c++14  -o MachineReassignment MachineReassignment.cpp
chmod a+x MachineReassignment
chmod a+x script1.run
chmod a+x script2.run
chmod a+x script3.run
chmod a+x script4.run
chmod a+x script5.run
nohup ./script1.run > ../result/data/out210831-S1.log &
nohup ./script2.run > ../result/data/out210831-S2.log &
nohup ./script3.run > ../result/data/out210831-S3.log &
nohup ./script4.run > ../result/data/out210831-S4.log &
nohup ./script5.run > ../result/data/out210831-S5.log &

ssh fdesouza@143.239.81.1 -p 40022
ssh fdesouza@143.239.81.140

filipesouzacit

git stash push --include-untracked
git stash drop



./MachineReassignment typeSearch=2 instance=a2_1 test=007 selectProcesses=4 subProblemSizeInit=10 subProblemSizeMax=10 improvementThreshold=9999999 runTime=10 failuresMax=400 discrepancyMax=5 seed=1 printFreq=1


[1] 27397
[2] 27398
[3] 27399
[4] 27400
[5] 27406