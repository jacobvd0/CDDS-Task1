#include "DynamicArray.h"
#include "HashTable.h"

Critter* DynamicArray::operator[](const int key)
{
    return &critterArray[key];
}

void DynamicArray::Init(Vector2 position, Vector2 velocity, float radius, const char* texture, HashTable* hashTable)
{
    Critter newCrit;
    if (critterCount != 0) {
        critterCount++;
        Critter* tmpArray = new Critter[critterCount+1];
        for (int i = 0; i < critterCount; i++) {
            tmpArray[i] = critterArray[i];
        }
        tmpArray[critterCount] = newCrit;
        delete[] critterArray;
        critterArray = tmpArray;
    }
    else {
        critterCount++;
        Critter* tmpArray = new Critter[critterCount];
        delete[] critterArray;
        critterArray = tmpArray;
    }
    newCrit.Init(position, velocity, radius, texture, hashTable);
}

void DynamicArray::Destroy(int arrayLoc)
{
    if (critterCount >= arrayLoc - 1) { return; }
    if (critterCount - 1 == 0){
        Critter* tmpArray = new Critter[0];
        delete[] critterArray;
        critterArray = tmpArray;
    }


    Critter* tmpArray = new Critter[critterCount - 1];
    int setLoc = 0;
    for (int i = 0; i <= critterCount; i++) {
        if (i == arrayLoc) { return; }

        tmpArray[setLoc] = tmpArray[i];
        tmpArray++;
    }
}

bool DynamicArray::CritterExists(int arrayLoc)
{
    if (arrayLoc + 1 == critterCount) {
        return true;
    }
    else {
        return false;
    }
}

int DynamicArray::GetCritCount()
{
    return critterCount;
}
