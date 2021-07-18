#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed May  5 16:45:09 2021

@author: filipe
"""

import sys
import glob
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os

bestSolution = pd.read_csv('bestSolution.csv')
instance = list(bestSolution["instance"].values)
BK = list(bestSolution["BK"].values)
init = list(bestSolution["init"].values)
result = {"instance":instance,
          "init":init,
          "BK":BK}
      
files = glob.glob('../result/solution/*/dataPlot_*')
testIds = sorted(list(set([i.split('/')[3] for i in files])))

for t in testIds:
    test = []
    test2 = []
    for i in instance:
        files = glob.glob('../result/solution/'+t+'/dataPlot_*'+i+'.*')
        r = []
        for f in files:
            with open(f) as fl:
                r.append(int(fl.readline().split(';')[-2]))
        r1 = 0 if len(r)<1 else np.mean(r)
        r2 = 0 if len(r)<1 else np.min(r)
        test.append(r1)
        test2.append(r2)
        
    result[t] = test
    result[t+'_min'] = test2
        
data = pd.DataFrame(result)

data.to_csv('../result/resultUpdate.csv',index=False)