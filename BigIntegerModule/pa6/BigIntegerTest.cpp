
#include <iostream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"

using namespace std;

int main(){
 string s1 = "100";
 string s2 = "-99";
 long x = 20382934;
 long y = -12;
 string s3 = "-12";
 BigInteger A = BigInteger(s1);
 BigInteger B = BigInteger(s2);
 BigInteger C = BigInteger(x);
 BigInteger D = BigInteger(y);
 BigInteger E = BigInteger(s3);
 cout << A << endl;
 cout << B << endl;
 cout << C << endl;
 cout << D << endl;
 cout << A.compare(B) << endl;
 cout << B.compare(A) << endl;
 cout << C.compare(D) << endl;
 cout << D.compare(E) << endl;

 BigInteger L = A.add(B);
 BigInteger P = D.add(E);
 BigInteger T = D.sub(E);
 BigInteger Z = D.mult(E);
 BigInteger I = A.mult(B);
 cout << L << endl;
 cout << P << endl;
 cout << T << endl;
 cout << Z << endl;
 cout << I << endl;

 C.negate();
 cout << C << endl;
 cout << C.sign() << endl;
 C.makeZero();
 cout << C << endl;
 cout << C.sign() << endl;
 return 0;
}


