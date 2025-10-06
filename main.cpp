// COMSC-210 | Lab 19 | Keng C Chan
// IDE used: Visual Studio Code (VS Code)
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#
#include <string>
#include <iomanip>
using namespace std;

struct Node {
    float rating;
    string comment;
    Node *next;
};

//Movie Class
class Movie {
private:
    string title;
    Node*head;

public:
    Movie(const string& movieTitle);
    ~Movie();
};
// function prototypes
// addToHead() adds a new node with the given value to Head of list
// arguments: head pointer, float rating, string comment
// returns: NA
void addToHead(Node *&head, float rating, string &comment);

// addToTail() adds a new node with the given value to Tail of list
// arguments: head pointer, float rating, string comment
// returns: NA
void addToTail(Node *&head, float rating, string &comment);

// displayReview() display the Review
// arguments: head pointer
// returns: NA
void displayReview(Node *head);

// deleteList() delete all node in the linked list
// arguments: head pointer
// returns: NA
void deleteList(Node *&head);

int main() {
    Node *head = nullptr;
    int choice;

    cout << "Which linked list method should we use?\n";
    cout << "    [1] New nodes are added at the head of the linked list\n";
    cout << "    [2] New nodes are added at the tail of the linked list\n";
    cout << "    Choice: ";
    cin >> choice;
    cin.ignore();

    char again = 'y';
    while (again == 'y' || again == 'Y'){
        float rating;
        string comment;
        cout << "Enter Review Rating (0-5): ";
        cin >> rating;
        cin.ignore();
        cout << "Enter Review Comments: ";
        getline(cin, comment);

        if (choice == 1){
            addToHead(head, rating, comment);
        }
        else {
            addToTail(head, rating, comment);
        }

        cout << "Enter another review? Y/N: ";
        cin >> again;
        cin.ignore();
    }
    cout << "Outputting all Reviews: \n";
    displayReview(head);
    
    deleteList(head);
    return 0;
}

void addToHead(Node *&head, float rating, string &comment){
    Node *newNode = new Node{rating, comment, head};
    head = newNode;
}

void addToTail(Node *&head, float rating, string &comment){
    Node *newNode = new Node{rating, comment, nullptr};
    if (!head){
        head = newNode;
        return;
    }
    Node *current = head;
    while (current->next){
        current = current->next;
    }
    current->next = newNode;
}

void displayReview(Node *head){
    if (!head) {
        cout << "Empty list.\n";
        return;
    }
    Node *current = head;

    int count = 0;
    float sum = 0;
    while (current) {
        cout << "    > Review #" << count << ": "
             << fixed << setprecision(1) 
             << current->rating << ": " 
             << current->comment << endl;
        sum += current->rating;
        current = current->next;
        count++;
    }
    if (count > 1) {
        cout << "    > Average: " << fixed << setprecision(5) 
             << (sum / (count - 1)) << endl;
    }
}

void deleteList(Node *&head){
    Node *current = head;
    while (current){
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}
