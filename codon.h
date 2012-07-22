#ifndef _CODON_H_
#define _CODON_H_

#include <string>
#include <vector>

using namespace std;

class Codon {
 public:
  Codon();
  ~Codon();
        static const int 
            A=0, R=1, N=2, D=3,
            C=4, E=5, Q=6, G=7,
            H=8, I=9, L=10, K=11,
            M=12, F=13, P=14, S=15,
            T=16, W=17, Y=18, V=19,
            STOP=20;

	static const char* AminoAcids[21];
	static const char* AminoAcidMono[21];
    
        vector<double> getFrequency(int aa);
        vector<double>* getFrequencyTable();
	vector<string> getCodon(int aa);
	vector<string>* getCodonTable();

	int readCodonFrequencyTable(char* file);
	void printCodonFrequencyTable();	
    
    private:
        vector<double> frequencyTable[21];
	vector<string> codonTable[21];
};

#endif
