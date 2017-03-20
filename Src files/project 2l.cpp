// project 2l.cpp : main project file.


    #include"stdafx.h"
#include <iostream>

using namespace std;
struct nodeType
{
    int info;
    nodeType *link;
};

void createList(nodeType*& first1, nodeType*& last1, nodeType*& first2, nodeType*& last2, int& length1, int& length2);
void printList(nodeType*& first);
void menu(nodeType*& first1);
void uniset(nodeType*& first1, nodeType*& last1, nodeType*& first2, nodeType*& last2, int& length1, int& length2);
void inter(nodeType*& first1, nodeType*& last1, nodeType*& first2, nodeType*& last2, int& length1, int& length2);
void difference(nodeType*& first1, nodeType*& last1, nodeType*& first2, nodeType*& last2, int& length1, int& length2);

int main()
{
     nodeType *first1, *last1, *first2, *last2;
     char answer;
     int length1 = 0;
	 int length2 = 0;
     while(answer != 'q')
    {
                 
    menu(first1);
    cin >> answer;
    
    switch (answer)
    {
           case 'c':
           case 'C': createList(first1, last1, first2, last2, length1, length2);
                     break;
           case 'p':
           case 'P': cout << "Printing Linked list 1" << endl;
                     printList(first1);
                     cout << "Printing Linked list 2" << endl;
                     printList(first2);
                   break;
           case 'u':
           case 'U': uniset(first1, last1, first2, last2, length1, length2);
                     break;
           case 'i':
           case 'I': inter(first1, last1, first2, last2, length1, length2);
                    break;
           case 'd':
           case 'D': difference(first1, last1, first2, last2, length1, length2);
                    break;
    }
}
    system("PAUSE");
    return 0;
}
void createList(nodeType*& first1, nodeType*& last1, nodeType*& first2, nodeType*& last2, int& length1, int& length2)
{
    int number;
    nodeType *newNode;
    
    first1 = NULL;
    last1 = NULL;
    
    cout<<"Enter # for set/linked list #1 (-999 to stop): ";
    cin>>number;
	
    cout<<endl;
    
     while (number != -999)
     {
         newNode = new nodeType; // create new node
         newNode->info = number;
         newNode->link = NULL;
			length1++;
         if (first1 == NULL)
         {
            first1 = newNode;
            last1 = newNode;
         }
         else
         {
           last1->link = newNode;
           last1 = newNode;
		   //length++;
         }
         cout<<"Enter # for set/linked list #1 (-999 to stop): ";
         cin>>number;
		 
         cout<<endl;
     } // end of while-loop
        
        first2 = NULL;
        last2 = NULL;
        
        cout<<"Enter # for set/linked list #2 (-999 to stop): ";
    cin>>number;
	
    cout<<endl;
    
     while (number != -999)
     {
         newNode = new nodeType; // create new node
         newNode->info = number;
         newNode->link = NULL;
			length2++;
         if (first2 == NULL)
         {
            first2 = newNode;
            last2 = newNode;
         }
         else
         {
           last2->link = newNode;
           last2 = newNode;
		  // length++;
         }
         cout<<"Enter # for set/linked list #2 (-999 to stop): ";
         cin>>number;
		 
         cout<<endl;
     } // end of while-loop
	// cout << length << endl;
} // end of build list function

void printList(nodeType*& first)
{

  //  cout<<"Inside printList...printing linked list...\n"<<endl;
        nodeType *current;
        current = first;    
        while (current != NULL)
        {
          cout << current->info<<endl;
          current = current->link;
        }

}   

void menu(nodeType*& first1)
{
     cout << "Choose what you would like to do." << endl;
     cout << "p - display both sets/linked list" << endl;
     cout << "U - Display the union of sets/linked list" << endl;
     cout << "I - display the intersection of sets/linked list" <<endl;
     cout << "d - display the deference of sets/linked list" <<endl;
     cout << "c - change #'s in the 2 sets/linked list" <<endl;
     cout << "q - to exit" << endl;
}

void uniset(nodeType*& first1, nodeType*& last1, nodeType*& first2, nodeType*& last2, int& length1, int& length2)
{
     bool found = false;
     nodeType *current1;
     nodeType *current2;
     nodeType *newnode;
     nodeType *f;
     nodeType *l;
     nodeType *current3;
     int length = length1 + length2;
     
     current1 = first1;
     current2 = first2;
     f = NULL;
     l = NULL;
     
     while (current1 != NULL)
     { // 1
           newnode = new nodeType;
           newnode -> info = current1 -> info;
           newnode -> link = NULL;
           if (f == NULL)
           { //2
           f = newnode;
           l = newnode;
           } // 1
           else
           { //3
               l -> link = newnode;
               l = newnode;
           } //2
           
           current1 = current1 -> link;
     } //3
     
     while(current2 != NULL)
     { //4
           newnode = new nodeType;
           newnode -> info = current2 -> info;
           newnode -> link = NULL;
           current1 = first1;

           if (found == false)
           { // 5
           if (f == NULL)
           { //6
           f = newnode;
           l = newnode;
           } //4
           else
           { //7
               l -> link = newnode;
               l = newnode;
               
           } //5
           current2 = current2 -> link;
           } //6
            // second while
     } // 7
	
		current3 = f;
		for (int b = 0; b < length; b++)
		{ // 8
			current1 = first1;
			current2 = first2;
			for(int t = 0; t < length1; t++)
			{ // 9
				//while(current1 != NULL)
			//	{ // 10
				if (current1 -> info == current3 -> info)
				{ // 11
					t = length1;
				} // 8
				else
				{
					//t++;
					current1 = current1 -> link;
				}
			//} // 9
			}
				for(int y = 0; y < length2; y++)
			{ // 12
			//	while(current2 != NULL)
			//	{ //13
				if (current2 -> info == current3 -> info)
				{ // 14
					y = length2;
				} // 10
				else
				{ 
				//	y++;
					current2 = current2 -> link;
				}
			//	} // 11
			} // 12
			if (current3 -> info == current1 -> info)
			{
			//	b++;
			current3 = current3 -> link;
			}
			else if (current2 -> info == current3 -> info)
			{
			current3 = current3 -> link;
			}
			else 
			{ // 15
           cout << current3 -> info << endl;
           current3 = current3 -> link;
			} // 13
		} // 14
}

