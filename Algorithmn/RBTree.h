///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Define the rb tree's function
///</describe>
/// <date>2020/3/9</date>
///***********************************************************************
#ifndef RBTREE_H
#define RBTREE_H

#include <string>

enum RB_COLOR_ENUM
{
	RED=0,

	BLACK
};

template <class T1,class T2>
struct TreeNode
{
	// Key 
	T1 key;

	// Value
	T2 value;

	// Node's color
	RB_COLOR_ENUM color;

	// Parent node
	TreeNode* pParent;

	// Left node
	TreeNode* pLeft;

	// Right node
	TreeNode* pRight;
};

template <class T1,class T2>
class RBTree
{
public:
	using KeyType = T1;
	using ValueType = T2;
	using NodeType = TreeNode<KeyType, ValueType>;

public:
	// Construct the RBTree
	explicit RBTree();
	
	// Detructe the RBTree
	~RBTree();
	
public:
	// Insert the key and value
	bool Insert(KeyType& key, ValueType& value);

	// Remove the key
	void Remove(KeyType& key);

	// Search the key
	bool Search(KeyType& key, ValueType& value);

	// Modify the key's data
	bool Modify(KeyType& key, ValueType& value);

	// Size of the tree
	int Size();

	// Is empty
	bool IsEmpty();

	// Get the error message
	std::string GetErrorMsg();

private:
	// Initialize the tree
	void Initialize();

	// Destory the tree
	void Destory();

	// Insert the key and value
	bool Insert(NodeType* pCurNode);

	// Insert fixup
	void InsertFixup(NodeType* pRoot,NodeType* pCurNode);

	// Remove fixup
	void RemoveFixup(NodeType* pRoot, NodeType* pCurNode);

	// Max node
	NodeType* Maximum();

	// Minimize node
	NodeType* Minimum();

	// Destory node
	void DestoryNode(NodeType* pNode);

	// Get min node
	NodeType* GetMinNode(NodeType* pNode);

	// Get max node
	NodeType* GetMaxNode(NodeType* pNode);

	// Create node
	NodeType* CreateNode(KeyType& key, 
		ValueType& value,
		RB_COLOR_ENUM eColor=RED,
		NodeType* pParent=nullptr,
		NodeType* pLeft=nullptr,
		NodeType* pRight=nullptr);

	// Search the node
	NodeType* Search(KeyType& key);

	// Remove the node
	void Remove(NodeType* pNode);

	// Get prodromal node
	NodeType* GetProdromal(NodeType* pCurNode);

	// Get successor node
	NodeType* GetSuccessor(NodeType* pCurNode);

	// Delete node
	void DeleteNode(NodeType*& pNode);

	// Enter delete mode1: current node has two child
	void EnterDeleteMode1(NodeType*& pRoot,NodeType*& pNode);

	// Enter delete mode2: current node has only one child
	void EnterDeleteMode2(NodeType*& pRoot, NodeType*& pNode);

	// Enter delete mode3: current node has no any child
	void EnterDeleteMode3(NodeType*& pRoot, NodeType*& pNode);

	// Left rotation
	void LeftRotation(NodeType* pNode);

	// Right rotation
	void RightRotation(NodeType* pNode);

private:
	// Get the disposed status
	inline bool GetDisposed() const
	{
		return m_bDisposed;
	}
	
	// Set the disposed status
	inline void SetDisposed(bool bDisposed)
	{
		m_bDisposed = bDisposed;
	}

	// Get the ErrorText
	inline std::string GetErrorText() const
	{
		return m_strErrorText;
	}

	// Set the ErrorText
	inline void SetErrorText(std::string strErrorText)
	{
		m_strErrorText = strErrorText;
	}

	// Get the Root
	inline NodeType*& GetRootNode() const
	{
		return m_pRoot;
	}

	// Set the Root
	inline void SetRootNode(NodeType* pRoot)
	{
		m_pRoot = pRoot;
	}

