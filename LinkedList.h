#include <vector>

#pragma once
using namespace std;

template <typename T>
class LinkedList {
public:
    // Nested class
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;
    };

private:
    // LinkedList data
    Node* head;
    Node* tail;
    unsigned int node_count;

public:
    // Behaviors
    // Iterate through all nodes and print out vals
    void PrintForward() const {
        Node* curr_node = head;
        while (curr_node != 0) {
            cout << curr_node->data << endl;
            curr_node = curr_node->next;
        }
    }

    // Same as PrintForward() but opposite
    void PrintReverse() const {
        Node* curr_node = tail;
        while (curr_node != 0) {
            cout << curr_node->data << endl;
            curr_node = curr_node->prev;
        }
    }

    // Recursively iterates through all nodes starting at passed in node and prints vals
    void PrintForwardRecursive(const Node* node) const {
        if (node->next == 0) {
            cout << node->data << endl;
        } else {
            cout << node->data << endl;
            PrintForwardRecursive(node->next);
        }
    }

    // Same as PrintForwardRecursive() but opposite
    void PrintReverseRecursive(const Node* node) const {
        if (node->prev == 0) {
            cout << node->data << endl;
        } else {
            cout << node->data << endl;
            PrintReverseRecursive(node->prev);
        }
    }

    // Accessors
    // Returns node_count
    unsigned int NodeCount() const {
        return node_count;
    }

    // Returns head node
    Node* Head() {
        return head;
    }

    // Returns tail node
    Node* Tail() {
        return tail;
    }

    // Returns a pointer to the node at that index.
    const Node* GetNode(unsigned int index) const {
        if (index >= node_count) {
            throw out_of_range("Index out of range.");
        }

        Node* curr_node = head;
        
        for (unsigned int i = 0; i < node_count; i++) {
            if (i == index){
                return curr_node;
            } 

            curr_node = curr_node->next;
        }

        return nullptr;
    }

    // Non-const GetNode()
    Node* GetNode(unsigned int index) {
        if (index >= node_count) {
            throw out_of_range("Index out of range.");
        }

        Node* curr_node = head;

        for (unsigned int i = 0; i < node_count; i++) {
            if (i == index){
                return curr_node;
            } 
            
            curr_node = curr_node->next;
        }

        return nullptr;
    }

    //Returns pointer to the first node with data matching param
    const Node* Find(const T& data) const {
        Node* curr_node = head;
        while (curr_node != 0) {
            if (curr_node->data == data) {
                return curr_node;
            }

            curr_node = curr_node->next;
        }

        return nullptr;
    }

    // Non-const Find()
    Node* Find(const T& data) {
        Node* curr_node = head;
        while (curr_node != 0) {
            if (curr_node->data == data) {
                return curr_node;
            }
            
            curr_node = curr_node->next;
        }

        return nullptr;
    }

    // Finds all nodes that match the param and store a ptr to the node in the passed vector
    void FindAll(vector<Node*>& outdata, const T&value) const {
        Node* curr_node = head;
        while (curr_node != 0) {
            if (curr_node->data == value) {
                outdata.push_back(curr_node);
            }
            
            curr_node = curr_node->next;
        }

        delete curr_node;
    }


    // Insertion
    // Creates new Node at the front of the list with param
    void AddHead(const T& data) {
        Node* node = new Node;
        node->data = data;
        node->prev = nullptr;

        if (node_count == 0) {
            node->next = nullptr;
            tail = node;
        } else {
            node->next = head;
            head->prev = node;
        }

        head = node;
        node_count++;
    }

    // Creates new Node at the end of the list with param
    void AddTail(const T& data) {
        Node* node = new Node;
        node->data = data;
        node->next = nullptr;

        if (node_count == 0) {
            node->prev = nullptr;
            head = node;
        } else {
            node->prev = tail;
            tail->next = node;
        }

        tail = node;
        node_count++;
    }

    // Iterates through array and creates new Nodes at front of list
    void AddNodesHead(const T* data, unsigned int count) {
        for (unsigned int i = 1; i <= count; i++) {
            AddHead(data[count-i]);
        }
    }

    // Iterates through array and creates new Nodes at end of list
    void AddNodesTail(const T* data, unsigned int count) {
        for (unsigned int i = 0; i < count; i++) {
            AddTail(data[i]);
            
        }
    }

    // Create a new node with passed data after passed node ptr
    void InsertAfter(Node* node, const T& data) {
        Node* new_node = new Node;
        new_node->data = data;
        new_node->prev = node;
        new_node->next = node->next;
        node->next->prev = new_node;
        node->next = new_node;
        node_count++;

    }

    // Create a new node with passed data before passed node ptr
    void InsertBefore(Node* node, const T& data) {
        Node* new_node = new Node;
        new_node->data = data;
        new_node->next = node;
        new_node->prev = node->prev;
        node->prev->next = new_node;
        node->prev = new_node;
        node_count++;
    }

    // Inserts new node for passed data at index
    void InsertAt(const T& data, unsigned int index) {
        if (index == 0){
            AddHead(data);
        } else if (index == node_count) {
            AddTail(data);
        } else {
            InsertBefore(GetNode(index), data);
        }
    }

    // Removal
    // Deletes first node in the list and returns whether it was removed
    bool RemoveHead() {
        if (this->head == 0) { return false; }

        Node* new_head = head->next;

        if (new_head != 0) { new_head->prev = nullptr; }

        delete this->head;
        node_count--;
        this->head = new_head;

        return true;
    }

    // Deletes last node in the list and returns whether it was removed
    bool RemoveTail() {
        if (this->tail == 0) { return false; }

        Node* new_tail = tail->prev;

        if (new_tail != 0) { new_tail->next = nullptr; }
        delete this->tail;
        node_count--;
        this->tail = new_tail;

        return true;
    }

    // Remove all nodes containing values matching passed in value and return removal count
    unsigned int Remove(const T&data) {
        vector<Node*> nodes;
        FindAll(nodes, data);
        int removals = 0;

        int num_nodes = nodes.size();
        for (int i = 0; i < num_nodes; i++) {
            Node* node = nodes.at(i);

            if (node->prev == 0) {
                bool success = RemoveHead(); 
                if (success) {
                    removals++; 
                    node_count--;
                }
            } else if (node->next == 0) {
                bool success = RemoveTail();
                if (success) {
                    removals++; 
                    node_count--;
                }
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
                delete node;
                removals++;
                node_count--;
            }
        }

        return removals;
    }

    // Delete node at passed in index and return whether it was successful
    bool RemoveAt(unsigned int index) {
        if (index >= node_count) {
            return false;
        } 
        
        if (index == 0) {
            return RemoveHead();
        }

        if (index == node_count - 1) {
            return RemoveTail();
        }

        Node* node = GetNode(index);
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        node_count--;

        return true;
    }

    // Deletes all nodes and reset node count
    void Clear() {
        while (RemoveTail()) {}
        this->head = nullptr;
        this->tail = nullptr;
    }

    // Operators
    const T& operator[](unsigned int index) const {
        if (index >= node_count) {
            throw out_of_range("Index out of range.");
        }

        return *(GetNode(index));
    }

    T& operator[](unsigned int index) {
        if (index >= node_count) {
            throw out_of_range("Index out of range.");
        }

        return (GetNode(index))->data;
    }

    // Overloaded equality operator
    // Checks that all data in the compared lists is the same
    bool operator==(const LinkedList<T>& rhs) const {
        if (this->node_count == rhs.node_count) {
            if (head->data != rhs.head->data) { return false; }
            if (tail->data != rhs.tail->data) { return false; }

            Node* curr_node = head->next;
            Node* check_against = rhs.head->next;

            for (unsigned int i = 1; i < node_count; i++) {
                if (curr_node->data != check_against->data) {
                    return false;
                }

                curr_node = curr_node->next;
                check_against = check_against->next;
            }

        } else {
            return false;
        }

        return true;
    }

    // Construction / Destruction
    LinkedList() {
        node_count = 0;
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList() {
        Node* curr_node = tail;
        while (curr_node != 0) {
            Node* prev = curr_node->prev;
            delete curr_node;
            curr_node = prev;
        }
        tail = 0;
    }

    // Copy Constructor recursive helper
    Node* copy_recursive(Node* head, Node* prev) {
        if (head == 0) {
            return head;
        }

        Node* node = new Node;
        node->data = head->data;
        node->prev = prev;
        node->next = copy_recursive(head->next, node);

        return node;
    }

    // Copy Constructor
    LinkedList(const LinkedList<T>& rhs) {
        this->node_count = rhs.node_count;        
        this->head = copy_recursive(rhs.head, nullptr);
        this->tail = GetNode(node_count-1);
    }

    // Copy Assignment Operator
    LinkedList<T> &operator=(const LinkedList<T> &rhs) {
        if (this != &rhs){
            LinkedList<T> temp(rhs);
            swap(temp.head, this->head);
            swap(temp.tail, this->tail);
            this->node_count = rhs.node_count;
        }

        return *this;
    }
};