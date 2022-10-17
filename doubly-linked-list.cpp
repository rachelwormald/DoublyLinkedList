#include "doubly-linked-list.h"
#include <iostream>

// implementing the node structure for the doubly linked list
// setting value equal to the given data value
// next and prev are null since there is no defined list
DoublyLinkedList::Node::Node(DataType data) {
    value = data;
    next = nullptr;
    prev = nullptr;
}

// Create a new empty DoublyLinkedList.
// size starts as 0 and head and tail as null since there is no list defined
DoublyLinkedList::DoublyLinkedList() {
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
}

// Destroy this DoublyLinkedList, freeing all dynamically allocated memory.
// creating a node that starts at the head of the list
// using while loop until the node is null meaning it's reached the end of the list
// creating a temp node to store the value of node next before it's deleted
// making node equal to temp to continue iterations
DoublyLinkedList::~DoublyLinkedList() {
    Node* node = head_;
    while (node != nullptr) {

        Node *temp = node->next;
        delete node;
        node = temp;
    }
}

// Returns the number of elements in the list.
// size represents the number of elements
unsigned int DoublyLinkedList::size() const {
    return size_;
}

// Returns the maximum number of elements the list can hold.
// returning pre-determined fixed capacity of list
unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}

// Returns true if the list is empty, false otherwise.
// list is empty if the size is 0 meaning there are no elements
// if this isn't the case, the function will return false
bool DoublyLinkedList::empty() const {
    if (size_ == 0) {

        return true;
    }

    return false;
}

// Returns true if the list is at capacity, false otherwise.
// the size is the elements in the list so if that equals the maximum number of elements that can be in the list it must be full
bool DoublyLinkedList::full() const {
    if (size_ == CAPACITY) {
        return true;
    }
    return false;
}

// Returns the value at the given index in the list. If index is invalid,
// return the value of the last element.
DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    // checks if the index is outside the range of indexes in the list - return the value the tail is pointing to which will be the value of the last element
    if (index >= size_) {
        return tail_->value;
    }
// iterating through list, starting at the head - creating a node to start here
    Node *tempNode = head_;
// using for loop to iterate the tempnode through the list stopping when i has reached the element before the index
// since the tempnode will equal tempnode next, it's value will be what's stored at the given index, so the tempnode value can be returned
    for (int i = 0; i != index; i++) {
        tempNode = tempNode->next;
    }
    return tempNode->value;
}

// Searches for the given value, and returns the index of this value if found.
// returns the size of the list otherwise.
// creating a tempnode again to iterate through list, creating a counter i as well
unsigned int DoublyLinkedList::search(DataType value) const {

    Node *tempNode = head_;
    int i = 0;

// while loop to run until the tempnode is null meaning it's iterated through the entire list
// if the value of the tempnode matches the value inputed to the function, return the counter which will increase by one for each index it iterates over
// size is returned if this function doesn't find a match
    while (tempNode != nullptr) {
        if (tempNode->value == value) {
            return i;
        }
        tempNode = tempNode->next;
        i++;

    }
    return size_;
}

// Prints all elements in the list to the standard output.
// tempnode created to iterate through list
void DoublyLinkedList::print() const {

    Node *tempNode = head_;
// while loop to run until the tempnode is null meaning it's iterated through the entire list
// for each iteration the function will output the value of each element, and tempnode is moved to the next element of the list
    while (tempNode != nullptr)
    {
        std::cout << tempNode->value << "\t";
        tempNode = tempNode->next;
    }

    std::cout << "\n";
}
// Private method to get the node at an index. This is optional, but you
// will probably find it useful
// edge case for invalid index
DoublyLinkedList::Node *DoublyLinkedList::getNode(unsigned int index) const {

    if( index >= size_)
    {
        return nullptr;
    }
// creating tempnode to iterate through list, starting at the head
    Node *tempNode = head_;
// going through list one by one and returning the node once it's reached the given index
    for (int i = 0; i != index; i++) {
        tempNode = tempNode->next;
    }
    return tempNode;
}


