#include <cctype>
#include <iostream>
#include <string>

using namespace std;

class LinkedStack {
private:
    struct Node {
        char data;
        Node* next;
        Node(char value, Node* nextNode = nullptr) : data(value), next(nextNode) {}
    };

    Node* topNode;

public:
    LinkedStack() : topNode(nullptr) {}

    ~LinkedStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void push(char value) {
        topNode = new Node(value, topNode);
    }

    void pop() {
        if (isEmpty()) {
            return;
        }

        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    char peek() const {
        if (isEmpty()) {
            return '\0';
        }
        return topNode->data;
    }
};

int precedence(char op) {
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}

string infixToPostfix(const string& infix) {
    LinkedStack stack;
    string postfix;

    for (char ch : infix) {
        if (isalnum(static_cast<unsigned char>(ch))) {
            postfix += ch;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.peek();
                stack.pop();
            }
            if (!stack.isEmpty() && stack.peek() == '(') {
                stack.pop();
            }
        } else {
            while (!stack.isEmpty() && stack.peek() != '(' &&
                   precedence(ch) <= precedence(stack.peek())) {
                postfix += stack.peek();
                stack.pop();
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.peek();
        stack.pop();
    }

    return postfix;
}

int main() {
    const string expressions[] = {
        "A+B",
        "A+B*C",
        "A*B+C",
        "(A+B)*C",
        "A+B*C-D",
        "A*(B+C)/D"
    };

    cout << "Infix to Postfix Conversion:\n";
    for (const string& expr : expressions) {
        cout << expr << " -> " << infixToPostfix(expr) << '\n';
    }

    return 0;
}
