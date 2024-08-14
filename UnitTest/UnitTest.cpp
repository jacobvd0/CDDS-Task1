#include "pch.h"
#include "CppUnitTest.h"
#include "HashTable.h"
#include "Critter.h"
#include "raylib.h"
#include "DynamicArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(HashTableTests)
	{
	public:
		

		TEST_METHOD(CritterTest)
		{
			Texture2D crit = LoadTexture("../CDDS_Optimise/res/10.png");

			HashTable textureTable;
			textureTable["critter"] = &crit;
			
			Assert::AreSame(textureTable["critter"]->id, crit.id);
		}

		TEST_METHOD(DestroyerTest)
		{
			Texture2D dest = LoadTexture("../CDDS_Optimise/res/9.png");

			HashTable textureTable;
			textureTable["destroyer"] = &dest;

			Assert::AreSame(textureTable["destroyer"]->id, dest.id);
		}
	};

	TEST_CLASS(DynamicArrayTests)
	{
	public:


		TEST_METHOD(Adding)
		{
			HashTable hashTable;
			DynamicArray critterArray;
			critterArray.Init(3, "TEST", &hashTable);
			
			
			
			Assert::AreEqual(true, critterArray[0]->critTest());
		}

		TEST_METHOD(Removing)
		{
			HashTable hashTable;
			DynamicArray critterArray;
			for (int i = 0; i <= 3; i++) { // Adds 3 critters to the array
				critterArray.Init(3, "TEST", &hashTable);
			}
			
			// Removes 1, so now there's 2
			critterArray.Destroy(1);

			// Checks if there's 2 critters
			Assert::AreEqual(2, critterArray.GetCritCount());
		}
	};
}