// Inserts a value into the list at a given index.

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{

    //can't have gaps in list therefore return false if given index is greater than size meaning it's at least 2 indexes past the last index
    // increasing size for each if statement since an element has been inserted so size has to increase
    if (index > size_)
    {
        return false;
    }

    // creating the node to be inserted with the inputed value
    Node* newNode = new Node(value);

    // for inserting into an empty list
    // just have to make both the head and the tail equal to the new node
    if (size_ == 0)
    {
        head_ = newNode;
        tail_ = newNode;
        size_++;
        return true;
    }

    // for when it's being inserted somewhere in the middle of the list
    // creating tempnode which is the node currently at the index the newnode has to be inserted at
    // since the tempnode will be moved up in the list it's prev needs to point to the new node which will take it's place
    // the inserted new node needs to point at the tempnode it's taking the place of
    if (index != size_) {
        Node* tempNode = getNode(index);
        tempNode->prev = newNode;
        newNode->next = tempNode;
    }

    //for when it's being inserted at the front of the list
    // additional from previous if statement to re-set the head to the new node if it's inserted at the beginning
    if (index == 0)
    {
        head_ = newNode;
        size_++;
        return true;
    }

    // for when it's being inserted onto the end - no nodes have to shift to different indexes
    // special case where tail has to be re-directed
    if (index == size_)
    {
        tail_ = newNode;
    }
    // defining the node preceding the new node and relocating it's next value to point at new node
    // setting previous of new node to previous to maintain links
    Node* prevNode = getNode(index-1);
    prevNode->next = newNode;
    newNode->prev = prevNode;
    size_++;
    return true;

}

// Inserts a value at the beginning of the list.
// calling insert function with index zero to insert at front
bool DoublyLinkedList::insert_front(DataType value) {
    return insert(value, 0);
}

// Inserts a value at the end of the list.
// calling insert function with index of size since that will be one more than the index so it will be inserted onto the end
bool DoublyLinkedList::insert_back(DataType value) {
    return insert(value, size_);
}

// Deletes a value from the list at the given index.
// will decrease size before returning since an element is being removed
// calling getnode with given index to locate the node we're trying to remove
bool DoublyLinkedList::remove(unsigned int index) {

    // case for when index is beyond the size of the list - will also cover if list is empty
    if (index >= size_)
    {
        return false;
    }
    //for removing from one element list
    // the list will be empty so head and tail are null
    if (size_ == 1)
    {
        delete getNode(index);
        head_ = nullptr;
        tail_ = nullptr;
        size_--;
        return true;
    }

    //case for when removing last node
    // defining previous node as the one before the given index
    // setting tail to previous node since the node it's pointing to is gone
    // prev node will now be last and so it's next will be null
    if (index == size_-1)
    {
        delete getNode(index);
        Node* prevNode = getNode(index-1);
        tail_ = prevNode;
        prevNode->next = nullptr;
        size_--;
        return true;
    }
    // defining the node after the node being removed
    Node* nextNode = getNode(index+1);
    // case for removing first node
    // since first element is being removed head was to re-assigned to the next node
    // the next node will no longer have a prev pointing to a node so it's going to be null
    if (index == 0)
    {
        delete getNode(index);
        head_ = nextNode;
        nextNode->prev = nullptr;
        size_--;
        return true;
    }
    // case for removing node in the middle
    // defining previous node again & next node is still in scope
    // re-assigning previous and next nodes
    else
    {
        delete getNode(index);
        Node* prevNode = getNode(index-1);
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        size_--;
        return true;
    }

}

// Deletes a value from the beginning of the list.
// calls remove function with index set as zero (front)
bool DoublyLinkedList::remove_front() {
    return remove(0);
}

// Deletes a value at the end of the list.
// calls remove function and sets index as the size -1 since the last index is one less than the size
bool DoublyLinkedList::remove_back() {
    return remove(size_-1);
}

// Replaces the value at the given index with the given value.
bool DoublyLinkedList::replace(unsigned int index, DataType value) {

    // case for when index is past index of the list
    // cannot run
    if (index >= size_)
    {
        return false;
    }
// node that's having its value replaced defined and set at the index given
// setting the value of that node to the given value
    Node* replaceNode = getNode(index);
    replaceNode->value = value;
    return true;

}

