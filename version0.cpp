#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <list>
using namespace std;

// liste contenant les derivés d'une racine
struct Derived_words
{
    vector<string> derived_words_list;
    int frequence;
};
// Noeud d'une arbre
struct Node {
    string arabic_root;
    char letters[3];
    Derived_words* derived;
    Node* left;
    Node* right;
};
struct Arbre {
    Node* root;

    Arbre() { root = nullptr; }

    // Create a new node
    Node* create_node(const string& word) {
        Node* node = new Node;
        node->arabic_root = word;
        node->left = nullptr;
        node->right = nullptr;
        node->derived = new Derived_words;
        node->derived->frequence = 0;
        return node;
    }

    // Insert recursively (pointer by reference!)
    void insert(Node*& tree_root, const string& word) {
        if (tree_root == nullptr) {
            tree_root = create_node(word);
            return;
        }
        if (word < tree_root->arabic_root)
            insert(tree_root->left, word);
        else if (word > tree_root->arabic_root)
            insert(tree_root->right, word);
        // equal values: ignore or handle duplicates
    }

    // Fill tree from vector
    void fill_tree(const vector<string>& words) {
        for (const auto& w : words) {
            insert(root, w);
        }
    }

    // In-order traversal
    void display(Node* tree_root) {
        if (!tree_root) return;
        cout << tree_root->arabic_root << " ";
        display(tree_root->left);
        display(tree_root->right);
    }

    void display() {
        display(root);
        cout << endl;
    }
};

vector<string> load_roots_from_file(const string &filename)
{

    vector<string> roots;
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Error: Cannot open file.\n";
        return roots;
    }

    string line;
    while (getline(file, line))
    {
        if (!line.empty())
            roots.push_back(line);
    }

    file.close();
    return roots;
};

class Engine
{
public:
    vector<string> derived_word_generation(string root, vector<string> ids)
    {

        vector<string> results;

        for (const auto &id : ids)
        {
            results.push_back(derived_word_generation(root, id));
        }

        return results;
    }
    string derived_word_generation(string root, string id)
    {
        if (root.length() < 3)
            return "";

        string result = "";

        for (int i = 0; i < id.length(); i++)
        {
            char c = id[i];

            string ch = id.substr(i, 2); // Get 2-byte Arabic char

            if (ch == "ف")
            {
                result += root[0];
                result += root[1];
                i++; // Skip second byte
            }
            else if (ch == "ع")
            {
                result += root[2];
                result += root[3];
                i++; // Skip second byte
            }
            else if (ch == "ل")
            {
                result += root[4];
                result += root[5];
                i++; // Skip second byte
            }
            else
            {
                // Regular character or second byte already handled
                result += c;
            }
        }

        return result;
    }
};

// 5.gestion de dervie valides

string get_original(string scheme, string derived_word)
{
    string original = "";
    for (size_t i = 0; i < scheme.size(); i += 2)
    {
        if (scheme.substr(i, 2) == "ف" || scheme.substr(i, 2) == "ع" || scheme.substr(i, 2) == "ل")
        {
            original += derived_word.substr(i, 2);
        }
    }
    return original;
}

string get_scheme(string root, string derived_word)
{
    vector<string> root_letters;
    for (size_t i = 0; i < root.size(); i += 2)
    {
        root_letters.push_back(root.substr(i, 2));
    }

    vector<string> decomposed_word;
    for (size_t i = 0; i < derived_word.size();)
    {
        decomposed_word.push_back(derived_word.substr(i, 2));
        i += 2;
    }

    string scheme_s = "";
    size_t root_index = 0;

    for (const auto &letter : decomposed_word)
    {
        if (root_index < 3 && letter == root_letters[root_index])
        {
            if (root_index == 0)
                scheme_s += "ف";
            else if (root_index == 1)
                scheme_s += "ع";
            else if (root_index == 2)
                scheme_s += "ل";

            root_index++; // move to next root letter
        }
        else
        {
            scheme_s += letter;
        }
    }
    return scheme_s;
}

bool compare(string original, string derived_word)
{
    string scheme = get_scheme(original, derived_word);
    string new_original = get_original(scheme, derived_word);
    return original == new_original;
};

struct MorphScheme
{
    string name;
    string description;
};

class MorphHashTable
{
private:
    static const int TABLE_SIZE = 31; // simple prime number
    list<MorphScheme> table[TABLE_SIZE];

    // Optimized hash function using DJB2
    int hashFunction(const string &key)
    {
        unsigned long hash = 5381;
        for (unsigned char c : key)
        {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % TABLE_SIZE;
    }

public:
    // Add a scheme
    void insert(const MorphScheme &scheme)
    {
        int index = hashFunction(scheme.name);
        // check duplicate
        for (auto &s : table[index])
        {
            if (s.name == scheme.name)
            {
                s.description = scheme.description; // modify existing
                return;
            }
        }
        table[index].push_back(scheme);
    }

    // Remove a scheme
    void remove(const string &name)
    {
        int index = hashFunction(name);
        table[index].remove_if([&](const MorphScheme &s)
                               { return s.name == name; });
    }

    // Find a scheme
    MorphScheme *find(const string &name)
    {
        int index = hashFunction(name);
        for (auto &s : table[index])
        {
            if (s.name == name)
                return &s;
        }
        return nullptr;
    }

    // Display all schemes
    void display()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            if (!table[i].empty())
            {
                cout << "Index " << i << ":\n";
                for (auto &s : table[i])
                {
                    cout << "  " << s.name << " -> " << s.description << "\n";
                }
            }
        }
    }
};

int main(){

    vector<string> words = load_roots_from_file("roots.txt");

    Arbre tree;
    tree.fill_tree(words);

    cout << "BST In-order:\n";
    tree.display();

    return 0;


};