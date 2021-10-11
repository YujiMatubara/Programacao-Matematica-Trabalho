compiler = g++
flags = -Ofast -march=native -Wall -lm -lCbc -lOsiClp -lOsi
scriptname = run4All.sh

args = ../cases/insta/inst_1_1000.txt

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