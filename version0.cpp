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
     string apply_scheme(string root) {
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


int main() {
    // Define schemes
    Scheme s1 = {"مفعول", "mafʿūl", "Passive participle"};
    Scheme s2 = {"فاعل", "fāʿil", "Active participle"};
    Scheme s3 = {"تفعيل", "tafʿīl", "Causative"};
    Scheme s4 = {"تفعيل", "tafʿīl", "Causative"};
    Scheme s5 = {"افتعل", "iftala", "Causative"};

    
    // Apply to root "كتب" (k-t-b: to write)
    string root = "كتب";
    
    cout << s1.apply_scheme(root) << endl;  // مكتوب (written)
    cout << s2.apply_scheme(root) << endl;  // كاتب (writer)
    cout << s3.apply_scheme(root) << endl;  // تكتيب (causative)
    
    // Apply to root "درس" (d-r-s: to study)
    root = "درس";
    cout << s1.apply_scheme(root) << endl;  // مدروس (studied)
    cout << s2.apply_scheme(root) << endl;  // دارس (student)
    cout << s3.apply_scheme(root) << endl;  // تكتيب (causative)


    root = "خرط";
    cout << s1.apply_scheme(root) << endl;  // مدروس (studied)
    cout << s2.apply_scheme(root) << endl;  // دارس (student)
    cout << s3.apply_scheme(root) << endl;  // تكتيب (causative)
    
    return 0;
}







