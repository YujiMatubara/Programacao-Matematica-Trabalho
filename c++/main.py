#from pulp import *

import mip as mp 
import pandas as pd
import numpy as np
import sys



#Importing data
path = sys.argv[1] #Define path for input file
data = pd.read_csv(path, sep = " ", header = None) #Matrix with data
data.drop(data.columns[data.shape[1] - 1], axis = 1, inplace = True) #Cleaning the last column
data = data.to_numpy() #Transforming to numpy matrix

#lp = LpProblem("model", LpMaximize)
#x = LpVariable.matrix("x", data, cat="Binary")


#############MODELAGEM############

#Objective function
for i in range(0,int(np.sqrt(data.size))):
    for j in range(0,int(np.sqrt(data.size))):
        lp += lpSum(data[i][j] * x.index(i,j))


aux = 0
#Constraints
for i in range(0,int(np.sqrt(data.size))):
    for j in range(0,int(np.sqrt(data.size))):
        aux += lpSum(x.index(i,j)) == 1
    lp += aux
    aux = 0

for i in range(0,int(np.sqrt(data.size))):
    for j in range(0,int(np.sqrt(data.size))):
        aux += lpSum(x.index(j,i)) == 1
    lp += aux
    aux = 0

##################################

lp.solve()

for i in range(0,int(np.sqrt(data.size))):
    for j in range(0,int(np.sqrt(data.size))):
        print(x.index(i,j))

lp.writeMPS("model.mps")
#os.system("make cpp")