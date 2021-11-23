#include <iostream>
#include <assert.h>
#include "pq.h"
using namespace std;

void test_default_constructor()
{
    MinPriorityQueue<int> mpqD;
    assert(mpqD.heapSize == 0);
    assert(mpqD.capacity == 100);
    MinPriorityQueue<int> mpq1(5);
    assert(mpq1.heapSize == 0);
    assert(mpq1.capacity == 5);
    cout << "Default Constructor Passed" << endl;
}

void test_insert()
{
    MinPriorityQueue<int> mpq1(5);
    int num1 = 8;
    try
    {
        mpq1.insert(&num1);
    }
    catch (FullError e)
    {
        cout << "Full Error" << endl;
    }

    int num2 = 1;
    try
    {
        mpq1.insert(&num2);
    }
    catch (FullError e)
    {
        cout << "Full Error" << endl;
    }

    int num3 = 4;
    try
    {
        mpq1.insert(&num3);
    }
    catch (FullError e)
    {
        cout << "Full Error" << endl;
    }

    int num4 = 3;
    try
    {
        mpq1.insert(&num4);
    }
    catch (FullError e)
    {
        cout << "Full Error" << endl;
    }

    int num5 = 5;
    try
    {
        mpq1.insert(&num5);
    }
    catch (FullError e)
    {
        cout << "Full Error" << endl;
    }
    assert(mpq1.toString() == "[1, 3, 4, 8, 5]");
    cout << "Insert Passed" << endl;
}

void test_copy_constructor()
{
    MinPriorityQueue<int> mpq1(5);
    int num1 = 8;
    int num2 = 1;
    int num3 = 4;
    int num4 = 3;
    int num5 = 5;
    mpq1.insert(&num1);
    mpq1.insert(&num2);
    mpq1.insert(&num3);
    mpq1.insert(&num4);
    mpq1.insert(&num5);

    MinPriorityQueue<int> mpq3(mpq1);
    assert(mpq3.toString() == mpq1.toString());
    cout << "Copy Constructor Passed" << endl;
}

void test_minimum()
{
    MinPriorityQueue<int> mpq1(5);
    int num1 = 8;
    int num2 = 1;
    int num3 = 4;
    int num4 = 3;
    int num5 = 5;
    mpq1.insert(&num1);
    mpq1.insert(&num2);
    mpq1.insert(&num3);
    mpq1.insert(&num4);
    mpq1.insert(&num5);

    try
    {
        mpq1.minimum();
    }
    catch (EmptyError e)
    {
        cout << "Empty Error" << endl;
    }
    assert(*(mpq1.minimum()) == 1);
    cout << "Minimum Passed" << endl;
}

void test_extractMin()
{
    MinPriorityQueue<int> mpq1(5);
    int num1 = 8;
    int num2 = 1;
    int num3 = 4;
    int num4 = 3;
    int num5 = 5;
    mpq1.insert(&num1);
    mpq1.insert(&num2);
    mpq1.insert(&num3);
    mpq1.insert(&num4);
    mpq1.insert(&num5);

    try
    {
        int *val = mpq1.extractMin();
        assert(*(val) == 1);
    }
    catch (EmptyError e)
    {
        cout << "Empty Error" << endl;
    }
    cout << "extractMin Passed" << endl;
}

void test_decreaseKey()
{
    MinPriorityQueue<int> mpq1(5);
    int num1 = 8;
    int num2 = 1;
    int num3 = 4;
    int num4 = 3;
    int num5 = 5;
    mpq1.insert(&num1);
    mpq1.insert(&num2);
    mpq1.insert(&num3);
    mpq1.insert(&num4);
    mpq1.insert(&num5);

    int newKey = 2;

    try
    {
        mpq1.decreaseKey(0, &newKey);
    }
    catch (KeyError e)
    {
        cout << "Key Error" << endl;
    }
    assert(*(mpq1.A[0]) == 2);
    cout << "decreaseKey Passed" << endl;
}

void test_length()
{
    MinPriorityQueue<int> mpq1(5);
    int num1 = 8;
    int num2 = 1;
    int num3 = 4;
    int num4 = 3;
    int num5 = 5;
    mpq1.insert(&num1);
    mpq1.insert(&num2);
    mpq1.insert(&num3);
    mpq1.insert(&num4);
    mpq1.insert(&num5);

    int lengthVal = mpq1.length();
    assert(lengthVal == mpq1.heapSize);
    cout << "length Passed" << endl;
}

void test_empty()
{
    MinPriorityQueue<int> mpq1(5);
    int num1 = 8;
    int num2 = 1;
    int num3 = 4;
    int num4 = 3;
    int num5 = 5;
    mpq1.insert(&num1);
    mpq1.insert(&num2);
    mpq1.insert(&num3);
    mpq1.insert(&num4);
    mpq1.insert(&num5);

    bool isEmpty1 = mpq1.empty();
    assert(isEmpty1 == false);

    MinPriorityQueue<int> mpq2(3);

    bool isEmpty2 = mpq2.empty();
    assert(isEmpty2 == true);

    cout << "empty Passed" << endl;
}

int main()
{
    test_default_constructor();
    test_copy_constructor();
    test_insert();
    test_minimum();
    test_extractMin();
    test_decreaseKey();
    test_length();
    test_empty();
}