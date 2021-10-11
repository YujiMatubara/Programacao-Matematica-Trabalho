/*
 *  Grupo 6.
 *
 *  Implementacoes realizadas em "C++", usando o ambiente de programacao compartilhado do Visual Studio Code (Visual Studio Live Share).
 *
*/

#include <iostream>
#include <unistd.h>
#include <cassert>
#include <stdio.h>

//#include "gurobi_c++.h"

#include <coin-or/CbcModel.hpp>
#include "coin-or/OsiClpSolverInterface.hpp"

using namespace std;

int main(int argc, char *argv[]){
    OsiClpSolverInterface solver;

    int numMpsReadErrors = solver.readMps("model.mps");

    CbcModel model(solver);

    model.branchAndBound();
    int numberColumns = model.solver()->getNumCols();

    const double *solution = model.solver()->getColSolution();

    for (int iColumn = 0; iColumn < numberColumns; iColumn++) {
        double value = solution[iColumn];
        if (fabs(value) > 1.0e-7 && model.solver()->isContinuous(iColumn)){
            printf("x_%d has value %g\n", iColumn, value);
        }
    }

    return 0;
}


/*



*/