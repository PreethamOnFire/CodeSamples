

#include <iostream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"
#include "List.h"
#include <cctype>
#include <cmath>

#define base 1000000000
#define power 9

extern int normalize();

BigInteger::BigInteger(){
  signum = 0;
}

BigInteger::BigInteger(long x){
  if (x > 0){
    signum = 1;
  } else if (x < 0){
    signum = -1;
  } else {
    signum = 0;
  }
  long y = std::abs(x); 
  while(y > 0){
    long i = y % base;
    digits.insertAfter(i);
    y = y / base;
  }
}

BigInteger::BigInteger(std::string s){
  if(s == ""){
    throw std::invalid_argument("BigInteger: Constructor: empty string");
  }
  int count = int(s.length()) - 1;
  int bound = 0;
  if(s[0] == '-'){
    signum = -1;
    bound = 1;
  } else if (s[0] == '+') {
    bound = 1;
    signum = 1;
  } else {
    signum = 1;
  }
  if((count-bound) <= 0){
    throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
  }
  while(count >= bound){
    std::string n = "";
    int p = 0;
    while(p < power && count >= bound){
      if(!std::isdigit(s[count])){
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
      }
      n = s[count] + n;
      count--;
      p++;
    }
    long x = std::stol(n);
    digits.insertAfter(x);
  }
  while((digits.length() > 0) && (digits.peekNext() == 0)){
    digits.eraseAfter();
  }
  if (digits.length() == 0){
    signum = 0;
  }
}

BigInteger::BigInteger(const BigInteger& N){
  signum = N.signum;
  digits = N.digits;
}

int BigInteger::sign() const{
  return signum;
}

int BigInteger::compare(const BigInteger& N) const{
  if(signum < N.signum){
    return -1;
  } else if (signum > N.signum){
    return 1;
  }
  List A = digits;
  List B = N.digits;
  if(N.signum > 0){
    if (A.length() < B.length()){
      return -1;
    } else if (A.length() > B.length()){
      return 1;
    }
    A.moveFront();
    B.moveFront();
    while(B.position() != B.length()){
      long x = A.moveNext();
      long y = B.moveNext();
      if (x < y){
        return -1;
      } else if (x > y){
        return 1;
      }
    }
  } else if (N.signum < 0){
    if (A.length() < B.length()){
      return 1;
    } else if (A.length() > B.length()){
      return -1;
    }
    A.moveFront();
    B.moveFront();
    while(B.position() != B.length()){
      long x = A.moveNext();
      long y = B.moveNext();
      if (x < y){
        return 1;
      } else if (x > y){
        return -1;
      }
    }
  } 
  return 0;
}

void BigInteger::makeZero(){
  signum = 0;
  digits.clear();  
}

void BigInteger::negate(){
  if(signum < 0){
    signum = 1;
  } else if (signum > 0){
    signum = -1;
  }
}

int normalize(List &A){
  if(A.length() == 0){
    return 0;
  }
  int sign = 1;
  A.moveFront();
  if(A.peekNext() < 0){
    while(A.position() != A.length()){
      long x = A.moveNext()*-1;
      A.setBefore(x);
    }
    sign = -1;
  }
  long carry = 0;
  A.moveBack();
  while(A.position() != 0){
    long x = A.peekPrev();
    if (x < 0){
      x += base + carry;
      A.setBefore(x);
      carry=-1;
    } else {
      x += carry;
      carry = 0;
      if (x >= base){
        carry = x/base;
	x = x % base;
      }
      A.setBefore(x);
    }
    A.movePrev();
  }
  if(carry != 0){
    A.insertAfter(carry);
  }
  return sign;
}

BigInteger BigInteger::add(const BigInteger& N) const{
  List A = digits;
  List B = N.digits;
  BigInteger L;
  
  List C;
  A.moveBack();
  B.moveBack();
  while((A.position() != 0) && (B.position() != 0)){
    long x = (signum*A.movePrev()) + (N.signum*B.movePrev());
    C.insertAfter(x);
  }
    
  while(A.position() != 0){
    C.insertAfter((signum*A.movePrev()));
  }
  while(B.position() != 0){
    C.insertAfter((N.signum*B.movePrev()));
  }

  L.signum = normalize(C);
  C.moveFront();
  while((C.length() > 0) && (C.peekNext() == 0)){
    C.eraseAfter();
  }
  if(C.length() == 0){
    L.signum = 0;
  }
  L.digits = C;
  return L;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
  List A = digits;
  List B = N.digits;
  BigInteger L;
  
  List C;
  A.moveBack();
  B.moveBack();
  while((A.position() != 0) && (B.position() != 0)){
    long x = (signum*A.movePrev()) - (N.signum*B.movePrev());
    C.insertAfter(x);
  }
    
  while(A.position() != 0){
    C.insertAfter((signum*A.movePrev()));
  }
    
  while(B.position() != 0){
    C.insertAfter((-1*(N.signum*B.movePrev())));
  }
    
  L.signum = normalize(C);
  C.moveFront();
  while((C.length() > 0) && (C.peekNext() == 0)){
    C.eraseAfter();
  }
  if(C.length() == 0){
    L.signum = 0;
  }
  L.digits = C;
  return L;
}

BigInteger BigInteger::mult(const BigInteger& N) const{
  BigInteger M;
  if ((signum == 0) || (N.signum == 0)){
    return M;
  }
  List A = digits;
  List B = N.digits;
  int count = 0;
  B.moveBack();
  while(B.position() != 0){
    long x = B.movePrev();
    BigInteger L;
    L.signum = 1;
    L.digits = digits;
    L.digits.moveBack();
    while (L.digits.position() != 0){
      long y = L.digits.movePrev();
      y = (y*signum) * (x*N.signum);
      L.digits.setAfter(y);
    }
    L.digits.moveBack();
    for(int i = 0; i < count; i++){
      L.digits.insertBefore(0);
    }
    M += L;
    count++;
  }
  return M;
}

std::string BigInteger::to_string(){
  std::string s = "";
  if(signum < 0){
    s += "-";
  } else if (signum == 0){
    s += "0";
    return s;
  }
  digits.moveFront();
  s += std::to_string(digits.moveNext());
  while (digits.position() < digits.length()){
    std::string n = std::to_string(digits.moveNext());
    int z = power - int(n.length());
    for(int i = 0; i < z; i++){
      n = "0" + n;
    }
    s += n;
  }
  return s;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ){
  return stream << N.to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ){
  int x = A.compare(B);
  return (x == 0);
}

bool operator<( const BigInteger& A, const BigInteger& B ){
  int x = A.compare(B);
  return (x == -1);
}

bool operator<=( const BigInteger& A, const BigInteger& B ){
  int x = A.compare(B);
  return ((x == -1) || (x == 0));
}

bool operator>( const BigInteger& A, const BigInteger& B ){
  int x = A.compare(B);
  return (x == 1);
}

bool operator>=( const BigInteger& A, const BigInteger& B ){
  int x = A.compare(B);
  return ((x == 1) || (x == 0));
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ){
  return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ){
  BigInteger temp = A.add(B);
  std::swap(A.signum, temp.signum);
  std::swap(A.digits, temp.digits);
  return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ){
  return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ){
  BigInteger temp = A.sub(B);
  std::swap(A.signum, temp.signum);
  std::swap(A.digits, temp.digits);
  return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ){
  return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ){
  BigInteger temp = A.mult(B);
  std::swap(A.signum, temp.signum);
  std::swap(A.digits, temp.digits);
  return A;
}










