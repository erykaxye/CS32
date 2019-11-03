
#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <iostream>
#include <string>
using KeyType = std::string;
using ValueType = double;

class Map
{
public:
	Map();
	Map(const Map& other); //copy
	Map& operator=(const Map& other); //assign
	~Map();
	bool empty() const;
	int size() const;
	bool insert(const KeyType& key, const ValueType& value);
	bool update(const KeyType& key, const ValueType& value);
	bool insertOrUpdate(const KeyType& key, const ValueType& value);
	bool erase(const KeyType& key);
	bool contains(const KeyType& key) const;
	bool get(const KeyType& key, ValueType& value) const;
	bool get(int i, KeyType& key, ValueType& value) const;
	void swap(Map& other);
private:
	struct Node
	{
		KeyType key;
		ValueType value;
		Node *prev;
		Node *next;
	};
	Node *head;
	Node *tail;
};

bool combine(const Map& m1, const Map& m2, Map& result);

void subtract(const Map& m1, const Map& m2, Map& result); 

#endif //MAP_INCLUDED