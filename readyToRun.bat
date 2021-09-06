#!/bin/bash
g++ -std=c++14  -o MachineReassignment MachineReassignment.cpp
chmod a+x MachineReassignment
chmod a+x script1.run
chmod a+x script2.run
chmod a+x script3.run
chmod a+x script4.run
chmod a+x script5.run
nohup ./script1.run > ../result/data/out210906-S1.log &
nohup ./script2.run > ../result/data/out210906-S2.log &
nohup ./script3.run > ../result/data/out210906-S3.log &
nohup ./script4.run > ../result/data/out210906-S4.log &
nohup ./script5.run > ../result/data/out210906-S5.log &

ssh fdesouza@143.239.81.1 -p 40022
ssh fdesouza@143.239.81.140



filipesouzacit

git stash push --include-untracked
git stash drop



./MachineReassignment typeSearch=2 instance=a2_1 test=007 selectProcesses=4 subProblemSizeInit=10 subProblemSizeMax=10 improvementThreshold=9999999 runTime=10 failuresMax=400 discrepancyMax=5 seed=1 printFreq=1


[1] 32562
[2] 32563
[3] 32564
[4] 32565
[5] 32570


chmod a+x script.run
nohup ./script.run > ../data/plot/out210906.log &