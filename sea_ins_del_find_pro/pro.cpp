#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string source_file, your_word_for_search, your_inserted_text, the_whole_text_for_operations;
    int choice;

    cout << "Enter file name: ";
    cin >> source_file;

    cout << "Choose an option:\n1. Search for a word\n2. Delete a word\n3. Insert text next to a specific word\n";
    cin >> choice;
    cin.ignore();

    ifstream file(source_file);
    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    the_whole_text_for_operations = buffer.str();
    file.close();

    if (choice == 1) {
        cout << "Enter word to search: ";
        cin >> your_word_for_search;
        size_t pos = the_whole_text_for_operations.find(your_word_for_search);
        if (pos != string::npos) {
            cout << "Found \"" << your_word_for_search << "\" in the file." << endl;
        }
        else {
            cout << "Word not found." << endl;
        }
    }
    else if (choice == 2) {
        cout << "Enter word to delete: ";
        cin >> your_word_for_search;
        size_t pos;
        while ((pos = the_whole_text_for_operations.find(your_word_for_search)) != string::npos) {
            the_whole_text_for_operations.erase(pos, your_word_for_search.length());
        }
        ofstream outFile(source_file);
        outFile << the_whole_text_for_operations;
        outFile.close();
        cout << "Word deleted successfully." << endl;
    }
    else if (choice == 3) {
        cout << "Enter word to insert next to: ";
        cin >> your_word_for_search;
        cout << "Enter text to insert: ";
        cin.ignore();
        getline(cin, your_inserted_text);

        size_t pos = the_whole_text_for_operations.find(your_word_for_search);
        if (pos != string::npos) {
            the_whole_text_for_operations.insert(pos + your_word_for_search.length(), " " + your_inserted_text);
            ofstream outFile(source_file);
            outFile << the_whole_text_for_operations;
            outFile.close();
            cout << "Text inserted successfully." << endl;
        }
        else {
            cout << "Word not found." << endl;
        }
    }
    else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
