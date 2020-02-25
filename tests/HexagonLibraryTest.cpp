#include "gtest/gtest.h"
#include <hexlib/HexagonLibrary.hpp>

class HexLibraryTest : public ::testing::Test {
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

TEST_F(HexLibraryTest, Add2Hexagons) {

    Hexagon h1(0, 1, -1);
    Hexagon h2(1, 1, -2);
    auto result = HexagonLibrary::Add(h1, h2);

    EXPECT_EQ(result.q, 1);
    EXPECT_EQ(result.r, 2);
    EXPECT_EQ(result.s, -3);
}

TEST_F(HexLibraryTest, ScaleHexagon) {

    Hexagon h(1, 2, -3);
    auto result = HexagonLibrary::Scale(h, 3);

    EXPECT_EQ(result.q, 3);
    EXPECT_EQ(result.r, 6);
    EXPECT_EQ(result.s, -9);
}

TEST_F(HexLibraryTest, GetDirection) {


    auto result = HexagonLibrary::Direction(1);

    EXPECT_EQ(result.q, 1);
    EXPECT_EQ(result.r, -1);
    EXPECT_EQ(result.s, 0);
}

TEST_F(HexLibraryTest, GetHexagonNeighbour) {

    Hexagon h(1, 2, -3);
    auto result = HexagonLibrary::Neighbor(h, 3);

    EXPECT_EQ(result.q, 0);
    EXPECT_EQ(result.r, 2);
    EXPECT_EQ(result.s, -2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}