
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial {
    struct Node {
        int c, e;
        Node* next;
        Node(int a, int b) : c(a), e(b), next(NULL) {}
    };
    Node* head = NULL;

public:
    void insert(int c, int e) {
        if (c == 0) return;
        Node** p = &head;

        while (*p && (*p)->e > e)
            p = &(*p)->next;

        if (*p && (*p)->e == e) {
            (*p)->c += c;
            if ((*p)->c == 0) {
                Node* t = *p;
                *p = t->next;
                delete t;
            }
        } else {
            Node* t = new Node(c, e);
            t->next = *p;
            *p = t;
        }
    }

    Polynomial operator+(Polynomial b) {
        Polynomial r;
        for (Node* t = head; t; t = t->next)
            r.insert(t->c, t->e);
        for (Node* t = b.head; t; t = t->next)
            r.insert(t->c, t->e);
        return r;
    }

    Polynomial operator-(Polynomial b) {
        Polynomial r;
        for (Node* t = head; t; t = t->next)
            r.insert(t->c, t->e);
        for (Node* t = b.head; t; t = t->next)
            r.insert(-t->c, t->e);
        return r;
    }

    Polynomial operator*(Polynomial b) {
        Polynomial r;
        for (Node* a = head; a; a = a->next)
            for (Node* t = b.head; t; t = t->next)
                r.insert(a->c * t->c, a->e + t->e);
        return r;
    }

    double evaluate(double x) {
        double s = 0;
        for (Node* t = head; t; t = t->next)
            s += t->c * pow(x, t->e);
        return s;
    }

    void display() {
        if (!head) { cout << "0"; return; }
        for (Node* t = head; t; t = t->next) {
            cout << t->c;
            if (t->e) cout << "x";
            if (t->e > 1) cout << "^" << t->e;
            if (t->next) cout << " + ";
        }
    }
};

int main() {
    Polynomial p1, p2;
    int n, c, e;

    cout << "Enter terms of P1: ";
    cin >> n;
    while (n--) {
        cin >> c >> e;
        p1.insert(c, e);
    }

    cout << "Enter terms of P2: ";
    cin >> n;
    while (n--) {
        cin >> c >> e;
        p2.insert(c, e);
    }

    cout << "\nP1 = "; p1.display();
    cout << "\nP2 = "; p2.display();

    cout << "\nAddition = ";
    (p1 + p2).display();

    cout << "\nSubtraction = ";
    (p1 - p2).display();

    cout << "\nMultiplication = ";
    (p1 * p2).display();

    double x;
    cout << "\nEnter x: ";
    cin >> x;

    cout << "P1 Value = " << p1.evaluate(x);
    cout << "\nP2 Value = " << p2.evaluate(x);

    return 0;
}
