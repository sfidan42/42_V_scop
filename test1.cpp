#include "inc/glm2/transform.hpp"
#include "inc/glm2/vec.hpp"
#include "inc/glm2/mat.hpp"
#include "dep/lib/inc/glm/glm.hpp"
#include "dep/lib/inc/glm/gtc/matrix_transform.hpp"
#include "dep/lib/inc/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

int main(void)
{
    // Test dot product
    {
        glm2::vec3 glm2_v1(1.0f, 2.0f, 3.0f);
        glm2::vec3 glm2_v2(4.0f, 5.0f, 6.0f);
        float glm2_dot = glm2::dot(glm2_v1, glm2_v2);

        glm::vec3 glm_v1(1.0f, 2.0f, 3.0f);
        glm::vec3 glm_v2(4.0f, 5.0f, 6.0f);
        float glm_dot = glm::dot(glm_v1, glm_v2);

        assert(glm2_dot == glm_dot);
        std::cout << "dot product test passed.\n";
    }

    // Test length
    {
        glm2::vec3 glm2_v(3.0f, 4.0f, 0.0f);
        float glm2_length = glm2::length(glm2_v);

        glm::vec3 glm_v(3.0f, 4.0f, 0.0f);
        float glm_length = glm::length(glm_v);

        assert(glm2_length == glm_length);
        std::cout << "length test passed.\n";
    }

    // Test cross product
    {
        glm2::vec3 glm2_v1(1.0f, 0.0f, 0.0f);
        glm2::vec3 glm2_v2(0.0f, 1.0f, 0.0f);
        glm2::vec3 glm2_cross = glm2::cross(glm2_v1, glm2_v2);


        glm::vec3 glm_v1(1.0f, 0.0f, 0.0f);
        glm::vec3 glm_v2(0.0f, 1.0f, 0.0f);
        glm::vec3 glm_cross = glm::cross(glm_v1, glm_v2);


        assert(glm2_cross.x == glm_cross.x && glm2_cross.y == glm_cross.y && glm2_cross.z == glm_cross.z);
        std::cout << "cross product test passed.\n";
    }

    // Test normalize
    {
        glm2::vec3 glm2_v(3.0f, 4.0f, 0.0f);
        glm2::vec3 glm2_normalized = glm2::normalize(glm2_v);

        std::cout << "glm2_normalized: " << glm2_normalized.x << " " << glm2_normalized.y << " " << glm2_normalized.z << std::endl;

        glm::vec3 glm_v(3.0f, 4.0f, 0.0f);
        glm::vec3 glm_normalized = glm::normalize(glm_v);

        std::cout << "glm_normalized: " << glm_normalized.x << " " << glm_normalized.y << " " << glm_normalized.z << std::endl;

        assert(std::abs(glm2_normalized.x - glm_normalized.x) < 1e-6 &&
               std::abs(glm2_normalized.y - glm_normalized.y) < 1e-6 &&
               std::abs(glm2_normalized.z - glm_normalized.z) < 1e-6);
        std::cout << "normalize test passed.\n";
    }

    // Test lookAt
    {
        glm2::vec3 glm2_camPos(0.0f, 0.0f, 5.0f);
        glm2::vec3 glm2_camTarget(0.0f, 0.0f, 0.0f);
        glm2::vec3 glm2_camUp(0.0f, 1.0f, 0.0f);
        glm2::mat4 glm2_lookAt = glm2::lookAt(glm2_camPos, glm2_camTarget, glm2_camUp);

        glm::vec3 glm_camPos(0.0f, 0.0f, 5.0f);
        glm::vec3 glm_camTarget(0.0f, 0.0f, 0.0f);
        glm::vec3 glm_camUp(0.0f, 1.0f, 0.0f);
        glm::mat4 glm_lookAt = glm::lookAt(glm_camPos, glm_camTarget, glm_camUp);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                assert(std::abs(glm2_lookAt[i][j] - glm_lookAt[i][j]) < 1e-6);
            }
        }
        std::cout << "lookAt test passed.\n";
    }

    // Test rotate
    {
        glm2::mat4 glm2_identity(1.0f);
        glm2::vec3 glm2_axis(0.0f, 1.0f, 0.0f);
        float glm2_angle = glm2::radians(90.0f);
        glm2::mat4 glm2_rotate = glm2::rotate(glm2_identity, glm2_angle, glm2_axis);

        glm::mat4 glm_identity(1.0f);
        glm::vec3 glm_axis(0.0f, 1.0f, 0.0f);
        float glm_angle = glm::radians(90.0f);
        glm::mat4 glm_rotate = glm::rotate(glm_identity, glm_angle, glm_axis);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                assert(std::abs(glm2_rotate[i][j] - glm_rotate[i][j]) < 1e-6);
            }
        }
        std::cout << "rotate test passed.\n";
    }

    // Test perspective
    {
        float glm2_fovy = glm2::radians(45.0f);
        float glm2_aspect = 16.0f / 9.0f;
        float glm2_near = 0.1f;
        float glm2_far = 100.0f;
        glm2::mat4 glm2_perspective = glm2::perspective(glm2_fovy, glm2_aspect, glm2_near, glm2_far);

        float glm_fovy = glm::radians(45.0f);
        float glm_aspect = 16.0f / 9.0f;
        float glm_near = 0.1f;
        float glm_far = 100.0f;
        glm::mat4 glm_perspective = glm::perspective(glm_fovy, glm_aspect, glm_near, glm_far);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                assert(std::abs(glm2_perspective[i][j] - glm_perspective[i][j]) < 1e-6);
            }
        }
        std::cout << "perspective test passed.\n";
    }

    // Test radians
    {
        float glm2_radians = glm2::radians(180.0f);
        float glm_radians = glm::radians(180.0f);

        assert(std::abs(glm2_radians - glm_radians) < 1e-6);
        std::cout << "radians test passed.\n";
    }

    // Test value_ptr
    {
        glm2::mat4 glm2_mat(1.0f);
        const float *glm2_data = glm2::value_ptr(glm2_mat);

        glm::mat4 glm_mat(1.0f);
        const float *glm_data = glm::value_ptr(glm_mat);

        for (int i = 0; i < 16; ++i) {
            assert(std::abs(glm2_data[i] - glm_data[i]) < 1e-6);
        }
        std::cout << "value_ptr test passed.\n";
    }

    std::cout << "All tests passed!\n";
    return 0;
}