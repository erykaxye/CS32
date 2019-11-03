
#include "Map.h"
#include <iostream>
//using namespace std; 

Map::Map()         // Create an empty map (i.e., one with no key/value pairs)
{
	m_nKeys = 0;
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
	KeyType tempkey;
	ValueType tempval;
	int counter = m_nKeys;
	m_nKeys = other.m_nKeys;
	other.m_nKeys = counter;

	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		tempkey = m[i].m_k;
		m[i].m_k = other.m[i].m_k;
		other.m[i].m_k = tempkey;

		tempval = m[i].m_v;
		m[i].m_v = other.m[i].m_v;
		other.m[i].m_v = tempval;
	}
}

void Map::dump() const
{

}

