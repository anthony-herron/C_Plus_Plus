struct nodetype
{
       char info;
       nodetype *link;
};

class linkedstacktype
{
      public:
             linkedstacktype();		
             void pop();
             char top();
             void push(char n);
             bool isemptystack();
             bool isfullstack();
			 void reversestack(linkedstacktype& stack);
			
      private:
              nodetype *stacktop;
              
};
linkedstacktype::linkedstacktype()
{
                      stacktop = NULL;
                        
}

void linkedstacktype::pop()
{
     nodetype *temp;
     
	if(stacktop != NULL)
	{
                temp = stacktop;
                stacktop = stacktop -> link;
                delete temp;
     }
	else
		cout << "cannot remove from an empty stack." << endl;
}

char linkedstacktype::top()
{
        if(stacktop != NULL)
			return stacktop -> info;
			else 
			cout << "cannot view an empty stack." << endl;
}

void linkedstacktype::push(char newelement)
{
        nodetype *newnode;
        
        newnode = new nodetype;
        newnode -> info = newelement;
        newnode -> link = stacktop;
        stacktop = newnode;
		
}

bool linkedstacktype::isemptystack()
{
                return (stacktop == NULL);
           
               
}

bool linkedstacktype::isfullstack()
{
               
                return false;
               
}

void linkedstacktype::reversestack(linkedstacktype& stack2)
{
     
	while(stacktop != NULL)
	{                     
	stack2.push(top());
	pop();
	}
	
	 
	
}
