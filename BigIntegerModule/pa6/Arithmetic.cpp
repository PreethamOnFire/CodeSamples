

#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h"

using namespace std;

int main(int argc, char * argv[]){
  ifstream in;
  ofstream out;

  if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
  }

  in.open(argv[1]);
  if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
  }

  out.open(argv[2]);
  if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
  }

  string line;
  getline(in, line);
  BigInteger A = BigInteger(line);
  getline(in, line);
  getline(in, line); 
  BigInteger B = BigInteger(line);
   
  out << A << endl << endl;
  out << B << endl << endl;
  BigInteger C = A + B;
  out << C << endl << endl;
  BigInteger F = A-B;
  out << F << endl << endl;
  BigInteger G = A-A;
  out << G << endl << endl;
  BigInteger H = (3*A) - (2*B);
  out << H << endl << endl;
  BigInteger I = A*B;
  out << I << endl << endl;
  BigInteger J = A*A;
  out << J << endl << endl;
  BigInteger K = B*B;
  out << K << endl << endl;
  BigInteger L = (9*A*A*A*A) + (16*B*B*B*B*B);
  out << L << endl << endl;

  in.close();
  out.close();
  return 0;
}
