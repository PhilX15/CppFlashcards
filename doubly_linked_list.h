#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node *next;
    Node *prev;

    Node (T value) : data(value), next(nullptr), prev(nullptr) {}

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
    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        while (head != nullptr) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(T value) {
        Node<T> *new_node = new Node<T>(value);
        new_node->prev = tail;
        if (tail != nullptr) {
            tail->next = new_node;
            tail = new_node;
        } else {
            tail = new_node;
            head = new_node;
        }
    }

    void push_front(T value) {
        Node<T> *new_node = new Node<T>(value);
        new_node->next = head;
        if (head != nullptr) {
            head->prev = new_node;
            head = new_node;
        } else {
            tail = new_node;
            head = new_node;
        }
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

    Node<T> *find(T value) {
        if (this->is_empty()) throw out_of_range("List is empty");

        Node<T> *current_node = head;
        while (current_node != nullptr) {
            if (current_node->data == value) {
                return current_node;
            }
            current_node = current_node->next;
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

    friend ostream& operator<<(ostream& os, const List& list) {
        if (list.is_empty()) {
            cout << "List is empty";
            return os;
        }

        Node<T> *current_node = list.head;
        while (current_node != nullptr) {
            cout << *current_node << " ";
            current_node = current_node->next;
        }
        return os;
    }
};