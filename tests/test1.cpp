#include "gtest/gtest.h"

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

};

// Tests that the Foo::Bar() method does Abc.
TEST_F(FooTest, MethodBarDoesAbc) {
    EXPECT_EQ(true, true);
}

// Tests that Foo does Xyz.
TEST_F(FooTest, DoesXyz) {
// Exercises the Xyz feature of Foo.
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}