#include "pch.h"
#include "CppUnitTest.h"
#include "..\LR_03.3rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestCreateNode)
		{
			int value = 10;
			Node* node = createNode(value);
			Assert::IsNotNull(node);
			Assert::AreEqual(value, node->data);
			Assert::IsNull(node->prev);
			Assert::IsNull(node->next);
			delete node;
		}

		TEST_METHOD(TestAppend)
		{
			Node* head = nullptr;
			append(head, 10);
			Assert::IsNotNull(head);
			Assert::AreEqual(10, head->data);
			Assert::IsNull(head->prev);
			Assert::IsNull(head->next);

			append(head, 20);
			Assert::IsNotNull(head->next);
			Assert::AreEqual(20, head->next->data);
			Assert::AreEqual(10, head->next->prev->data);
			Assert::IsNull(head->next->next);

			// Clean up
			delete head->next;
			delete head;
		}

		TEST_METHOD(TestPrintList)
		{
			Node* head = nullptr;
			append(head, 10);
			append(head, 20);
			append(head, 30);

			// Redirect cout to a stringstream
			std::stringstream buffer;
			std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

			printList(head);

			// Restore cout
			std::cout.rdbuf(old);

			Assert::AreEqual(std::string("10 20 30 \n"), buffer.str());

			// Clean up
			delete head->next->next;
			delete head->next;
			delete head;
		}

		TEST_METHOD(TestCountNegativeElements)
		{
			Node* head = nullptr;
			append(head, 10);
			append(head, -20);
			append(head, 30);
			append(head, -40);
			append(head, -15);
			append(head, 25);

			int count = countNegativeElements(head);
			Assert::AreEqual(3, count);

			// Clean up
			Node* temp;
			while (head != nullptr) {
				temp = head;
				head = head->next;
				delete temp;
			}
		}
	};
}
