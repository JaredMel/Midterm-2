#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
//Declares and Initilizes variables
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
//the DoublyLinkedList Class
class DoublyLinkedList {
private:
    //the Node struct
    struct Node {
        //Declares and Initilizes attributes
        string name;
        Node* prev;
        Node* next;
        //Node constructor
        Node(string nam, Node* p = nullptr, Node* n = nullptr) {
            //Sets attribute values
            name = nam;
            prev = p;
            next = n;
        }
    };
    //Declares and initilizes attributes
    Node* head;
    Node* tail;
public:
    //DoublyLinkedList constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }
    //the insert_after method
    void insert_after(string value, int position) {
        //Checks if position is less than 0
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        //Creates the new Node struct with its values set to value
        Node* newNode = new Node(value);
        //Checks if the list is empty
        if (!head) {
            head = tail = newNode;
            return;
        }
        //Creates a temp node and sets it to head
        Node* temp = head;
        //Traverses the DoublyLinkedList to find the correct position
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        //Checks if position exceeds the List's size and deletes the Node
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        //adds the newNode by pointing to the next node and setting it to the temp node pointing to it's next node
        newNode->next = temp->next;
        //sets the newNode pointing to the previous to equal the temp node
        newNode->prev = temp;
        //Checks if Node is being added at the tail
        if (temp->next)
            //temp points to the next points to the prev and sets it to newNode
            temp->next->prev = newNode;
        else
            //sets the tail to the newNode
            tail = newNode;
        //sets the temp's next pointer to point at newNode
        temp->next = newNode;
    }
    //the delete_val method
    void delete_val(string value) {
        //Checks if the list is empty
        if (!head) return;
        //Creates a temp node and sets it to head
        Node* temp = head;
        //Traverses the DoublyLinkedList to find the value
        while (temp && temp->name != value)
            temp = temp->next;
        //if can't find value return
        if (!temp) return;
        //Checks if value is at the head
        if (temp->prev)
            //temp points to the prev points to the next and sets it to temp pointing to next
            temp->prev->next = temp->next;
        else
            //sets the head equal to the next node
            head = temp->next;
        //Checks if value is at the tail
        if (temp->next)
            //temp points to the next points to the prev and sets it to temp pointing to prev
            temp->next->prev = temp->prev;
        else
            //sets the tail to the prev node
            tail = temp->prev;
        //deletes temp Node
        delete temp;
    }
    //the delete_pos method
    void delete_pos(int pos) {
        //Checks if list is empty
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        //checks if position is at the head
        if (pos == 1) {
            //calls the pop_front() method
            pop_front();
            return;
        }
        //Creates a temp node and sets it to head
        Node* temp = head;
        //for loop that iterates in till i = pos
        for (int i = 1; i < pos; i++){
            //checks if it reached the end of the list
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                //iterates to the next node
                temp = temp->next;
        }
        //checks if it reached the end of the list
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
        //checks if position is at the tail
        if (!temp->next) {
            //calls the pop_back() method
            pop_back();
            return;
        }
        //creates a tempPrev node and points it to the prev node behind temp
        Node* tempPrev = temp->prev;
        //Sets the next pointer for tempPrev to the next pointer for temp
        tempPrev->next = temp->next;
        //Sets the next pointer pointing to the prev for temp to the prev pointer for tempPrev
        temp->next->prev = tempPrev;
        //deletes the temp node
        delete temp;
    }
    //the push_back method
    void push_back(string v) {
        //creates the new node and sets it's value to v
        Node* newNode = new Node(v);
        //checks if list is empty
        if (!tail)
            //sets head equal to tail equal to newNode
            head = tail = newNode;
        else {
            //sets the next pointer for tail to newNode
            tail->next = newNode;
            //sets the prev pointer for newNode to tail
            newNode->prev = tail;
            //sets tail to newNode
            tail = newNode;
        }
    }
    //the push_front method
    void push_front(string v) {
        //creates the new node and sets it's value to v
        Node* newNode = new Node(v);
        //checks if list is empty
        if (!head)
            //sets head equal to tail equal to newNode
            head = tail = newNode;
        else {
            //sets the next pointer for newNode to head
            newNode->next = head;
            //sets the prev pointer for head to newNode
            head->prev = newNode;
            //sets head to newNode
            head = newNode;
        }
    }
    //the pop_front method
    void pop_front() {
        //checks if list is empty
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        //creates temp Node and sets it to head
        Node * temp = head;
        //checks if there is more than one val in the list
        if (head->next) {
            //sets head to the next pointer for head
            head = head->next;
            //sets the prev pointer for head to nullptr
            head->prev = nullptr;
        }
        else
            //sets the head equal to tail equal to nullptr
            head = tail = nullptr;
        //deletes temp node
        delete temp;
    }
    //the pop_back method
    void pop_back() {
        //checks if list is empty
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        //creates temp node and sets it to tail
        Node * temp = tail;
        //checks if there is more than one val in the list
        if (tail->prev) {
            //sets tail to the pointer prev for tail
            tail = tail->prev;
            //sets the next pointer for tail to nullptr
            tail->next = nullptr;
        }
        else
            //sets head equal to tail equal to nullptr
            head = tail = nullptr;
        //deletes temp node
        delete temp;
    }
    //the destructor for the DoublyLinkedList class
    ~DoublyLinkedList() {
        //Traverses the DoublyLinkedList
        while (head) {
            //creates temp node and sets it to head
            Node* temp = head;
            //sets head to the next pointer for head
            head = head->next;
            //deletes temp node
            delete temp;
        }
    }
    //the print method
    void print() {
        //creates current node and sets it to head
        Node* current = head;
        //checks if list is empty
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        //iterates through the list starting at the head
        while (current) {
            //prints nodes data
            cout << "       " << current->name << endl;
            //sets current to the next node
            current = current->next;
        }
    }
    //the print_reverse method
    void print_reverse() {
        //creates current node and sets it to tail
        Node* current = tail;
        //checks if list is empty
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        //iterates through the list starting at the tail
        while (current) {
            //prints nodes data
            cout << current->name << " ";
            //sets current to the prev node
            current = current->prev;
        }
        //end line
        cout << endl;
    }
    //the every_other_element methode
    void every_other_element() {
        //creates current node and sets it to head
        Node* current = head;
        //checks if list is empty
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            //prints nodes data
            cout << current->name << " ";
            //sets current to the next node
            current = current->next;
            //sets current to the next node
            current = current->next;
        }
        //end line
        cout << endl;
    }

    string returnHead() {return head->name;}
    string returnTail() {return tail->name;}
    string returnPos(int pos) {
        //Creates a temp node and sets it to head
        Node* temp = head;
        //for loop that iterates in till i = pos
        for (int i = 1; i < pos; i++){
            //checks if it reached the end of the list
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                //iterates to the next node
                temp = temp->next;
        }
        return temp->name;
    }
};
//the main function
int main() {
    int prob;
    int ran;
    DoublyLinkedList list;
    ifstream ifs;
    string name;
    vector<string> names;
    int count = 0;

    ifs.open("names.txt");

    if (ifs)
    {
        for (size_t i = 0; i < 99; i++)
        {
            getline(ifs, name);
            names.push_back(name);
        }
        ifs.close();
    }
    else
    {
        //prints and exits cause the file wasn't found
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Store opens:" << endl;
    for (size_t i = 0; i < 5; i++)
    {
        ran = rand() % 99;
        list.push_back(names[ran]);
        cout << "   " << names[ran] << " joins the line" << endl;
        count++;
    }
    cout << "Resulting line:" << endl;
    list.print();

    for (size_t i = 1; i < 20; i++)
    {
        cout << "Time step #" << i+1 << ":" << endl;
        prob = rand() % 100 + 1;

        if (prob <= 40)
        {
            cout << list.returnHead() << " is served" << endl;
            list.pop_front();
            count--;
        }

        if (prob <= 60)
        {
            ran = rand() % 99;
            list.push_back(names[ran]);
            cout << "   " << names[ran] << " joins the line" << endl;
            count++;
        }
        
        if (prob <= 20)
        {
            cout << list.returnTail() << " (at the rear) left the line" << endl;
            list.pop_back();
            count--;
        }
        
        if (prob <= 10)
        {
            ran = rand() % count + 1;
            cout << list.returnPos(ran) << " left the line" << endl;
            list.delete_pos(ran);
            count--;
        }

        if (prob <= 10)
        {
            ran = rand() % 99;
            list.push_back(names[ran]);
            cout << "   " << names[ran] << " (VIP) joins the line" << endl;
            count++;
        }
    }
    
    //returns 0
    return 0;
}