void inter(nodeType*& first1, nodeType*& last1, nodeType*& first2, nodeType*& last2, int& length1, int& length2)
{
     nodeType *current1;
     nodeType *current2;
     nodeType *f;
     nodeType *l;
     nodeType *newnode;
     nodeType *current3;
	 bool found = false;
     int length = length1 + length2;
	 //nodeType *current;

     f = NULL;
     l = NULL;
     current1 = first1;
     current2 = first2;
     
     cout << "entering" << endl;
     
    

           /*if(current1 == last1)
           {
                       current1 = first1;
                       current2 = current2 -> link;
           }*/
           while (current1 != NULL)
     { // 1
           newnode = new nodeType;
           newnode -> info = current1 -> info;
           newnode -> link = NULL;
           if (f == NULL)
           { //2
           f = newnode;
           l = newnode;
           } // 1
           else
           { //3 
               l -> link = newnode;
               l = newnode;
           } //2
           
           current1 = current1 -> link;
     } //3
     
     while(current2 != NULL)
     { //4
           newnode = new nodeType;
           newnode -> info = current2 -> info;
           newnode -> link = NULL;
           current1 = first1;

           if (found == false)
           { // 5
           if (f == NULL)
           { //6
           f = newnode;
           l = newnode;
           } //4
           else
           { //7
               l -> link = newnode;
               l = newnode;
               
           } //5
           current2 = current2 -> link;
           } //6
            // second while
     } // 7
           

		   //current = f;
		  current3 = f;
		for (int b = 0; b < length; b++)
		{ // 8
			current1 = first1;
			current2 = first2;
			//cout << "finish" << endl;
			for(int t = 0; t < length1; t++)
			{ // 9
				//while(current1 != NULL)
				//{ // 10
				if (current1 -> info == current3 -> info)
				{ // 11
					t = length1;
				} // 8
				else
				{
					current1 = current1 -> link;
				}
		//	} // 9
			}
				for(int y = 0; y < length2; y++)
			{ // 12
			//	while(current1 != NULL)
			//	{ //13
				if (current2 -> info == current3 -> info )
				{ // 14
					y = length2;
				} // 10
				else
				{
					current2 = current2 -> link;
				}
			//	} // 11
			} // 12
			if (current3 -> info  == current1 -> info)
			{
				 cout << current3 -> info << endl;
			current3 = current3 -> link;
			}
			else if (current2 -> info == current3 -> info)
			{
				 cout << current3 -> info << endl;
			current3 = current3 -> link;
			}
			/*else if(current3->info==current3->link->info)
			{
				delete current3;
					current3 = current3->link;
			}*/
			else
			{
           current3 = current3 -> link;
			} // 13
		} // 14
           
       
}

void difference(nodeType*& first1, nodeType*& last1, nodeType*& first2, nodeType*& last2, int& length1, int& length2)
{

	bool found = false;
     nodeType *current1;
     nodeType *current2;
     nodeType *newnode;
     nodeType *f;
     nodeType *l;
     nodeType *current3;
     int length = length1 + length2;
     
     current1 = first1;
     current2 = first2;
     f = NULL;
     l = NULL;
     
     for(int c = 0; c < length; c++)
	 {
		 current2 = first2;
		
		 for(int i = 0; i < length2; i++)
		 {
			 if (current1 -> info == current2 -> info)
			 i = length2;
			 else
				 current2 = current2 -> link;
		 }
		 
		 if (current1 -> info != current2 -> info)
		 {
			 newnode = new nodeType;
           newnode -> info = current1 -> info;
           newnode -> link = NULL;
           if (f == NULL)
           { //2
           f = newnode;
           l = newnode;
           } // 1
           else
           { //3 
               l -> link = newnode;
               l = newnode;
           } //2
           
           current1 = current1 -> link;
     } //3
	 else
		 current1 = current1 -> link;
	 }
	 
     current3 = f;

	 while (current3 != NULL)
	 {
		 cout << current3 -> info << endl;
		 current3 = current3 -> link;
	 }
	
}