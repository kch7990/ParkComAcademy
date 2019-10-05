#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef signed long int Long;

template <typename T>
class LinkedList {
public:
	class Node {
		friend class LinkedList;
	public:
		Node() {
			this->previous = this;
			this->next = this;
		}
		Node(Node *previous, T object, Node *next) {
			this->previous = previous;
			this->object = object;
			this->next = next;
		}
		Node(T object) {
			this->previous = this;
			this->object = object;
			this->next = this;
		}
		Node(Node *previous, T object) {
			this->previous = previous;
			this->object = object;
			this->next = this;
		}
		Node(T object, Node *next) {
			this->previous = this;
			this->object = object;
			this->next = next;
		}
		Node(const Node& source) {
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;
		}
		~Node() {}
		Node& operator =(const Node& source) {
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;

			return *this;
		}
		T& GetObject() const {
			return const_cast<T&>(this->object);
		}
	private:
		Node *previous;
		T object;
		Node *next;
	};
public:
	LinkedList();
	LinkedList(const LinkedList& source);
	~LinkedList();
	Node* InsertBefore(Node *index, T object);
	Node* InsertAfter(Node *index, T object);
	Node* AppendFromHead(T object);
	Node* AppendFromTail(T object);
	Node* Delete(Node *index);
	Node* DeleteFromHead();
	Node* DeleteFromTail();
	void DeleteAllItems();
	Node* LinearSearchUnique(void *key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*compare)(void*, void*));
	Node* First();
	Node* Previous();
	Node* Next();
	Node* Last();
	Node* Move(Node *index);
	LinkedList& operator=(const LinkedList& source);
	T& operator [](Long index);
	Long GetLength() const;
	Node* GetCurrent() const;
private:
	Node *head;
	Node *tail;
	Long length;
	Node *current;
};
template <typename T>
inline Long LinkedList<T>::GetLength() const {
	return this->length;
}
template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetCurrent() const {
	return const_cast<Node*>(this->current);
}

template <typename T>
LinkedList<T>::LinkedList()
{
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
}


