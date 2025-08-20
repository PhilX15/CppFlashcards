#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node *next;
    Node *prev;

    Node (T value) : data(value), next(nullptr), prev(nullptr) {}

    bool operator==(Node& n) {
        return (data == n.data && next == n.next && prev == n.prev);
    }

    friend ostream& operator<<(ostream& os, const Node& node) {
        cout << node.data;
        return os;
    }
};

template <typename T>
class List {
private:
    Node<T> *head;
    Node<T> *tail;

public:
    class Iterator {
        private:
            Node<T> *current;
        public:
            Iterator(Node<T>* node) : current(node) {}

            T& operator*() const {
                return current->data;
            }

            Iterator& operator++() {
                if (current) {
                    current = current->next;
                }
                return *this;
            }

            bool operator!=(const Iterator& other) {
                return current != other.current;
            }
    };

    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        while (head != nullptr) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    List(const List& other) : head(nullptr), tail(nullptr) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    List& operator=(const List& other) {
        if (this == &other) {
            return *this;
        }

        while (!is_empty()) {
            pop_front();
        }

        Node<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }

        return *this;
    }


    void push_back(T value) {
        Node<T> *new_node = new Node<T>(value);
        new_node->prev = tail;
        new_node->next = nullptr;
        if (tail != nullptr) {
            tail->next = new_node;
        } else {
            head = new_node;
        }
        tail = new_node;
    }

    void push_front(T value) {
        Node<T> *new_node = new Node<T>(value);
        new_node->next = head;
        new_node->prev = nullptr;
        if (head != nullptr) {
            head->prev = new_node;
        } else {
            tail = new_node;
        }
        head = new_node;
    }

    T pop_back() {
        if (this->is_empty()) throw out_of_range("List is empty");

        T result = tail->data;
        Node<T> *temp = tail;

        if (tail == head) {
            delete tail;
            tail = nullptr;
            head = nullptr;

            return result;
        }

        tail = tail->prev;
        tail->next = nullptr;
        delete temp;

        return result;
    }

    T pop_front() {
        if (this->is_empty()) throw out_of_range("List is empty");

        T result = head->data;
        Node<T> *temp = head;
        
        if (tail == head) {
            delete tail;
            tail = nullptr;
            head = nullptr;

            return result;
        }

        head = head->next;
        head->prev = nullptr;
        delete temp;

        return result;
    }

    T pop(Node<T> *node) {
        if (this->is_empty()) throw out_of_range("List is empty");

        Node<T> *current_node = head;
        while (current_node != nullptr) {
            if (current_node == node) {
                break;
            }
            current_node = current_node->next;
        }

        if (current_node == nullptr) {
            throw "Node not in list";
        }

        T result = current_node->data;

        if (current_node->prev != NULL) {
            current_node->prev->next = current_node->next;
        } else {
            head = current_node->next;
        }

        if (current_node->next != NULL) {
            current_node->next->prev = current_node->prev;
        } else {
            tail = current_node->prev;
        }

        delete current_node;

        return result;
    }

    T pop(unsigned int index) {
        if (this->is_empty()) throw out_of_range("List is empty");

        if (index >= this->size()) throw out_of_range("Index out of range");
        
        unsigned int current_index = 0;
        Node<T> *current_node = head;
        while (current_node != nullptr) {
            if (current_index == index) {
                break;
            }
            current_node = current_node->next;
            current_index++;
        }

        T result = current_node->data;

        if (current_node->prev != NULL) {
            current_node->prev->next = current_node->next;
        } else {
            head = current_node->next;
        }

        if (current_node->next != NULL) {
            current_node->next->prev = current_node->prev;
        } else {
            tail = current_node->prev;
        }

        delete current_node;

        return result;
    }

    Node<T> *find(T value) {
        Node<T> *current_node = head;
        while (current_node != nullptr) {
            if (current_node->data == value) {
                return current_node;
            }
            current_node = current_node->next;
        }

        return nullptr;
    }

    Node<T> *operator[](unsigned int index) const {
        if (this->is_empty()) throw out_of_range("List is empty");

        if (index >= this->size()) throw out_of_range("Index out of range");

        unsigned int current_index = 0;
        Node<T> *current_node = head;
        while (current_node != nullptr) {
            if (current_index == index) {
                return current_node;
            }
            current_node = current_node->next;
            current_index++;
        }

        return nullptr;
    }

    size_t size() const {
        size_t result = 0;
        Node<T> *current_node = head;
        while (current_node != nullptr) {
            result++;
            current_node = current_node->next;
        }

        return result;
    }

    bool is_empty() const {
        return (head == nullptr && tail == nullptr);
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const { 
        return Iterator(nullptr); 
    }
};

#endif