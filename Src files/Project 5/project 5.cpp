//Anthony Herron
//Project 5
//Dr. Stone
//This project takes a group of given numbers and put them into a binary tree. Next it will find out which of the numbers are leaves. Last it will output anything that could possibly be on the right or left of that number. It will not output a number that is in the tree. 

//#include "stdafx.h"
#include <iostream>

using namespace std;

#include "test.h"

int main()
{
    binarytreetype tree;
    
    tree.insert(25);
    tree.insert(38);
    tree.insert(17);
    tree.insert(35);
    tree.insert(12);
    tree.insert(21);
    tree.insert(42);
    tree.insert(8);
    tree.insert(14);
    

    cout << tree.possiblekids() << endl;
    
    system ("pause");
    return 0;
}

