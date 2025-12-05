#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

class Stack {
    vector<int> st;
    int size;
public:
    Stack(int n) { size = n; }

    void showSimulation(string action, int value = -1) {
        cout << "\n-----------------------------\n";
        cout << "Action: " << action;
        if (value != -1) cout << " (" << value << ")";
        cout << "\nCurrent Stack:\n";

        if (st.empty()) {
            cout << "[ EMPTY ]\n";
        } else {
            for (int i = st.size()-1; i >= 0; i--) {
                cout << "| " << st[i] << " |\n";
                cout << "\n";
            }
        }
        usleep(700000); // delay for animation
    }

    void push(int x) {
        if (st.size() == size) {
            cout << "\nStack Overflow!\n";
            showSimulation("Overflow Occurred");
            return;
        }
        st.push_back(x);
        showSimulation("Push", x);
    }

    void pop() {
        if (st.empty()) {
            cout << "\nStack Underflow!\n";
            showSimulation("Underflow Occurred");
            return;
        }
        int x = st.back();
        st.pop_back();
        showSimulation("Pop", x);
    }

    void peek() {
        if (st.empty()) {
            cout << "\nStack Empty!\n";
            showSimulation("Peek Failed");
            return;
        }
        showSimulation("Peek (Top = " , st.back());
    }

    void display() {
        showSimulation("Display");
    }
};

int main() {
    int n;
    cout << "\nEnter stack size: ";
    cin >> n;

    Stack s(n);
    int choice, x;

    while (true) {
        cout << "\n1 Push\n2 Pop\n3 Peek\n4 Display\n5 Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> x;
                s.push(x);
                break;
            case 2:
                s.pop();
                break;
            case 3:
                s.peek();
                break;
            case 4:
                s.display();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid Choice\n";
        }
    }
}
