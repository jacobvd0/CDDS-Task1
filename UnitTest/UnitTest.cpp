#include "pch.h"
#include "CppUnitTest.h"
#include "../CDDS_Optimise/HashTable.h"
#include "../CDDS_Optimise/Critter.h"
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
			Texture2D crit = LoadTexture("../CDDS_Optimise/res/10.png");

			HashTable textureTable;
			textureTable["critter"] = &crit;

			Assert::AreSame(crit.id, textureTable["critter"]->id);
		}
	};
}
