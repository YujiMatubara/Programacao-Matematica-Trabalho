compiler = g++
flags = -O3 -march=native -Wall -lm -lCbc -lOsiClp -lOsi -lpthread -lgurobi_c++ -lgurobi91
scriptname = run4All.sh
GUROBI_HOME="/home/tomieiro/gurobi"


all:
	$(compiler) main.cpp Hungarian.cpp -o Main.bin $(flags)

run:
	python3 main.py $(args)

cpp:
	./Main.bin 0

python:
	python3 main.py

script: all
	./run.sh

permissions:
	sudo chmod a+x run.sh Main.bin

clean:
	rm *.bin |\
	rm ../results/cbc/cases/ra/* |\
	rm ../results/cbc/cases/rb/* |\
	rm ../results/gurobi/cases/ra/* |\
	rm ../results/gurobi/cases/rb/* |\
	rm ../results/hungaro/cases/ra/* |\
	rm ../results/hungaro/cases/rb/*

lib:
	git clone https://github.com/mcximing/hungarian-algorithm-cpp.git