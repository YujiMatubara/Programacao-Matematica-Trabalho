#!/bin/bash

insta="../cases/insta/*"
instb="../cases/instb/*"

run_for_all(){
    for f in $@
    do
    python3 main.py $f
    TIME=$(time ($(./Main.bin > ../results/cbc/cases/${f//inst/r}) >/dev/null 2>&1) 2>&1)
    echo $TIME >> ../results/cbc/cases/${f//inst/r}
    done
}

run_for_all $insta;
run_for_all $instb;
