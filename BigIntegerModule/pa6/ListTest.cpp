
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

using namespace std;

int main(){
  List L;
  for(int i = 0; i < 20; i++){
    L.insertBefore(i);
  }
  cout << "L = " << L << endl;
  cout << "Elements " << L.length() << endl;
  cout << "Front " << L.front() << endl;
  cout << "Back " << L.back() << endl;

  List R = L;
  bool iseq = R==L;
  cout << iseq << endl;

  L.moveFront();
  cout << "peekFront " << L.peekNext() << endl;
  cout << "Position of 8 " << L.findNext(8) << endl;
  cout << "Position of 9 " << L.findPrev(9) << endl;
  L.moveFront();
  for(int i = 0; i < 10; i++){
    L.moveNext();
  }
  cout << "peekFront " << L.peekNext() << endl;
  L.eraseAfter();
  cout << "L = " << L << endl;
  L.eraseBefore();
  cout << "L = " << L << endl;
  cout << "Position of cursor after delete " << L.position() << endl;
  cout << "peekFront " << L.peekNext() << endl;
  cout << "peekPrev " << L.peekPrev() << endl;

  cout << "R = " << R << endl;

  R.moveFront();
  for(int i = 0; i < 4; i++){
    R.moveNext();
  }
  R.setAfter(13);
  R.setBefore(13);
  cout << "R = " << R << endl;
  iseq = R==L;
  cout << iseq << endl;

  List D = L.concat(R);
  
  cout << "D = " << D << endl;
  
  D.clear();
  cout << "D after clear = " << D << endl;
  
  List E;
  E.insertBefore(1);
  E.insertBefore(3);
  E.insertBefore(2);
  E.insertBefore(4);
  E.insertBefore(2);
  E.insertBefore(6);
  E.insertBefore(4);
  E.insertBefore(7);
  for (int i = 0; i < 3; i++){
    E.movePrev();
  }
  cout << "E = " << E << endl;
  E.cleanup();
  cout << "E = " << E << endl;
  cout << "Position of cursor " << E.position() << endl;
  cout << "peekFront " << E.peekNext() << endl;
  cout << "peekPrev " << E.peekPrev() << endl;
  return 0;
}