	// Get the Size
	inline int GetSize() const
	{
		return m_iSize;
	}

	// Set the Size
	inline void SetSize(int iSize)
	{
		m_iSize = iSize;
	}

private:
	// Root node
	NodeType* m_pRoot;
	
	// Tree size
	int m_iSize;
	
	// Error message
	std::string m_strErrorText;
	
	// Disposed status
	bool m_bDisposed;	
};

/**********Implement section*************/

// Construct the RBTree
template <class T1, class T2>
RBTree<T1,T2>::RBTree():
	m_pRoot(nullptr),
	m_iSize(0),
	m_strErrorText(""),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the RBTree
template <class T1, class T2>
RBTree<T1, T2>::~RBTree()
{
	Destory();
}

// Initialize the tree
template <class T1, class T2>
void RBTree<T1, T2>::Initialize()
{

}

// Destory the tree
template <class T1, class T2>
void RBTree<T1, T2>::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		DestoryNode(GetRootNode());
	}
}

// Destory node
template <class T1, class T2>
void RBTree<T1, T2>::DestoryNode(NodeType* pNode)
{
	if (pNode==nullptr)
	{
		return;
	}

	if (pNode->pLeft != nullptr)
	{
		DestoryNode(pNode->pLeft);
	}
	else if (pNode->pRight != nullptr)
	{
		DestoryNode(pNode->pRight);
	}

	delete pNode;

	pNode = nullptr;
}

// Get min node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::GetMinNode(NodeType* pNode)
{
	if (pNode==nullptr)
	{
		return nullptr;
	}

	while (pNode->pLeft !=nullptr)
	{
		pNode = pNode->pLeft;
	}

	return pNode;
}

// Get max node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::GetMaxNode(NodeType* pNode)
{
	if (pNode == nullptr)
	{
		return nullptr;
	}

	while (pNode->pRight != nullptr)
	{
		pNode = pNode->pRight;
	}

	return pNode;
}

// Max node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::Maximum()
{
	return GetMaxNode(GetRootNode());
}

// Minimize node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::Minimum()
{
	return GetMinNode(GetRootNode());
}

// Create node
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::CreateNode(KeyType& key,
	ValueType& value,
	RB_COLOR_ENUM eColor,
	NodeType* pParent,
	NodeType* pLeft,
	NodeType* pRight)
{
	NodeType* pNode = new NodeType();	
	if (pNode != nullptr)
	{
		pNode->key = key;

		pNode->value = value;

		pNode->color = eColor;

		pNode->pParent = pParent;

		pNode->pLeft = pLeft;

		pNode->pRight = pRight;
	}

	return pNode;
}

// Left rotation
template <class T1, class T2>
void RBTree<T1, T2>::LeftRotation(NodeType* pNode)
{
	if (pNode==nullptr)
	{
		return;
	}

	// Get right node at first
	NodeType* pRightNode = pNode->pRight;

	pNode->pRight = pRightNode->pLeft;

	if (pRightNode->pLeft !=nullptr)
	{
		pRightNode->pLeft->pParent = pNode;
	}

	pRightNode->pParent = pNode->pParent;

	if (pNode->pParent==nullptr)
	{
		SetRootNode(pRightNode);
	}
	else
	{
		if (pNode==pNode->pParent->pLeft)
		{
			pNode->pParent->pLeft = pRightNode;
		}
		else
		{
			pNode->pParent->pRight = pRightNode;
		}
	}

	pRightNode->pLeft = pNode;

	pNode->pParent = pRightNode;
}

