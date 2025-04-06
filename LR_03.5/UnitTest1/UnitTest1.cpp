#include "pch.h"
#include "CppUnitTest.h"
#include "../LR_03.5.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestPush)
		{
			Elem* stack = nullptr;
			stack = push(stack, "test");
			Assert::IsNotNull(stack);
			Assert::AreEqual(stack->info, string("test"));
			delete stack;
		}

		TEST_METHOD(TestPop)
		{
			Elem* stack = nullptr;
			stack = push(stack, "test");
			Info value;
			stack = pop(stack, value);
			Assert::AreEqual(value, string("test"));
			Assert::IsNull(stack);
		}

		TEST_METHOD(TestCreateStackFromFile)
		{
			ofstream outFile("testfile.txt");
			outFile << "word1 word2 word3";
			outFile.close();

			Elem* stack = createStackFromFile("testfile.txt");
			Assert::IsNotNull(stack);
			Assert::AreEqual(stack->info, string("word3"));
			stack = pop(stack, stack->info);
			Assert::AreEqual(stack->info, string("word2"));
			stack = pop(stack, stack->info);
			Assert::AreEqual(stack->info, string("word1"));
			stack = pop(stack, stack->info);
			Assert::IsNull(stack);
		}

		TEST_METHOD(TestPrintStack)
		{
			Elem* stack = nullptr;
			stack = push(stack, "test1");
			stack = push(stack, "test2");
			stack = push(stack, "test3");

			// Redirect cout to a stringstream to capture the output
			stringstream buffer;
			streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

			printStack(stack);

			// Restore cout
			cout.rdbuf(oldCout);

			Assert::AreEqual(buffer.str(), string("test3 test2 test1 \n"));

			// Clean up
			while (stack != nullptr) {
				stack = pop(stack, stack->info);
			}
		}

		TEST_METHOD(TestStackLength)
		{
			Elem* stack = nullptr;
			Assert::AreEqual(stackLength(stack), 0);

			stack = push(stack, "test1");
			stack = push(stack, "test2");
			stack = push(stack, "test3");

			Assert::AreEqual(stackLength(stack), 3);

			// Clean up
			while (stack != nullptr) {
				stack = pop(stack, stack->info);
			}
		}

		TEST_METHOD(TestSplitStack)
		{
			Elem* stack = nullptr;
			stack = push(stack, "test1");
			stack = push(stack, "test2");
			stack = push(stack, "test3");
			stack = push(stack, "test4");

			Elem* stack1 = nullptr;
			Elem* stack2 = nullptr;

			splitStack(&stack, 2, &stack1, &stack2);

			Assert::AreEqual(stackLength(stack1), 2);
			Assert::AreEqual(stackLength(stack2), 2);

			// Clean up
			while (stack1 != nullptr) {
				stack1 = pop(stack1, stack1->info);
			}
			while (stack2 != nullptr) {
				stack2 = pop(stack2, stack2->info);
			}
		}

		TEST_METHOD(TestDuplicateStack)
		{
			Elem* stack = nullptr;
			stack = push(stack, "test1");
			stack = push(stack, "test2");
			stack = push(stack, "test3");

			Elem* duplicate = duplicateStack(stack);

			Assert::AreEqual(stackLength(stack), stackLength(duplicate));

			// Clean up
			while (stack != nullptr) {
				stack = pop(stack, stack->info);
			}
			while (duplicate != nullptr) {
				duplicate = pop(duplicate, duplicate->info);
			}
		}
	};
}
