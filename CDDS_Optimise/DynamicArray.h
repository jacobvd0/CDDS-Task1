#pragma once
#include "Critter.h"
class DynamicArray
{
public:
	DynamicArray();
	~DynamicArray();
	Critter* operator[] (const int key) const;
	void Init(Vector2 position, Vector2 velocity, float radius, const char* texture, HashTable* hashTable);
	void Destroy(int arrayLoc);
	bool CritterExists(int arrayLoc);
	int GetCritCount();
private:
	int critterCount = 0;
	Critter* critterArray;
};

