#pragma once
#include "Critter.h"
class DynamicArray
{
public:
	DynamicArray();
	~DynamicArray();
	Critter* operator[] (const int key) const;
	void Init(float radius, const char* texture, HashTable* hashTable);
	void Destroy(int arrayLoc);
	bool CritterExists(int arrayLoc);
	int GetCritCount();
	void Draw(int arrayLoc);
private:
	int critterCount = 0;
	Critter* critterArray;

	float radius;
	const char* texture;
	HashTable* hashTable;
};

