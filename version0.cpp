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

    // 1️⃣ Decompose root
    vector<string> root_letters;
    for (size_t i = 0; i < root.size(); i += 2) {
        root_letters.push_back(root.substr(i, 2));
    }

    // 2️⃣ Decompose derived word
    vector<string> decomposed_word;
    for (size_t i = 0; i < derived_word.size();) {
        size_t charLength = 2;  
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

    // 4️⃣ return scheme
    string scheme_s="";
    for (const auto& s : scheme)
        scheme_s+=s;
    cout<<(scheme_s) <<endl;
    return scheme_s;
};
bool compare(string original,string derived_word){
    string scheme =  verification_morphology(original,derived_word);
    string new_original = get_original(scheme,derived_word);
    return original==new_original;

};

int main() {
  // Pattern: فاعل
cout << compare("كتب", "كاتب");       // true
cout <<compare("جلس", "جالس");       // true
cout <<compare("لعب", "لاعب");       // true

// Pattern: مفعول
cout <<compare("كتب", "مكتوب");      // true
cout <<compare("شرب", "مشروب");      // true
cout <<compare("حفظ", "محفوظ");      // true

// Pattern: افتعل
cout <<compare("كتب", "اكتتب");      // true
cout <<compare("حفظ", "احتفظ");      // true

// Pattern: تفعيل
cout <<compare("علم", "تعليم");      // true
cout <<compare("نظم", "تنظيم");      // true
cout << compare("درس", "تدريس");      // true




     return 0;
};






