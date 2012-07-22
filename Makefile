all: codon
	g++ -O3 main.c codon.o -o taleTool

codon:
	g++ -O3 -c codon.c

clean:
	rm *.o
