// Author: Michael Tarasov
// CIS 3100 BMWA Fall 2022

#include "Header.h"
#include <iostream>
#include <fstream>

using namespace std;

const int MAXFILENAMELENGTH = 50;
const int MAXPHRASELENGTH = 5;

ifstream openInput()
{
    char filename[MAXFILENAMELENGTH];
    ifstream file;
    do
    {
        cout << "Enter the source data file name: ";
        cin >> filename;
        file.open(filename);
    }
    while (!file.is_open())
        ;
    return file;
}

int getPhraseLength()
{
    int input;
    do
    {
        cout << "How many adjacent words are in a phrase, enter 1-5: ";
        cin >> input;
    } while (input < 1 || input > MAXPHRASELENGTH);
    return input;
}

ofstream openOutput()
{
    char filename[MAXFILENAMELENGTH];
    ofstream file;
    cout << "Enter the phrase frequency file name: ";
    cin >> filename;
    file.open(filename);
    return file;
}

int main()
{
    ifstream speech = openInput();
    int phrase_length = getPhraseLength();
    ofstream results = openOutput();
    return 0;
}
