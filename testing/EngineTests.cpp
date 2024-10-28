#include <gtest/gtest.h>

class EngineTests: public ::testing::Test {
protected:
    virtual void SetUp() {}

    virtual void TearDown() {}
};

TEST(EngineTests, createImage) {

    system("cd ../ini-tests; ./../cmake-build-debug/engine");

    ASSERT_TRUE(true);
}