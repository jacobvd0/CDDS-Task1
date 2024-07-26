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

	TEST_CLASS(OriginPointTests)
	{
	public:


		TEST_METHOD(OriginTest)
		{
			Critter testCrit;
			testCrit.SetOrigin({ 0.5,0.5 });
			
			Assert::AreEqual(13.5f, testCrit.OriginTest(27, 25).x);
		}
	};
}
