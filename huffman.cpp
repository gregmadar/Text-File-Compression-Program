#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "pq.h"
#include "node.h"
#include "store.h"

using namespace std;

// Utility function to check if Huffman Tree contains only a single node
bool isLeaf(Node *root)
{
    return root->left == nullptr && root->right == nullptr;
}

Store<int> frequencyStore(string input)
{
    Store<int> store;
    stringstream s;
    ifstream inF(input);
    s << inF.rdbuf();
    string str = s.str();
    for (int i = 0; i < str.size(); i++)
    {
        char chr = str[i];
        if (store.containKey(chr))
        {
            int currFreq = store.valueOfKey(chr);
            store.changeValue(chr, currFreq + 1);
        }
        else
        {
            store.set(chr, 1);
        }
    }
    return store;
}

Store<string> storeCodes(Node *node, Store<string> store, string curr)
{
    if (node != nullptr)
    {
        if (isLeaf(node))
        {
            store.set(node->ch, curr);
            return store;
        }
        curr.push_back('0');
        store = storeCodes(node->left, store, curr);
        curr.pop_back();
        curr.push_back('1');
        store = storeCodes(node->right, store, curr);
    }
    return store;
}

Node *createHuffmantree(Store<int> store)
{
    int n = store.size();
    MinPriorityQueue<Node> pq;
    for (int i = 0; i < n; i++)
    {
        Node *tempNode = new Node;
        tempNode->ch = store.keyOfIndex(i);
        int *tempInt = new int(store[i]);
        tempNode->freq = tempInt;
        pq.insert(tempNode);
    }

    // do till there is more than one node in store
    for (int i = 0; i < store.size() - 1; i++)
    {
        // Remove the two nodes of the highest priority
        // (the lowest frequency) from the queue
        Node *tempNode = new Node;
        tempNode->left = pq.extractMin();
        tempNode->right = pq.extractMin();
        *(tempNode->freq) = *(tempNode->left->freq) + *(tempNode->right->freq);
        pq.insert(tempNode);
    }
    return pq.extractMin();
}

pair<string, int> encodeStrToBit(string encodedStr)
{
    stringstream bs;

    char b = 0;
    int count = 0;
    for (int i = 0; i < encodedStr.size(); i++)
    {
        if (encodedStr[i] == '0')
        {
            b = b << 1;
        }
        else if (encodedStr[i] == '1')
        {
            b = (b << 1) | 1;
        }
        count += 1;
        if (count == 8)
        {
            bs << b;
            b = 0;
            count = 0;
        }
    }

    b = b << (8 - count);
    bs << b;
    pair<string, int> result(bs.str(), 8 - count);
    return result;
}

string bitToEncodeStr(string bitStr)
{
    int count = 0;
    stringstream es;
    for (int i = 0; i < bitStr.size(); i++)
    {
        for (int count = 7; count > -1; count--)
        {
            if (bitStr[i] & (1 << count))
            {
                es << '1';
            }
            else
            {
                es << '0';
            }
        }
    }
    return es.str();
}

void encode(string input, string output, Store<string> store)
{

    // read input file
    ifstream inF(input);
    ofstream outF(output);
    stringstream s;
    s << inF.rdbuf();
    string inputString = s.str();

    // encode to string
    stringstream es;
    for (int i = 0; i < inputString.size(); i++)
    {
        char chr = inputString[i];
        string encodedChar = store.valueOfKey(chr);
        es << encodedChar;
    }
    string encodedString = es.str();

    // encode to bit
    pair<string, int> temp = encodeStrToBit(encodedString);
    string bits = temp.first;
    int pad = temp.second;

    outF << store.toHeader();

    // append padding bits
    outF << pad;

    // convert encoded string to bits
    outF << bits;
}

void decode(string input, string output)
{
    ifstream inF(input);
    ofstream outF(output);

    // read input file to text
    stringstream s;
    s << inF.rdbuf();
    string inputString = s.str();

    // get header
    stringstream hs;
    int i = 0;
    while (inputString[i] != ',' || inputString[i + 1] != ',')
    {
        const char temp = inputString[i];
        hs << temp;
        i++;
    }
    string hStr = hs.str();
    i = i + 2;

    // get padding
    int pad = inputString[i] - '0';
    i++;

    // get encoded string
    stringstream ds;
    while (i < inputString.size())
    {
        ds << inputString[i];
        i++;
    }
    string encodedBitStrString = ds.str();

    // parse header to store
    Store<string> store;
    int j = 0;
    while (j < hStr.size())
    {
        char ch = hStr[j];
        j++;
        stringstream val;
        while (j < hStr.size() && hStr[j] != ',')
        {
            val << hStr[j];
            j++;
        }
        j++;
        store.set(ch, val.str());
    }
    string encodedStr = bitToEncodeStr(encodedBitStrString);

    // depadding last bit
    encodedStr = encodedStr.substr(0, encodedStr.size() - pad);

    // decode by using store
    stringstream code;
    for (int i = 0; i < encodedStr.size(); i++)
    {
        code << encodedStr[i];
        if (store.containValue(code.str()))
        {
            outF << store.keyOfValue(code.str());
            code.str("");
        }
    }
}

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "-c") == 0)
    {
        Store<int> storeFreq = frequencyStore(argv[2]);
        Node *root = createHuffmantree(storeFreq);
        Store<string> storeHuffman;
        string curr;
        storeHuffman = storeCodes(root, storeHuffman, curr);
        encode(argv[2], argv[3], storeHuffman);
    }

    else if (strcmp(argv[1], "-d") == 0)
    {
        decode(argv[2], argv[3]);
    }
    else
    {
        cout << "Invalid command" << endl;
    }
    return 0;
}