g++ -std=c++14  -o MachineReassignment MachineReassignment.cpp
chmod a+x MachineReassignment
chmod a+x script1.run
chmod a+x script2.run
chmod a+x script3.run
chmod a+x script4.run
chmod a+x script5.run
nohup ./script1.run > ../result/data/out210923-S1.log &
nohup ./script2.run > ../result/data/out210923-S2.log &
nohup ./script3.run > ../result/data/out210923-S3.log &
nohup ./script4.run > ../result/data/out210923-S4.log &
nohup ./script5.run > ../result/data/out210923-S5.log &
