sample.pdf: sample_1.dat
	python3 graph.py
sample_1.dat: sample.x
	mpiexec -np 4 ./sample.x 2000 0 1
sample.x: sample.c
	mpic++ sample.c -o sample.x -std=c++11

clean:
	rm *.x
	rm *.dat
	rm *.pdf
