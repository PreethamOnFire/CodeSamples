

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

//Private constructor
List::Node::Node(ListElement x){
  data = x;
  next = nullptr;
  prev = nullptr;
}

//Class Contructor and Destructors

List::List(){
  frontDummy = nullptr;
  backDummy = nullptr;
  beforeCursor = nullptr;
  afterCursor = nullptr;
  pos_cursor = 0;
  num_elements = 0;
}

List::List(const List& L){
  frontDummy = nullptr;
  backDummy = nullptr;
  num_elements = 0;
  beforeCursor = nullptr;
  afterCursor = nullptr;
  pos_cursor = 0;
  Node* N = L.frontDummy;
  while( N != nullptr){
    this->insertBefore(N->data);
    N = N->next;
  }
}

List::~List(){
  this->moveFront();
  while(num_elements > 0){
    this->eraseAfter();
  }
}

//Access functions
int List::length() const{
  return num_elements;
}

ListElement List::front() const{
  if (num_elements <= 0){
    throw std::length_error("List: front(): empty List");
  }
  return(frontDummy->data);
}

ListElement List::back() const{
  if (num_elements <= 0){
    throw std::length_error("List: back(): empty List");
  }
  return(backDummy->data);
}

int List::position() const{
  if(pos_cursor < 0 || pos_cursor > num_elements){
    throw std::range_error("List: position(): out of bounds of List");
  }
  return pos_cursor;
}

ListElement List::peekNext() const{
  if(pos_cursor >= num_elements){
    throw std::range_error("List: peekNext(): cursor at back");
  }
  return (afterCursor->data);
}

ListElement List::peekPrev() const{
  if(pos_cursor <= 0){
    throw std::range_error("List: peekPrev(): cursor at front");
  }
  return (beforeCursor->data);
}

//Manipulation Procedures
void List::clear(){
  this->moveFront();
  while(num_elements > 0){
    this->eraseAfter();
  }
}

void List::moveFront(){
  pos_cursor = 0;
  beforeCursor = nullptr;
  afterCursor = frontDummy;
}

void List::moveBack(){
  pos_cursor = num_elements;
  beforeCursor = backDummy;
  afterCursor = nullptr;
}

ListElement List::moveNext(){
  if(pos_cursor >= num_elements){
    throw std::range_error("List: moveNext(): cursor at back");
  }
  beforeCursor = afterCursor;
  ListElement temp = afterCursor->data;
  afterCursor = afterCursor->next;
  pos_cursor++;
  return temp;
}

ListElement List::movePrev(){
  if(pos_cursor <= 0){
    throw std::range_error("List: movePrev(): cursor at front");
  }
  afterCursor = beforeCursor;
  ListElement temp = beforeCursor->data;
  beforeCursor = beforeCursor->prev;
  pos_cursor--;
  return temp;
}

void List::insertAfter(ListElement x){
  Node *N = new Node(x);
  
  N->next = afterCursor;
  N->prev = beforeCursor;
  if(num_elements == 0){
    frontDummy = backDummy = N;
    afterCursor = N;
  } else {
    if(pos_cursor == 0){
      afterCursor->prev = N;
      frontDummy = N;
    } else if (pos_cursor == num_elements){
      beforeCursor->next = N;
      backDummy = N;
    } else {
      beforeCursor->next = N;
      afterCursor->prev = N;
    }
    afterCursor = N;
  }
  num_elements++; 
}

void List::insertBefore(ListElement x){
  Node *N = new Node(x);

  N->next = afterCursor;
  N->prev = beforeCursor;
  if(num_elements == 0){
    frontDummy = backDummy = N;
    beforeCursor = N;
  } else {
    if(pos_cursor == 0){
      afterCursor->prev = N;
      frontDummy = N;
    } else if (pos_cursor == num_elements){
      beforeCursor->next = N;
      backDummy = N;
    } else {
      beforeCursor->next = N;
      afterCursor->prev = N;
    }
    beforeCursor = N;
  }
  pos_cursor++;
  num_elements++;
}

