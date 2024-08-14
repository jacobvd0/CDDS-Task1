#include "DynamicArray.h"
#include "HashTable.h"
#include <iostream>
#include "raylib.h"
#include "raymath.h"

DynamicArray::DynamicArray()
{
    critterArray = new Critter[0];
    critterCount = -1;
}

DynamicArray::~DynamicArray()
{
}

Critter* DynamicArray::operator[](const int key) const
{
    return &critterArray[key];
}

void DynamicArray::Init(float _radius, const char* _texture, HashTable* _hashTable)
{
    ++critterCount;
    Critter newCrit;
    if (critterCount != 0) {
        Critter* tmpArray = new Critter[critterCount+3];
        for (int i = 0; i < critterCount; i++) {
            tmpArray[i] = critterArray[i];
        }
        tmpArray[critterCount] = newCrit;
        delete[] critterArray;
        critterArray = tmpArray;
    }
    else {
        Critter* tmpArray = new Critter[critterCount + 2];
        delete[] critterArray;
        critterArray = tmpArray;
    }
    radius = _radius;
    texture = _texture;
    hashTable = _hashTable;
}

void DynamicArray::Destroy(int arrayLoc)
{
    critterCount--;
    if (critterCount < arrayLoc) { return; }
    if (critterCount == 0){
        Critter* tmpArray = new Critter[0];
        delete[] critterArray;
        critterArray = tmpArray;
    }


    Critter* tmpArray = new Critter[critterCount+3];
    int setLoc = 0;

    for (int i = 0; i <= critterCount; i++) {
        if (i == arrayLoc || setLoc >= critterCount) { continue; }
        tmpArray[setLoc] = critterArray[i];
        setLoc++;
    }
    delete[] critterArray;
    critterArray = tmpArray;
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

void DynamicArray::Draw(int arrayLoc)
{
    if (arrayLoc - 1 > critterCount) 
        return;

    Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
    velocity = Vector2Scale(Vector2Normalize(velocity), 80);

    if (!critterArray[arrayLoc].isLoaded())
        critterArray[arrayLoc].Init({ (float)(5 + rand() % (GetScreenWidth() - 10)), (float)(5 + (rand() % GetScreenHeight() - 10))},
            velocity,
            radius, texture, hashTable);

    critterArray[arrayLoc].Draw();
}
