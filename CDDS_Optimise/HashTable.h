#pragma once
#include "raylib.h"
class HashTable
{
public:
	Texture2D*& operator[](const char* key);
private:
	unsigned int tableSize = 50;
	Texture2D** hashTable = new Texture2D * [tableSize];
	unsigned int Hash(const char* data, unsigned int size);
	
};

