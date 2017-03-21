struct binarytreenode
{
	int info;
	binarytreenode *llink;
	binarytreenode *rlink;
};

class binarytreetype
{
	public:
		binarytreetype();
		bool isempty();
		void inordertaversal();
		void preordertraversal();
		void postordertraversal();
		int treeheight();
		int treenodecount();
		int treeleavescount();
		void destroytree();
		void insert(int item);
		void deletenode(int item);
		int singleParent2();
		int possiblekids();

        
	protected:
		binarytreenode *root;

	private:
		void copytree(binarytreenode *copiedtreeroot, binarytreenode *othertreeroot);
		void inorder(binarytreenode *p);
		void preorder(binarytreenode *p);
		void postorder(binarytreenode *p);
		int height(binarytreenode *p);
		int max(int x, int y);
		int nodecount(binarytreenode *p);
		int leavescount(binarytreenode *p);
		void deletefromtree(binarytreenode *p);
		 int singleParent(binarytreenode *p);
		 int possiblechildren(binarytreenode *p, binarytreenode *first);

};

binarytreetype::binarytreetype()
{
	root = NULL;
}

bool binarytreetype::isempty()
{
	return (root == NULL);
}

void binarytreetype::inordertaversal()
{
	inorder(root);
}

void binarytreetype::preordertraversal()
{
	preorder(root);
}

void binarytreetype::postordertraversal()
{
	postorder(root);
}

int binarytreetype::treeheight()
{
	return height(root);
}

int binarytreetype::treenodecount()
{
	return nodecount(root);
}

int binarytreetype::treeleavescount()
{
	return leavescount(root);
}

void binarytreetype::inorder(binarytreenode *p)
{
	if (p != NULL)
	{
		inorder(p->llink);
		cout << p->info << " ";
		inorder(p->rlink);
	}
}

void binarytreetype::preorder(binarytreenode *p)
{
	if (p != NULL)
	{
		cout << p->info << " ";
		preorder(p->llink);
		preorder(p->rlink);
	}
}

void binarytreetype::postorder(binarytreenode *p)
{
	if (p != NULL)
	{
		postorder(p->llink);
		postorder(p->rlink);
		cout << p->info << " ";
	}
}

int binarytreetype::height(binarytreenode *p)
{
	if (p == NULL)
		return 0;
	else
		return 1 + max(height(p->llink), height(p->rlink));
}

int binarytreetype::max(int x, int y)
{
	if (x >= y)
		return x;
	else
		return y;
}

void binarytreetype::copytree(binarytreenode *copiedtreeroot, binarytreenode *othertreeroot)
{
	if (othertreeroot == NULL)
		copiedtreeroot = NULL;
	else
	{
		copiedtreeroot = new binarytreenode;
		copiedtreeroot -> info = othertreeroot -> info;
		copytree(copiedtreeroot -> llink, othertreeroot -> llink);
		copytree(copiedtreeroot -> rlink, othertreeroot -> rlink);
	}
}

void binarytreetype::insert(int item)
{
	binarytreenode *current;
	binarytreenode *trailcurrent;
	binarytreenode *newnode;

	newnode = new binarytreenode;

	if (newnode != NULL)
	{
		newnode->info = item;
		newnode->llink = NULL;
		newnode-> rlink = NULL;
	}

	if (root == NULL)
		root = newnode;

	else
	{
		current = root;
		while (current != NULL)
		{
			trailcurrent = current;
			if (current -> info == item)
			{
				cout << "The insert item is already in the list";
				cout << "duplicates are not allowed." << item << endl;
				return;
			}
			else if (current -> info > item)
				current = current -> llink;
			else
				current = current -> rlink;
		}
		if (trailcurrent -> info > item)
			trailcurrent -> llink = newnode;
		else
			trailcurrent -> rlink = newnode;
	}
}

void binarytreetype:: deletenode(int item)
{
	binarytreenode *current;
	binarytreenode *trailcurrent;
	bool found = false;

	if (root == NULL)
		cout << "cannot delete from the empty tree." << endl;
	else
	{
		current = root;
		trailcurrent = root;
		while (current != NULL && !found)
		{
			if (current->info == item)
				found = true;
			else
			{
				trailcurrent = current;

				if ( current -> info > item)
					current = current ->llink;
				else
					current = current ->rlink;
			}
		}

		if (current == NULL)
			cout << "the delete item is not in the tree." << endl;
		else if(found)
		{
			if (current == root)
				deletefromtree(root);
			else if (trailcurrent -> info > item)
				deletefromtree(trailcurrent -> llink);
			else
				deletefromtree(trailcurrent -> rlink);
		}
	}
}

