#pragma once
#include "stdafx.h"

template <class T> class List
{
private:

	struct Node
	{
		T info;
		Node *prev;
		Node *next;
	};

	Node *head;
	int size;

public:

	List();
	List(const List<T> &other);
	~List();

	int Get_Size();
	T& operator[](int index);
	List<T> operator=(const List<T> &L);

	void Push_Back(T info);
	void Pop_Back();

	void Insert(T info, int index);
	void Delete(int index);
};


template <class T> List<T>::List() { head = nullptr; size = 0; }

template <class T> List<T>::List(const List<T> &other)
{
	Node* buf = other.head->next;
	for (int i = 0; i < other.size; i++)
	{
		this->Push_Back(buf->info);
		buf = buf->next;
	}
}

template <class T> List<T>::~List()
{
	while (head)
	{
		Node *cur = head->next;

		if (head->prev) head->prev->next = nullptr;
		if (head->next) head->next->prev = nullptr;
		head->next = nullptr;
		head->prev = nullptr;
		delete head;
		head = nullptr;
		if (cur) head = cur;
	}
}

template <class T> int List<T>::Get_Size() { return this->size; }

template <class T> T& List<T>::operator[](int index)
{
	Node *cur_el = head->next;
	for (int i = 0; i < index; i++)
	{
		cur_el = cur_el->next;
	}
	return cur_el->info;
}

template <class T> List<T> List<T>::operator=(const List<T> &L)
{
	for (int i = 0; i < this->size; i++)
	{
		this->Pop_Back();
	}

	Node *buf = L.head->next;
	for (int i = 0; i < L.size; i++)
	{
		this->Push_Back(buf->info);
		buf = buf->next;
	}

	return *this;
}

template <class T> void List<T>::Push_Back(T info)
{
	Node *new_el = new Node();

	if (!head)
	{
		head = new_el;
		new_el->prev = new_el;
		new_el->next = new_el;
		new_el->info = info;

		size = 1;
	}
	else
	{
		new_el->prev = head;
		new_el->next = head->next;
		head->next->prev = new_el;
		head->next = new_el;
		new_el->info = info;
		head = new_el;
		size++;
	}
}

template <class T> void List<T>::Pop_Back()
{
	Delete(size);
}

template <class T> void List<T>::Insert(T info, int index)
{
	Node *new_el = new Node();

	if (!head)
	{
		head = new_el;
		new_el->prev = new_el;
		new_el->next = new_el;
		new_el->info = info;

		size = 1;
		return;
	}

	Node *buf = head;
	for (int i = 0; i < index; i++)
	{
		buf = buf->next;
	}

	new_el->prev = buf->prev;
	new_el->next = buf;
	buf->prev->next = new_el;
	buf->prev = new_el;
	new_el->info = info;

	size++;
}

template <class T> void List<T>::Delete(int index)
{
	if (!size) return;

	Node *del_el = head;
	for (int i = 0; i < index; i++)
	{
		del_el = del_el->next;
	}

	if (del_el == head) head = del_el->prev;

	del_el->prev->next = del_el->next;
	del_el->next->prev = del_el->prev;

	delete del_el;
	del_el = nullptr;
	size--;
	if (!size) head = nullptr;
}