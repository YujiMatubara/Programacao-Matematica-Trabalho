#!/bin/bash

insta="../cases/insta/*"
instb="../cases/instb/*"

cbc(){
    for f in $@
    do
    python3 main.py $f
    TIME=$(time ($(./Main.bin 0 > ../results/cbc/cases/${f//inst/r}) >/dev/null 2>&1) 2>&1)
    echo $TIME >> ../results/cbc/cases/${f//inst/r}
    done
}

gurobi(){
    for f in $@
    do
    python3 main.py $f
    TIME=$(time ($(./Main.bin 1 > ../results/gurobi/cases/${f//inst/r}) >/dev/null 2>&1) 2>&1)
    echo $TIME >> ../results/gurobi/cases/${f//inst/r}
    done
}

hungaro(){
    for f in $@
    do
    python3 main.py $f
    TIME=$(time ($(./Main.bin 2 > ../results/hungaro/cases/${f//inst/r}) >/dev/null 2>&1) 2>&1)
    echo $TIME >> ../results/hungaro/cases/${f//inst/r}
    done
}

#Calling for CBC
CBC(){
cbc $insta;
cbc $instb;
}

GUROBI(){
#Calling for Gurobi
gurobi $insta;
gurobi $instb;
}

#Calling for hungaro

HUNGARO(){
hungaro $insta;
hungaro $insta;
}

CBC;
#GUROBI;
