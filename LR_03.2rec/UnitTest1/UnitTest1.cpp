#include "pch.h"
#include "CppUnitTest.h"
#include "../LR_03.2rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestEnqueue)
		{
			Elem* first = NULL;
			Elem* last = NULL;
			enqueue(first, last, 10);
			Assert::IsNotNull(first);
			Assert::IsNotNull(last);
			Assert::AreEqual(10, first->info);
			Assert::AreEqual(10, last->info);
		}

		TEST_METHOD(TestDequeue)
		{
			Elem* first = NULL;
			Elem* last = NULL;
			enqueue(first, last, 10);
			enqueue(first, last, 20);
			Info value = dequeue(first, last);
			Assert::AreEqual(10, value);
			Assert::AreEqual(20, first->info);
			Assert::IsNull(first->link);
		}

		TEST_METHOD(TestReverseList)
		{
			Elem* first = NULL;
			Elem* last = NULL;
			enqueue(first, last, 10);
			enqueue(first, last, 20);
			enqueue(first, last, 30);
			reverseList(first, last);
			Assert::AreEqual(30, first->info);
			Assert::AreEqual(20, first->link->info);
			Assert::AreEqual(10, first->link->link->info);
			Assert::IsNull(first->link->link->link);
		}

		TEST_METHOD(TestPrintList)
		{
			Elem* first = NULL;
			Elem* last = NULL;
			enqueue(first, last, 10);
			enqueue(first, last, 20);
			enqueue(first, last, 30);
			std::stringstream buffer;
			std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
			printList(first);
			std::cout.rdbuf(old);
			Assert::AreEqual(std::string("10 20 30 \n"), buffer.str());
		}
	};
}
