#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Nodelof {
    friend class LOF;
public:
    int data;           // Data of the node
    Nodelof *next;      // Pointer to the next node

    // Constructor
    Nodelof(int d, Nodelof *n = nullptr) {
        data = d;
        next = n;
    };

    void printNodelof(){
        cout << data << " " << next << endl;
    }

    ~Nodelof(){};
};

class LOF {
    friend class Nodelof;
private:
    Nodelof *headlof;   //The Node
    int lenght = 0;
public:
    // Constructor
    LOF(Nodelof *head = nullptr) {
        headlof = head;
    }

    // Destructor
    ~LOF() {}

    Nodelof *gethead() {return (headlof);}
    int getcount() {return (lenght);}

    bool isEmpty() {return headlof == nullptr;}

    // Function to add a node to the front of the list
    void addNode(int d) {
        Nodelof* newNode = new Nodelof(d, headlof);
        headlof = newNode;
        lenght++;
    }

    //function to see if there is a node in the list with the data
    bool find(int d) {
        if (!isEmpty()) {
            Nodelof *current = headlof;
            while (current != nullptr) {
                if (current->data == d) {
                    return true;
                }
                current = current->next;
            }
        }
        return false;
    }
};


class Nodelow {
    friend class LOW;
public:
    string word;        //word
    Nodelof *headlof;    //Pointer to head of lof
    int count;          // Number of nodes in the lof
    Nodelow *nextlow;       //Pointer to next node of low

    // Constructor
    Nodelow(string wordf = " ", Nodelof *h = nullptr, int d = 0, Nodelow *n = nullptr) {
        word = wordf;
        headlof = h;
        count = d;
        nextlow = n;
    };

    ~Nodelow(){};
};

class LOW {
private:
    Nodelow* headlow;    // The Node
    int lenght;
public:
    //Constructor
    LOW(Nodelow *h = nullptr){
        headlow = h;
    }

    //Destructor
    ~LOW(){};

    Nodelow *gethead() {return (headlow);}

    bool isEmpty() {return (headlow == nullptr);}

    // Insert a new node at the head of the list
    void addNode(string Newword, Nodelof *h) {
        Nodelow *NewNode;

        NewNode = new Nodelow(Newword, h, lenght, headlow);
        headlow = NewNode;
    }

    // Search for a node with a given word and return its pointer
    Nodelow *search(string wordf) {
        Nodelow *curr = headlow;
        while (curr != nullptr) {
            if (curr->word == wordf) {
                return (curr);
            }
            curr = curr->nextlow;
        }
        return nullptr;
    }

    void printList() {
        Nodelow *current = headlow;
        while (current != nullptr) {
            cout << current->word << endl;
            cout << "LOF: ";
            Nodelof *currentLof = current->headlof;
            int x = 0;
            while (currentLof != nullptr) {
                cout << currentLof->data << " ";
                currentLof = currentLof->next;
                x++;
            }
            cout << endl;
            cout << "Count: " << x << endl;
            cout << endl;
            current = current->nextlow;
        }
    }
};

LOW low;

void process_file(int number) {
    //fix the name
    string filename = "input/" + to_string(number) + ".txt";
    // Open the file
    ifstream file(filename);

    // Check if the file is opened successfully
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // Process the file line by line
    string line;
    while (getline(file, line)) {
        // Create something like a 'string stream' to extract words from the line
        istringstream iss(line);

        // Process each word in the line
        string word;
        while (iss >> word) {
            int y = 0;
            // Check if the word is already in the LOW list
            Nodelow* current_low = low.gethead();
            int pos = 0;
            while (current_low != nullptr && current_low->word != word) {
                current_low = current_low->nextlow;
                pos++;
            }

            // If the word is not in the LOW list, add it to the head
            if (current_low == nullptr) {
                LOF lof;
                lof.addNode(number);
                low.addNode(word,lof.gethead());
                current_low = low.gethead();
            } else {

                // Get the LOF list of the word
                Nodelow* wordPtr = low.search(word);
                Nodelof* head_lof = wordPtr->headlof;

                // Add the file to the LOF list of the word if the file doesn't already exist
                LOF lof(head_lof);
                if (!lof.find(number)) {
                    lof.addNode(number);

                    // Update the headlof of the word in the LOW list
                    wordPtr->headlof = lof.gethead();
                }

            }
            y++;
            // Add the file to the LOF list of the word
            current_low->count++;
        }
    }

    // Close the file
    file.close();
}




int main() {
    int orderOfFiles[] = {26, 94, 22, 40, 43, 24, 87, 44, 31, 45, 6, 49, 14, 53, 58, 33, 74, 13, 19, 93, 55, 71, 39, 29, 10, 80, 86, 77, 79, 82, 9, 92, 17, 96, 50, 2, 65, 90, 89, 11, 57, 51, 68, 83, 66, 54, 27, 95, 48, 81, 70, 25, 4, 60, 21, 76, 75, 61, 15, 37, 30, 62, 34, 56, 88, 59, 1, 32, 3, 73, 78, 42, 16, 36, 7, 47, 12, 67, 85, 64, 28, 52, 84, 98, 69, 41, 63, 72, 46, 20, 18, 100, 97, 99, 23, 38, 35, 91, 8, 5};
    for (int i=0;i<=100;i++) {
        process_file(orderOfFiles[i]);
    }
    low.printList();
    string wordy;
    cout << "Give a word (EOF to exit): ";

    cin >> wordy;
    do {
        cout << "Give a word (EOF to exit): ";
        getline(cin, wordy);
        if (wordy != "EOF") {
            //search to find the word. search function returns the pointer.
            Nodelow *f = low.search(wordy);
            if (f != nullptr) {
                Nodelof *fk = f->headlof;
                //prints the data
                while (fk != nullptr) {
                    cout << fk->data << " ";
                    fk = fk->next;
                }
            } else {
                cout << "Word not found in any file." << endl;
            }
        }
        cout << endl;
    } while (wordy != "EOF");
    return 0;
}