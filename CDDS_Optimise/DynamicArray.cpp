#include "DynamicArray.h"
#include "HashTable.h"
#include <iostream>

DynamicArray::DynamicArray()
{
    critterArray = new Critter[1];
}

DynamicArray::~DynamicArray()
{
}

Critter* DynamicArray::operator[](const int key) const
{
    return &critterArray[key];
}

void DynamicArray::Init(Vector2 position, Vector2 velocity, float radius, const char* texture, HashTable* hashTable)
{
    Critter newCrit;
    if (critterCount != 0) {
        critterCount++;
        Critter* tmpArray = new Critter[critterCount];
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
    std::cout << "CREATE: " << critterCount << "\nPOS: " << position.x << ", " << position.y << "\nVelocity: "<< velocity.x<< ", " << velocity.y << "\nRadius: "<< radius << "\nTexture: " << texture << "\nHashtable: " << hashTable->isWorking() << "\n\n";
    std::cout << "Actual size: " << sizeof(critterArray) << std::endl;
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


    Critter* tmpArray = new Critter[critterCount-1];
    int setLoc = 0;
    for (int i = 0; i <= critterCount; i++) {
        if (i == arrayLoc) { continue; }

        tmpArray[setLoc] = tmpArray[i];
        tmpArray++;
    }
    std::cout << "DESTROY: " << critterCount << "\n";
}

bool DynamicArray::CritterExists(int arrayLoc)
{
    if (arrayLoc + 1 <= critterCount) {
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
