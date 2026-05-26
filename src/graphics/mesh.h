#ifndef FPS_MESH_H
#define FPS_MESH_H

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace FPS
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();

        void render() const;
        static std::unique_ptr<Mesh> createCube();
        static std::unique_ptr<Mesh> createSphere(float radius, int slices, int stacks);
        static std::unique_ptr<Mesh> createPlane(float width, float height);

    private:
        unsigned int VAO, VBO, EBO;
        unsigned int indexCount;

        void setupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    };
}

#endif
