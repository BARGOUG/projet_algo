#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <list>
using namespace std;

struct Derived_words{
    vector <string> derived_wrods_list;
    int frequence;

};
struct Node {
    string arabic_root;
    char letters[3];
    Derived_words* derived;
    Node* left;
    Node* right;
};





class Engine{
     string derived_word_generation(string root,string id) {
        if (root.length() < 3) return "";
        
        string result = "";
        
        for (int i = 0; i < id.length(); i++) {
            // Check single byte (ASCII) or first byte of Arabic
            char c = id[i];
            
            // Check for Arabic letters by comparing substrings
            string ch = id.substr(i, 2);  // Get 2-byte Arabic char
            
            if (ch == "ف") {
                result += root[0];
                result += root[1];
                i++;  // Skip second byte
            }
            else if (ch == "ع") {
                result += root[2];
                result += root[3];
                i++;  // Skip second byte
            }
            else if (ch == "ل") {
                result += root[4];
                result += root[5];
                i++;  // Skip second byte
            }
            else {
                // Regular character or second byte already handled
                result += c;
            }
        }
        
        return result;
    }
};
string get_original(string scheme,string derived_word){
    string original= "";
    for(size_t i = 0; i < scheme.size(); i += 2){
        if(scheme.substr(i,2)=="ف" || scheme.substr(i,2)=="ع"  || scheme.substr(i,2)=="ل"){
            original+=derived_word.substr(i,2);
        }
    }
    return original;
}

string verification_morphology(string root, string derived_word) {
    vector<string> root_letters;
    for (size_t i = 0; i < root.size(); i += 2) {
        root_letters.push_back(root.substr(i, 2));
    }

    vector<string> decomposed_word;
    for (size_t i = 0; i < derived_word.size();) {
        decomposed_word.push_back(derived_word.substr(i, 2));
        i += 2;
    }

    string scheme_s = "";
    size_t root_index = 0;

    for (const auto& letter : decomposed_word) {
        if (root_index < 3 && letter == root_letters[root_index]) {
            if (root_index == 0) scheme_s += "ف";
            else if (root_index == 1) scheme_s += "ع";
            else if (root_index == 2) scheme_s += "ل";

            root_index++;  // move to next root letter
        }
        else {
            scheme_s += letter;
        }
    }
    return scheme_s;
}

bool compare(string original,string derived_word){
    string scheme =  verification_morphology(original,derived_word);
    string new_original = get_original(scheme,derived_word);
    return original==new_original;

};









struct MorphScheme {
    string name;         // e.g., "فاعل", "مفعول", "افتعل"
    string description;  // optional description
    // You can add a function pointer or lambda for transformation rule
    // For simplicity, we just store a string here
};

// ------------------ Hash Table ------------------
class MorphHashTable {
private:
    static const int TABLE_SIZE = 31; // simple prime number
    list<MorphScheme> table[TABLE_SIZE];

    // Simple hash function based on first character UTF-8 code
    int hashFunction(const string& key) {
        if (key.empty()) return 0;
        return (unsigned char)key[0] % TABLE_SIZE;
    }

public:
    // Add a scheme
    void insert(const MorphScheme& scheme) {
        int index = hashFunction(scheme.name);
        // check duplicate
        for (auto& s : table[index]) {
            if (s.name == scheme.name) {
                s.description = scheme.description; // modify existing
                return;
            }
        }
        table[index].push_back(scheme);
    }

    // Remove a scheme
    void remove(const string& name) {
        int index = hashFunction(name);
        table[index].remove_if([&](const MorphScheme& s){ return s.name == name; });
    }

    // Find a scheme
    MorphScheme* find(const string& name) {
        int index = hashFunction(name);
        for (auto& s : table[index]) {
            if (s.name == name) return &s;
        }
        return nullptr;
    }

    // Display all schemes
    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (!table[i].empty()) {
                cout << "Index " << i << ":\n";
                for (auto& s : table[i]) {
                    cout << "  " << s.name << " -> " << s.description << "\n";
                }
            }
        }
    }
};



int main() {
    MorphHashTable hashTable;

    // Insert schemes
    hashTable.insert({"فاعل", "active participle"});
    hashTable.insert({"مفعول", "passive participle"});
    hashTable.insert({"افتعل", "derived verb pattern"});
    hashTable.insert({"تفعيل", "causative or intensive pattern"});

    // Display all schemes
    cout << "All morphological schemes:\n";
    hashTable.display();

    // Find a scheme
    MorphScheme* scheme = hashTable.find("مفعول");
    if (scheme) {
        cout << "Found scheme: " << scheme->name << " -> " << scheme->description << "\n";
    }

    // Remove a scheme
    hashTable.remove("افتعل");
    cout << "After removing 'افتعل':\n";
    hashTable.display();

    return 0;
}





