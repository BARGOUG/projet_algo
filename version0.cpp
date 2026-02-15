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
        //decompose the dervied word into single characters
    vector<string> decomposed_word;
    for (size_t i = 0; i < derived_word.size();) {
         char c = derived_word[i];
        size_t charLength = 2;
        decomposed_word.push_back(derived_word.substr(i, charLength));
        i += charLength;
    }

    for (const auto& letter : decomposed_word) {
        cout << letter << endl;
    }
}


int main() {
     
    verification_morphology("ب","مكتوب");

     return 0;
};







