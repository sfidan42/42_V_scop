#include "inc/glm2/vec.hpp"
#include "dep/lib/inc/glm/glm.hpp"
#include <iostream>
#include <cassert>

int main(void)
{
    // Test default constructor
    {
        glm2::vec3 glm2_v1;
        glm::vec3 glm_v1;

        std::cout << "glm2_v1: " << glm2_v1.x << " " << glm2_v1.y << " " << glm2_v1.z << std::endl;
        std::cout << "glm_v1: " << glm_v1.x << " " << glm_v1.y << " " << glm_v1.z << std::endl;

        std::cout << "Default constructor test passed.\n";
    }

    // Test scalar constructor
    {
        glm2::vec3 glm2_v2(5.0f);
        assert(glm2_v2.x == 5.0f && glm2_v2.y == 5.0f && glm2_v2.z == 5.0f);

        glm::vec3 glm_v2(5.0f);
        assert(glm_v2.x == 5.0f && glm_v2.y == 5.0f && glm_v2.z == 5.0f);

        std::cout << "Scalar constructor test passed.\n";
    }

    // Test copy constructor
    {
        glm2::vec3 glm2_v2(5.0f);
        glm2::vec3 glm2_v3(glm2_v2);
        assert(glm2_v3.x == 5.0f && glm2_v3.y == 5.0f && glm2_v3.z == 5.0f);

        glm::vec3 glm_v2(5.0f);
        glm::vec3 glm_v3(glm_v2);
        assert(glm_v3.x == 5.0f && glm_v3.y == 5.0f && glm_v3.z == 5.0f);

        std::cout << "Copy constructor test passed.\n";
    }

    // Test assignment operator
    {
        glm2::vec3 glm2_v2(5.0f);
        glm2::vec3 glm2_v4;
        glm2_v4 = glm2_v2;
        assert(glm2_v4.x == 5.0f && glm2_v4.y == 5.0f && glm2_v4.z == 5.0f);

        glm::vec3 glm_v2(5.0f);
        glm::vec3 glm_v4;
        glm_v4 = glm_v2;
        assert(glm_v4.x == 5.0f && glm_v4.y == 5.0f && glm_v4.z == 5.0f);

        std::cout << "Assignment operator test passed.\n";
    }

    // Test variadic constructor
    {
        glm2::vec3 glm2_v5(1.0f, 2.0f, 3.0f);
        assert(glm2_v5.x == 1.0f && glm2_v5.y == 2.0f && glm2_v5.z == 3.0f);

        glm::vec3 glm_v5(1.0f, 2.0f, 3.0f);
        assert(glm_v5.x == 1.0f && glm_v5.y == 2.0f && glm_v5.z == 3.0f);

        std::cout << "Variadic constructor test passed.\n";
    }

    // Test array assignment operator
    {
        glm2::vec3 glm2_v6;
        glm2_v6 = {4.0f, 5.0f, 6.0f};
        assert(glm2_v6.x == 4.0f && glm2_v6.y == 5.0f && glm2_v6.z == 6.0f);

        glm::vec3 glm_v6;
        glm_v6 = {4.0f, 5.0f, 6.0f};
        assert(glm_v6.x == 4.0f && glm_v6.y == 5.0f && glm_v6.z == 6.0f);

        std::cout << "Array assignment operator test passed.\n";
    }

    // Test subscript operator (non-const)
    {
        glm2::vec3 glm2_v6 = {4.0f, 5.0f, 6.0f};
        glm2_v6[0] = 7.0f;
        glm2_v6[1] = 8.0f;
        glm2_v6[2] = 9.0f;
        assert(glm2_v6.x == 7.0f && glm2_v6.y == 8.0f && glm2_v6.z == 9.0f);

        glm::vec3 glm_v6 = {4.0f, 5.0f, 6.0f};
        glm_v6[0] = 7.0f;
        glm_v6[1] = 8.0f;
        glm_v6[2] = 9.0f;
        assert(glm_v6.x == 7.0f && glm_v6.y == 8.0f && glm_v6.z == 9.0f);

        std::cout << "Non-const subscript operator test passed.\n";
    }

    // Test subscript operator (const)
    {
        const glm2::vec3 glm2_v7(10.0f, 11.0f, 12.0f);
        assert(glm2_v7[0] == 10.0f && glm2_v7[1] == 11.0f && glm2_v7[2] == 12.0f);

        const glm::vec3 glm_v7(10.0f, 11.0f, 12.0f);
        assert(glm_v7[0] == 10.0f && glm_v7[1] == 11.0f && glm_v7[2] == 12.0f);

        std::cout << "Const subscript operator test passed.\n";
    }

    // Test operator*=
    {
        glm2::vec3 glm2_v8(1.0f, 2.0f, 3.0f);
        glm2_v8 *= 2.0f;
        assert(glm2_v8.x == 2.0f && glm2_v8.y == 4.0f && glm2_v8.z == 6.0f);

        glm::vec3 glm_v8(1.0f, 2.0f, 3.0f);
        glm_v8 *= 2.0f;
        assert(glm_v8.x == 2.0f && glm_v8.y == 4.0f && glm_v8.z == 6.0f);

        std::cout << "operator*= test passed.\n";
    }

    // Test operator-=
    {
        glm2::vec3 glm2_v9(5.0f, 5.0f, 5.0f);
        glm2_v9 -= glm2::vec3(1.0f, 2.0f, 3.0f);
        assert(glm2_v9.x == 4.0f && glm2_v9.y == 3.0f && glm2_v9.z == 2.0f);

        glm::vec3 glm_v9(5.0f, 5.0f, 5.0f);
        glm_v9 -= glm::vec3(1.0f, 2.0f, 3.0f);
        assert(glm_v9.x == 4.0f && glm_v9.y == 3.0f && glm_v9.z == 2.0f);

        std::cout << "operator-= test passed.\n";
    }

    // Test operator+=
    {
        glm2::vec3 glm2_v10(1.0f, 2.0f, 3.0f);
        glm2_v10 += glm2::vec3(4.0f, 5.0f, 6.0f);
        assert(glm2_v10.x == 5.0f && glm2_v10.y == 7.0f && glm2_v10.z == 9.0f);

        glm::vec3 glm_v10(1.0f, 2.0f, 3.0f);
        glm_v10 += glm::vec3(4.0f, 5.0f, 6.0f);
        assert(glm_v10.x == 5.0f && glm_v10.y == 7.0f && glm_v10.z == 9.0f);

        std::cout << "operator+= test passed.\n";
    }

    // Test operator+
    {
        glm2::vec3 glm2_v11 = glm2::vec3(1.0f, 2.0f, 3.0f) + glm2::vec3(4.0f, 5.0f, 6.0f);
        assert(glm2_v11.x == 5.0f && glm2_v11.y == 7.0f && glm2_v11.z == 9.0f);

        glm::vec3 glm_v11 = glm::vec3(1.0f, 2.0f, 3.0f) + glm::vec3(4.0f, 5.0f, 6.0f);
        assert(glm_v11.x == 5.0f && glm_v11.y == 7.0f && glm_v11.z == 9.0f);

        std::cout << "operator+ test passed.\n";
    }

    // Test operator-
    {
        glm2::vec3 glm2_v12 = glm2::vec3(5.0f, 5.0f, 5.0f) - glm2::vec3(1.0f, 2.0f, 3.0f);
        assert(glm2_v12.x == 4.0f && glm2_v12.y == 3.0f && glm2_v12.z == 2.0f);

        glm::vec3 glm_v12 = glm::vec3(5.0f, 5.0f, 5.0f) - glm::vec3(1.0f, 2.0f, 3.0f);
        assert(glm_v12.x == 4.0f && glm_v12.y == 3.0f && glm_v12.z == 2.0f);

        std::cout << "operator- test passed.\n";
    }

    // Test operator* (vec * vec)
    {
        glm2::vec3 glm2_v13 = glm2::vec3(1.0f, 2.0f, 3.0f) * glm2::vec3(4.0f, 5.0f, 6.0f);
        assert(glm2_v13.x == 4.0f && glm2_v13.y == 10.0f && glm2_v13.z == 18.0f);

        glm::vec3 glm_v13 = glm::vec3(1.0f, 2.0f, 3.0f) * glm::vec3(4.0f, 5.0f, 6.0f);
        assert(glm_v13.x == 4.0f && glm_v13.y == 10.0f && glm_v13.z == 18.0f);

        std::cout << "operator* (vec * vec) test passed.\n";
    }

    // Test operator* (vec * scalar)
    {
        glm2::vec3 glm2_v14 = glm2::vec3(1.0f, 2.0f, 3.0f) * 2.0f;
        assert(glm2_v14.x == 2.0f && glm2_v14.y == 4.0f && glm2_v14.z == 6.0f);

        glm::vec3 glm_v14 = glm::vec3(1.0f, 2.0f, 3.0f) * 2.0f;
        assert(glm_v14.x == 2.0f && glm_v14.y == 4.0f && glm_v14.z == 6.0f);

        std::cout << "operator* (vec * scalar) test passed.\n";
    }

    // Test operator==
    {
        glm2::vec3 glm2_v15(1.0f, 2.0f, 3.0f);
        glm2::vec3 glm2_v16(1.0f, 2.0f, 3.0f);
        assert(glm2_v15 == glm2_v16);

        glm::vec3 glm_v15(1.0f, 2.0f, 3.0f);
        glm::vec3 glm_v16(1.0f, 2.0f, 3.0f);
        assert(glm_v15 == glm_v16);

        std::cout << "operator== test passed.\n";
    }

    std::cout << "All tests passed!\n";
    return 0;
}