void List::setAfter(ListElement x){
  if(pos_cursor >= num_elements){
    throw std::range_error("List: setAfter(): cursor at back");
  }
  afterCursor->data = x;
}

void List::setBefore(ListElement x){
  if(pos_cursor <= 0){
    throw std::range_error("List: setBefore(): cursor at front");
  }
  beforeCursor->data = x;
}

void List::eraseAfter(){
  if(pos_cursor >= num_elements){
    throw std::range_error("List: eraseAfter(): cursor at back");
  }
  Node* N = afterCursor;
  if (num_elements == 1){
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
  } else {
    if (pos_cursor == 0){
      Node* P = N->next;
      P->prev = beforeCursor;
      frontDummy = P;
    } else if (pos_cursor == (num_elements-1)){
      beforeCursor->next = nullptr;
      backDummy = beforeCursor;
    } else {
      Node* P = N->next;
      P->prev = beforeCursor;
      beforeCursor->next = P;
    }
    afterCursor = N->next;
  }
  num_elements--;
  delete N;
}

void List::eraseBefore(){
  if(pos_cursor <= 0){
    throw std::range_error("List: eraseBefore(): cursor at front");
  }
  Node* N = beforeCursor;
  if (num_elements == 1){
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
  } else {
    if (pos_cursor == 1){
      Node* P = N->next;
      P->prev = nullptr;
      frontDummy = P;
    } else if (pos_cursor == (num_elements)){
      Node* P = N->prev;
      P->next = nullptr;
      backDummy = P;
    } else {
      Node* P = N->prev;
      P->next = afterCursor;
      afterCursor->prev = P;
    }
    beforeCursor = N->prev;
  }
  num_elements--;
  pos_cursor--;
  delete N;
}

// Other functions
int List::findNext(ListElement x){
  if(num_elements > 0){
    while(pos_cursor < num_elements){
      if(x == this->moveNext()){
        return pos_cursor;
      }
    }
  }
  return -1;
}

int List::findPrev(ListElement x){
  if(num_elements > 0){
    while(pos_cursor > 0){
      if(x == this->movePrev()){
        return pos_cursor;
      }
    }
  }
  return -1;
}

void List::cleanup(){
  int pos = pos_cursor;
  int count = 0;
  while(count < num_elements-1){
    this->moveFront();
    for(int i = 0; i < count; i++){
      this->moveNext();
    }
    ListElement x = this->peekNext();
    this->moveNext();
    while(pos_cursor < num_elements){
      if(this->moveNext() == x){
	if(pos_cursor <= pos){
          pos--;
	}
	this->eraseBefore();
      }
    }
    count++;
  }

  this->moveFront();
  for(int i = 0; i < pos; i++){
    this->moveNext();
  }
}


List List::concat(const List& L) const{
  List R = *this;
  Node* N = L.frontDummy;
  R.moveBack();
  while(N != nullptr){
    R.insertBefore(N->data);
    N = N->next;
  }
  R.moveFront();
  return R;
}

std::string List::to_string() const{
  Node *N = nullptr;
  if(num_elements == 0){
    std::string l = "()";
    return l;
  }
  std::string s = "(";

  for(N=frontDummy; N->next != nullptr; N=N->next){
    s += std::to_string(N->data)+", ";
  }
  s += std::to_string(N->data)+") ";

  return s;
}

bool List::equals(const List& R) const{
  if (this->num_elements != R.num_elements){
    return false;
  }
  Node* N = this->frontDummy;
  Node* M = R.frontDummy;
  while(N!=nullptr){
    if(N->data != M->data){
      return false;
    }
    N = N->next;
    M = M->next;
  }
  return true;
}

// Overloaded Operators
std::ostream& operator<<(std::ostream& stream, const List& L) {
  return stream << L.to_string();
}

bool operator==(const List& A, const List& B){
  return A.equals(B);
}

List& List::operator=( const List& L){
  if(this != &L){
    List temp = L;

    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(num_elements, temp.num_elements);
    std::swap(pos_cursor, temp.pos_cursor);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
  }

  return *this;
}