void binarytreetype:: deletefromtree(binarytreenode *p)
{
	binarytreenode *current;
	binarytreenode *trailcurrent;
	binarytreenode *temp;

	if (p == NULL)
		cout << " Error: the node to be delete is NULL." << endl;
	else if (p -> llink == NULL && p -> rlink == NULL)
	{
		temp = p;
		p = NULL;
		delete temp;
	}
	else if (p->llink == NULL)
	{
		temp = p;
		p = temp -> rlink;
		delete temp;
	}
	else if (p-> rlink == NULL)
	{
		temp = p;
		p = temp -> llink;
		delete temp;
	}

	else
	{
		current = p ->llink;
		trailcurrent = NULL;

		while (current -> rlink != NULL)
		{
			trailcurrent = current;
			current = current -> llink;
		}

		p -> info = current -> info;

		if (trailcurrent == NULL)
			p -> llink = current -> llink;
		else 
			trailcurrent -> rlink = current -> llink;

		delete current;
	}
}

int binarytreetype::nodecount(binarytreenode *p)
{
	if (p == NULL)
		return 0;
	else 
		return 1 + nodecount(p -> llink) + nodecount (p -> rlink);
}

int binarytreetype::leavescount(binarytreenode *p)
{
	if (p == NULL)
		return 0;
	else if ((p -> llink == NULL) && (p -> rlink == NULL))
		return 1;
	else
		return leavescount(p -> llink) + leavescount(p -> rlink);
}
int binarytreetype::singleParent(binarytreenode *p)
{   
    int count=0;
	
		 if(p == NULL) 
      return 0;
  else if((p->llink == NULL) && (p->rlink == NULL)) 
      return 0;
      else if(p->llink == NULL && p->rlink != NULL ||  p->llink != NULL && p->rlink == NULL)
      return 1;
      else
   return 1 + singleParent(p->llink) + singleParent(p->rlink);
				
}

int binarytreetype::singleParent2()
{
    return singleParent(root);
}

int binarytreetype::possiblekids()
{
	binarytreenode *first = root;
	int count = 0;
    return possiblechildren(root, first);   
}

int binarytreetype::possiblechildren(binarytreenode *p, binarytreenode *first)
{
    
    int num1 = 0;
    int num2 = 0;
    bool found = false;

	binarytreenode *current1;
	current1 = first;
	binarytreenode *current2;
	current2 = first;

	if (p == NULL)
    return 0;
	 else if ((p -> llink == NULL) && (p -> rlink == NULL))   
	 {

		 num1 = p-> info;
		 num2 = p -> info;
		 
		   cout << "The left of " << num1 << ": ";
		   num1--;
		   while (num1 != -1)
		   {
           while ((current1 != NULL) && (current2 != NULL))
		   {
			   if(( num1 == current1 -> info) || (num1 == current2 -> info))
			   {
				   current1 = NULL;
				   current2 = NULL;
				   found = true;
			   }
			   else
			   {
			   current1 = current1 -> llink;
			   current2 = current2 -> rlink;
			   }
			   
		   }
		   if (found != true)
		   {
		   cout << num1 << " ";
			num1--;
			current1 = first;
		   current2 = first;
		   }
		   else
			   num1 = -1;
		   }
		   cout << endl;

		   current1 = first;
		   current2 = first;

		   cout << "The right of " << num2 << ": ";
		   num2++;
		   found = false;
		   while (num2 != 101)
		   {
           while ((current1 != NULL) && (current2 != NULL))
		   {
			   if(( num2 == current1 -> info) || (num2 == current2 -> info))
			   {
				   current1 = NULL;
				   current2 = NULL;
				   found = true;
			   }
			   else
			   {
			   current1 = current1 -> llink;
			   current2 = current2 -> rlink;
			   }
			   
		   }
		   if (found != true)
		   {
		   cout << num2 << " ";
			num2++;
			current1 = first;
		   current2 = first;
		   }
		   else
			   num2 = 101;
		   }
		   cout << endl;
		   cout << endl;   
	}
	else
	{		
	 return possiblechildren(p -> llink, first) + possiblechildren(p -> rlink, first);
        }

}
 

