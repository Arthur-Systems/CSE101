/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA6
* List.c
* Contains the function definitions for the List ADT
***/




#include "List.h"

// Node constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);

    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}


List::List(const List &L) : List() {
    for (Node* node = L.frontDummy->next; node != L.backDummy; node = node->next) {
        insertBefore(node->data);
    }
    moveFront();
    for (int i = 0; i < L.position(); ++i) {
        moveNext();
    }
}


List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------
int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if (num_elements == 0) {
        throw std::length_error("List: front(): empty list");
    }
    return frontDummy->next->data;
};

ListElement List::back() const {
    if (num_elements == 0) {
        throw std::length_error("List: back(): empty list");
    }
    return backDummy->prev->data;
}

int List::position() const {
    return pos_cursor;
}


ListElement List::peekNext() const {
    if (afterCursor == backDummy) {
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}


ListElement List::peekPrev() const {
    if (beforeCursor == frontDummy) {
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------


void List::clear() {
    Node *temp = frontDummy->next;
    while (temp != backDummy) {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

void List::moveFront() {
    if (num_elements > 0) {
        afterCursor = frontDummy->next;
        beforeCursor = frontDummy;
        pos_cursor = 0;
    }
    else{
        afterCursor = backDummy;
        beforeCursor = frontDummy;
        pos_cursor = 0;
    }
}

void List::moveBack() {
    if (num_elements > 0) {
        beforeCursor = backDummy->prev;
        afterCursor = backDummy;
        pos_cursor = num_elements;
    }
}

ListElement List::moveNext() {
    if (pos_cursor < num_elements) {
        beforeCursor = afterCursor;
        afterCursor = afterCursor->next;
        pos_cursor++;
        return beforeCursor->data;
    } else {
        throw std::range_error("List: moveNext(): cursor at back");
    }
}


ListElement List::movePrev() {
    if (pos_cursor > 0) {
        afterCursor = beforeCursor;
        beforeCursor = beforeCursor->prev;
        pos_cursor--;
        return afterCursor->data;
    } else {
        throw std::range_error("List: movePrev(): cursor at front");
    }
}


void List::insertAfter(ListElement x) {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements++;
    pos_cursor++;
}

void List::setAfter(ListElement x) {
    if (num_elements == 0) {
        throw std::length_error("setAfter() called on empty List");
    }
    if (pos_cursor == num_elements) {
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    if (num_elements == 0) {
        throw std::length_error("setBefore() called on empty List");
    }
    if (pos_cursor == 0) {
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}



void List::eraseAfter() {
    if (num_elements == 0) {
        throw std::length_error("List Error: eraseAfter() called on empty List");
    }
    if (pos_cursor == num_elements) {
        throw std::range_error("List: eraseAfter(): cursor at back");
    }

    Node* toErase = afterCursor;
    toErase->next->prev = beforeCursor;
    beforeCursor->next = toErase->next;
    afterCursor = toErase->next;
    delete toErase;
    num_elements--;
    // pos_cursor does not change since we're deleting after the cursor
}



void List::eraseBefore() {
    if (num_elements == 0) {
        throw std::length_error("List Error: eraseBefore() called on empty List");
    }
    if (pos_cursor == 0) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }

    Node* toErase = beforeCursor;
    toErase->prev->next = afterCursor;
    afterCursor->prev = toErase->prev;
    beforeCursor = toErase->prev;
    delete toErase;
    num_elements--;
    pos_cursor--; // Adjust cursor position since we removed a node before it
}





// Other Functions ---------------------------------------------------------

int List::findNext(ListElement x) {
    Node* current = afterCursor;  // Start searching from the element after the cursor
    int foundPosition = pos_cursor;  // This will track the position of the cursor

    while (current != backDummy) {  // Traverse till the end of the list
        if (current->data == x) {
            // Found the element x
            beforeCursor = current;  // Set the beforeCursor to the found element
            afterCursor = current->next;  // Set the afterCursor to the element after the found element
            pos_cursor = foundPosition + 1;  // Update the cursor position to be after the found element
            return pos_cursor;  // Return the new cursor position, which is after the found element
        }
        current = current->next;  // Move to the next element
        foundPosition++;  // Move the cursor position forward
    }
     moveBack();  // Move the cursor to the back of the list
    return -1;  // Return -1 if the element is not found
}


int List::findPrev(ListElement x) {
    Node* current = beforeCursor; // Start from the node before the cursor
    int currentPosition = pos_cursor - 1; // Since we are starting from beforeCursor

    // Move backward in the list
    while (current != frontDummy) {
        if (current->data == x) {
            // Found the element x, reposition the cursor
            afterCursor = current; // afterCursor is now at the found node
            beforeCursor = current->prev; // beforeCursor is before the found node
            pos_cursor = currentPosition; // Update cursor position
            return pos_cursor; // Return the updated cursor position
        }
        // Move to the previous node and update the position
        current = current->prev;
        currentPosition--;
    }

    // Element not found, reposition cursor to the front
    moveFront();
    return -1;
}

void List::cleanup() {
    int currentPos = 0;
    Node* currentNode = frontDummy->next;

    while (currentNode != backDummy) {
        int comparePos = currentPos + 1;
        Node* compareNode = currentNode->next;

        while (compareNode != backDummy) {
            if (compareNode->data == currentNode->data) {
                Node* nodeToDelete = compareNode;
                compareNode = compareNode->next;

                if (nodeToDelete == beforeCursor) {
                    beforeCursor = beforeCursor->prev;
                } else if (nodeToDelete == afterCursor) {
                    afterCursor = afterCursor->next;
                }

                // Remove the duplicate node
                nodeToDelete->prev->next = nodeToDelete->next;
                nodeToDelete->next->prev = nodeToDelete->prev;
                delete nodeToDelete;
                num_elements--;
                if (comparePos <= pos_cursor) pos_cursor--;
            } else {
                compareNode = compareNode->next;
            }
            comparePos++;
        }

        currentNode = currentNode->next;
        currentPos++;
    }
}

List List::concat(const List& L) const {
    List newList;

    // Copy elements from this list to newList
    Node* currentThis = this->frontDummy->next;
    while (currentThis != this->backDummy) {
        newList.insertBefore(currentThis->data);  // Inserting before cursor, which is at the end of newList
        currentThis = currentThis->next;
    }

    // Now the cursor in newList is at the position after the last element of 'this' list.
    // Copy elements from L to newList.
    Node* currentL = L.frontDummy->next;
    while (currentL != L.backDummy) {
        newList.insertBefore(currentL->data);  // This will insert the element before the cursor
        currentL = currentL->next;
    }

    // As insertions were made before the cursor, we need to move cursor to front to match the original order
    newList.moveFront();

    return newList;
}





std::string List::to_string() const {
    std::string s = "(";
    Node* current = frontDummy->next;
    while (current != backDummy) {
        s += std::to_string(current->data);
        if (current->next != backDummy) {
            s += ", ";
        }
        current = current->next;
    }
    s += ")";
    return s;
}

bool List::equals(const List &R) const {
    if (num_elements != R.num_elements) {
        return false;
    }
    Node *temp = frontDummy->next;
    Node *temp2 = R.frontDummy->next;
    while (temp != backDummy) {
        if (temp->data != temp2->data) {
            return false;
        }
        temp = temp->next;
        temp2 = temp2->next;
    }
    return true;
}

std::ostream &operator<<(std::ostream &stream, const List &L) {
    stream << L.to_string();
    return stream;
}

bool operator==(const List &L, const List &R) {
    return L.equals(R);
}

List& List::operator=(const List& L) {
    if (this != &L) { // Protect against self-assignment
        List temp(L); // Use copy constructor to make a copy
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);

    }
    return *this;
}




