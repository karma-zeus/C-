#include "mesh.h"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <cmath>

namespace FPS
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
        : indexCount(indices.size())
    {
        setupMesh(vertices, indices);
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void Mesh::setupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        // Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);

        // TexCoord
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    void Mesh::render() const
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    }

    std::unique_ptr<Mesh> Mesh::createCube()
    {
        std::vector<Vertex> vertices = {
            {{-1, -1, -1}, {0, 0, -1}, {0, 0}},
            {{1, -1, -1}, {0, 0, -1}, {1, 0}},
            {{1, 1, -1}, {0, 0, -1}, {1, 1}},
            {{-1, 1, -1}, {0, 0, -1}, {0, 1}},
        };

        std::vector<unsigned int> indices = {
            0, 1, 2, 2, 3, 0
        };

        return std::make_unique<Mesh>(vertices, indices);
    }

    std::unique_ptr<Mesh> Mesh::createSphere(float radius, int slices, int stacks)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (int i = 0; i <= stacks; ++i)
        {
            float phi = glm::pi<float>() * i / stacks;
            for (int j = 0; j <= slices; ++j)
            {
                float theta = 2.0f * glm::pi<float>() * j / slices;
                float x = radius * sin(phi) * cos(theta);
                float y = radius * cos(phi);
                float z = radius * sin(phi) * sin(theta);

                Vertex v;
                v.position = {x, y, z};
                v.normal = glm::normalize(v.position);
                v.texCoord = {(float)j / slices, (float)i / stacks};
                vertices.push_back(v);
            }
        }

        for (int i = 0; i < stacks; ++i)
        {
            for (int j = 0; j < slices; ++j)
            {
                int first = (i * (slices + 1)) + j;
                int second = first + slices + 1;

                indices.push_back(first);
                indices.push_back(second);
                indices.push_back(first + 1);

                indices.push_back(second);
                indices.push_back(second + 1);
                indices.push_back(first + 1);
            }
        }

        return std::make_unique<Mesh>(vertices, indices);
    }

    std::unique_ptr<Mesh> Mesh::createPlane(float width, float height)
    {
        std::vector<Vertex> vertices = {
            {{-width/2, 0, -height/2}, {0, 1, 0}, {0, 0}},
            {{width/2, 0, -height/2}, {0, 1, 0}, {1, 0}},
            {{width/2, 0, height/2}, {0, 1, 0}, {1, 1}},
            {{-width/2, 0, height/2}, {0, 1, 0}, {0, 1}},
        };

        std::vector<unsigned int> indices = {
            0, 1, 2, 2, 3, 0
        };

        return std::make_unique<Mesh>(vertices, indices);
    }
}
