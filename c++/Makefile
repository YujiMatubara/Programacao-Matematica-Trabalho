compiler = g++
flags = -O3 -Wall -lm -lCbc -lOsiClp -lOsi
scriptname = run4All.sh

args = ../cases/toy_problem.txt

all:
	$(compiler) main.cpp -o Main.bin $(flags)

run:
	python3 main.py $(args)

cpp:
	./Main.bin

python:
	python3 main.py

script:
	./run.sh

permissions:
	sudo chmod a+x run.sh

clean:
	rm *.bin