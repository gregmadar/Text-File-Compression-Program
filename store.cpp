#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
void Store<T>::set(char key, T val)
{
    pair<char, T> tmp(key, val);
    v.push_back(tmp);
}

template <class T>
T Store<T>::valueOfKey(char key)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first == key)
        {
            return v[i].second;
        }
    }
    throw Key_Store_Error();
}

template <class T>
char Store<T>::keyOfIndex(int index)
{
    return v[index].first;
}

template <class T>
char Store<T>::keyOfValue(T val)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].second == val)
        {
            return v[i].first;
        }
    }
    throw Value_Store_Error();
}

template <class T>
bool Store<T>::containValue(T val)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].second == val)
        {
            return true;
        }
    }
    return false;
}

template <class T>
bool Store<T>::containKey(char key)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first == key)
        {
            return true;
        }
    }
    return false;
}

template <class T>
void Store<T>::changeValue(char key, T val)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i].first == key)
        {
            v[i].second = val;
        }
    }
}

template <class T>
T Store<T>::operator[](int i)
{
    return v[i].second;
}

template <class T>
int Store<T>::size()
{
    return v.size();
}

template <class T>
string Store<T>::toHeader()
{
    std::stringstream ss;
    for (int i = 0; i < v.size(); i++)
    {
        string chr = string(1, v[i].first);
        ss << chr << v[i].second << ",";
    }
    ss << ",";
    return ss.str();
}