#pragma once
#include "Arduino.h"
#include "Common.h"


// FIFO list
template<class DATA> class Queue {

private:
  int front = 0;  //buffer[front] not contain data, front is next empty index
  int back = 0;   //buffer[back] contain data
  DATA* buffer = NULL;

public:
  int size = 0;
  int capacity = 0;
  

  Queue(int capacity) {
    this->capacity = capacity;
    buffer = (DATA*)malloc(capacity * sizeof(DATA));
  }

  ~Queue()
  {
    free(buffer);
  }

  // Add an element to the buffer
  bool push(DATA val) {
    if (full()) return false;
    
    buffer[front] = val;
    front = (front + 1) % capacity;
    size++;
    return true;
  }

  // Remove an element from the buffer
  DATA pop() {
    if (empty()) return 0;
    DATA val = buffer[back];
    back = (back + 1) % capacity;
    size--;
    return val;
  }

  bool empty() const {
    return size == 0;
  }

  bool full() const {
    return size == capacity;
  }

};
