// Secure Diary Manager in C++

// This program allows users to securely store and manage their personal diary entries.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Struct to represent a diary entry
struct DiaryEntry {
   string diaryTitle; // Title of the diary entry
   string entryContent; // Content of the diary entry
};

class SecureDiary {
private:
   vector<DiaryEntry> diaryEntries; // Vector to store diary entries
   const string filename = "diary.txt"; // File to store diary entries
   const string masterPassword = "1234"; // Master password for demo purposes

   // Function to encrypt diary entries
   string encrypt(string text) {
       // Shift each character by 1
       for (char& c : text) c += 1;
       return text;
   }

   // Function to decrypt diary entries
   string decrypt(string text) {
       // Shift each character back by 1
       for (char& c : text) c -= 1;
       return text;
   }

   // Load diary entries from file
   void loadEntries() {
       ifstream file(filename);
       if (!file.is_open()) return;
       string title, content;
       while (getline(file, title) && getline(file, content)) {
           DiaryEntry entry;
           entry.diaryTitle = decrypt(title);
           entry.entryContent = decrypt(content);
           diaryEntries.push_back(entry);
       }
       file.close();
   }

   // Save diary entries to file
   void saveEntries() {
       ofstream file(filename);
       for (const auto& entry : diaryEntries) {
           file << encrypt(entry.diaryTitle) << "\n" << encrypt(entry.entryContent) << "\n";
       }
       file.close();
   }

public:
   // Function to check master password
   bool login() {
       string input;
       cout << "Enter master password: ";
       cin >> input;
       return input == masterPassword;
   }

   // Function to add a new diary entry
   void addEntry() {
       DiaryEntry entry;
       cout << "Enter diary title: ";
       cin.ignore();
       getline(cin, entry.diaryTitle);
       cout << "Enter entry content: ";
       getline(cin, entry.entryContent);
       diaryEntries.push_back(entry);
       cout << "Entry added successfully!\n";
   }

   // Function to view all diary entries
   void viewEntries() const {
       cout << "\nDiary Entries:\n";
       for (const auto& entry : diaryEntries) {
           cout << "Title: " << entry.diaryTitle << "\nContent: " << entry.entryContent << "\n\n";
       }
   }

   // Function to search for a diary entry
   void searchEntry() const {
       string keyword;
       cout << "Enter keyword to search: ";
       cin >> keyword;
       bool found = false;
       for (const auto& entry : diaryEntries) {
           if (entry.diaryTitle.find(keyword) != string::npos || entry.entryContent.find(keyword) != string::npos) {
               cout << "Title: " << entry.diaryTitle << "\nContent: " << entry.entryContent << "\n\n";
               found = true;
           }
       }
       if (!found) cout << "No entries found.\n";
   }

   // Main menu function
   void menu() {
       loadEntries();
       int choice;
       do {
           cout << "\n--- Secure Diary Manager ---\n";
           cout << "1. Add Entry\n";
           cout << "2. View Entries\n";
           cout << "3. Search Entry\n";
           cout << "4. Exit\n";
           cout << "Choose an option: ";
           cin >> choice;
           switch (choice) {
           case 1:
               addEntry();
               break;
           case 2:
               viewEntries();
               break;
           case 3:
               searchEntry();
               break;
           case 4:
               saveEntries();
               break;
           default:
               cout << "Invalid option. Try again.\n";
           }
       } while (choice != 4);
   }
};

int main() {
   SecureDiary diary;
   if (diary.login()) {
       diary.menu();
   } else {
       cout << "Wrong password. Access denied.\n";
   }
   return 0;
}
