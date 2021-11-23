#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>

class Store
{
private:
    vector<pair<char, T>> v;

public:
    int size();
    void set(char key, T val);
    char keyOfIndex(int index);
    char keyOfValue(T val);
    bool containValue(T val);
    bool containKey(char key);
    void changeValue(char key, T val);
    T operator[](int i);
    T valueOfKey(char key);
    string toHeader();
};

class Key_Store_Error
{
};
class Value_Store_Error
{
};

#include "store.cpp"
#endif