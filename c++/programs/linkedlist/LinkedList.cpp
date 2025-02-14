#include <iostream>
#include "LinkedListNode.h"
using namespace std;

class LinkedList {
public: 
    LinkedList() : head(nullptr) {}
    ~LinkedList();
    void Prepend (int data);
    void Print() const;
private:
    LinkedListNode *head;
};

LinkedList::~LinkedList() {
    //delete head; // this will only delete first space
    LinkedListNode *curr = head;
    while (curr != nullptr) {
        head = curr->next;
        delete curr;
        curr = head;
    }
}

void LinkedList::Prepend(int data) {
    LinkedListNode *node = new LinkedListNode(data);
    // head = node;
    node->next = head;
    head = node;
}

void LinkedList::Print() const {
    LinkedListNode *curr = head;
    if (head == nullptr) {
        cout << "empty list" << endl;
    } else {
        for (; curr != nullptr; curr = curr->next)
        cout << curr->data << " "; 
    }
    cout << endl;
}

int main() {
    LinkedList list;

    list.Prepend(1);
    list.Prepend(2);
    list.Prepend(3);
    list.Prepend(4);

    list.Print(); 

    return 0;
}
