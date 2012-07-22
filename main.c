#include <iostream>
#include "codon.h"

using namespace std;

// yeast codon table from http://downloads.yeastgenome.org/unpublished_data/codon/ysc.orf.cod
//void generateRandomTALE(char* aa, char codonTable, double* freqTable const char* dna, int len

int main(int argc, char* argv[]) {
    if (argc < 2)
        return -1;
    
    Codon c;
    cout << c.readCodonFrequencyTable(argv[1]) << endl;
    c.printCodonFrequencyTable();
    return 0;
}