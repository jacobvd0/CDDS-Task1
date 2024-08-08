#pragma once
#include "raylib.h"
#include <iostream>
class HashTable
{
public:
	Texture2D*& operator[](const char* key) {
		auto hashedKey = Hash(key, strlen(key)) % tableSize;
		return hashTable[hashedKey];
	}

	bool isWorking() {
		return true;
	}
private:
	unsigned int tableSize = 50;
	Texture2D** hashTable = new Texture2D * [tableSize];
	unsigned int Hash(const char* data, unsigned int size) {
		unsigned int hash = 0;
		for (unsigned int i = 0; i < size; i++) {
			hash += data[i];
		}
		return hash;
	}
	
};