// Right rotation
template <class T1, class T2>
void RBTree<T1, T2>::RightRotation(NodeType* pNode)
{
	if (pNode == nullptr)
	{
		return;
	}

	// Get left node at first
	NodeType* pLeftNode = pNode->pLeft;

	pNode->pLeft = pLeftNode->pRight;

	if (pLeftNode->pRight!=nullptr)
	{
		pLeftNode->pRight->pParent = pNode;
	}

	pLeftNode->pParent = pNode->pParent;

	if (pNode->pParent==nullptr)
	{
		SetRootNode(pLeftNode);
	}
	else
	{
		if (pNode==pNode->pParent->pLeft)
		{
			pNode->pParent->pLeft = pLeftNode;
		}
		else
		{
			pNode->pParent->pRight = pLeftNode;
		}
	}

	pLeftNode->pRight = pNode;

	pNode->pParent = pLeftNode;
}

// Insert fixup
template <class T1, class T2>
void RBTree<T1, T2>::InsertFixup(NodeType* pRoot, NodeType* pCurNode)
{
	if (pRoot==nullptr || pCurNode==nullptr)
	{
		return;
	}

	NodeType* pCurrentNode = pCurNode;

	// If parent node's color is black and it is no need to fix tree
	while (pCurrentNode->pParent->color==RED)
	{
		if (pCurrentNode == pCurrentNode->pParent->pLeft)
		{
			// Get uncle node
			NodeType* pUncleNode = pCurrentNode->pParent->pRight;

			// Uncle node's color is red and we can simply change their colors
			if (pUncleNode->color==RED)
			{
				pCurrentNode->pParent->color = BLACK;

				pCurrentNode->pParent->pParent->color = RED;

				pUncleNode->color = BLACK;

				pCurrentNode = pCurrentNode->pParent->pParent;
			}
			else 
			{
				// If we insert node to the parent's right and we need to left rotate it 
				// to be like inserting node to the parent's left
				if (pCurrentNode== pCurrentNode->pParent->pRight)
				{
					pCurrentNode = pCurrentNode->pParent;

					LeftRotation(pCurrentNode);
				}

				// If we insert node to the parent's left
				{
					pCurrentNode = pCurrentNode->pParent->pParent;

					RightRotation(pCurrentNode);

					pCurrentNode->pParent->color = BLACK;

					pCurrentNode->color = RED;
				}
			}
		}
		else
		{
			// Get uncle node
			NodeType* pUncleNode = pCurrentNode->pParent->pLeft;

			if (pUncleNode->color == RED)
			{
				pCurrentNode->pParent->color = BLACK;

				pCurrentNode->pParent->pParent->color = RED;

				pUncleNode->color = BLACK;

				pCurrentNode = pCurrentNode->pParent->pParent;
			}
			else
			{
				if (pCurrentNode == pCurrentNode->pParent->pLeft)
				{
					pCurrentNode = pCurrentNode->pParent;

					RightRotation(pCurrentNode);
				}

				pCurrentNode = pCurrentNode->pParent->pParent;

				LeftRotation(pCurrentNode);

				pCurrentNode->pParent->color = BLACK;

				pCurrentNode->color = RED;
			}
		}
	}

	// Make root node's color to be black
	pRoot->color = BLACK;
}

// Insert the key and value
template <class T1, class T2>
bool RBTree<T1, T2>::Insert(NodeType* pCurNode)
{
	if (pCurNode==nullptr)
	{
		return false;
	}

	NodeType* pNode = GetRootNode();

	NodeType* pInsertNode = nullptr;

	while (pNode!=nullptr)
	{
		pInsertNode = pNode;

		if (pCurNode->key<pNode->key)
		{
			pNode = pNode->pLeft;
		}
		else
		{
			pNode = pNode->pRight;
		}
	}

	if (pNode==nullptr)
	{
		SetRootNode(pCurNode);
	}
	else
	{
		if (pCurNode->key < pInsertNode->key)
		{
			pInsertNode->pLeft = pCurNode;
		}
		else
		{
			pInsertNode->pRight = pCurNode;
		}

		pCurNode->pParent = pInsertNode;
	}

	pCurNode->color = RED;

	return true;
}