template <typename T>
LinkedList<T>::LinkedList(const LinkedList& source)
{
	Node *sourcePrevious = 0;
	Node *sourceCurrent = source.head;
	Node *current = 0;
	Node *previous = 0;

	while (sourceCurrent != sourcePrevious)
	{
		if (previous != 0)
		{
			this->current = new Node(previous, sourceCurrent->object);
		}
		else
		{
			this->current = new Node(sourceCurrent->object);
		}

		if (previous != 0)
		{
			previous->next = this->current;
		}
		else
		{
			this->head = this->current;
		}

		if (source.current == sourceCurrent)
		{
			current = this->current;
		}

		previous = this->current;
		sourcePrevious = sourceCurrent;
		sourceCurrent = sourceCurrent->next;
	}

	this->tail = this->current;
	this->current = current;
	this->length = source.length;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	Node *previous = 0;

	this->current = this->head;
	while (this->current != previous)
	{
		previous = this->current;
		this->head = this->current->next;
		if (this->current != 0)
		{
			delete this->current;
		}

		this->current = this->head;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertBefore(Node *index, T object)
{
	if (this->head != index)
	{
		this->current = new Node(index->previous, object, index);
	}
	else
	{
		this->current = new Node(object, index);
	}

	if (this->head != index)
	{
		index->previous->next = this->current;
	}
	else
	{
		this->head = this->current;
	}

	index->previous = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertAfter(Node *index, T object)
{
	if (this->tail != index)
	{
		this->current = new Node(index, object, index->next);
	}
	else
	{
		this->current = new Node(index, object);
	}

	if (this->tail != index)
	{
		index->next->previous = this->current;
	}
	else
	{
		this->tail = this->current;
	}

	index->next = this->current;
	this->length++;

	return this->current;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromHead(T object)
{
	if (this->head != 0)
	{
		this->current = new Node(object, this->head);
	}
	else
	{
		this->current = new Node(object);
	}

	if (this->head != 0)
	{
		this->head->previous = this->current;
	}
	else
	{
		this->tail = this->current;
	}

	this->head = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromTail(T object)
{
	if (this->tail != 0)
	{
		this->current = new Node(this->tail, object);
	}
	else
	{
		this->current = new Node(object);
	}

	if (this->tail != 0)
	{
		this->tail->next = this->current;
	}
	else
	{
		this->head = this->current;
	}

	this->tail = this->current;
	this->length++;

	return this->current;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Delete(Node *index) {
	if (this->head != index && this->tail != index) {
		index->previous->next = index->next;
		index->next->previous = index->previous;
		this->current = index->next;
	}
	else if (this->tail != index) {
		index->next->previous = index->next;
		this->head = index->next;
		this->current = index->next;
	}
	else if (this->head != index) {
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	if (index != 0) {
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromHead() {
	this->current = this->head;
	if (this->head != this->tail) {
		this->head->next->previous = this->head->next;
		this->head = this->head->next;
	}
	else {
		this->head = 0;
		this->tail = 0;
	}
	if (this->current != 0) {
		delete this->current;
	}
	this->current = this->head;
	this->length--;

	return 0;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromTail() {
	this->current = this->tail;
	if (this->head != this->tail) {
		this->tail->previous->next = this->tail->previous;
		this->tail = this->tail->previous;
	}
	else {
		this->head = 0;
		this->tail = 0;
	}
	if (this->current != 0) {
		delete this->current;
	}
	this->current = this->tail;
	this->length--;

	return 0;
}

template <typename T>
void LinkedList<T>::DeleteAllItems() {
	Node *previous = 0;

	this->current = this->head;
	while (this->current != previous) {
		previous = this->current;
		this->head = this->current->next;
		if (this->current != 0) {
			delete this->current;
		}
		this->current = this->head;
	}
	this->head = 0;
	this->tail = 0;
	this->current = 0;
	this->length = 0;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::LinearSearchUnique(void *key,
	int(*compare)(void *, void *)) {
	Node *index = 0;
	Node *previous = 0;
	this->current = this->head;
	while (this->current != previous && compare(&this->current->object, key) != 0) {
		previous = this->current;
		this->current = this->current->next;
	}
	if (this->current != previous) {
		index = this->current;
	}

	return index;
}
template <typename T>
void LinkedList<T>::LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*compare)(void *, void*)) {
	Node *previous = 0;
	Long i = 0;
	*count = 0;

	*indexes = new Node*[this->length];
	this->current = this->head;
	while (this->current != previous) {
		if (compare(&this->current->object, key) == 0) {
			(*indexes)[i] = this->current;
			i++;
			(*count)++;
		}
		previous = this->current;
		this->current = this->current->next;
	}
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::First() {
	this->current = this->head;

	return this->current;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Previous() {
	this->current = this->current->previous;

	return this->current;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Next() {
	this->current = this->current->next;

	return this->current;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Last() {
	this->current = this->tail;

	return this->current;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Move(Node *index) {
	this->current = index;

	return this->current;
}
template <typename T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList& source) {
	Node *previous = 0;
	Node *sourceCurrent = source.head;
	Node *sourcePrevious = 0;
	Node *current = 0;

	this->current = this->head;
	while (this->current != previous) {
		previous = this->current;
		this->head = this->current->next;
		if (this->current != 0) {
			delete this->current;
		}
		this->current = this->head;
	}
	previous = 0;
	while (sourceCurrent != sourcePrevious) {
		if (previous != 0) {
			this->current = new Node(previous, sourceCurrent->object);
		}
		else {
			this->current = new Node(sourceCurrent->object);
		}
		if (previous != 0) {
			previous->next = this->current;
		}
		else {
			this->head = this->current;
		}
		if (source.current == sourceCurrent) {
			current = this->current;
		}
		previous = this->current;
		sourcePrevious = sourceCurrent;
		sourceCurrent = sourceCurrent->next;
	}
	this->tail = this->current;
	this->current = current;
	this->length = source.length;

	return *this;
}
template <typename T>
T& LinkedList<T>::operator [](Long index) {
	Node *current = this->head;
	Long i = 0;
	while (i < index) {
		current = current->next;
		i++;
	}

	return current->object;
}

#endif //_LINKEDLIST_H