#include "Map.h"
#include <iostream>
using namespace std; 

Map::Map()
{
	head = tail = nullptr;  
}

Map::Map(const Map& other) //copy
{
	Node *p = other.head; //iterator 
	head = tail = nullptr; 

	if (other.empty())
		return; 

	//insertion for head 
	Node *n = new Node(); 
	n->key = p->key; 
	n->value = p->value; 
	head = tail = n; 
	p = p->next; 

	//insertion for rest to the tail of the list 
	while (p != nullptr)
	{
		insert(p->key, p->value);
		p = p->next; 
	}
	head->prev = tail->next = nullptr;
}

Map& Map::operator=(const Map& other) //assign
{
	if (this != &other) //uh idk
	{
		Map temp(other); 
		swap(temp); 
	}
	return *this; 
}

Map::~Map()
{
	Node *p = head; 
	while (p != nullptr)
	{
		Node *n = p->next; 
		delete p; 
		p = n;
	}
}

bool Map::empty() const
{
	if (head == nullptr && tail == nullptr) //to be safe?: 
		return true;
	return false;
}

int Map::size() const
{
	int size = 0; 
	Node *p = head;
	while (p != nullptr) 
	{
		size++; 
		p = p->next; //lol does this work
	}
	return size; 
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (empty())
	{
		Node *n = new Node; 
		n->key = key; 
		n->value = value; 
		head = tail = n;
		n->next = n->prev = nullptr;
		return true; 
	}
	else if (contains(key))
		return false;
	Node *n = new Node;
	n->key = key;
	n->value = value;
	tail->next = n;
	n->prev = tail; 
	tail = n; 
	n->next = nullptr;
	return true; 
} 

bool Map::update(const KeyType& key, const ValueType& value)
{
	Node *p = head;
	while (p != nullptr) 
	{
		if (p->key == key)
		{
			p->value = value; 
			return true;
		}
		p = p->next;  
	}
	return false; 
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (contains(key))
		update(key, value);
	insert(key, value);
	return true; //always returns true
}

bool Map::erase(const KeyType& key)
{
	if (empty())
		return false;
	if (contains(key))
	{
		if (head->key == key) //if key is head 
		{
			Node *p = head;
			head = p->next;
			delete p;
			head->prev = nullptr; 
			return true; 
		}
		else if (tail->key == key)
		{
			Node *p = tail; 
			tail = p->prev; 
			delete p;
			tail->next = nullptr;
			return true; 
		}
		else if (size() == 1)
		{
			delete head;
			head = tail = nullptr;
			return true;
		}
		else
		{
			Node *n = head;
			while (n != nullptr)
			{
				if (n->next != nullptr && n->next->key == key)
					break;
				n = n->next;
			}
			if (n != nullptr)
			{
				Node *q = n->prev;
				Node *r = n->next;
				q->next = r;
				r->prev = q;
				delete n;
				return true;
			}
		}
	}
	return false; 
}

bool Map::contains(const KeyType& key) const
{
	Node *p = head;
	while (p != nullptr) 
	{
		if (p->key == key)
			return true; 
		p = p->next; 
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	if (contains(key))  
	{
		Node *p = head;
		while (p != nullptr)
		{
			if (p->key == key)
			{
				value = p->value;
				return true;
			}
			p = p->next; 
		}
	}
	return false; 
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < 0 || i >= size())
		return false; 
	Node *p = head;
	int counter = 0; 
	while (counter != i) 
	{
		p = p->next;
		counter++;
	}
	key = p->key;
	value = p->value;
	return true;
}

void Map::swap(Map& other)
{
	Node *temph = head;  //temp head and tail
	Node *tempt = tail; 
	head = other.head; //swaps heads and tails 
	tail = other.tail; 
	other.head = temph;
	other.tail = tempt; 
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
	/*
	if (&m1 == &result) //is this correct? 
	{
		Map temp = m1;
		return true; //aka dont do anything? 
	}
	else if (&m2 == &result)
	{
		Map temp = m2;
		return true;
	}
	*/
	
	if (&m1 == &m2)
	{
		result = m1;
		return true;
	}

	Map temp1 = m1; 
	Map temp2 = m2; 

	temp1.swap(result); 
	bool match = true;

	for (int i = 0; i < temp2.size(); i++)
	{
		KeyType m2k;
		ValueType m2v;
		temp2.get(i, m2k, m2v);
		if (!result.contains(m2k))
			result.insert(m2k, m2v);
		else
		{
			ValueType m1v;
			result.get(m2k, m1v);
			if (m1v != m2v)
			{
				result.erase(m2k);
				match = false;
			}
		}
	}
	return match; 
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
	/*
	if (&m1 == &result) //is this correct? 
		return; //aka dont do anything? 
	else if (&m2 == &result)
		return;
		*/
	if (&m1 == &m2)
	{
		Map empty;
		result.swap(empty);
		return;
	}

	Map temp1 = m1;
	Map temp2 = m2;

	Map empty;
	empty.swap(result);

	for (int i = 0; i < temp1.size(); i++)
	{
		KeyType m1k;
		ValueType m1v;
		temp1.get(i, m1k, m1v);
		
		if (!temp2.contains(m1k))
			result.insert(m1k, m1v); 
	}

}

