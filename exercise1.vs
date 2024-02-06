#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec2 vertexTexCoord;

uniform mat4 projectionViewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

out vec3 shaderColor;
out vec2 shaderTexCoord;

out vec3 worldSpacePosition; //vector that is transformed using the model matrix only
out vec3 worldSpaceNormal; //vector that is transformed using the normal matrix
out vec3 objectColor;

void main()
{
    shaderColor = vertexColor;
    objectColor = vertexColor;
    shaderTexCoord = vertexTexCoord;

    worldSpacePosition =  (modelMatrix * vec4(vertexPosition, 1.0f)).xyz;
    worldSpaceNormal = (normalMatrix * vec4(vertexNormal, 1.0f)).xyz;
    gl_Position = projectionViewMatrix * vec4(worldSpacePosition, 1.0f);
}