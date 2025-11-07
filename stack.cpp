#include <iostream>
using namespace std;

const int MAX = 314; // Max size of stack, pi but without decimals because I can't do that and I'm sad about it!

class Stack {  // Stack def. using a fixed size array
private:
    int arr[MAX];
    int top;

public:
    Stack() {
        top = -1;
    }

    void push(int value) { //Add a number to the top of the stack
        if (top >= MAX - 1) {
            cout << "Too Much!" << endl;
        } else {
            top++;
            arr[top] = value;
            cout << value << " pushed to stack." << endl;
        }
    }

    void pop() { // Remove the top number from the stack
        if (top < 0) {
            cout << "Stack is sad!" << endl;
        } else {
            cout << arr[top] << " popped from stack." << endl;
            top--;
        }
    }

    void peek() {
        if (top < 0) {
            cout << "Stack is sad!" << endl;
        } else {
            cout << "Best(top) element is: " << arr[top] << endl;
        }
    }

    void display() {
        if (top < 0) {
            cout << "Stack is sad!" << endl;
        } else {
            cout << "Stack elements: ";
            for (int i = 0; i <= top; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Stack s;
    s.push(71);
    s.push(22);
    s.push(5);
    s.display();
    s.peek();
    s.pop();
    s.display();

    return 0;
}
