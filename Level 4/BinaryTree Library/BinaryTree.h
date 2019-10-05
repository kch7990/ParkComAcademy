#ifndef _BINARYTREE_H
#define _BINARYTREE_H

typedef signed long int Long;
template <typename T>
class BinaryTree {
public:
	class Node {
		friend class BinaryTree;
	public:
		Node() {
			this->left = 0;
			this->right = 0;
		}
		Node(T key) {
			this->left = 0;
			this->key = key;
			this->right = 0;
		}
		Node(const Node& source) {
			this->key = source.key;
			this->left = 0;
			this->right = 0;
			if (source.left != 0) {
				this->left = new Node(*source.left);
			}
			if (source.right != 0) {
				this->right = new Node(*source.right);
			}
		}
		~Node() {
			if (this->left != 0) {
				delete this->left;
			}
			if (this->right != 0) {
				delete this->right;
			}
		}
		void MakeKeys(T(*keys), Long *count, Long *i) {
			if (this->left != 0) {
				this->left->MakeKeys(keys, count, i);
			}
			keys[*i] = this->key;
			(*i)++;
			(*count)++;
			if (this->right != 0) {
				this->right->MakeKeys(keys, count, i);
			}
		}
		void DeleteAllItems() {
			if (this->left != 0) {
				this->left->DeleteAllItems();
			}
			if (this->right != 0) {
				this->right->DeleteAllItems();
			}
			this->left = 0;
			this->right = 0;
			delete this;
		}
		static Node* MakeTree(T(*keys), Long first, Long last) {
			Node *node = 0;
			if (first <= last) {
				Long mid = (first + last) / 2;
				node = new Node(keys[mid]);
				node->left = MakeTree(keys, first, mid - 1);
				node->right = MakeTree(keys, mid + 1, last);
			}
			return node;
		}
		Node& operator =(const Node& source) {
			this->key = source.key;
			this->left = 0;
			this->right = 0;
			if (source.left != 0) {
				this->left = new Node;
				*this->left = *source.left;
			}
			if (source.right != 0) {
				this->right = new Node;
				*this->right = *source.right;
			}
			return *this;
		}
		T& GetKey() const {
			return const_cast<T&>(this->key);
		}
	private:
		Node *left;
		T key;
		Node *right;
	};
public:
	BinaryTree();
	BinaryTree(const BinaryTree& source);
	~BinaryTree();
	Node* Insert(T key, int(*compare)(void*, void*));
	Node* Delete(T key, int(*compare)(void*, void*));
	Node* Search(T key, int(*compare)(void*, void*));
	void MakeBalance();
	void MakeKeys(T* (*keys), Long *count);
	void DeleteAllItems();
	void MakeTree(T(*keys), Long count);
	BinaryTree& operator =(const BinaryTree& source);

	Long GetLength() const;
	Long GetBalance() const;
private:
	Node *root;
	Long length;
	Long balance;
};
template <typename T>
inline Long BinaryTree<T>::GetLength() const {
	return this->length;
}
template <typename T>
inline Long BinaryTree<T>::GetBalance() const {
	return this->balance;
}

