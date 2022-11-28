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
    } while (!file.is_open());
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
    file << "The file: " << filename << " contains ";
    return file;
}

MyString* parseSpeech(int phrase_length, ifstream &speech, int &phrase_count, int &word_count)
{
    MyString word;
    int maxphrasecount = 100;
    MyString* phrases = new MyString[maxphrasecount];
    while (speech >> word)
    {
        word.ToUpper();
        if (word.Length() > 0)
        {
            word_count++;
            if (word_count == maxphrasecount) {
                MyString* expansion = new MyString[maxphrasecount + 100];
                for (int i = 0; i < maxphrasecount; i++) {
                    expansion[i] = phrases[i];
                }
                delete[] phrases;
                phrases = expansion;
                maxphrasecount += 100;
            }
            for (int i = 0; i < phrase_length; i++)
            {
                int phrase_index = phrase_count - i;
                if (phrase_index >= 0)
                {
                    phrases[phrase_index] = phrases[phrase_index] + word;
                }
            }
            phrase_count++;
        }
    }
    speech.close();
    phrase_count = phrase_count - phrase_length + 1;
    return phrases;
}

void swap(MyString array[], int pos1, int pos2)
{
    MyString temp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = temp;
}

void sortArr(MyString array[], int start, int end)
{
    // sortArr is an adapted version of the quicksort algorithm described at https://www.geeksforgeeks.org/cpp-program-for-quicksort/
    if (end <= start)
    {
        return;
    }

    int pivotindex = start;
    for (int i = start + 1; i <= end; i++)
    {
        if (array[i] <= array[start])
        {
            pivotindex++;
        }
    }
    swap(array, start, pivotindex);
    {
        int i = start;
        int j = end;

        while (i < pivotindex)
        {
            while (array[i] <= array[pivotindex])
            {
                i++;
            }

            while (array[j] > array[pivotindex])
            {
                j--;
            }

            if (j > pivotindex && i < pivotindex)
            {
                swap(array, i, j);
            }
        }
    }

    sortArr(array, start, pivotindex - 1);
    sortArr(array, pivotindex + 1, end);
}

void countOccurences(MyString phrases[], int phrase_count, int &unique_phrase_count)
{
    for (int i = 0; i < phrase_count - 1; i++)
    {
        int incrementer = 1;
        if (phrases[i].Length() > 0)
        {
            while (phrases[i] == phrases[i + incrementer])
            {
                phrases[i]++;
                unique_phrase_count--;
                MyString empty;
                phrases[i + incrementer] = empty;
                incrementer++;
                if (i + incrementer >= phrase_count)
                {
                    break;
                }
            }
            i = i + incrementer - 1;
        }
    }
}

void outputResults(ofstream &file, MyString phrases[], int word_count, int phrase_count, int unique_phrase_count)
{

    file << word_count << " Words.\n";
    file << "There are " << unique_phrase_count << " unique terms.\n";
    file << '\n';
    for (int i = 0; i < phrase_count; i++)
    {
        if (phrases[i].Length() > 0)
        {
            file << phrases[i];
            file << '\n';
        }
    }
    file.close();
}

int main()
{
    ifstream speech = openInput();
    int phrase_length = getPhraseLength();
    ofstream results = openOutput();

    int phrase_count = 0;
    int word_count = 0;

    MyString* phrases = parseSpeech(phrase_length, speech, phrase_count, word_count);
    int unique_phrase_count = phrase_count;

    sortArr(phrases, 0, phrase_count - 1);

    countOccurences(phrases, phrase_count, unique_phrase_count);

    sortArr(phrases, 0, phrase_count - 1);

    outputResults(results, phrases, word_count, phrase_count, unique_phrase_count);

    return 0;
}
