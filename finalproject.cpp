/*
CAMERA CONTROLS
W - Forward
A - Strafe Left
S - Backward
D - Strafe Right

LIGHT POSITION CONTROLS
UP - Increase Y-axis Value
DOWN - Decrease Y-axis Value
LEFT - Decrease X-axis Value
RIGHT - Increase X-axis Value
RIGHT_SHIFT - Increase Z-axis Value
RIGHT_CTRL - Decrease Z-axis Value
*/
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <gdev.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Exercise 1 - John Tamano & Christian Olivares"
GLFWwindow *pWindow;

//Camera
float yaw = -90.0f;
float pitch = 0.0f;
//Mouse state
bool firstMouse = true;
float lastX = 1280.0f/2.0f;
float lastY = 720.0f/2.0f;
//DeltaTime
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float deltaPulse = 0.0f;
float lastSin = 0.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 lightPosition = glm::vec3(-2.0f, 0.0f, 1.0f);

float fenceVertices[] =
    {
        // position (x,y,z)             color (r,g,b)           normal (x,y,z)      texture(s,t)

        //Picket Cube, Base             //0
        -0.14f, 0.00f, 0.07f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.25f, 0.0f,
        -0.14f, 0.00f, -0.07f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
        0.14f, 0.00f, 0.07f,            1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.75f, 0.0f,
        0.14f, 0.00f, -0.07f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.0f, 0.0f,

        //Picket Cube, Top              //4
        -0.14f, 1.12f, 0.07f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.25f, 1.0f,
        -0.14f, 1.12f, -0.07f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.0f, 1.0f,
        0.14f, 1.12f, 0.07f,            1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.75f, 1.0f,
        0.14f, 1.12f, -0.07f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.0f, 1.0f,

        //Picket Tip                    //8
        0.00f, 1.40f, 0.07f,            1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
        0.00f, 1.40f, -0.07f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.0f, 0.0f,


        //Lower Plank, Base             //10
        -0.50f, 0.28f, 0.06f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.50f, 0.0f,
        -0.50f, 0.28f, -0.06f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.50f, 0.45f,
        0.50f, 0.28f, 0.06f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.50f, 0.0f,
        0.50f, 0.28f, -0.06f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.50f, 0.45f,
    
        //Lower Plank, Top              //14
        -0.50f, 0.42f, 0.06f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.50f, 0.15f,
        -0.50f, 0.42f, -0.06f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.50f, 0.30f,
        0.50f, 0.42f, 0.06f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.50f, 0.15f,
        0.50f, 0.42f, -0.06f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.50f, 0.30f,


        //Upper Plank, Base             //18
        -0.50f, 0.7f, 0.06f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.50f, 0.70f,
        -0.50f, 0.7f, -0.06f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.50f, 1.0f,
        0.50f, 0.7f, 0.06f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.50f, 0.70f,
        0.50f, 0.7f, -0.06f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.50f, 1.0f,
    
        //Upper Plank, Top              //22
        -0.50f, 0.84f, 0.06f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.50f, 0.80f,
        -0.50f, 0.84f, -0.06f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.50f, 0.90f,
        0.50f, 0.84f, 0.06f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.50f, 0.80f,
        0.50f, 0.84f, -0.06f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.50f, 0.90f,
    };

GLuint fenceIndices[] =
    {
        //Picket Base
        0,1,2,
        3,2,1,
        //Front Face Picket Cube
        0,2,4,
        2,6,4,
        //Back Face Picket Cube
        7,3,1,
        1,5,7,
        //Left Face Picket Cube
        5,1,0,
        0,4,5,
        //Right Face Picket Cube
        2,3,6,
        7,6,3,

        //Front Face Tip
        6,8,4,
        //Left Face Tip
        9,5,4,
        4,8,9,
        //Right Face Tip
        6,7,9,
        9,8,6,
        //Back Face Tip
        5,9,7,

        //Lower Plank Base
        10,11,12,
        13,12,11,
        //Lower Plank Top
        16,15,14,
        15,16,17,
        //Lower Plank Front Face
        10,12,14,
        12,16,14,
        //Lower Plank Back Face
        17,13,11,
        11,15,17,
        // //Lower Plank Left Face
        // 15,11,10,
        // 10,14,15,
        // //Lower Plank Right Face
        // 12,13,16,
        // 17,16,13,

        //Upper Plank Base
        18,19,20,
        21,20,19,
        //Upper Plank Top
        24,23,22,
        23,24,25,
        //Upper Plank Front Face
        18,20,22,
        20,24,22,
        //Upper Plank Back Face
        25,21,19,
        19,23,25,
        // //Upper Plank Left Face
        // 23,19,18,
        // 18,22,23,
        // //Upper Plank Right Face
        // 20,21,24,
        // 25,24,21,
    };


