/***
* Arthur Wei
* hwei20
* 2023 Fall CSE101 PA7
* Dictionary.cpp
* Contains the implementation of the Dictionary ADT
***/

#include "Dictionary.h"

// Node constructor
Dictionary::Node::Node(keyType k, valType v) : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr) {
}

// Dictionary constructor
Dictionary::Dictionary() {
    nil = new Node("", 0);
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, nil);
}

// Destructor
Dictionary::~Dictionary() {
    postOrderDelete(root);
    delete nil;
}

// Helper Functions
void Dictionary::inOrderString(std::string&s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string&s, Node* R) const {
    if (R != nil) {
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// Recursively inserts a deep copy of the subtree rooted at R, terminating at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    // Recursively searches current, left, right
    if (R->key == N->key) {
        return;
    }
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || k == R->key) {
        return R;
    }
    if (k < R->key) {
        return search(R->left, k);
    }
    return search(R->right, k);
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R != nil) {
        while (R->left != nil) {
            R = R->left;
        }
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R != nil) {
        while (R->right != nil) {
            R = R->right;
        }
    }
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nil) {
        return nil;
    }

    // Case 1: Right subtree exists
    if (N->right != nil) {
        return findMin(N->right);
    }

    // Case 2: No right subtree
    Node* parentN = N->parent;
    while (parentN != nil && N == parentN->right) {
        N = parentN;
        parentN = parentN->parent;
    }
    return parentN;
}


Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nil) {
        return nil;
    }

    // Case 1: Left subtree exists
    if (N->left != nil) {
        return findMax(N->left);
    }

    // Case 2: No left subtree
    Node* parentN = N->parent;
    while (parentN != nil && N == parentN->left) {
        N = parentN;
        parentN = parentN->parent;
    }
    return parentN;
}


// Access functions
int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil;
}

valType& Dictionary::getValue(keyType k) const {
    Node* N = search(root, k);
    if (N == nil) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return N->val;
}

bool Dictionary::hasCurrent() const {
    return current != nil;
}

keyType Dictionary::currentKey() const {
    if (current == nil) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (current == nil) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures
void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* keyNode = search(root, k);

    if (keyNode != nil) {
        // Key exists, update the value
        keyNode->val = v;
    }
    else {
        // Key does not exist, insert a new node
        Node* newNode = new Node(k, v);
        newNode->left = newNode->right = nil;

        Node* searchNode = root;
        Node* parentNode = nil;

        // Find the correct position to insert the new node
        while (searchNode != nil) {
            parentNode = searchNode;
            if (newNode->key < searchNode->key) {
                searchNode = searchNode->left;
            }
            else {
                searchNode = searchNode->right;
            }
        }

        newNode->parent = parentNode;

        // Determine the child relationship
        if (parentNode == nil) {
            // The tree was empty, new node is the root
            root = newNode;
        }
        else if (newNode->key < parentNode->key) {
            // Insert as left child
            parentNode->left = newNode;
        }
        else {
            // Insert as right child
            parentNode->right = newNode;
        }

        num_pairs++; // Increment the number of key-value pairs
    }
}


void Dictionary::remove(keyType k) {
    Node* keyNode = search(root, k);
    if (keyNode == nil) {
        throw std::invalid_argument("Dictionary: remove(): key \"" + k + "\" does not exist");
    }

    // Handle the case where the node has two children
    if (keyNode->left != nil && keyNode->right != nil) {
        Node* successor = findMin(keyNode->right);
        keyNode->key = successor->key;
        keyNode->val = successor->val;
        keyNode = successor; // Now delete the successor
    }

    // Now keyNode has at most one child
    Node* child = (keyNode->left != nil) ? keyNode->left : keyNode->right;

    // If keyNode is not root, link its parent to its child
    if (keyNode->parent != nil) {
        if (keyNode == keyNode->parent->left) {
            keyNode->parent->left = child;
        } else {
            keyNode->parent->right = child;
        }
    } else {
        root = child; // keyNode is root, update root to its child
    }

    // Update the parent pointer of the child
    if (child != nil) {
        child->parent = keyNode->parent;
    }

    // Update current if it points to the node being removed
    if (current == keyNode) {
        current = nil;
    }

    delete keyNode;
    num_pairs -= 1;
}


void Dictionary::begin() {
    current = findMin(root);
}

void Dictionary::end() {
    current = findMax(root);
}

void Dictionary::next() {
    if (current != nil) {
        current = findNext(current);
    }
    else {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
}

void Dictionary::prev() {
    if (current != nil) {
        current = findPrev(current);
    }
    else {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
}

// Other Functions
std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary&D) const {
    return to_string() == D.to_string();
}

// Overloaded Operators
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<(std::ostream&stream, Dictionary&D) {
    return stream << D.to_string();
}


bool operator==(const Dictionary&A, const Dictionary&B) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=(const Dictionary&D) {
    if (this != &D) {
        clear();
        preOrderCopy(D.root, nil);
    }
    return *this;
}
