#include <cstdlib>
#include <exception>
#include <iostream>
#include <functional>
#include <map>
#include <string>

#include "math.hpp"

#define TEST(expr, expected) \
    std::cout << #expr << "\n" << (expr) << "\nexpected:\n" << expected << "\n" << std::endl

using mat23f = mat<2, 3, float>;
using mat43f = mat<4, 3, float>;
using mat34f = mat<3, 4, float>;
using mat53f = mat<5, 3, float>;

void    ex00()
{
    std::cout << "--- vec ---\n" << std::endl;
    {
        vec2f   u(2, 3);
        vec2f   v(5, 7);
        TEST(u.add(v), "[7, 10]");
    }
    {
        vec2f   u(2, 3);
        vec2f   v(5, 7);
        TEST(u.sub(v), "[-3, -4]");
    }
    {
        vec2f   u(2, 3);
        TEST(u.scl(2), "[4, 6]");
    }

    std::cout << "--- mat ---\n" << std::endl;
    {
        mat2f   u{{1, 2}, {3, 4}};
        mat2f   v{{7, 4}, {-2, 2}};
        TEST(u.add(v), "[8, 6] [1, 6]");
    }
    {
        mat2f   u{{1, 2}, {3, 4}};
        mat2f   v{{7, 4}, {-2, 2}};
        TEST(u.sub(v), "[-6, -2] [5, 2]");
    }
    {
        mat2f   u{{1, 2}, {3, 4}};
        TEST(u.scl(2), "[2, 4] [6, 8]");
    }
}

void    ex01()
{
    vec3f   e1(1, 0, 0);
    vec3f   e2(0, 1, 0);
    vec3f   e3(0, 0, 1);
    vec3f   v1(1, 2, 3);
    vec3f   v2(0, 10, -100);

    TEST(vec3f::linear_combination({e1, e2, e3}, {10, -2, 0.5}), "[10, -2, 0.5]");
    TEST(vec3f::linear_combination({v1, v2}, {10, -2}), "[10, 0, 230]");
}

void    ex02()
{
    TEST(lerp(0.0, 1.0, 0.0), "0");
    TEST(lerp(0.0, 1.0, 1.0), "1");
    TEST(lerp(0.0, 1.0, 0.5), "0.5");
    TEST(lerp(21.0, 42.0, 0.3), "27.3");
    TEST(lerp(vec2f(2, 1), vec2f(4, 2), 0.3), "[2.6, 1.3]");
    TEST(lerp(mat2f{{2, 1}, {3, 4}}, mat2f{{20, 10}, {30, 40}}, 0.5), "[11, 5.5] [16.5, 22]");
}

void    ex03()
{
    TEST(vec2f(0, 0).dot(vec2f(1, 1)), "0");
    TEST(vec2f(1, 1).dot(vec2f(1, 1)), "2");
    TEST(vec2f(-1, 6).dot(vec2f(3, 2)), "9");
}

void    ex04()
{
    vec3f   u(0, 0, 0);
    vec3f   v(1, 2, 3);
    vec2f   w(-1, -2);

    TEST(u.norm_1(), "0");
    TEST(u.norm(), "0");
    TEST(u.norm_inf(), "0");

    TEST(v.norm_1(), "6");
    TEST(v.norm(), "3.74165738");
    TEST(v.norm_inf(), "3");

    TEST(w.norm_1(), "3");
    TEST(w.norm(), "2.236067977");
    TEST(w.norm_inf(), "2");
}

void    ex05()
{
    TEST(vec2f::angle_cos(vec2f(1, 0), vec2f(1, 0)), "1");
    TEST(vec2f::angle_cos(vec2f(1, 0), vec2f(0, 1)), "0");
    TEST(vec2f::angle_cos(vec2f(-1, 1), vec2f(1, -1)), "-1");
    TEST(vec2f::angle_cos(vec2f(2, 1), vec2f(4, 2)), "1");
    TEST(vec3f::angle_cos(vec3f(1, 2, 3), vec3f(4, 5, 6)), "0.974631846");
}

void    ex06()
{
    TEST(vec3f::cross(vec3f(0, 0, 1), vec3f(1, 0, 0)), "[0, 1, 0]");
    TEST(vec3f::cross(vec3f(1, 2, 3), vec3f(4, 5, 6)), "[-3, 6, -3]");
    TEST(vec3f::cross(vec3f(4, 2, -3), vec3f(-2, -5, 16)), "[17, -58, -16]");
}

void    ex07()
{
    std::cout << "--- mul_vec ---\n" << std::endl;
    TEST((mat2f{{1, 0}, {0, 1}} * vec2f(4, 2)), "[4, 2]");
    TEST((mat2f{{2, 0}, {0, 2}} * vec2f(4, 2)), "[8, 4]");
    TEST((mat2f{{2, -2}, {-2, 2}} * vec2f(4, 2)), "[4, -4]");

    std::cout << "--- mul_mat ---\n" << std::endl;
    TEST((mat2f{{1, 0}, {0, 1}} * mat2f{{1, 0}, {0, 1}}), "[1, 0] [0, 1]");
    TEST((mat2f{{1, 0}, {0, 1}} * mat2f{{2, 1}, {4, 2}}), "[2, 1] [4, 2]");
    TEST((mat2f{{3, -5}, {6, 8}} * mat2f{{2, 1}, {4, 2}}), "[-14, -7] [44, 22]");
}

