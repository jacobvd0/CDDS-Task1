#include "pch.h"
#include "CppUnitTest.h"
#include "HashTable.h"
#include "Critter.h"
#include "raylib.h"

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
			
			Assert::AreSame(crit.id, textureTable["critter"]->id);
		}

		TEST_METHOD(DestroyerTest)
		{
			Texture2D dest = LoadTexture("../CDDS_Optimise/res/9.png");

			HashTable textureTable;
			textureTable["destroyer"] = &dest;

			Assert::AreSame(dest.id, textureTable["destroyer"]->id);
		}
	};

	TEST_CLASS(OriginPointTests)
	{
	public:


		TEST_METHOD(OriginTest)
		{
			HashTable textureTable;
			Critter testCrit;
			//Vector2 expected()

			Texture2D crit = LoadTexture("res/10.png");
			textureTable["critter"] = &crit;

			testCrit.Init({ 0,0 }, { 0, 0 }, 0, "critter", &textureTable);
			testCrit.SetOrigin({ 0.5,0.5 });
			
			testCrit.GetOriginRaw();
			Assert::AreEqual(13.5f, testCrit.GetOriginRaw().x);
		}
	};
}
