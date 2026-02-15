#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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

int main() {

    vector<string> roots;
    ifstream infile("roots.txt"); // open the file

    if (!infile) {
        cerr << "Error: Cannot open file!" << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        if (!line.empty()) {
            roots.push_back(line); // add each word to vector
        }
    }

    infile.close();
    cout << "Loaded Arabic roots:" << endl;
    for (const auto& word : roots) {
        cout << word << endl;
    }
     return 0;
};






