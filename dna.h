#ifndef _DNA_H_
#define _DNA_H_

#include <string>

using namespace std;

class DNA {
 public:
  DNA();
  DNA(string seq);

  void setSeq(string seq);
  string seq();
  string rc();
  double pair(string seq, double temp);

 private:
  string sequence;
  string reverseComp;
};

#endif
