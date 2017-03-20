// project 3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

ifstream infile;
ofstream outfile;

#include "project 3.h"




void read(linkedstacktype& stack, linkedstacktype& vowelstack);
void vowels(linkedstacktype vowelstack);
void print(linkedstacktype stack);

int main()
{
	infile.open ("project 3.txt");
	outfile.open("project 3 out.txt");

	linkedstacktype stack;
	linkedstacktype stack2;
	linkedstacktype vowelstack;

	read(stack, vowelstack);
	vowels(vowelstack);

	print(stack);
	system("pause");
	return 0;
}

void read(linkedstacktype& stack, linkedstacktype& vowelstack)
{
	char words;
	

	while(!infile.eof())
	{
		infile >> words;

		if (words == 'a' || words == 'A')
			vowelstack.push(words);
		else if (words == 'e' || words == 'E')
			vowelstack.push(words);
		else if (words == 'i' || words == 'I')
			vowelstack.push(words);
		else if (words == 'o' || words == 'O')
			vowelstack.push(words);
		else if (words == 'u' || words == 'U')
			vowelstack.push(words);
	
		stack.push(words);
	}
}
void vowels(linkedstacktype vowelstack)
{
	int vowel1 = 0;
	int vowel2 = 0;
	int vowel3 = 0;
	int vowel4 = 0;
	int vowel5 = 0;

	while (!vowelstack.isemptystack())
	{
		//vowelstack.top();
		if (vowelstack.top() == 'a' || vowelstack.top() == 'A')
			vowel1++;
		else if (vowelstack.top() == 'e' || vowelstack.top() == 'E')
			vowel2++;
		else if (vowelstack.top() == 'i' || vowelstack.top() == 'I')
			vowel3++;
		else if (vowelstack.top() == 'o' || vowelstack.top() == 'O')
			vowel4++;
		else if (vowelstack.top() == 'u' || vowelstack.top() == 'U')
			vowel5++;

		vowelstack.pop();
	}
		cout << "There are "<< vowel1 << " a's in the file" << endl;
	cout << "There are "<< vowel2 << " e's in the file" << endl;
	cout << "There are "<< vowel3 << " i's in the file" << endl;
	cout << "There are "<< vowel4 << " o's in the file" << endl;
	cout << "There are "<< vowel5 << " u's in the file" << endl;
}
void print(linkedstacktype stack)
{
	int count = 0;

	while(!stack.isemptystack())
	{
		count++;
		outfile << stack.top();
		if(count == 20)
			outfile << endl;
		stack.pop();
		
		if (count >= 20)
			count = 0;
	}
}
