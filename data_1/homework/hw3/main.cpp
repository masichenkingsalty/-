#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <fstream>
using namespace std;

struct HuffmanNode {
    char data;
    int weight;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode(char c, int w) : data(c), weight(w), left(NULL), right(NULL) {}
};

struct CompareHuffmanNode {
    bool operator()(const HuffmanNode *a, const HuffmanNode *b) const {
        return a->weight > b->weight;
    }
};

map<char, int> calculate_frequencies(string text) {
    map<char, int> freq;
    for (int i = 0; i < text.size(); i++) {
        char c = text[i];
        if (freq.find(c) == freq.end()) {
            freq[c] = 1;
        } else {
            freq[c]++;
        }
    }
    return freq;
}

HuffmanNode *build_huffman_tree(map<char, int> freq) {
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareHuffmanNode> pq;
    for (map<char, int>::iterator it = freq.begin(); it != freq.end(); it++) {
        HuffmanNode *n = new HuffmanNode(it->first, it->second);
        pq.push(n);
    }
    while (pq.size() > 1) {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();
        HuffmanNode *parent = new HuffmanNode('-', left->weight + right->weight);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}

void generate_huffman_codes_helper(HuffmanNode *root, string code, map<char, string> &codes) {
    if (!root) {
        return;
    }
    if (root->data != '-') {
        codes[root->data] = code;
    }
    generate_huffman_codes_helper(root->left, code + "0", codes);
    generate_huffman_codes_helper(root->right, code + "1", codes);
}

map<char, string> generate_huffman_codes(HuffmanNode *root) {
    map<char, string> codes;
    generate_huffman_codes_helper(root, "", codes);
    return codes;
}

void print_character_statistics(map<char, int> freq) {
    cout << "Character statistics:" << endl;
    for (map<char, int>::iterator it = freq.begin(); it != freq.end(); it++) {
        if (it->first == ' ') {
            cout << "Space: ";
        } else if (it->first == '\n') {
            cout << "Newline: ";
        } else if (it->first == '\t') {
            cout << "Tab: ";
        } else {
            cout << it->first << ": ";
        }
        cout << it->second << endl;
    }
}

int main() {
    ifstream file("dream.txt");
    string text ((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>())); // 将文件内容保存到string中
    map<char, int> freq = calculate_frequencies(text);
    print_character_statistics(freq);
    HuffmanNode *root = build_huffman_tree(freq);
    map<char, string> codes = generate_huffman_codes(root);
    for (map<char, string>::iterator it = codes.begin(); it != codes.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }
    return 0;
}
