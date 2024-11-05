#include<iostream>

using namespace std; 

struct Node {
    int data; 
    Node* next; 
};

class LinkedList {
private: 
    Node* head; 

public: 
    LinkedList() : head(NULL) {}

    void insert_beginning(int val) {
        Node* newNode = new Node(); 
        newNode->data = val; 
        newNode->next = head; 
        head = newNode; 
    }

    void insert_end(int val) {
        Node* newNode = new Node();
        newNode->data = val; 
        newNode->next = nullptr; 

        if (head == nullptr) {
            head = newNode; 
            return; 
        }

        //traverse to the end of the list with temp
        Node* temp = head; 

        while (temp->next) {
            temp = temp->next; 
        }

        temp->next = newNode; 

    }

    void insert_at_position(int val, int pos) {
        
        if (pos < 1) {
            cout << "pos should be bigger than 0";
        } else if (pos == 1) {
            insert_beginning(val);
            return; 
        } else {
            Node* newNode = new Node();
            newNode->data = val; 

            Node* temp = head; 
            for (int i=0; i < pos - 1 && temp; i++) {
                temp = temp->next; 
            }

            if (!temp) {
                cout << "out of range";
                delete newNode; 
                return; 
            }

            newNode->next = temp->next; 
            temp->next = newNode; 
        }
    }

    void deletefrom_beginning() {
        if (!head) {
            cout << "list empty";
            return; 
        }
        Node* temp = head; 
        head = head->next;
        delete temp; 
    }

    void deletefrom_end() {

        if (!head) {
            cout << "list empty";
            return; 
        }

        if (!head->next) {
            delete head; 
            head = NULL; 
            return; 
        }

        Node* temp = head; 
        while (temp->next->next) {
            temp = temp->next;
        }
        
        delete temp->next; 
        temp->next = NULL;

    }

    void deletefrom_pos(int pos) {

        if (pos < 1) {
            cout << "come on, can't do that";
            return; 
        } else if (pos == 1) {
            deletefrom_beginning();
            return; 
        }

        if (!head) {
            cout << "list empty";
            return; 
        }

        //traverse list until right before pos
        Node* temp = head; 
        for (int i=0; i < pos - 2 && temp; i++) {
            temp = temp->next; 
        }

        if (!temp || !temp->next) {
            cout << "error occured, out of bounds";
            return; 
        }

        Node* todelete = temp->next; 
        temp->next = temp->next->next; 
        delete todelete; 
    }

    void display() {

        if (!head) {
            cout << "list empty";
            return; 
        }
        
        Node* temp = head; 
        while (temp->next) {
            cout << temp->data << "->"; 
            temp = temp->next; 
        }
        cout << temp->data; 
        cout << "->NULL";

    }

};

int main() {

    LinkedList list1; 

    list1.insert_beginning(3); 
    list1.insert_beginning(2); 
    list1.insert_beginning(1); 
    list1.insert_end(4); 
    list1.insert_at_position(5,1);

    list1.deletefrom_beginning(); 
    list1.deletefrom_end();

    list1.deletefrom_pos(2);

    list1.display();

    return 0; 
}