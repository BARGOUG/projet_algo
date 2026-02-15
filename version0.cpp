#include <iostream>
#include <string>
#include <vector>

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

struct Scheme{
    string id;
    string abstract_scheme;
    string rule;
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
    void verification_morphology(string root, string derived_word) {
        //decompose the dervied word into single characters
    vector<string> decomposed_word;
    for (size_t i = 0; i < derived_word.size();) {
         char c = derived_word[i];
        size_t charLength = 1;
        decomposed_word.push_back(derived_word.substr(i, charLength));
        i += charLength;
    }

    for (const auto& letter : decomposed_word) {
        cout << letter << endl;
    }
}
};





















void verification_morphology(string root, string derived_word) {

    // 1️⃣ Decompose root
    vector<string> root_letters;
    for (size_t i = 0; i < root.size(); i += 2) {
        root_letters.push_back(root.substr(i, 2));
    }

    // 2️⃣ Decompose derived word
    vector<string> decomposed_word;
    for (size_t i = 0; i < derived_word.size();) {
        size_t charLength = 2;  // assuming Arabic UTF-8 2 bytes
        decomposed_word.push_back(derived_word.substr(i, charLength));
        i += charLength;
    }

    // 3️⃣ Extract scheme
    vector<string> scheme;

    for (const auto& letter : decomposed_word) {

        if (letter == root_letters[0])
            scheme.push_back("ف");
        else if (letter == root_letters[1])
            scheme.push_back("ع");
        else if (letter == root_letters[2])
            scheme.push_back("ل");
        else
            scheme.push_back(letter);
    }

    // 4️⃣ Print scheme
    cout << "Scheme: ";
    for (const auto& s : scheme)
        cout << s;

    cout << endl;
};

int main() {
     
    verification_morphology("كتب","مكتوب");

     return 0;
};







