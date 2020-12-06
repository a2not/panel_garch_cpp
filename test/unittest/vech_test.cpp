#include <gtest/gtest.h>
#include <panel_garch/matrix>
#include <panel_garch/vech>

TEST(VechTest, Normal) {
    Matrix<int> m(2, 2);
    m[0][0] = 1;
    m[1][0] = 2;
    m[0][1] = 2;
    m[1][1] = 3;
    Matrix<int> t(3, 1);
    t[0][0] = 1;
    t[1][0] = 2;
    t[2][0] = 3;

    ASSERT_TRUE(t == vech(m));
}
