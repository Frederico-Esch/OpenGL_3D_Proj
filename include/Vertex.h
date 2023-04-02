#pragma once
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec2 TextureCoord;

    Vertex(glm::vec3 position, glm::vec2 textureCoord) : Position(position), TextureCoord(textureCoord) { }
};
