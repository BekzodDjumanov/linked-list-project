// This program was developed by Bekzod Djumanov and Jonathan Lowery for CMSC202-65 Group Project on May 4th 2025
// This program will create singly and doubly linked lists to store basic information in a shop.

#include <iostream>
#include <string>
using namespace std;
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std::chrono;
#include <cmath>

//basic customer class
class Customer{
    public:
    int customerID;
    string toppings;
    string size;
    bool isCompleted;

    int getCustomerID() {
        return customerID;
    }
    string getToppings() {
        return toppings;
    }
    string getSize() {
        return size;
    }
    bool getIsCompleted() {
        return isCompleted;
    }

    void setCustomerID(int id) {
        customerID = id;
    }
    void setToppings(string t) {
        toppings = t;
    }
    void setSize(string s) {
        size = s;
    }
    void setIsCompleted(bool c) {
        isCompleted = c;
    }

    void View() {
        cout << "Customer ID: " << customerID << endl;
        cout << "Toppings: " << toppings << endl;
        cout << "Size: " << size << endl;
        cout << "Is Completed: " << (isCompleted ? "Yes" : "No") << endl;
    }

    Customer() {
        customerID = rand() % 99 + 1;
        toppings = "Unknown";
        size = "Unknown";
        isCompleted = false;
    }
    Customer(int id, string t, string s, bool c) {
        customerID = id;
        toppings = t;
        size = s;
        isCompleted = c;
    }


};
// single linked list
class Node{
    public:
    Customer data;
    Node* next;

    Node(Customer c){
        data = c;
        next = nullptr;
    }
};
// double linked list
class NodeDoubly{
    public:
    Customer data;
    NodeDoubly* next;
    NodeDoubly* prev;

    NodeDoubly(Customer c){
        data = c;
        next = nullptr;
        prev = nullptr;
    }
};


int main(){
    srand(time(0));
    int choice = 0;
    int customerID = rand() % 999 + 1; // random initilization for customerID
    string toppings;
    string size;
    bool isCompleted;
    Node* head = nullptr; // initilization of head pointer
    NodeDoubly* headDoubly = nullptr; // initilization of headDoubly pointer

    Node* current = nullptr; // used for (adding to) doubly linked list (case 4)
    Node* prev = nullptr; // also used for (adding to) doubly linked list (case 4)

    auto start = high_resolution_clock::now(); // all time related

    for (int i = 0; i < 1000000; ++i) {}

    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;





    while (choice != 6){
        cout << "\nMenu" << endl;

        cout << "--------------------------" << endl;

        // UI
        cout << "1. Add a New Order" << endl;
        cout << "2. Delete an Order" << endl;
        cout << "3. Search for an Order" << endl;
        cout << "4. Complete an Order" << endl;
        cout << "5. Display Incomplete Orders" << endl;
        cout << "6. Exit Program" << endl;
        cout << "--------------------------" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;
        cin.ignore();
        if (cin.fail()) { // any instances of this are for input validation
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid Input, exiting..." << endl;
            return 0;
        }
        Customer customer1; // create instance of customer

        switch(choice){
            case 1:
                cout << "---------------------------" << endl;
                customerID = rand() % 99 + 1;
                cout << "Customer ID: " << customerID << endl;

                cout << "Enter Toppings: ";
                getline(cin, toppings);

                cout << "Enter the Pizza Size: ";
                getline(cin, size);

                customer1 = Customer(customerID, toppings, size, false); // create customer object (but not completed)

                {
                    Node* newNode = new Node(customer1); // add to singly linked list
                    newNode->next = head;
                    head = newNode;
                }

                cout << "---------------------------" << endl;
                break;
            case 2:
                cout << "---------------------------" << endl;
                cout << "Enter Customer ID to delete: ";
                cin >> customerID;
                
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nInvalid input, returning to Menu..." << endl;
                    break;
                }

                    {
                    Node* current = head; // current will be used to traverse the singly linked list, if ID is found, it will be deleted
                    Node* prev = nullptr;
                    bool found = false;

                    while (current != nullptr) {
                        if (current->data.getCustomerID() == customerID) {
                            found = true;

                            if (prev == nullptr) {
                                head = current->next; 
                            } else {
                                prev->next = current->next;
                            }

                            delete current;
                            cout << "\nOrder with Customer ID " << customerID << " has been deleted." << endl;
                            break;
                        }

                        prev = current;
                        current = current->next;
                    }

                    if (!found) { // if ID is not found, print this
                        cout << "\nOrder with Customer ID " << customerID << " not found." << endl;
                    }
                }

                cout << "---------------------------" << endl;
                break;
            case 3:
                cout << "Enter Customer ID to search: ";
                cin >> customerID;
                cin.ignore();
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nInvalid input, returning to Menu..." << endl;
                    break;
                }
                cout << "(Order found in " << duration.count()<< " seconds)" << endl; // time
                cout << "---------------------------" << endl;

                {
                    Node* current = head; // once again, current will be used to traverse the list and if found, it will print
                    bool found = false;

                    while (current != nullptr) {
                        if (current->data.getCustomerID() == customerID) {
                            cout << "Order found:" << endl;
                            current->data.View();
                            found = true;
                            break;
                        }
                        current = current->next;
                    }

                    if (!found) {
                        cout << "\nNo order found with Customer ID " << customerID << endl;
                    }

                    cout << "---------------------------" << endl;
                }
                break;
            case 4:
                current = head; // same deal here
                prev = nullptr;
                cout << "Enter Customer ID to complete: ";
                cin >> customerID;
                cin.ignore();
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nInvalid input, returning to Menu..." << endl;
                    break;
                }
                while (current != nullptr && current->data.getCustomerID() != customerID) {
                    prev = current;
                    current = current->next;
                }

                if (current != nullptr) { // if current is found, begin completion
                    current->data.setIsCompleted(true);
                    if (prev != nullptr) { // if current is not the head
                        prev->next = current->next; // link previous node to next node
                    } else {
                        head = current->next; // if current is the head, move head to next node
                    }


                    NodeDoubly* newDoublyNode = new NodeDoubly(current->data); // create new doubly node
                    

                    newDoublyNode->next = headDoubly; // link new doubly node to headDoubly
                    if (headDoubly != nullptr) {
                        headDoubly->prev = newDoublyNode;
                    }
                    headDoubly = newDoublyNode; // link new doubly node to headDoubly

                    delete current; // deletes instance of current in singly linked list

                    cout << "\nOrder with Customer ID " << customerID << " has been completed." << endl;

                } else {
                    cout << "\nOrder with Customer ID " << customerID << " not found." << endl;
                }
                cout << "---------------------------" << endl;
                break;
            case 5:
                if (head == nullptr) {
                    cout << "\nNo incomplete orders.\n" << endl;
                    break;
                } else{ 

                    cout << "Incomplete Orders:" << endl;
                    Node* currentNode = head;
                    while (currentNode != nullptr) {
                        currentNode->data.View();
                        currentNode = currentNode->next;
                    }
                }
            cout << "---------------------------" << endl;
            break;

            default:
            cout << "\nInvalid choice." << endl;
            break;
        }
        }
    if (headDoubly == nullptr) { // basically, if the doubly linked list is empty, print this
        cout << "\nNo completed orders." << endl;
    } else {
        cout << "\nCompleted Orders:" << endl;
        NodeDoubly* currentDoublyNode = headDoubly; // traverse the doubly linked list using currentDoublyNode
        while (currentDoublyNode != nullptr) {
            currentDoublyNode->data.View();
            currentDoublyNode = currentDoublyNode->next;
        }
    }
    
}