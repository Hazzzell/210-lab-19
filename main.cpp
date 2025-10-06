// COMSC-210 | Lab 19 | Keng C Chan
// IDE used: Visual Studio Code (VS Code)
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    float rating;
    string comment;
    Node *next;
};

// function prototypes
// addToHead() adds a new node with the given value to Head of list
// arguments: head pointer, float rating, const string comment
// returns: NA
void addToHead(Node *&head, float rating, const string &comment);

// addToTail() adds a new node with the given value to Tail of list
// arguments: head pointer, float rating, const string comment
// returns: NA
void addToTail(Node *&head, float rating, const string &comment);

// displayReview() display the Review
// arguments: head pointer
// returns: NA
void displayReview(Node *head);

// deleteList() delete all node in the linked list
// arguments: head pointer
// returns: NA
void deleteList(Node *&head);

// vector<string> readCommentsFromFile() reads the comment from file reviews.txt
// arguments: const string &filename
// returns: NA
vector<string> readCommentsFromFile(const string &filename);

//Movie Class
class Movie {
private:
    string title;
    Node*head;
public:
    Movie(const string& movieTitle) : title(movieTitle), head(nullptr) {}      //Constructor
    ~Movie(){deleteList(head);}                                                //Destructor
    void addReview(const string &comment);    //auto random rating
    void displayReviews() const;
    string getTitle() const {return title;}
};
//Movie Class Implementation
void Movie::addReview(const string &comment) {
    float rating = static_cast<float>(rand() % 41 + 10) / 10.0; //random 1.0-5.0
    addToHead(head, rating, comment);
}

void Movie::displayReviews() const {
    cout << "Movie: " << title << endl;
    displayReview(head);
}


int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<string> comments = readCommentsFromFile("reviews.txt");
    if (comments.empty()) {
        cout << "Error in review comments.\n";
        return 1;
    }
    vector<Movie> movies;
    movies.push_back(Movie("The Matrix"));
    movies.push_back(Movie("Inception"));
    movies.push_back(Movie("Interstellar"));
    movies.push_back(Movie("Parasite"));

    //Add at least 3 reviews per movie
    for (auto& movie : movies) {
        for (int i = 0; i < 3; ++i) {
            int idx = rand() % comments.size();
            movie.addReview(comments[idx]);
        }
    }

    //Display
    for (const auto& movie : movies) {
        movie.displayReviews();
    }

    return 0;
}

void addToHead(Node *&head, float rating, const string &comment){
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

vector<string> readCommentsFromFile(const string &filename) {
    vector<string> comments;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening file: " << filename << endl;
        return comments;
    }
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) comments.push_back(line);
    }
    fin.close();
    return comments;
}

