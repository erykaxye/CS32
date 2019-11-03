

#include "newMap.h"
#include <iostream>
#include <cstdlib>
using namespace std; 

Map::Map(const int number)         // Create an empty map (i.e., one with no key/value pairs)
{
	m_nKeys = 0;
	if (number == 0)
		m = new Thing[DEFAULT_MAX_ITEMS];
	else if (number < 0)
	{
		cout << "Integer must be positive" << endl;
		exit(1);
	}
	else
		m = new Thing[number];
}

Map::Map()
{
	m_nKeys = 0;
	m = new Thing[DEFAULT_MAX_ITEMS];
}

Map::~Map() //destructor
{
	delete[] m; ///?????
}

Map::Map(const Map& other) //copy constructor. 
{
	m_nKeys = other.m_nKeys;
	m = new Thing[m_nKeys];
	for (int i = 0; i < m_nKeys; i++)
		m[i] = other.m[i];
}

Map& Map::operator=(const Map& equ) //assignment operator
{
	if (this != &equ) //??
	{
		m_nKeys = equ.m_nKeys;
		delete[] m;
		m = new Thing[m_nKeys];
		for (int i = 0; i < m_nKeys; i++)
			m[i] = equ.m[i];
	}
	return *this;
}

bool Map::empty() const  // Return true if the map is empty, otherwise false. const? 
{
	if (m_nKeys == 0)
		return true;
	return false;
}

int Map::size() const   // Return the number of key/value pairs in the map. const?
{
	return m_nKeys;
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
{
	if (m_nKeys < DEFAULT_MAX_ITEMS) //idk the equal
	{
		//add it to the array? 
		for (int i = 0; i < m_nKeys; i++)
			if (key == m[i].m_k)
				return false;
		m[m_nKeys].m_k = key;
		m[m_nKeys].m_v = value;
		m_nKeys++;
		return true;
	}
	else
		return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
	if (m_nKeys <= DEFAULT_MAX_ITEMS) //idk the equal
	{
		for (int i = 0; i < m_nKeys; i++)
		{
			if (key == m[i].m_k)//array postion i
			{
				m[i].m_v = value;
				//porbbaly delete smth and then map to smth else
				return true;
			}
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
{
	if (m_nKeys <= DEFAULT_MAX_ITEMS) //idk the equal
	{
		for (int i = 0; i < m_nKeys; i++)
		{
			if (key == m[i].m_k)//array postion i
			{
				m[i].m_v = value;
				return true;
			}
		}
		if (m_nKeys < DEFAULT_MAX_ITEMS)
		{
			m[m_nKeys].m_k = key;
			m[m_nKeys].m_v = value;
			m_nKeys++;
			return true;
		}
		return false;
	}
	return false;
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
	if (m_nKeys <= DEFAULT_MAX_ITEMS) //idk the equal
	{
		for (int i = 0; i < m_nKeys; i++)
		{
			if (key == m[i].m_k)//array postion i
			{
				for (i; i < m_nKeys - 1; i++)
				{
					//probably delete smth
					m[i].m_k = m[i + 1].m_k;
					m[i].m_v = m[i + 1].m_v;
				}
				m_nKeys--;
				return true;
			}
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const //const?
											 // Return true if key is equal to a key currently in the map, otherwise
											 // false.
{
	for (int i = 0; i < m_nKeys; i++)
		if (key == m[i].m_k)//array postion i
			return true;
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
	for (int i = 0; i < m_nKeys; i++)
	{
		if (key == m[i].m_k)//array postion i
		{
			//set value to the value it currently maps to?
			value = m[i].m_v;
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
{
	if (i >= 0 && i < size())
	{
		key = m[i].m_k;
		value = m[i].m_v;
		return true;
	}
	return false;
}

//The three-argument get function enables a client to iterate over all elements of a Map because of this property it must have: 
//If nothing is inserted into or erased from the map in the interim, then calling that version of get size() times with the first 
//parameter ranging over each of the integers from 0 to size()-1 inclusive will copy into the other parameters every key/value pair 
//from the map exactly once. The order in which key/value pairs are copied is up to you. In other words, this client code fragment

void Map::swap(Map& other)
// Exchange the contents of this map with the other one. 
{
	Map tempm(*this);
	*this = other;
	other = tempm;
}
//Change the implementation of the swap function so that the number of statement executions when swapping two maps is the 
//same no matter how many key/value pairs are in the maps. (You would not satisfy this requirement if, for example, your swap 
//function caused a loop to visit each pair in the map, since the number of statements executed by all the iterations of the 
//loop would depend on the number of pairs in the map.)
/*
Thimg* tempm = m;
m = other.m;
other.m = tempm;
*/

void Map::dump() const
{

}
