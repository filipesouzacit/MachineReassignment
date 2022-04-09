#!/bin/bash
g++ -std=c++14  -o MachineReassignment MachineReassignment.cpp
chmod a+x MachineReassignment
chmod a+x script1.run
chmod a+x script2.run
chmod a+x script3.run
chmod a+x script4.run
chmod a+x script5.run
nohup ./script1.run > ../result/data/out220408-S1.log &
nohup ./script2.run > ../result/data/out220408-S2.log &
nohup ./script3.run > ../result/data/out220408-S3.log &
nohup ./script4.run > ../result/data/out220408-S4.log &
nohup ./script5.run > ../result/data/out220408-S5.log &

ssh fdesouza@143.239.81.1 -p 40022
ssh fdesouza@143.239.81.140

g++ -std=c++11 -F/Library/Frameworks -I/usr/local/include  -c ortoolsTest.cpp
g++ -std=c++11 -F/Library/Frameworks -I/usr/local/include -framework gecode -o ortoolsTest ortoolsTest.cpp


g++ -I/usr/local/include -c ortoolsTest.cpp
g++ -o ortoolsTest  -L/usr/local/lib ortoolsTest.o  -lgecodesearch -lgecodeint -lgecodekernel  -lgecodesupport

LD_LIBRARY_PATH=/usr/local/lib
echo $LD_LIBRARY_PATH
export LD_LIBRARY_PATH
./ortoolsTest


filipesouzacit

git stash push --include-untracked
git stash drop



./MachineReassignment typeSearch=2 instance=a2_1 test=007 selectProcesses=4 subProblemSizeInit=10 subProblemSizeMax=10 improvementThreshold=9999999 runTime=10 failuresMax=400 discrepancyMax=5 seed=1 printFreq=1


./machineReassignment -t 300 -p data/model_a2_1.txt -i data/assignment_a2_1.txt -o sol.csv -name -s 1 -log onscreen


[1] 20418
[2] 20419
[3] 20420
[4] 20421
[5] 20426


chmod a+x script.run
nohup ./script.run > ../data/plot/out210914.log &


tar -zxvf prog-1-jan-2005.tar.gz

tar -zcvf ../data/072.tar.gz 072/


du -sh 072.tar.gz

scp fdesouza@143.239.81.140:~/MachineReassignment/result/solution.tar.gz /home/fdesouza/
scp -i  -p 40022 fdesouza@143.239.81.1:~/solution.tar.gz Users/filipe/CLionProjects/result/
# scp username@example.com:/opt/test.tar.gz /var/
# scp -P 2022 username@example.com:/opt/test.tar.gz /var/4
# scp -i private_key.pem username@example.com:/opt/test.tar.gz /var/