#include "pch.h"
#include "CppUnitTest.h"
#include "../LR_03.8.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestAddStudent)
		{
			Student* head = nullptr;
			addStudent(head, "Smith", 4.5, 1000);
			Assert::IsNotNull(head);
			Assert::AreEqual(std::string("Smith"), head->surname);
			Assert::AreEqual(4.5, head->averageScore);
			Assert::AreEqual(1000, head->scholarship);

			addStudent(head, "Johnson", 3.8, 0);
			Assert::IsNotNull(head->next);
			Assert::AreEqual(std::string("Johnson"), head->next->surname);
			Assert::AreEqual(3.8, head->next->averageScore);
			Assert::AreEqual(0, head->next->scholarship);

			clearList(head);
		}

		TEST_METHOD(TestFindStudentsByAverage)
		{
			Student* head = nullptr;
			addStudent(head, "Smith", 4.5, 1000);
			addStudent(head, "Johnson", 3.8, 0);
			addStudent(head, "Williams", 4.5, 500);

			std::ostringstream output;
			std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

			findStudentsByAverage(head, 4.5);

			std::cout.rdbuf(oldCout);
			std::string result = output.str();
			Assert::IsTrue(result.find("Smith") != std::string::npos);
			Assert::IsTrue(result.find("Williams") != std::string::npos);
			Assert::IsTrue(result.find("Johnson") == std::string::npos);

			clearList(head);
		}

		TEST_METHOD(TestRemoveNonScholarship)
		{
			Student* head = nullptr;
			addStudent(head, "Smith", 4.5, 1000);
			addStudent(head, "Johnson", 3.8, 0);
			addStudent(head, "Williams", 4.0, 0);

			removeNonScholarship(head);

			Assert::IsNotNull(head);
			Assert::AreEqual(std::string("Smith"), head->surname);
			Assert::IsNull(head->next);

			clearList(head);
		}
	};
}