float pillarVertices[] =
    {
        // position (x,y,z)             color (r,g,b)           normal (x,y,z)      texture(s,t)

        //Pillar Cube, Base             //0
        -0.14f, 0.00f, 0.14f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.25f, 0.0f,
        -0.14f, 0.00f, -0.14f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
        0.14f, 0.00f, 0.14f,            1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.75f, 0.0f,
        0.14f, 0.00f, -0.14f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.0f, 0.0f,

        //Pillar Cube, Top              //4
        -0.14f, 1.12f, 0.14f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.25f, 1.0f,
        -0.14f, 1.12f, -0.14f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.0f, 1.0f,
        0.14f, 1.12f, 0.14f,            1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.75f, 1.0f,
        0.14f, 1.12f, -0.14f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.0f, 1.0f,

        //Pillar Cap, Base              //8
        -0.28f, 1.12f, 0.28f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    -0.10f, -0.10f,
        -0.28f, 1.12f, -0.28f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    -0.10f, 1.1f,
        0.28f, 1.12f, 0.28f,            1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.1f, -0.10f,
        0.28f, 1.12f, -0.28f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.1f, 1.1f,

        //Pillar Cap, Middle            //12
        -0.28f, 1.19f, 0.28f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
        -0.28f, 1.19f, -0.28f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.0f, 1.0f,
        0.28f, 1.19f, 0.28f,            1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.0f, 0.0f,
        0.28f, 1.19f, -0.28f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    1.0f, 1.0f,

        //Pillar Cap, Top               //16
        -0.14f, 1.30f, 0.14f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.40f, 0.40f,
        -0.14f, 1.30f, -0.14f,          1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.40f, 0.60f,
        0.14f, 1.30f, 0.14f,            1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.60f, 0.40f,
        0.14f, 1.30f, -0.14f,           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 0.0f,    0.60f, 0.60f,
    };

GLuint pillarIndices[] =
    {
        //Pillar Base
        0,1,2,
        3,2,1,
        //Front Face Pillar Cube
        0,2,4,
        2,6,4,
        //Back Face Pillar Cube
        7,3,1,
        1,5,7,
        //Left Face Pillar Cube
        5,1,0,
        0,4,5,
        //Right Face Pillar Cube
        2,3,6,
        7,6,3,

        //Cap Base 
        //Left
        4,8,9,
        9,5,4,
        //Back
        5,9,11,
        11,7,5,
        //Right
        6,7,11,
        11,10,6,
        //Front
        4,6,10,
        10,8,4,

        //Front Face Pillar Cap
        8,10,12,
        14,12,10,
        //Back Face Pillar Cap
        15,11,9,
        9,13,15,
        //Left Face Pillar Cap
        13,9,8,
        8,12,13,
        //Right Face Pillar Cap
        10,11,14,
        15,14,11,

        //Cap Slant 
        //Left
        12,16,17,
        17,13,12,
        //Back
        13,17,19,
        19,15,13,
        //Right
        19,18,15,
        14,15,18,
        //Front
        18,16,14,
        12,14,16,

        //Cap Top
        16,18,17,
        17,18,19,
    };


