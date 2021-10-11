#!/bin/bash

insta="../cases/insta/*"
instb="../cases/instb/*"

run_for_all(){
    for f in $@
    do
    make run args=$f
    done
}

run_for_all $insta;
run_for_all $instb;
