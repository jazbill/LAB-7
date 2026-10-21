#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

class LinkedQueue {
private:
    struct Node {
        string data;
        Node* next;
        Node(const string& value) : data(value), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;

public:
    LinkedQueue() : frontNode(nullptr), rearNode(nullptr) {}

    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    void enqueue(const string& value) {
        Node* newNode = new Node(value);
        if (rearNode == nullptr) {
            frontNode = rearNode = newNode;
            return;
        }

        rearNode->next = newNode;
        rearNode = newNode;
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }

        Node* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
    }

    string front() const {
        if (isEmpty()) {
            return "";
        }
        return frontNode->data;
    }

    void displayQueue() const {
        Node* current = frontNode;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " ";
            }
            current = current->next;
        }
        cout << '\n';
    }
};

int main() {
    constexpr int serviceSeconds = 10;

    LinkedQueue customerQueue;

    customerQueue.enqueue("Ali");
    customerQueue.enqueue("John");
    customerQueue.enqueue("Sara");
    customerQueue.enqueue("David");
    customerQueue.enqueue("Emma");

    cout << "Waiting customers: ";
    customerQueue.displayQueue();

    while (!customerQueue.isEmpty()) {
        string currentCustomer = customerQueue.front();
        cout << "Now serving: " << currentCustomer << '\n';

        this_thread::sleep_for(chrono::seconds(serviceSeconds));

        customerQueue.dequeue();
        cout << "Service completed: " << currentCustomer
             << " (" << serviceSeconds << " seconds)" << '\n';
    }

    cout << "All customers have been served." << '\n';
    cout << "Queue is " << (customerQueue.isEmpty() ? "empty." : "not empty.") << '\n';

    return 0;
}