template <typename T>
BinaryTree<T>::BinaryTree() {
	this->root = 0;
	this->length = 0;
	this->balance = 0;
}
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& source) {
	this->root = new Node;
	*this->root = *source.root;
	this->length = source.length;
	this->balance = source.balance;
}
template <typename T>
BinaryTree<T>::~BinaryTree() {
	if (this->root != 0) {
		delete this->root;
	}
}
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Insert(T key, int(*compare)(void*, void*)) {
	Node *index;
	Node *parent = 0;

	index = this->root;
	while (index != 0) {
		parent = index;
		if (compare(&index->key, &key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	index = new Node(key);
	if (parent != 0) {
		if (compare(&parent->key, &key) > 0) {
			parent->left = index;
		}
		else {
			parent->right = index;
		}
		if (compare(&this->root->key, &key) > 0) {
			this->balance--;
		}
		else {
			this->balance++;
		}
	}
	else {
		this->root = index;
	}
	this->length++;
	
	return index;
}
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Delete(T key, int(*compare)(void*, void*)) {
	Node *index;
	Node *deleteNode;
	Node *parentofDelete = 0;
	Node *changeNode = 0;
	Node *parentofChange = 0;

	deleteNode = this->root;
	while (deleteNode != 0 && compare(&deleteNode->key, &key) != 0) {
		parentofDelete = deleteNode;
		if (compare(&deleteNode->key, &key) > 0) {
			deleteNode = deleteNode->left;
		}
		else {
			deleteNode = deleteNode->right;
		}
	}
	index = deleteNode->right;
	while (index != 0) {
		parentofChange = changeNode;
		changeNode = index;
		index = index->left;
	}
	if (deleteNode->right == 0) {
		index = deleteNode->left;
	}
	while (index != 0) {
		parentofChange = changeNode;
		changeNode = index;
		index = index->right;
	}
	if (changeNode != 0 && parentofChange == 0) {
		parentofChange = deleteNode;
	}
	if (changeNode != 0) {
		if (changeNode->left != 0 || changeNode->right != 0) {
			if (parentofChange != deleteNode) {
				if (changeNode->left != 0) {
					parentofChange->right = changeNode->left;
				}
				else {
					parentofChange->left = changeNode->right;
				}
			}
			else {
				if (changeNode->left != 0) {
					parentofChange->left = changeNode->left;
				}
				else {
					parentofChange->right = changeNode->right;
				}
			}
		}
		else {
			if (parentofChange->left == changeNode) {
				parentofChange->left = 0;
			}
			else {
				parentofChange->right = 0;
			}
		}
		changeNode->left = deleteNode->left;
		changeNode->right = deleteNode->right;
		if (parentofDelete != 0) {
			if (parentofDelete->left == deleteNode) {
				parentofDelete->left = changeNode;
			}
			else {
				parentofDelete->right = changeNode;
			}
		}
		else {
			this->root = changeNode;
		}
	}
	else {
		if (parentofDelete != 0) {
			if (parentofDelete->left == deleteNode) {
				parentofDelete->left = 0;
			}
			else {
				parentofDelete->right = 0;
			}
		}
		else {
			this->root = 0;
		}
	}
	if (deleteNode != 0) {
		deleteNode->left = 0;
		deleteNode->right = 0;
		delete deleteNode;
	}
	this->length--;
	if (this->root != 0) {
		if (parentofDelete != 0) {
			if (compare(&this->root->key, &key) > 0) {
				this->balance++;
			}
			else {
				this->balance--;
			}
		}
		else {
			if (compare(&this->root->key, &key) < 0) {
				this->balance++;
			}
			else {
				this->balance--;
			}
		}
	}
	return 0;
}
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Search(T key, int(*compare)(void*, void*)) {
	Node *index = this->root;
	while (index != 0 && compare(&index->key, &key) != 0) {
		if (compare(&index->key, &key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}
template <typename T>
void BinaryTree<T>::MakeBalance() {
	T(*keys);
	Long count;
	this->MakeKeys(&keys, &count);
	this->DeleteAllItems();
	this->MakeTree(keys, count);
	if (keys != 0) {
		delete[] keys;
	}
}
template <typename T>
void BinaryTree<T>::MakeKeys(T* (*keys), Long *count) {
	*count = 0;
	Long i = 0;
	*keys = new T[this->length];
	if (this->root != 0) {
		this->root->MakeKeys(*keys, count, &i);
	}
}
template <typename T>
void BinaryTree<T>::DeleteAllItems() {
	this->root->DeleteAllItems();
	this->root = 0;
	this->length = 0;
	this->balance = 0;
}
template <typename T>
void BinaryTree<T>::MakeTree(T(*keys), Long count) {
	this->root = Node::MakeTree(keys, 0, count - 1);
	this->length = count;
	Long remainder = count % 2;
	if (remainder == 0) {
		this->balance = 1;
	}
}
template <typename T>
BinaryTree<T>& BinaryTree<T>::operator =(const BinaryTree& source) {
	if (this->root != 0) {
		delete this->root;
	}
	this->root = new Node;
	*this->root = *source.root;
	this->length = source.length;
	this->balance = source.balance;

	return *this;
}

#endif //BINARYTREE_H
































