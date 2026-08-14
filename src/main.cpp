#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cstring>

#include "vec.hpp"

void    test_vec()
{
    vec3f  v(0);
    std::cout << v << std::endl;
    std::cout << "op + " << v + vec3f(1) << std::endl;
    std::cout << "op += " << (v += vec3f(1)) << std::endl;
    std::cout << "add " << v.add(1) << std::endl;

    std::cout << std::endl;

    v = vec3f(0);
    std::cout << v << std::endl;
    std::cout << "op - " << v - vec3f(1) << std::endl;
    std::cout << "op -= " << (v -= vec3f(1)) << std::endl;
    std::cout << "sub " << v.sub(1) << std::endl;

    std::cout << std::endl;

    v = vec3f(1);
    std::cout << v << std::endl;
    std::cout << "op * " << v * 2 << std::endl;
    std::cout << "op *= " << (v *= 2) << std::endl;
    std::cout << "scl " << v.scl(2) << std::endl;

    std::cout << std::endl;

    std::cout << "op -v " << -v << std::endl;
    std::cout << "op == " << (v == v) << std::endl;
    std::cout << "op != " << (v != v) << " " << (v != -v) << std::endl;
}

int main(void)
{
    test_vec();
}
