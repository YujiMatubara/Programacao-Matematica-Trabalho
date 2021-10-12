import os
from mip import Model, BINARY, MAXIMIZE, solver, xsum, CBC, maximize
import pandas as pd
import numpy as np
import sys


#Importing data
path = sys.argv[1] #Define path for input file
c = pd.read_csv(path, sep = " ", header = None) #Matrix with data
c.drop(c.columns[c.shape[1] - 1], axis = 1, inplace = True) #Cleaning the last column
c = c.to_numpy() #Transforming to numpy matrix


#Inst model
m = Model(sense=MAXIMIZE, solver_name=CBC)

n = len(c) #Finding matrix n
N = set(range(n)) # Define 

#Define x type and interval N²
x = [{j: m.add_var(var_type=BINARY) for j in N} for i in N]

#Σ Σ c_ij * x_ij (Funcao objetivo)
m.objective = xsum(xsum(c[i][j] * x[i][j] for i in N) for j in N)

#Σ x_ij == 1 (Restricoes)
for i in N:
    m += xsum(x[i][j] for j in N) == 1

for j in N:
    m += xsum(x[i][j] for i in N) == 1

m.optimize(max_seconds=10)

#m.write('model.lp')
#os.system("make cpp")