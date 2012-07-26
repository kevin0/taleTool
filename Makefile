all: codon dna
	g++ -O3 main.c codon.o dna.o -o taleTool

codon:
	g++ -O3 -c codon.c

dna:
	g++ -O3 -c dna.c

clean:
	rm *.o
