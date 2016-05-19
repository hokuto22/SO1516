binaries = testeArv

teste-arvore:
	gcc -Wall testeArv.c -o testeArv

users-gen:
	gcc logGen.c -o logGen && ./logGen

dummy-gen:
	gcc dummy.c -o dummy && mkdir Dummy && ./dummy

clean-all:
	rm -f *.log $(binaries) *.o