float axeVertices[] =
    {
        // position (x,y,z)             color (r,g,b)           normal (x,y,z)

        //Base shaft
        0.00f, 0.00f, 0.00f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,
        0.14f, 0.00f, 0.14f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,
        0.14f, 0.00f, -0.14f,           0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,
        0.28f, 0.00f, 0.00f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,

        //Shaft point #1
        -0.14f, 0.43f, 0.00f,           0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f, //#5
        0.00f, 0.43f, 0.14f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,
        0.00f, 0.43f, -0.14f,           0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,
        0.14f, 0.43f, 0.00f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,

        //Shaft point #2
        0.00f, 0.86f, 0.00f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f, //#9
        0.14f, 0.86f, 0.14f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,
        0.14f, 0.86f, -0.14f,           0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,
        0.28f, 0.86f, 0.00f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,

        //Shaft top
        0.00f, 1.57f, 0.00f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f, //#13
        0.14f, 1.57f, 0.14f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,
        0.14f, 1.57f, -0.14f,           0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,
        0.28f, 1.57f, 0.00f,            0.64f, 0.45f, 0.29f,       0.0f, 0.0f, 0.0f,

        //Axe head cube, bottom face
        0.00f, 1.14f, -0.14f,           0.45f, 0.45f, 0.45f,       0.0f, 0.0f, 0.0f, //#17
        0.00f, 1.14f, 0.14f,            0.45f, 0.45f, 0.45f,       0.0f, 0.0f, 0.0f,
        0.28f, 1.14f, -0.14f,           0.45f, 0.45f, 0.45f,       0.0f, 0.0f, 0.0f,
        0.28f, 1.14f, 0.14f,            0.45f, 0.45f, 0.45f,       0.0f, 0.0f, 0.0f,

        //Axe head cube, top face
        0.00f, 1.43f, -0.14f,           0.45f, 0.45f, 0.45f,       0.0f, 0.0f, 0.0f, //#21
        0.00f, 1.43f, 0.14f,            0.45f, 0.45f, 0.45f,       0.0f, 0.0f, 0.0f,
        0.28f, 1.43f, -0.14f,           0.45f, 0.45f, 0.45f,       0.0f, 0.0f, 0.0f,
        0.28f, 1.43f, 0.14f,            0.45f, 0.45f, 0.45f,       0.0f, 0.0f, 0.0f,

        //Axe head blade
        0.71f, 1.86f, 0.00f,            0.75f, 0.75f, 0.75f,       0.0f, 0.0f, 0.0f, //#25
        1.14f, 1.36f, 0.00f,            0.75f, 0.75f, 0.75f,       0.0f, 0.0f, 0.0f,
        0.71f, 0.86f, 0.00f,            0.75f, 0.75f, 0.75f,       0.0f, 0.0f, 0.0f,   

};

GLuint axeIndices[] =
    {
        //Base shaft
        2, 1, 0,
        2, 3, 1,

        //Shaft point #1
        4, 0, 1,
        4, 1, 5,
        6, 2, 0,
        6, 0, 4,
        7, 3, 2,
        7, 2, 6,
        5, 1, 3,
        5, 3, 7,

        //Shaft point #2
        8, 4, 5,
        8, 5, 9,
        10, 6, 4,
        10, 4, 8,
        11, 7, 6,
        11, 6, 10,
        9, 5, 7,
        9, 7, 11,

        //Shaft point #3
        12, 8, 9,
        12, 9, 13,
        14, 10, 8,
        14, 8, 12,
        15, 11, 10,
        15, 10, 14,
        13, 9, 11,
        13, 11, 15,

        //Shaft point top
        14, 12, 13,
        14, 13, 15,

        //Axe head cube
        //Front face
        21, 17, 19,
        21, 19, 23,
        //Left face
        20, 16, 17,
        20, 17, 21,
        //Back face
        22, 18, 16,
        22, 16, 20,
        //Right face
        23, 19, 18,
        23, 18, 22,
        //Bottom Face
        16, 19, 17,
        16, 18, 19,
        //Top Face
        20, 21, 23,
        20, 23, 22,

        //Axe head blade
        //Top & Bottom face
        22, 23, 24,
        18, 26, 19,
        //Front & Back face
        24, 23, 19,
        24, 19, 26,
        24, 18, 22,
        24, 26, 18,
        //Tip Front & Back face 
        24, 26, 25,
        24, 25, 26,

};


