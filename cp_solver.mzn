include "globals.mzn";
include "chuffed.mzn";
set of int:P; 
set of int:B; 
set of int:M;
set of int:MT;
set of int:R;
set of int:S;
set of int:L;
int:numM;
int:numR;
int:numP;

int:processMoveCost;
int:serviceMoveCost;
int:machineMoveCost;

array[1..1] of int:TR;
array[1..1,1..3] of int:balance;
array[1..1] of int:balanceCost;
array[1..2] of int:loadCost;
array[1..2] of int:spreadMin;
array[1..4] of int:location;
array[1..3] of int:machine;
array[1..4] of int:neighbourhood; 
array[1..3] of int:PMC;
array[1..2] of set of int:service; 
array[1..2] of set of int:depends; 
array[1..4,1..2] of int:capacity;
array[1..4,1..2] of int:scapacity;
array[1..5,1..2] of int:capacityTransient;
array[1..3,1..2] of int:requeriment;
array[1..4,1..4] of int:MMC;

include "data.dzn"; 

array[1..numP] of var 1..numM:mapP;


%trace("t: ", requeriment[1,1]):;

%Dependency constraints
constraint forall (s in S where card(depends[s])>0) 
          (forall (d in depends[s])
          (forall (p in service[s]) ((count_lt([neighbourhood[mapP[p1]]| p1 in service[d]],neighbourhood[mapP[p]],0)))));

%(among(card(service[s]),[neighbourhood[mapP[p]]| p in service[s]], {})));
%Spread constraints
constraint forall (s in S) (nvalue([location[mapP[p]]| p in service[s]])>=spreadMin[s]);
%Conflict constraints
constraint forall (s in S) (alldifferent([mapP[p]| p in service[s]]));
%Capacity constraints
constraint forall (r in R) (bin_packing_capa([capacity[m,r]|m in M] ,mapP,[requeriment[p,r]| p in P]));

%Transient usage constraints
constraint forall (r in TR) (bin_packing_capa([capacityTransient[m,r]|m in MT], 
                                              [((mapP[p]==machine[p]) * (numM+1))+((mapP[p]!=machine[p]) * mapP[p]) |p in P], 
                                              [requeriment[p,r] | p in P]));

solve ::seq_search([int_search(mapP, input_order, indomain_min)])
%Load cost
minimize sum([sum([max(0,sum([requeriment[p,r]|p in P where mapP[p]==m])-scapacity[m,r])|m in M])*loadCost[r]|r in R])+
%Balance cost
         sum([sum([max(0,balance[b,3]*(capacity[m,balance[b,1]]-sum([requeriment[p,balance[b,1]]|p in P where mapP[p]==m]))
         -(capacity[m,balance[b,2]]-sum([requeriment[p,balance[b,2]]|p in P where mapP[p]==m])))|m in M])*balanceCost[b]|b in B])+
%Process move cost
         sum([PMC[p]|p in P where mapP[p]!=machine[p]])*processMoveCost +
%Machine move cost       
         sum([MMC[machine[p],mapP[p]] |p in P])*machineMoveCost +
%Service move cost
         max([sum([1|p in service[s] where mapP[p]!=machine[p]])|s in S])*serviceMoveCost;
 
 
output 
       [format_justify_string(6,show(mp))++"\n"| mp in mapP]++
       ["\n Best Cost: "++show(sum([sum([max(0,sum([requeriment[p,r]|p in P where mapP[p]==m])-scapacity[m,r])|m in M])*loadCost[r]|r in R])+
         sum([sum([max(0,balance[b,3]*(capacity[m,balance[b,1]]-sum([requeriment[p,balance[b,1]]|p in P where mapP[p]==m]))
         -(capacity[m,balance[b,2]]-sum([requeriment[p,balance[b,2]]|p in P where mapP[p]==m])))|m in M])*balanceCost[b]|b in B])+
         sum([PMC[p]|p in P where mapP[p]!=machine[p]])*processMoveCost +
         sum([MMC[machine[p],mapP[p]] |p in P])*machineMoveCost +
         max([sum([1|p in service[s] where mapP[p]!=machine[p]])|s in S])*serviceMoveCost)];