// Insert the key and value
template <class T1, class T2>
bool RBTree<T1, T2>::Insert(KeyType& key, ValueType& value)
{
	// Create a node
	NodeType* pNode = CreateNode(key, value);
	if (pNode==nullptr)
	{
		return false;
	}

	// Search the key to know wether we can insert it
	NodeType* pSearchNode = Search(key);
	if (pSearchNode != nullptr)
	{
		return false;
	}

	// Insert the data to the tree
	Insert(pNode);

	// Fix the tree to be balanced
	InsertFixup(GetRootNode(),pNode);

	SetSize(GetSize()+1);

	return true;
}

// Get prodromal node(in-order: left max node)
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::GetProdromal(NodeType* pCurNode)
{
	if (pCurNode==nullptr)
	{
		return nullptr;
	}

	if (pCurNode->pLeft!=nullptr)
	{
		return GetMaxNode(pCurNode->pLeft);
	}

	NodeType* pParent = pCurNode->pParent;

	while (pParent !=nullptr && (pCurNode== pParent->pLeft))
	{
		pCurNode = pParent;

		pParent = pCurNode->pParent;
	}

	return pParent;
}

// Get successor node(in-order: right min node)
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::GetSuccessor(NodeType* pCurNode)
{
	if (pCurNode == nullptr)
	{
		return nullptr;
	}

	if (pCurNode->pRight != nullptr)
	{
		return GetMinNode(pCurNode->pRight);
	}

	NodeType* pParent = pCurNode->pParent;

	while (pParent != nullptr && (pCurNode == pParent->pRight))
	{
		pCurNode = pParent;

		pParent = pCurNode->pParent;
	}

	return pParent;
}

// Delete node
template <class T1, class T2>
void RBTree<T1, T2>::DeleteNode(NodeType*& pNode)
{
	if (pNode!=nullptr)
	{
		delete pNode;

		pNode = nullptr;
	}
}

// Enter delete mode1: current node has two child
template <class T1, class T2>
void RBTree<T1, T2>::EnterDeleteMode1(NodeType*& pRoot, NodeType*& pNode)
{
	if (pRoot == nullptr || pNode == nullptr)
	{
		return;
	}

	// Find successor node at first
	NodeType* pSuccessorNode = GetSuccessor(pRoot);

	// Get successor's child (Successor has one child at most and it is right node)
	NodeType* pSuccessorChildNode = pSuccessorNode->pRight;

	// Change successor's child's parent (on another way ,this successor node is deleted. But remember it is still there)
	NodeType* pSuccessorParentNode = pSuccessorNode->pParent;

	if (pSuccessorParentNode==pNode)
	{
		pSuccessorParentNode = pSuccessorNode;
	}
	else
	{
		pSuccessorParentNode->pLeft = pSuccessorChildNode;

		if (pSuccessorChildNode!=nullptr)
		{
			pSuccessorChildNode->pParent = pSuccessorParentNode;
		}

		pSuccessorNode->pRight = pNode->pRight;

		pNode->pRight->pParent = pSuccessorNode;
	}

	// Make successor node to replace current deleted node
	pSuccessorParentNode = pNode->pParent;

	pSuccessorNode->color = pNode->color;

	pSuccessorNode->key = pNode->key;

	pSuccessorNode->value = pNode->value;

	pSuccessorNode->pLeft = pNode->pLeft;

	pNode->pLeft->pParent = pSuccessorNode;

	// If the node's color is red, it is no need to fixup the tree
	if (pNode->color == BLACK)
	{
		RemoveFixup(pRoot, pNode);
	}

	// Delete the node
	DeleteNode(pNode);
}

