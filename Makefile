binaries = testeArv

teste-arvore:
	gcc -Wall testeArv.c -o testeArv

clean-all:
	rm -f *.log $(binaries) *.o
