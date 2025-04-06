#include "pch.h"
#include "CppUnitTest.h"
#include "../LR_03.6.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestEnqueue)
		{
			Elem* first = nullptr;
			Elem* last = nullptr;
			enqueue(first, last, "test");
			Assert::IsNotNull(first);
			Assert::IsNotNull(last);
			Assert::AreEqual(string("test"), first->info);
			Assert::IsNull(first->link);
		}

		TEST_METHOD(TestDequeue)
		{
			Elem* first = nullptr;
			Elem* last = nullptr;
			enqueue(first, last, "test");
			string value = dequeue(first, last);
			Assert::AreEqual(string("test"), value);
			Assert::IsNull(first);
			Assert::IsNull(last);
		}

		TEST_METHOD(TestPrintQueue)
		{
			Elem* first = nullptr;
			Elem* last = nullptr;
			enqueue(first, last, "test1");
			enqueue(first, last, "test2");
			// Redirect cout to a stringstream to capture the output
			stringstream buffer;
			streambuf* oldCout = cout.rdbuf(buffer.rdbuf());
			printQueue(first);
			cout.rdbuf(oldCout);
			Assert::AreEqual(string("test1 test2 \n"), buffer.str());
		}

		TEST_METHOD(TestAreQueuesEqual)
		{
			Elem* first1 = nullptr;
			Elem* last1 = nullptr;
			Elem* first2 = nullptr;
			Elem* last2 = nullptr;
			enqueue(first1, last1, "test");
			enqueue(first2, last2, "test");
			Assert::IsTrue(areQueuesEqual(first1, first2));
			enqueue(first2, last2, "test2");
			Assert::IsFalse(areQueuesEqual(first1, first2));
		}

		TEST_METHOD(TestDestroyQueue)
		{
			Elem* first = nullptr;
			Elem* last = nullptr;
			enqueue(first, last, "test");
			destroyQueue(first, last);
			Assert::IsNull(first);
			Assert::IsNull(last);
		}

		TEST_METHOD(TestMergeQueues)
		{
			Elem* first1 = nullptr;
			Elem* last1 = nullptr;
			Elem* first2 = nullptr;
			Elem* last2 = nullptr;
			Elem* first3 = nullptr;
			Elem* last3 = nullptr;
			enqueue(first1, last1, "test1");
			enqueue(first2, last2, "test2");
			mergeQueues(first1, last1, first2, last2, first3, last3);
			Assert::IsNull(first1);
			Assert::IsNull(first2);
			Assert::AreEqual(string("test1"), first3->info);
			Assert::AreEqual(string("test2"), first3->link->info);
		}

		TEST_METHOD(TestProcessWords)
		{
			Elem* first = nullptr;
			Elem* last = nullptr;
			processWords("test1 test2", first, last);
			Assert::AreEqual(string("test1"), first->info);
			Assert::AreEqual(string("test2"), first->link->info);
		}

		TEST_METHOD(TestProcessFile)
		{
			Elem* evenQueueFirst = nullptr;
			Elem* evenQueueLast = nullptr;
			Elem* oddQueueFirst = nullptr;
			Elem* oddQueueLast = nullptr;
			ofstream file("testfile.txt");
			file << "line1\nline2\nline3\n";
			file.close();
			processFile("testfile.txt", evenQueueFirst, evenQueueLast, oddQueueFirst, oddQueueLast);
			Assert::AreEqual(string("line1"), oddQueueFirst->info);
			Assert::AreEqual(string("line3"), oddQueueFirst->link->info);
			Assert::AreEqual(string("line2"), evenQueueFirst->info);
			remove("testfile.txt");
		}
	};
}
