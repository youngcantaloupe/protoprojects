#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

#include <iostream>
using namespace std;

class LinkedListNode {
    friend class LinkedList;
private:
    int data;
    LinkedListNode *next;
public:
    LinkedListNode(int data = 0) : data(data), next(nullptr) {}
    int GetData() const {return data;}

};

#endif
