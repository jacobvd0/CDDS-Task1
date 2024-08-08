#pragma once
#include "Critter.h"
class DynamicArray
{
public:
	Critter* operator[] (const int key);
	void Init(Vector2 position, Vector2 velocity, float radius, const char* texture, HashTable* hashTable);
	void Destroy(int arrayLoc);
	bool CritterExists(int arrayLoc);
	int GetCritCount();
private:
	int critterCount = 0;
	Critter* critterArray = new Critter[0];
};