// Enter delete mode2: current node has only one child
template <class T1, class T2>
void RBTree<T1, T2>::EnterDeleteMode2(NodeType*& pRoot, NodeType*& pNode)
{
	if (pRoot==nullptr || pNode==nullptr)
	{
		return;
	}

	// Get current node's child
	NodeType* pChild = nullptr;

	if (pNode->pLeft != nullptr)
	{
		pChild = pNode->pLeft;
	}
	else
	{
		pChild = pNode->pRight;
	}

	// Get current node's parent
	NodeType* pParent = pRoot;

	if (pNode->pParent != nullptr)
	{
		pParent = pNode->pParent;
	}

	// Change this child's parent
	pChild->pParent = pParent;

	if (pNode == pParent->pLeft)
	{
		pParent->pLeft = pChild;
	}
	else
	{
		pParent->pRight = pChild;
	}

	// If the node's color is red, it is no need to fixup the tree
	if (pNode->color == BLACK)
	{
		RemoveFixup(pRoot, pNode);
	}

	// Delete the node
	DeleteNode(pNode);
}

// Enter delete mode3: current node has no any child
template <class T1, class T2>
void RBTree<T1, T2>::EnterDeleteMode3(NodeType*& pRoot, NodeType*& pNode)
{
	if (pRoot == nullptr || pNode == nullptr)
	{
		return;
	}

	// If the node's color is red, it is no need to fixup the tree
	if (pNode->color == BLACK)
	{
		RemoveFixup(pRoot, pNode);
	}

	// Delete the node
	DeleteNode(pNode);
}

// Remove fixup
template <class T1, class T2>
void RBTree<T1, T2>::RemoveFixup(NodeType* pRoot, NodeType* pCurNode)
{

}

// Remove the node
template <class T1, class T2>
void RBTree<T1, T2>::Remove(NodeType* pNode)
{
	if (pNode==nullptr)
	{
		return;
	}

	NodeType* pRoot = GetRootNode();

	// Deleted node has two children
	if (pNode->pLeft!=nullptr && pNode->pRight!=nullptr)
	{
		EnterDeleteMode1(pRoot, pNode);

		return;
	}

	// Deleted node has one child
	if (pNode->pLeft!=nullptr || pNode->pRight!=nullptr)
	{
		EnterDeleteMode2(pRoot, pNode);
	}
	else // Deleted node has no child
	{
		EnterDeleteMode3(pRoot, pNode);
	}
}

// Remove the key
template <class T1, class T2>
void RBTree<T1, T2>::Remove(KeyType& key)
{
	// Search the node with key
	NodeType* pNode = Search(key);
	if (pNode==nullptr)
	{
		return;
	}

	// Remove the node
	Remove(pNode);

	SetSize(GetSize() - 1);
}

// Search the key
template <class T1, class T2>
bool RBTree<T1, T2>::Search(KeyType& key, ValueType& value)
{
	NodeType* pNode = Search(key);
	if (pNode==nullptr)
	{
		return false;
	}

	value = pNode->value;

	return true;
}

// Search the key
template <class T1, class T2>
RBTree<T1, T2>::NodeType* RBTree<T1, T2>::Search(KeyType& key)
{
	NodeType* pNode = GetRootNode();

	while (pNode != nullptr)
	{
		if (key == pNode->key)
		{
			break;
		}
		else if (key < pNode->key)
		{
			pNode = pNode->pLeft;
		}
		else
		{
			pNode = pNode->pRight;
		}
	}

	return pNode;
}

// Modify the key's data
template <class T1, class T2>
bool RBTree<T1, T2>::Modify(KeyType& key, ValueType& value)
{
	NodeType* pNode = Search(key);
	if (pNode==nullptr)
	{
		return false;
	}

	pNode->value = value;

	return true;
}

// Size of the tree
template <class T1, class T2>
int RBTree<T1, T2>::Size()
{
	return GetSize();
}

// Is empty
template <class T1, class T2>
bool RBTree<T1, T2>::IsEmpty()
{
	return GetRootNode() == nullptr;
}

// Get the error message
template <class T1, class T2>
std::string RBTree<T1, T2>::GetErrorMsg()
{
	return GetErrorText();
}

#endif // RBTREE_H
