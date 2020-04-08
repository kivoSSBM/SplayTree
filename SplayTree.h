#ifndef SPLAYTREE_H
#define SPLAYTREE_H 
#include <vector>

template<typename T>
class Node
{
public:
	T element;
	Node* left;
	Node* right;
	Node* parent;
	Node()
	{
		this->element = T();
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
	Node(T element)
	{
		this->element = element;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
	~Node() {}
};

template<typename T>
class SplayTree
{
private:
	int nrOfNodes;
	Node<T>* root;

	void rotateLeft(Node<T>*& theRoot, Node<T>* x); 
	void rotateRight(Node<T>*& theRoot, Node<T>* x);
	void splay(Node<T>*& theRoot, Node<T>*theNode);
	Node<T>* getMinNode(Node<T>* theNode);
	Node<T>* getMaxNode(Node<T>* theNode);
	
	void preOrderRecursive(Node<T> theNode, std::vector<T> & list) const;
	void inOrderRecursive(Node<T> theNode, std::vector<T> & list) const;
	void postOrderRecursive(Node<T> theNode, std::vector<T> & list) const;
	void preOrderMemory(Node<T>*theNode);
public:
	SplayTree();
	~SplayTree();

	void insert(T element);
	void remove(T element);
	bool find(T element);
	std::vector<T> preOrderWalk()const;
	std::vector<T> inOrderWalk() const;
	std::vector<T> postOrderWalk() const;
	T getMin();
	T getMax();
	T getRoot(); 
	size_t size();

};
#endif // !SPLAYTREE_H

template<typename T>
void SplayTree<T>::rotateLeft(Node<T>*& theRoot, Node<T>* x)
{
	Node<T>* y = x->right;
	x->right = y->left;
	if (y->left != nullptr) 
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == nullptr) //x is root
		theRoot = y;
	else if (x == x->parent->left) //x is left child
		x->parent->left = y;
	else
		x->parent->right = y;
	
	y->left = x;
	x->parent = y;
}

template<typename T>
void SplayTree<T>::rotateRight(Node<T>*& theRoot, Node<T>* x)
{
	Node<T>* y = x->left;
	x->left = y->right;
	if (y->right != nullptr) 
		y->right->parent = x;
	
	y->parent = x->parent;
	if (x->parent == nullptr) //x is root
		theRoot = y;
	else if (x == x->parent->right) //x is left child
		x->parent->right = y;
	else
		x->parent->left = y;

	y->right = x;
	x->parent = y;
}

template<typename T>
void SplayTree<T>::splay(Node<T>*& theRoot, Node<T>* theNode)
{
	while (theNode->parent != nullptr) //node is not root
	{ 
		if (theNode->parent == theRoot) //single rotation //theNode->parent != nullptr
		{ 
			if (theNode == theNode->parent->right)
				rotateLeft(theRoot, theNode->parent);
			else if (theNode == theNode->parent->left)
				rotateRight(theRoot, theNode->parent);
		}
		else //double rotation
		{
			Node<T>* theParent = theNode->parent;
			Node<T>* theGrandparent = theParent->parent;

			if (theNode->parent->left == theNode && theParent->parent->right == theParent) //left right children, right left rotate
			{
				rotateRight(theRoot, theParent);
				rotateLeft(theRoot, theGrandparent);
			}
			else if (theNode->parent->right == theNode && theParent->parent->left == theParent) //right left children, left right rotate
			{
				rotateLeft(theRoot, theParent);
				rotateRight(theRoot, theGrandparent);
			}
			else if (theNode->parent->right == theNode && theParent->parent->right == theParent) //right right children, left left rotate
			{
				rotateLeft(theRoot, theGrandparent);
				rotateLeft(theRoot, theParent);
			}
			else if (theNode->parent->left == theNode && theParent->parent->left == theParent) //left left children, right right rotate
			{ 
				rotateRight(theRoot, theGrandparent);
				rotateRight(theRoot, theParent);
			}
		}
	}
}

template<typename T>
Node<T>* SplayTree<T>::getMinNode(Node<T>* theNode)
{
	Node<T>* walker = theNode;
	if (walker != nullptr)
	{
		while (walker->left != nullptr)
			walker = walker->left;
	}
	return walker;
}

template<typename T>
Node<T>* SplayTree<T>::getMaxNode(Node<T>* theNode)
{
	Node<T>* walker = theNode;
	if (walker != nullptr)
	{
		while (walker->right != nullptr)
			walker = walker->right;
	}
	return walker;
}

template<typename T>
void SplayTree<T>::preOrderRecursive(Node<T>  theNode, std::vector<T> & list) const 
{
	list.push_back(theNode.element);
	if (theNode.left != nullptr)
		preOrderRecursive(*theNode.left, list);
	if (theNode.right != nullptr)
		preOrderRecursive(*theNode.right, list);
}

template<typename T>
void SplayTree<T>::inOrderRecursive(Node<T> theNode, std::vector<T> & list) const
{	
	if (theNode.left != nullptr)
		inOrderRecursive(*theNode.left, list);
	list.push_back(theNode.element);
	if (theNode.right != nullptr)
		inOrderRecursive(*theNode.right, list);
}

template<typename T>
void SplayTree<T>::postOrderRecursive(Node<T> theNode, std::vector<T>& list) const
{
	if (theNode.left != nullptr)
		postOrderRecursive(*theNode.left, list);
	if (theNode.right != nullptr)
		postOrderRecursive(*theNode.right, list);
	list.push_back(theNode.element);
}

template<typename T>
inline void SplayTree<T>::preOrderMemory(Node<T>* theNode)
{
	if (theNode->left != nullptr)
		preOrderMemory(theNode->left);
	if (theNode->right != nullptr)
		preOrderMemory(theNode->right);
	delete theNode;	
}

template<typename T>
SplayTree<T>::SplayTree()
{
	this->root = nullptr;
	this->nrOfNodes = 0;
}

template<typename T>
SplayTree<T>::~SplayTree()
{
	if (this->root != nullptr)
		preOrderMemory(this->root);
}

template<typename T>
void SplayTree<T>::insert(T element)
{
	Node<T>* newNode = new Node<T>(element);
	Node<T>* walker = this->root;
	Node<T>* parent = nullptr;
	while (walker != nullptr) 
	{
		parent = walker;
		if (newNode->element == walker->element)
			walker = nullptr;
		else if (newNode->element > walker->element)
			walker = walker->right;
		else if (newNode->element < walker->element)
			walker = walker->left;
	}
	newNode->parent = parent;
	if (parent == nullptr) //new node becomes root
	{
		this->root = newNode;
		this->nrOfNodes++;
	}
	else if (newNode->element != parent->element)
	{
		if (newNode->element > parent->element)
			parent->right = newNode;
		else if (newNode->element < parent->element)
			parent->left = newNode;
		this->nrOfNodes++;
		splay(this->root, newNode); //would splay root works here?
	}

}
template<typename T>
void SplayTree<T>::remove(T element)
{
	Node<T>* walker = this->root;
	while (walker != nullptr && walker->element != element)
	{
		if (walker->element < element)
			walker = walker->right;
		else if (walker->element > element)
			walker = walker->left;
	}
	if (walker != nullptr)
	{
		splay(this->root, walker);//splay
		Node<T>* leftSubTree = this->root->left;
		if (leftSubTree != nullptr)
			leftSubTree->parent = nullptr;
		Node<T>* rightSubTree = this->root->right;
		if (rightSubTree != nullptr)
			rightSubTree->parent = nullptr;
		
		delete walker;
		nrOfNodes--;
		if (rightSubTree == nullptr)
		{
			this->root = leftSubTree;
		}
		else if (leftSubTree != nullptr)
		{
			Node<T>* maxOfLeft = getMaxNode(leftSubTree);
			splay(leftSubTree, maxOfLeft);
			maxOfLeft->right = rightSubTree;
			rightSubTree->parent = leftSubTree;
			this->root= leftSubTree;
		}
		else if(leftSubTree == nullptr)
		{
			this->root = rightSubTree;
		}
	}
}
template<typename T>
bool SplayTree<T>::find(T element)
{
	bool result = false;
	Node<T>* walker = this->root;
	while (walker != nullptr && walker->element != element)
	{
		if (walker->element == element)
			result = true;
		else if (walker->element < element)
			walker = walker->right;
		else if (walker->element > element)
			walker = walker->left;
		if (walker != nullptr && walker->element == element)
			result = true;
	}
	if (walker != nullptr)
		splay(this->root, walker);
	return result;
}
template<typename T>
std::vector<T> SplayTree<T>::preOrderWalk() const
{
	std::vector<T> list;
	if (this->root != nullptr)
		preOrderRecursive(*this->root, list);
	return list;
}

template<typename T>
std::vector<T> SplayTree<T>::inOrderWalk() const
{
	std::vector<T> list;
	if (this->root != nullptr)
		inOrderRecursive(*this->root, list);
	return list;
}

template<typename T>
std::vector<T> SplayTree<T>::postOrderWalk() const
{
	std::vector<T> list;
	if (this->root != nullptr)
		postOrderRecursive(*this->root, list);
	return list;
}

template<typename T>
T SplayTree<T>::getMin()
{
	T element = T();
	if (this->root != nullptr)
	{
		element = this->getMinNode(this->root)->element;
		splay(this->root, this->getMinNode(this->root));
	}
	else
	{
		throw("is nullptr");
	}
	return element;
}

template<typename T>
T SplayTree<T>::getMax()
{
	T element = T();
	if (this->root != nullptr)
	{
		element = this->getMaxNode(this->root)->element;
		splay(this->root, this->getMaxNode(this->root));
	}
	else
		throw("is nullptr");
	return element;
}

template<typename T>
T SplayTree<T>::getRoot()
{
	T element = T();
	if(root!=nullptr)
		element = this->root->element;
	else
		throw("is nullptr");
	return element;
}

template<typename T>
size_t SplayTree<T>::size()
{
	return nrOfNodes;
}