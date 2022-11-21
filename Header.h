#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

const int STRING_SIZE = 100;

class MyString
{
private:
	char strval[STRING_SIZE];
	int strln; // length of string value
	int frequency;

public:
	// constructors
	MyString() : strln(0), frequency(1)
	{
		strcpy(strval, "");
	}

	MyString(char s[]);
	// initialize string value to s
	MyString(const MyString &s)
	{
		strcpy(strval, s.strval);
		strln = s.strln;
		frequency = s.frequency;
	}

	// accessor functions/operators
	int Length() const
	{
		return strln;
	}

	bool isAcceptable(char c) // only accept alphanumeric characters
	{
		return (((c >= 48) && (c <= 57)) || ((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)));
	}

	void ToUpper()
	{
		int n = strln, m = 0;

		for (int i = 0; i < strln; i++)
		{

			if (isAcceptable(strval[i]))
			{
				strval[m] = toupper(strval[i]);
				m++;
			}
			else
				n--;
		}
		strln = n;
		strval[n] = '\0';
	}

	bool operator==(MyString s) const;
	bool operator>(MyString s) const;
	bool operator>=(MyString s) const;
	bool operator<(MyString s) const;
	bool operator<=(MyString s) const;
	MyString operator+(MyString s) const;
	MyString operator=(MyString s);
	MyString operator++(int)
	{
		frequency += 1;
		return *this;
	}

	char &operator[](int indx)
	{
		return strval[indx];
	}

	// file input/output functions
	friend ifstream &operator>>(ifstream &i, MyString &str);
	friend ofstream &operator<<(ofstream &o, MyString &str);
};

MyString::MyString(char c[])
{
	strcpy(strval, c);
	strln = strlen(c);
	frequency = 1;
}

bool MyString::operator==(MyString s) const
{
	return (strcmp(strval, s.strval) == 0);
}

bool MyString::operator>(MyString s) const
{
	if (frequency == s.frequency)
	{
		return (strcmp(strval, s.strval) > 0);
	}
	else
	{
		return (frequency < s.frequency);
	}
}

bool MyString::operator>=(MyString s) const
{
	if (frequency == s.frequency)
	{
		return (strcmp(strval, s.strval) >= 0);
	}
	else
	{
		return (frequency < s.frequency);
	}
}

bool MyString::operator<(MyString s) const
{
	if (frequency == s.frequency)
	{
		return (strcmp(strval, s.strval) < 0);
	}
	else
	{
		return (frequency > s.frequency);
	}
}

bool MyString::operator<=(MyString s) const
{
	if (frequency == s.frequency)
	{
		return (strcmp(strval, s.strval) <= 0);
	}
	else
	{
		return (frequency > s.frequency);
	}
}

MyString MyString::operator+(MyString s) const
{
	char str[STRING_SIZE];

	strcpy(str, this->strval);
	strcat(str, " ");
	strcat(str, s.strval);

	return MyString(str);
}

MyString MyString::operator=(MyString s)
{
	strcpy(strval, s.strval);
	strln = s.strln;
	frequency = s.frequency;
	return *this;
}

ifstream &operator>>(ifstream &i, MyString &str)
{
	i >> str.strval;
	str.strln = strlen(str.strval);
	return i;
}

ofstream &operator<<(ofstream &o, MyString &str)
{
	for (int i = 0; i < str.strln; i++)
		o << str.strval[i];
	for (int j = 0; j < 60 - str.strln; j++)
		o << ' ';
	if (str.frequency > 1)
		o << "\t" << str.frequency;
	return o;
}
#endif
