//
// Created by johnk on 2022/9/11.
//

#include <type_traits>

#include <gtest/gtest.h>

#include <Mirror/TypeInfo.h>

int Add(int a, int b)
{
    return a + b;
}

struct TestClass {
    int a;

    int Add(int b) const
    {
        return a + b;
    }
};

TEST(TypeTest, TypeTraitsTest)
{
    ASSERT_TRUE((std::is_same_v<Mirror::FunctionTraits<decltype(&Add)>::RetType, int>));
    ASSERT_TRUE((std::is_same_v<Mirror::FunctionTraits<decltype(&Add)>::ArgsTupleType, std::tuple<int, int>>));

    ASSERT_TRUE((std::is_same_v<Mirror::MemberVariableTraits<decltype(&TestClass::a)>::ClassType, TestClass>));
    ASSERT_TRUE((std::is_same_v<Mirror::MemberVariableTraits<decltype(&TestClass::a)>::ValueType, int>));

    ASSERT_TRUE((std::is_same_v<Mirror::MemberFunctionTraits<decltype(&TestClass::Add)>::ClassType, const TestClass>));
    ASSERT_TRUE((std::is_same_v<Mirror::MemberFunctionTraits<decltype(&TestClass::Add)>::RetType, int>));
    ASSERT_TRUE((std::is_same_v<Mirror::MemberFunctionTraits<decltype(&TestClass::Add)>::ArgsTupleType, std::tuple<int>>));
}
