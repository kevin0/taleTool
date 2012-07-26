#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include "codon.h"
#include "dna.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3)
        return -1;
    
    // Read the codon frequency table
    Codon c;
    if (c.readCodonFrequencyTable(argv[1]) < 0)
        return -1;    
    //c.printCodonFrequencyTable();
    
    // Read the amino acid sequence file
    vector<string> aaSeq;
    string tmp;
    ifstream infile;
    infile.open(argv[2]);
    aaSeq.empty();
    
    infile >> tmp;
    while (infile.good()) {
        aaSeq.push_back(tmp);
        infile >> tmp;
    }
    
    // for each aaSeq, generate a random oligo sampled from the codon frequency table
    // make sure the oligo does not fold on itself
    vector<DNA> dna;
    DNA d;
    srand48(time(NULL));
    for (int i=0; i<aaSeq.size(); i++) {
        d.setSeq(c.generateOligo(aaSeq[i]));
        dna.push_back(d);
        //cout << c.generateOligo(aaSeq[i]) << endl;
    }
    //for (int i=0; i<dna.size(); i++)
    //    cout << i << endl << dna[i].seq() << endl << dna[i].rc() << endl;
    
    return 0;
}