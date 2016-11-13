#pragma once

#include <vector>
#include <CL/cl.hpp>
#include <glm/glm.hpp>

#define ATTR_PACKED __attribute__ ((__packed__))

namespace pbd {
    enum VertexAttributes {
        POSITION = 0,
        NORMAL = 1,
        TEX_COORD = 2,
        COLOR = 3,
        VELOCITY = 4,
        MASS = 5
    };

    /**
     * Host (CPU) representation of a vertex.
     * Matches the memory layout of the Vertex struct
     * in kernels/common/Mesh.cl
     *
     * The __padding elements are needed to match vec3's
     * with OpenCL's cl_float3, which * are 4-component
     * vectors.
     */
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
        glm::vec4 color;
    };

    /**
     * Host (CPU) representation of a triangle.
     * Matches the memory layout of the Triangle struct
     * in kernels/common/Mesh.cl
     */
    struct ATTR_PACKED Triangle {
        glm::uvec3 vertices;
    };
}
