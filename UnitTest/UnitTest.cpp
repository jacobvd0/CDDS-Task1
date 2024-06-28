#include "pch.h"
#include "CppUnitTest.h"
#include "../CDDS_Optimise/HashTable.h"
#include "../CDDS_Optimise/Critter.h"
#include "raylib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		

		TEST_METHOD(CritterTest)
		{
			HashTable ht;

			Texture2D crit = LoadTexture("../CDDS_Optimise/res/10.png");

			ht["critter"] = &crit;
			
			Assert::AreEqual(crit.id, ht["critter"]->id);
		}

		TEST_METHOD(DestroyerTest)
		{
			HashTable ht;

			ht["critter"] = &LoadTexture("../CDDS_Optimise/res/10.png");

			Texture2D dest = LoadTexture("../CDDS_Optimise/res/9.png");

			ht["destroyer"] = &dest;

			Assert::AreEqual(dest.id, ht["destroyer"]->id);
		}
	};
}
