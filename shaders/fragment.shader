#version 450 core

uniform sampler2D cubeTexture;

layout (location = 0) in vec2 texturePos;

out vec4 colorOut;

void main() {
    colorOut = texture(cubeTexture, texturePos); //vec4(1, 0, 0, 1);
}
