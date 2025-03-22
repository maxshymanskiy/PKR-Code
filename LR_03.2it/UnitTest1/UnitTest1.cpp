#include "pch.h"
#include "CppUnitTest.h"
#include "../LR_03.2it.cpp"

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
			Assert::IsNull(first->link);

			enqueue(first, last, 20);
			Assert::AreEqual(10, first->info);
			Assert::AreEqual(20, last->info);
			Assert::IsNotNull(first->link);
			Assert::IsNull(last->link);
		}

		TEST_METHOD(TestDequeue)
		{
			Elem* first = NULL;
			Elem* last = NULL;

			enqueue(first, last, 10);
			enqueue(first, last, 20);

			int value = dequeue(first, last);
			Assert::AreEqual(10, value);
			Assert::AreEqual(20, first->info);
			Assert::IsNull(first->link);

			value = dequeue(first, last);
			Assert::AreEqual(20, value);
			Assert::IsNull(first);
			Assert::IsNull(last);
		}

		TEST_METHOD(TestReverseList)
		{
			Elem* first = NULL;
			Elem* last = NULL;

			for (int i = 1; i <= 5; i++)
				enqueue(first, last, i);

			reverseList(first, last);

			int expectedValues[] = { 5, 4, 3, 2, 1 };
			Elem* current = first;
			for (int i = 0; i < 5; i++)
			{
				Assert::AreEqual(expectedValues[i], current->info);
				current = current->link;
			}
		}

		TEST_METHOD(TestPrintList)
		{
			Elem* first = NULL;
			Elem* last = NULL;

			for (int i = 1; i <= 3; i++)
				enqueue(first, last, i);

			std::stringstream buffer;
			std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

			printList(first);

			std::cout.rdbuf(old);
			std::string text = buffer.str();
			Assert::AreEqual(std::string("1 2 3 \n"), text);
		}
	};
}