void getNormals()
{   


    for(int i = 0; i < static_cast<int>(sizeof(fenceIndices)/(sizeof(int))); i+=3){
        
        //*11 because each vertex has 11 elements
        int vertexA = fenceIndices[i]*11;
        int vertexB = fenceIndices[i+1]*11;
        int vertexC = fenceIndices[i+2]*11;

        glm::vec3 vectorA = glm::vec3(fenceVertices[vertexA], fenceVertices[vertexA+1], fenceVertices[vertexA+2]);
        // std::cout << "VertexA: " << fenceVertices[i] << ", " << fenceVertices[i+1] << ", " << fenceVertices[i+2] << std::endl;
        glm::vec3 vectorB = glm::vec3(fenceVertices[vertexB], fenceVertices[vertexB+1], fenceVertices[vertexB+2]);
        glm::vec3 vectorC = glm::vec3(fenceVertices[vertexC], fenceVertices[vertexC+1], fenceVertices[vertexC+2]);

        glm::vec3 differenceBA = vectorB - vectorA;
        //std::cout << "B-A: " << differenceBA.x << ", " << differenceBA.y << ", " << differenceBA.z << std::endl;
        glm::vec3 differenceCA = vectorC - vectorA;
        

        glm::vec3 crossProduct = glm::cross(differenceBA, differenceCA);
        //std::cout << "Cross: " << crossProduct.x << ", " << crossProduct.y << ", " << crossProduct.z << std::endl;

        glm::vec3 normalVector = glm::normalize(crossProduct);
        //std::cout << "normalVector: " << normalVector.x << ", " << normalVector.y << ", " << normalVector.z << std::endl;

        //Normal of Vertex A
        fenceVertices[vertexA+6] = normalVector.x;
        fenceVertices[vertexA+7] = normalVector.y;
        fenceVertices[vertexA+8] = normalVector.z;
        //Normal of Vertex B
        fenceVertices[vertexB+6] = normalVector.x;
        fenceVertices[vertexB+7] = normalVector.y;
        fenceVertices[vertexB+8] = normalVector.z;
        //Normal of Vertex C
        fenceVertices[vertexC+6] = normalVector.x;
        fenceVertices[vertexC+7] = normalVector.y;
        fenceVertices[vertexC+8] = normalVector.z;
        // std::cout << "Triangle " << i/3 << ": " << fenceVertices[vertexA] << ", " << fenceVertices[vertexB] << ", " << fenceVertices[vertexC] << std::endl;
    };

    for(int i = 0; i < static_cast<int>(sizeof(pillarIndices)/(sizeof(int))); i+=3){
        
        //*11 because each vertex has 11 elements
        int vertexA = pillarIndices[i]*11;
        int vertexB = pillarIndices[i+1]*11;
        int vertexC = pillarIndices[i+2]*11;

        glm::vec3 vectorA = glm::vec3(pillarVertices[vertexA], pillarVertices[vertexA+1], pillarVertices[vertexA+2]);
        // std::cout << "VertexA: " << fenceVertices[i] << ", " << fenceVertices[i+1] << ", " << fenceVertices[i+2] << std::endl;
        glm::vec3 vectorB = glm::vec3(pillarVertices[vertexB], pillarVertices[vertexB+1], pillarVertices[vertexB+2]);
        glm::vec3 vectorC = glm::vec3(pillarVertices[vertexC], pillarVertices[vertexC+1], pillarVertices[vertexC+2]);

        glm::vec3 differenceBA = vectorB - vectorA;
        //std::cout << "B-A: " << differenceBA.x << ", " << differenceBA.y << ", " << differenceBA.z << std::endl;
        glm::vec3 differenceCA = vectorC - vectorA;
        

        glm::vec3 crossProduct = glm::cross(differenceBA, differenceCA);
        //std::cout << "Cross: " << crossProduct.x << ", " << crossProduct.y << ", " << crossProduct.z << std::endl;

        glm::vec3 normalVector = glm::normalize(crossProduct);
        //std::cout << "normalVector: " << normalVector.x << ", " << normalVector.y << ", " << normalVector.z << std::endl;

        //Normal of Vertex A
        pillarVertices[vertexA+6] = normalVector.x;
        pillarVertices[vertexA+7] = normalVector.y;
        pillarVertices[vertexA+8] = normalVector.z;
        //Normal of Vertex B
        pillarVertices[vertexB+6] = normalVector.x;
        pillarVertices[vertexB+7] = normalVector.y;
        pillarVertices[vertexB+8] = normalVector.z;
        //Normal of Vertex C
        pillarVertices[vertexC+6] = normalVector.x;
        pillarVertices[vertexC+7] = normalVector.y;
        pillarVertices[vertexC+8] = normalVector.z;
        // std::cout << "Triangle " << i/3 << ": " << pillarVertices[vertexA] << ", " << pillarVertices[vertexB] << ", " << pillarVertices[vertexC] << std::endl;
    };


    for(int i = 0; i < static_cast<int>(sizeof(axeIndices)/(sizeof(int))); i+=3){
        
        //*9 because each vertex has 9 elements
        int vertexA = axeIndices[i]*9;
        int vertexB = axeIndices[i+1]*9;
        int vertexC = axeIndices[i+2]*9;

        glm::vec3 vectorA = glm::vec3(axeVertices[vertexA], axeVertices[vertexA+1], axeVertices[vertexA+2]);
        // std::cout << "VertexA: " << fenceVertices[i] << ", " << fenceVertices[i+1] << ", " << fenceVertices[i+2] << std::endl;
        glm::vec3 vectorB = glm::vec3(axeVertices[vertexB], axeVertices[vertexB+1], axeVertices[vertexB+2]);
        glm::vec3 vectorC = glm::vec3(axeVertices[vertexC], axeVertices[vertexC+1], axeVertices[vertexC+2]);

        glm::vec3 differenceBA = vectorB - vectorA;
        //std::cout << "B-A: " << differenceBA.x << ", " << differenceBA.y << ", " << differenceBA.z << std::endl;
        glm::vec3 differenceCA = vectorC - vectorA;
        

        glm::vec3 crossProduct = glm::cross(differenceBA, differenceCA);
        //std::cout << "Cross: " << crossProduct.x << ", " << crossProduct.y << ", " << crossProduct.z << std::endl;

        glm::vec3 normalVector = glm::normalize(crossProduct);
        //std::cout << "normalVector: " << normalVector.x << ", " << normalVector.y << ", " << normalVector.z << std::endl;

        //Normal of Vertex A
        axeVertices[vertexA+6] = normalVector.x;
        axeVertices[vertexA+7] = normalVector.y;
        axeVertices[vertexA+8] = normalVector.z;
        //Normal of Vertex B
        axeVertices[vertexB+6] = normalVector.x;
        axeVertices[vertexB+7] = normalVector.y;
        axeVertices[vertexB+8] = normalVector.z;
        //Normal of Vertex C
        axeVertices[vertexC+6] = normalVector.x;
        axeVertices[vertexC+7] = normalVector.y;
        axeVertices[vertexC+8] = normalVector.z;
        //std::cout << "Triangle " << i/27 << ": " << vertices[i+6] << ", " << vertices[i+7] << ", " << vertices[i+8] << std::endl;
    };
};


