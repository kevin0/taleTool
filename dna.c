#include "dna.h"

DNA::DNA() {
  sequence = "";
  reverseComp = "";
}

DNA::DNA(string seq) {
  setSeq(seq);
}

void DNA::setSeq(string seq) {
  sequence = seq;
  reverseComp = "";
  for (int i=sequence.size()-1; i>=0; i--) {
    switch(sequence[i]) {
    case 'A':
    case 'a': reverseComp.push_back('T'); break;
    case 'T':
    case 't': reverseComp.push_back('A'); break;
    case 'G':
    case 'g': reverseComp.push_back('C'); break;
    case 'C':
    case 'c': reverseComp.push_back('G'); break;
    }
  }
}

string DNA::seq() {
  return sequence;
}

string DNA::rc() {
  return reverseComp;
};

double pair(string seq, double temp) {
  return 0;
}
