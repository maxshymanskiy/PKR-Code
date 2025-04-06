#include "pch.h"
#include "CppUnitTest.h"
#include "../LR_03.4.it.cpp"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestRemoveFunction)
        {
            Elem* L = nullptr;
            insert(L, 1);
            insert(L, 2);
            insert(L, 3);

            remove(L);

            Assert::IsNull(L, L"Список повинен бути nullptr після видалення");
        }

        TEST_METHOD(TestDisplayFunction)
        {
            Elem* L = nullptr;
            insert(L, 1);
            insert(L, 2);
            insert(L, 3);

            display(L);

            remove(L);
        }

    };
}