GLuint vbo, vbo2, vbo3;
GLuint vao, vao2, vao3;
GLuint ebo, ebo2, ebo3;
GLuint shader;
GLuint brownWoodTexture, ebonyWoodTexture;

bool setup()
{
    getNormals();

    //For fenceIndices
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fenceVertices), fenceVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fenceIndices), fenceIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (6 * sizeof(float)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (9 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    //For pillarIndices
    glGenVertexArrays(1, &vao3);
    glGenBuffers(1, &vbo3);
    glGenBuffers(1, &ebo3);
    glBindVertexArray(vao3);
    glBindBuffer(GL_ARRAY_BUFFER, vbo3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pillarVertices), pillarVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pillarIndices), pillarIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (6 * sizeof(float)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*) (9 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    //For axeVertices
    glGenVertexArrays(1, &vao2);
    glGenBuffers(1, &vbo2);
    glGenBuffers(1, &ebo2);
    glBindVertexArray(vao2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axeVertices), axeVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(axeIndices), axeIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) (6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    shader = gdevLoadShader("finalproject.vs", "finalproject.fs");
    if (!shader) return false;
    
    //https://www.freepik.com/free-photo/
    //brown-wooden-flooring_4246371.htm#query=wood%20texture&position=3&from_view=keyword&track=ais&uuid=7d00bbbe-cafd-4a10-b4d9-581342a45521
    brownWoodTexture = gdevLoadTexture("brown-wood.jpg", GL_REPEAT, true, true);
    if (! brownWoodTexture) return false;

    ebonyWoodTexture = gdevLoadTexture("ebony-wood.jpg", GL_MIRRORED_REPEAT, true, true);
    if (! ebonyWoodTexture) return false;

    return true;
}

void render()
{
    glClearColor(0.0f, 0.3f, 0.3f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, brownWoodTexture);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glBindVertexArray(vao);

    //Camera Controls
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    //Light Controls
    glUniform3fv(glGetUniformLocation(shader, "lightPosition"), 1, glm::value_ptr(lightPosition));


    glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

    //We only have to specify a camera position, a target position and a vector that represents the up vector in world space
                                    // camera position, target position, up vector
    glm::mat4 viewMatrix = glm::lookAt(cameraPos,  cameraPos + cameraFront,  cameraUp);

    //PROJECTION-VIEW MATRIX
    glm::mat4 projectionViewMatrix = projectionMatrix * viewMatrix;
    glUniformMatrix4fv(glGetUniformLocation(shader, "projectionViewMatrix"), 1, GL_FALSE, glm::value_ptr(projectionViewMatrix));


    //Draw first model
    //MODEL MATRIX
    glm::mat4 modelMatrix = glm::mat4(1.0f); //identity matrix

    float currentSin = sin(glfwGetTime());
    deltaPulse = currentSin - lastSin;
    lastSin = currentSin;

    float pulse;
    if(deltaPulse >= 0 && currentSin >= 0){
        pulse = sin(glfwGetTime());
    }
    else if(deltaPulse >= 0 && currentSin < 0){
        pulse = fabs(sin(glfwGetTime()));
    }
    else{
        pulse = 1;
    }
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-10.2f, 0.0f, -0.45f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(pulse, pulse, pulse));
    // modelMatrix = glm::rotate(modelMatrix, glm::radians( ( float) - 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 normalMatrix = glm::mat4(glm::transpose(glm::inverse(modelMatrix)));
    glUniformMatrix4fv(glGetUniformLocation(shader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

    //For cubes
    // glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (11 * sizeof(float)));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    


    //Draw second model at the right, set model matrix back
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7f, 0.7f, 0.7f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-13.5f, 0.0f, 0.5f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) - (glfwGetTime())*20), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    normalMatrix = glm::mat4(glm::transpose(glm::inverse(modelMatrix)));
    glUniformMatrix4fv(glGetUniformLocation(shader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

    //For cubes
    // glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (11 * sizeof(float)));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


    /*
    ================
    =====FENCES=====
    ================
    */

    //LEFT
    //1
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.64f, 0.0f, 0.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // normalMatrix = glm::mat4(glm::transpose(glm::inverse(modelMatrix)));
    // glUniformMatrix4fv(glGetUniformLocation(shader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //2
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.64f, 0.0f, -1.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //3
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.64f, 0.0f, -2.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //4
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.64f, 0.0f, -3.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //5
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.64f, 0.0f, -4.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //6
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.64f, 0.0f, -5.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


    //BACK
    //7
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.0f, 0.0f, -5.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //8
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.0f, 0.0f, -5.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //9
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.0f, 0.0f, -5.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //10
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -5.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //11
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(1.0f, 0.0f, -5.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //12
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0f, 0.0f, -5.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //13
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.0f, 0.0f, -5.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


    //RIGHT
    //14
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.64f, 0.0f, 0.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //15
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.64f, 0.0f, -1.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //16
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.64f, 0.0f, -2.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //17
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.64f, 0.0f, -3.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //18
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.64f, 0.0f, -4.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //19
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.64f, 0.0f, -5.0f+0.14f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    


    //FRONT
    //20
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.0f, 0.0f, 0.5f+0.14f+0.14f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //21
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.0f, 0.0f, 0.5f+0.14f+0.14f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //22
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0f, 0.0f, 0.5f+0.14f+0.14f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //23
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.0f, 0.0f, 0.5f+0.14f+0.14f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(fenceIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);



    /*
    ================
    =====PILLARS=====
    ================
    */
    glBindTexture(GL_TEXTURE_2D, ebonyWoodTexture);
    //Back Left
    glBindVertexArray(vao3);
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.2f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.64f, 0.0f, -5.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    normalMatrix = glm::mat4(glm::transpose(glm::inverse(modelMatrix)));
    glUniformMatrix4fv(glGetUniformLocation(shader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(pillarIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //Back Right
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.2f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.64f, 0.0f, -5.5f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(pillarIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //Front Left
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.2f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.64f, 0.0f, 0.5f+0.14f+0.14f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(pillarIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //Front Right
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.2f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(3.64f, 0.0f, 0.5f+0.14f+0.14f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(pillarIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //Entrance Left
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.5f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5f, 0.0f, 0.5f+0.14f+0.14f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(pillarIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    //Entrance Right
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.5f, 1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5f, 0.0f, 0.5f+0.14f+0.14f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glDrawElements(GL_TRIANGLES, sizeof(pillarIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


    //Drawing the axe
    glBindVertexArray(vao2);
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-12.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) - 60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians((float) - (glfwGetTime())*57.5f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    normalMatrix = glm::mat4(glm::transpose(glm::inverse(modelMatrix)));
    glUniformMatrix4fv(glGetUniformLocation(shader, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

    glDrawElements(GL_TRIANGLES, sizeof(axeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

//Source: https://www.youtube.com/watch?v=AWM4CUfffos
void handleKeys(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    float cameraSpeed = 100*deltaTime;

    //For movement
    if(glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if(glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if(glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if(glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    //For controlling light position
    if(glfwGetKey(pWindow, GLFW_KEY_UP) == GLFW_PRESS)
    {
        lightPosition.y += 0.3f;
        std::cout << "X: " << lightPosition.x << ", Y: " << lightPosition.y << ", Z: " << lightPosition.z << std::endl;
    }
    if(glfwGetKey(pWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        lightPosition.y -= 0.3f;
        std::cout << "X: " << lightPosition.x << ", Y: " << lightPosition.y << ", Z: " << lightPosition.z << std::endl;
    }
    if(glfwGetKey(pWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        lightPosition.x -= 0.3f;
        std::cout << "X: " << lightPosition.x << ", Y: " << lightPosition.y << ", Z: " << lightPosition.z << std::endl;
    }
    if(glfwGetKey(pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        lightPosition.x += 0.3f;
        std::cout << "X: " << lightPosition.x << ", Y: " << lightPosition.y << ", Z: " << lightPosition.z << std::endl;
    }
    if(glfwGetKey(pWindow, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
    {
        lightPosition.z += 0.3f;
        std::cout << "X: " << lightPosition.x << ", Y: " << lightPosition.y << ", Z: " << lightPosition.z << std::endl;
    }
    if(glfwGetKey(pWindow, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
    {
        lightPosition.z -= 0.3f;
        std::cout << "X: " << lightPosition.x << ", Y: " << lightPosition.y << ", Z: " << lightPosition.z << std::endl;
    }
}
void handleResize(GLFWwindow *pWindow, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* pWindow, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;

    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;
    lastY = ypos;
    lastX = xpos;

    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    //Avoid the screen being flipped
    if(pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if(pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!pWindow)
    {
        std::cout << "Cannot create the GLFW window.\n";
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1);
    glfwSetWindowAspectRatio(pWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwMakeContextCurrent(pWindow);

    glfwSetKeyCallback(pWindow, handleKeys);
    glfwSetFramebufferSizeCallback(pWindow, handleResize);

    //For Mouse Camera Movement
    glfwSetCursorPosCallback(pWindow, mouse_callback);

    glfwSetInputMode(pWindow, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // if our initial setup is successful...
    if (setup())
    {
        while (!glfwWindowShouldClose(pWindow))
        {
            render();
            glfwSwapBuffers(pWindow);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
