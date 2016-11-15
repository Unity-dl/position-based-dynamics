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
     */
    struct ATTR_PACKED Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
        glm::vec4 color;
    };

    /**
     * Host (CPU) representation of an edge.
     * Matches the memory layout of the Edge struct
     * in kernels/common/Mesh.cl
     */
    struct ATTR_PACKED Edge {
        // [0] is always valid
        // [1] can be -1, which means that this edge belongs to a single triangle
        int triangles[2];

        // [0, 1] are the vertices that make up the edge
        // [2, 3] are the remaining vertices of the connecting triangles
        int vertices[4];
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
