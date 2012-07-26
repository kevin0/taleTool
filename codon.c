#include "codon.h"
#include <cstddef>
#include <cstdlib>
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

int Codon::getAAIdx(char aa) {
  switch (aa) {
  case 'A': return 0;
  case 'R': return 1;
  case 'N': return 2;
  case 'D': return 3;
  case 'C': return 4;
  case 'E': return 5;
  case 'Q': return 6;
  case 'G': return 7;
  case 'H': return 8;
  case 'I': return 9;
  case 'L': return 10;
  case 'K': return 11;
  case 'M': return 12;
  case 'F': return 13;
  case 'P': return 14;
  case 'S': return 15;
  case 'T': return 16;
  case 'W': return 17;
  case 'Y': return 18;
  case 'V': return 19;
  case '*': return 20;
  default: return -1;
  }
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
  infile.open(file);
  if (!infile.is_open())
    return -1;

  string str = "";
  string aa, codon;
  float count, perthousand, fraction;

  // Read through to the beginning of the frequency table
  while (infile.good() && str.compare(".."))
    infile >> str;
  if (str.compare(".."))
    return -1;

  // Read the frequency table
  infile >> aa;
  infile >> codon;
  infile >> count;
  infile >> perthousand;
  infile >> fraction;
  while (infile.good()) {
    char pushed = 0;
    for (int i=0; i<21; i++) {
      if (!aa.compare(AminoAcids[i])) {
	codonTable[i].push_back(codon);
	frequencyTable[i].push_back(fraction);
	pushed = 1;
      }
    }
    if (!pushed) {
      return -1;
    }
    infile >> aa;
    infile >> codon;
    infile >> count;
    infile >> perthousand;
    infile >> fraction;
  }
  for (int i=0; i<21; i++) {
    float total=0;
    for (int j=0; j<codonTable[i].size(); j++)
      total += frequencyTable[i][j];
    for (int j=0; j<codonTable[i].size(); j++)
      frequencyTable[i][j] /= total;
  }
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


string Codon::generateOligo(string aaSeq) {
  string oligo = "";
  double r=0, freqCount;
  int idx=0;
  char foundCodon;

  for (int i=0; i<aaSeq.size(); i++) {
    idx = getAAIdx(aaSeq[i]);
    if (idx < 0)
      return string("");
    r = drand48();
    freqCount = 0;
    foundCodon = 0;
    for (int j=0; j<frequencyTable[idx].size(); j++) {
      freqCount += frequencyTable[idx][j];
      if (r <= freqCount) {
	oligo.append(codonTable[idx][j]);
	foundCodon = 1;
	break;
      }
    }
    if (!foundCodon) {
      oligo.append(*(codonTable[idx].end()-1));
    }
  }
  return oligo;
}
