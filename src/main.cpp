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
#include "gurobi_c++.h"
#include "Hungarian.h"


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

void *gurobi(void *model){
    return NULL;
}

void *hungaro(void *model){
    return NULL;
}

int main(int argc, char *argv[]){

    //CBC
    if(atoi(argv[1]) == 0){
        OsiClpSolverInterface solver;

        solver.readLp("model.lp");

        CbcModel model(solver);

        unsigned int time = 80;

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

    //GUROBI
    else if(atoi(argv[1]) == 1){
        unsigned int time = 80;

        try {
            GRBEnv env = GRBEnv();
            GRBModel model = GRBModel(env, "./model.lp");

            model.optimize();

            int optimstatus = model.get(GRB_IntAttr_Status);

            if (optimstatus == GRB_INF_OR_UNBD) {
            model.set(GRB_IntParam_Presolve, 0);
            model.optimize();
            optimstatus = model.get(GRB_IntAttr_Status);
            }
            
        } catch(GRBException e) {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
        } catch (...) {
            cout << "Error during optimization" << endl;
        }


        pthread_create(&(thread[0]), NULL, time_limit, &time);
        pthread_create(&thread[1], NULL, gurobi, NULL);

        pthread_join(thread[1], NULL);

        exit(EXIT_SUCCESS);

    }

    //HUNGARO
    else if(atoi(argv[1]) == 2){


        vector<vector<double>> c;
        //FAZER A LEITURA AQUI//
        //LER DOS ARQUIVOS TXT E GUARDAR EM VECTOR<VECTOR<double>> QUE EH O C ALI EMBAIXO

        unsigned int time = 80;
        double custo;
        
        vector<int> A;
        HungarianAlgorithm model;

        custo  = model.Solve(c, A);

        for (unsigned int i = 0; i < c.size(); i++){
            printf("x_%d = %d",A[i]);
        }

        printf("Cost: %lf",custo);

        pthread_create(&(thread[0]), NULL, time_limit, &time);
        pthread_create(&thread[1], NULL, hungaro, NULL);

        pthread_join(thread[1], NULL);

        exit(EXIT_SUCCESS);

    }

    else{
        exit(EXIT_FAILURE);
    }

}
