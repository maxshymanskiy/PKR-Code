#include "pch.h"
#include "CppUnitTest.h"
#include "../LR_03.7.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			int trainNumber = 123;
			int hours = 10;
			int minutes = 30;
			Train* trainNode = createTrainNode(trainNumber, hours, minutes);
			Assert::AreEqual(trainNode->trainNumber, trainNumber);
			Assert::AreEqual(trainNode->hours, hours);
			Assert::AreEqual(trainNode->minutes, minutes);
			Assert::IsNull(trainNode->next);
		}
		TEST_METHOD(TestMethod2)
		{
			int trainNumber = 456;
			int hours = 12;
			int minutes = 45;
			Train* trainNode = createTrainNode(trainNumber, hours, minutes);
			Assert::AreEqual(trainNode->trainNumber, trainNumber);
			Assert::AreEqual(trainNode->hours, hours);
			Assert::AreEqual(trainNode->minutes, minutes);
			Assert::IsNull(trainNode->next);
		}
		
	};
}
