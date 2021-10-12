/*
 *  Grupo 6.
 *
 *  Implementacoes realizadas em "C++", usando o ambiente de programacao compartilhado do Visual Studio Code (Visual Studio Live Share).
 *
*/
#include <stdio.h>
#include <coin-or/CbcModel.hpp>
#include <coin-or/OsiClpSolverInterface.hpp>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <string>

using namespace std;


pthread_t thread[2];

void *time_limit(void *time){
    sleep(*(unsigned int*)time);
    printf("\nTIME LIMIT REACHED!\n");
    exit(EXIT_FAILURE);
}

void *cbc(void *model){
    (*((CbcModel*)model)).branchAndBound();
    return NULL;
}


int main(int argc, char *argv[]){

    OsiClpSolverInterface solver;

    solver.readLp("model.lp");

    CbcModel model(solver);

    unsigned int time = 10;

    pthread_create(&(thread[0]), NULL, time_limit, &time);

    pthread_create(&thread[1], NULL, cbc, &model);

    pthread_join(thread[1], NULL);

    int numberColumns = model.solver()->getNumCols();
    const double *solution = model.solver()->getColSolution();

    for (int iColumn = 0; iColumn < numberColumns; iColumn++) {
        double value = solution[iColumn];
        if(value > 0)
            printf("x_%d = %g\n", iColumn, value);
    }
    
    exit(EXIT_SUCCESS);
}