void    ex08()
{
    TEST((mat2f{{1, 0}, {0, 1}}.trace()), "2");
    TEST((mat3f{{2, -5, 0}, {4, 3, 7}, {-2, 3, 4}}.trace()), "9");
    TEST((mat3f{{-2, -8, 4}, {1, -23, 4}, {0, 6, 4}}.trace()), "-21");
}

void    ex09()
{
    TEST((mat2f{{1, 2}, {3, 4}}.transpose()), "[1, 3] [2, 4]");
    TEST((mat3f{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}.transpose()), "[1, 4, 7] [2, 5, 8] [3, 6, 9]");
    TEST((mat23f{{1, 2}, {3, 4}, {5, 6}}.transpose()), "[1, 3, 5] [2, 4, 6]");
}

void    ex10()
{
    TEST((mat3f{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}.row_echelon()), "[1, 0, 0] [0, 1, 0] [0, 0, 1]");
    TEST((mat2f{{1, 2}, {3, 4}}.row_echelon()), "[1, 0] [0, 1]");
    TEST((mat2f{{1, 2}, {2, 4}}.row_echelon()), "[1, 2] [0, 0]");
    TEST((mat53f{
        {8, 5, -2, 4, 28},
        {4, 2.5, 20, 4, -4},
        {8, 5, 1, 4, 17},
    }.row_echelon()), "[1, 0.625, 0, 0, -12.1666667] [0, 0, 1, 0, -3.6666667] [0, 0, 0, 1, 29.5]");
}

void    ex11()
{
    TEST((mat2f{{1, -1}, {-1, 1}}.determinant()), "0");
    TEST((mat3f{{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}.determinant()), "8");
    TEST((mat3f{{8, 5, -2}, {4, 7, 20}, {7, 6, 1}}.determinant()), "-174");
    TEST((mat4f{
        {8, 5, -2, 4},
        {4, 2.5, 20, 4},
        {8, 5, 1, 4},
        {28, -4, 17, 1},
    }.determinant()), "1032");
}

void    ex12()
{
    TEST((mat3f{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}.inverse()), "[1, 0, 0] [0, 1, 0] [0, 0, 1]");
    TEST((mat3f{{2, 0, 0}, {0, 2, 0}, {0, 0, 2}}.inverse()), "[0.5, 0, 0] [0, 0.5, 0] [0, 0, 0.5]");
    TEST((mat3f{{8, 5, -2}, {4, 7, 20}, {7, 6, 1}}.inverse()),
        "[0.649425287, 0.097701149, -0.655172414] [-0.781609195, -0.126436782, 0.965517241] [0.143678161, 0.074712644, -0.206896552]");
}

void    ex13()
{
    TEST((mat3f{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}.rank()), "3");
    TEST((mat43f{
        {1, 2, 0, 0},
        {2, 4, 0, 0},
        {-1, 2, 1, 1},
    }.rank()), "2");
    TEST((mat34f{
        {8, 5, -2},
        {4, 7, 20},
        {7, 6, 1},
        {21, 18, 7},
    }.rank()), "3");
}

void    ex14()
{
    mat4f   p = mat4f::perspective(90, 16.0f / 9.0f, 0.1, 100);

    for (std::size_t col = 0; col < 4; col++)
    {
        for (std::size_t row = 0; row < 4; row++)
            std::cout << p(col, row) << (row != 3 ? ", " : "\n");
    }
}

const std::map<std::string, std::function<void(void)>>    funcs = {
    {"ex00", ex00},
    {"ex01", ex01},
    {"ex02", ex02},
    {"ex03", ex03},
    {"ex04", ex04},
    {"ex05", ex05},
    {"ex06", ex06},
    {"ex07", ex07},
    {"ex08", ex08},
    {"ex09", ex09},
    {"ex10", ex10},
    {"ex11", ex11},
    {"ex12", ex12},
    {"ex13", ex13},
    {"ex14", ex14},
};

static void run(const std::string& name, const std::function<void(void)>& f)
{
    std::cout << "===== " << name << " =====\n" << std::endl;
    try
    {
        f();
    }
    catch (const std::exception& e)
    {
        std::cout << "!! " << e.what() << '\n' << std::endl;
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: ./matrix <ex?? | all>" << std::endl;
        return (1);
    }

    if (std::string(av[1]) == "all")
    {
        for (const auto& [name, f] : funcs)
            run(name, f);
        return (0);
    }

    auto    find = funcs.find(av[1]);
    if (find == funcs.end() || !find->second)
    {
        std::cerr << "Invalid input: " << av[1] << std::endl;
        return (1);
    }

    run(find->first, find->second);
}
