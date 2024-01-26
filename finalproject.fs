#version 330 core

in vec3 shaderColor;
in vec2 shaderTexCoord;
in vec3 worldSpaceNormal; //aka n
in vec3 worldSpacePosition;
out vec4 fragmentColor;

uniform sampler2D shaderTexture;

uniform vec3 lightPosition;
vec3 lightColor = vec3(1.0f, 1.0f, 1.0f); //color of light aka C_L
float ambientStrength = 0.7f;
vec3 ambientColor = ambientStrength * lightColor;//ambient color C_D a*C_L


void main()
{

    //Using dot product to find max(dot(n,l),0) aka brightness
    float lightVector = max(dot(worldSpaceNormal, normalize(lightPosition)),0); //C_D

    fragmentColor = vec4(shaderColor, 1.0f)* vec4(lightVector+ambientColor, 1.0f)*texture(shaderTexture, shaderTexCoord);;


}