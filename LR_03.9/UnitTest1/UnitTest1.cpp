#include "pch.h"
#include "CppUnitTest.h"
#include "../LR_03.9.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestHeight)
		{
			Node* root = new Node{ nullptr, nullptr, 10 };
			root->left = new Node{ nullptr, nullptr, 5 };
			root->right = new Node{ nullptr, nullptr, 15 };

			Assert::AreEqual(2, Height(root));

			DeleteTree(root);
		}

		TEST_METHOD(TestBFactor)
		{
			Node* root = new Node{ nullptr, nullptr, 10 };
			root->left = new Node{ nullptr, nullptr, 5 };
			root->right = new Node{ nullptr, nullptr, 15 };

			Assert::AreEqual(0, BFactor(root));

			DeleteTree(root);
		}

		TEST_METHOD(TestRightRotation)
		{
			Node* root = new Node{ nullptr, nullptr, 10 };
			root->left = new Node{ nullptr, nullptr, 5 };

			RightRotation(root);

			Assert::AreEqual(5, root->info);
			Assert::IsNotNull(root->right);
			Assert::AreEqual(10, root->right->info);

			DeleteTree(root);
		}

		TEST_METHOD(TestLeftRotation)
		{
			Node* root = new Node{ nullptr, nullptr, 10 };
			root->right = new Node{ nullptr, nullptr, 15 };

			LeftRotation(root);

			Assert::AreEqual(15, root->info);
			Assert::IsNotNull(root->left);
			Assert::AreEqual(10, root->left->info);

			DeleteTree(root);
		}

		TEST_METHOD(TestFindMax)
		{
			Node* root = new Node{ nullptr, nullptr, 10 };
			root->right = new Node{ nullptr, nullptr, 15 };

			Node* maxNode = FindMax(root);

			Assert::IsNotNull(maxNode);
			Assert::AreEqual(15, maxNode->info);

			DeleteTree(root);
		}

		TEST_METHOD(TestBinarySearchInsert)
		{
			Node* root = nullptr;
			bool found = false;

			BinarySearchInsert(root, 10, found);
			Assert::IsNotNull(root);
			Assert::AreEqual(10, root->info);

			BinarySearchInsert(root, 5, found);
			Assert::IsNotNull(root->left);
			Assert::AreEqual(5, root->left->info);

			BinarySearchInsert(root, 15, found);
			Assert::IsNotNull(root->right);
			Assert::AreEqual(15, root->right->info);

			DeleteTree(root);
		}

		TEST_METHOD(TestBinarySearchDelete)
		{
			Node* root = nullptr;
			bool found = false;

			BinarySearchInsert(root, 10, found);
			BinarySearchInsert(root, 5, found);
			BinarySearchInsert(root, 15, found);

			root = BinarySearchDelete(root, 5);
			Assert::IsNull(root->left);

			root = BinarySearchDelete(root, 15);
			Assert::IsNull(root->right);

			root = BinarySearchDelete(root, 10);
			Assert::IsNull(root);

			DeleteTree(root);
		}

		TEST_METHOD(TestBalanceHeight)
		{
			Node* root = nullptr;
			bool found = false;

			BinarySearchInsert(root, 10, found);
			BinarySearchInsert(root, 5, found);
			BinarySearchInsert(root, 15, found);
			BinarySearchInsert(root, 20, found);

			BalanceHeight(root);

			Assert::AreEqual(10, root->info);
			Assert::AreEqual(15, root->right->info);

			DeleteTree(root);
		}

		TEST_METHOD(TestPostfixOrderWithMax)
		{
			Node* root = nullptr;
			bool found = false;

			BinarySearchInsert(root, 10, found);
			BinarySearchInsert(root, 5, found);
			BinarySearchInsert(root, 15, found);

			Node* maxNode = nullptr;
			PostfixOrderWithMax(root, maxNode);

			Assert::IsNotNull(maxNode);
			Assert::AreEqual(15, maxNode->info);

			DeleteTree(root);
		}
	};
}
