#include "codon.h"
#include <cstddef>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

const char* Codon::AminoAcids[21] = {
  "Ala","Arg","Asn","Asp",
  "Cys","Glu","Gln","Gly",
  "His","Ile","Leu","Lys",
  "Met","Phe","Pro","Ser",
  "Thr","Trp","Tyr","Val",
  "End"
};

const char* Codon::AminoAcidMono[21] = {
  "A","R","N","D",
  "C","E","Q","G",
  "H","I","L","K",
  "M","F","P","S",
  "T","W","Y","V",
  "*"
};

Codon::Codon() {
    for (int i=0; i<21; i++) {
      frequencyTable[i].empty();
      codonTable[i].empty();
    }
}

Codon::~Codon() {
  for (int i=0; i<21; i++) {
    frequencyTable[i].empty();
    codonTable[i].empty();
  }
}
    
vector<double>* Codon::getFrequencyTable() {
  return frequencyTable;
}
    
vector<double> Codon::getFrequency(int aa) {
  vector<double> v;
  if (aa < 0 || aa >= 21)
    return v;
  return frequencyTable[aa];
}

vector<string>* Codon::getCodonTable() {
  return codonTable;
}

vector<string> Codon::getCodon(int aa) {
  vector<string> v;
  if (aa < 0 || aa >= 21)
    return v;
  return codonTable[aa];
}

int Codon::readCodonFrequencyTable(char* file) {
  ifstream infile;
  cout << "Trying to open " << file << endl;
  infile.open(file);
  if (!infile.is_open())
    return -1;
  cout << "opened!" << endl;

  string str = "";
  string aa, codon;
  float count, perthousand, fraction;

  while (infile.good() && str.compare("..")) {
    infile >> str;
  }
  while (infile.good() && infile.peek()!=infile.eof()) {
    infile >> aa;
    infile >> codon;
    infile >> count;
    infile >> perthousand;
    infile >> fraction;

    char pushed = 0;
    for (int i=0; i<21; i++) {
      if (!aa.compare(AminoAcids[i])) {
	codonTable[i].push_back(codon);
	frequencyTable[i].push_back(fraction);
	pushed = 1;
      }
    }
    if (!pushed) {
      cout << "did not push codon " << aa << ":" << codon << endl;
      return -1;
    }
    cout << "pushed " << codon << endl;

  }
  cout << "done reading" << endl;
  return 0;
}

void Codon::printCodonFrequencyTable() {
  for (int i=0; i<21; i++) {
    cout << AminoAcidMono[i];
    for (int j=0; j<codonTable[i].size(); j++) {
      cout << "\t" << codonTable[i][j] <<"\t" << frequencyTable[i][j] << endl;
    }
  }
};
