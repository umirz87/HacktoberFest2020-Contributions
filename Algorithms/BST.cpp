#include<iostream>
using namespace std;

template <typename k, typename v>
struct TNode
{
k key;
v value;
TNode<k, v> *leftChild;
TNode<k, v> *rightChild;

};
template<typename k,typename v>
class BST
{
	TNode<k,v> * root;
public:
	BST()
	{
		root=nullptr;
	}
	TNode<k,v> * helper(TNode<k,v> * fromCopy)
	{
		if(fromCopy==nullptr)
			return nullptr;
		TNode<k,v> * temp=new TNode<k,v>();
		temp->key=fromCopy->key;
		temp->value=fromCopy->value;
		temp->leftChild=helper(fromCopy->leftChild);
		temp->rightChild=helper(fromCopy->rightChild);
		return temp;
	}
	BST(BST & obj)
	{
		this->root=helper(obj.root);
	}
	TNode<k,v> * NewNode(k key,v value)
	{
		TNode<k,v> * n=new TNode<k,v>();
		n->key=key;
		n->value=value;
		n->rightChild=n->leftChild=nullptr;
		return n;
	}
	TNode<k,v> * HelperInsert(TNode<k,v>*R,k key,v value)
	{
		if(R==nullptr)
			return NewNode(key,value);
		if(R->key>key)
			R->leftChild=HelperInsert(R->leftChild,key,value);
		else if(R->key<key)
		{
			R->rightChild=HelperInsert(R->rightChild,key,value);
		}
		else if(R->key==key)
		{
			return R;
		}
		return R;
	}
	void insert(k const key, v const value)
	{
		root=HelperInsert(this->root,key,value);
	}
	v * helpsearch(TNode<k,v>* R,k key)
	{
		int * ret;
		if(R==nullptr)
			return nullptr;
		if(R->key>key)
			ret=helpsearch(R->leftChild,key);
		else if(R->key<key)
		{
			ret=helpsearch(R->rightChild,key);
		}
		else if(R->key==key)
		{
			ret=&R->value;
			return ret;
		}
		return ret;
	}
	v* search(k key)
	{
		return helpsearch(this->root, key);
	}
	void helpInorder(TNode<k,v> * R)
	{
		if(R!=nullptr)
		{
			helpInorder(R->leftChild);
			cout<<R->key<<'\t';
			helpInorder(R->rightChild);
		}
	}
	void inorderPrintKeys()
	{
		helpInorder(this->root);
	}
	void helplength(TNode<k,v> * R,int &count)
	{
		
		if(R!=nullptr)
		{
			helplength(R->leftChild,count);
			count++;
			helplength(R->rightChild,count);
		}
	}
	int length()
	{
		int count=0;
		helplength(this->root,count);
		return count;
	}
	TNode<k,v>* min(TNode<k,v>* node)
     {
        TNode<k,v>* current = node;
        while (current && current->leftChild != NULL)
			current = current->leftChild;
 
        return current;
	 }
	TNode<k,v> * helpdelete(TNode<k,v>* R,k key)
	{
		if(R==nullptr)
			return R;
		if(key<R->key)
			R->leftChild=helpdelete(R->leftChild,key);
		else if(key>R->key)
			R->rightChild=helpdelete(R->rightChild,key);
		else
		{
			if(R->leftChild==nullptr)
			{
				TNode<k,v> * n=R->rightChild;
				delete R;
				return n;
			}
			else if(R->rightChild==nullptr)
			{
				TNode<k,v> * n=R->leftChild;
				delete R;
				return n;
			}
			TNode<k,v>* temp = min(R->rightChild);
            R->key = temp->key;
			R->rightChild = helpdelete(R->rightChild, temp->key);
    }
    return R;
	}
	void deleteKey(k key)
	{
		helpdelete(this->root,key);
	}
	~BST()
	{
		if(root!=nullptr)
		{
			delete [] root;
		}
	}
};
void main()
{
BST<int, int> tree; //the key and value both are of type int
tree.insert(500, 500);
tree.insert(1000, 1000);
tree.insert(1, 1);
tree.insert(600, 600);
tree.insert(700, 700);
tree.insert(10, 10);
tree.insert(30, 30);
tree.insert(9000, 9000);
tree.insert(50000, 50000);
tree.insert(20, 20);
BST<int, int> tree1(tree);
tree1.deleteKey(20);
tree1.deleteKey(500);
tree1.deleteKey(1000);
tree1.inorderPrintKeys();
cout << endl << endl;
cout<<"Tree1 Length: "<<tree1.length()<<endl;
int *val = tree1.search(1);
if (val != nullptr)
{
cout << "1 found" << endl;
}
val = tree1.search(123);
if (val == nullptr)
{
cout << "123 not found" << endl;
}
	system("pause");
}