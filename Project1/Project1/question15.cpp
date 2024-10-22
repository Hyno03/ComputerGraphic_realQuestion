#include <iostream>
#include <vector>
#include <cmath>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define M_PI 3.14159265358979323846

// Shader source code (with uniforms)
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 modelTransform;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;

void main()
{
    gl_Position = projection * view * modelTransform * vec4(position, 1.0);
    fragColor = color;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 fragColor;
out vec4 color;

void main()
{
    color = vec4(fragColor, 1.0); // use fragment color
}
)";

GLuint shaderProgram;

// Cube vertices and colors
std::vector<GLfloat> cubeVertices = {
    // Positions          // Colors
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
};

std::vector<GLuint> cubeIndices = {
    0, 1, 2, 2, 3, 0, // back face
    4, 5, 6, 6, 7, 4, // front face
    0, 1, 5, 5, 4, 0, // bottom face
    2, 3, 7, 7, 6, 2, // top face
    0, 3, 7, 7, 4, 0, // left face
    1, 2, 6, 6, 5, 1  // right face
};

std::vector<GLfloat> pyramidVertices = {
    // Positions          // Colors
    0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f, // Top vertex (red)
   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // Front-left (green)
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // Front-right (blue)
    0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // Back-right (yellow)
   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f  // Back-left (cyan)
};

std::vector<GLuint> pyramidIndices = {
    0, 1, 2, // Front face
    0, 2, 3, // Right face
    0, 3, 4, // Back face
    0, 4, 1, // Left face
    1, 2, 3, 3, 4, 1  // Base (two triangles)
};

const int coneSlices = 20;
std::vector<GLfloat> coneVertices;
std::vector<GLuint> coneIndices;

const int sphereSlices = 20;
const int sphereStacks = 20;
std::vector<GLfloat> sphereVertices;
std::vector<GLuint> sphereIndices;

void initCone() {
    // Base of the cone (circle)
    for (int i = 0; i < coneSlices; ++i) {
        float angle = 2.0f * M_PI * i / coneSlices;
        coneVertices.push_back(cos(angle) * 0.5f); // x
        coneVertices.push_back(0.0f);              // y
        coneVertices.push_back(sin(angle) * 0.5f); // z
        coneVertices.push_back(1.0f); // color r
        coneVertices.push_back(1.0f); // color g
        coneVertices.push_back(0.0f); // color b
    }

    // Apex of the cone
    coneVertices.push_back(0.0f); // x
    coneVertices.push_back(1.0f); // y (height of the cone)
    coneVertices.push_back(0.0f); // z
    coneVertices.push_back(1.0f); // color r
    coneVertices.push_back(0.0f); // color g
    coneVertices.push_back(0.0f); // color b

    // Creating indices
    for (int i = 0; i < coneSlices; ++i) {
        coneIndices.push_back(i);
        coneIndices.push_back((i + 1) % coneSlices);
        coneIndices.push_back(coneSlices);
    }
}

void initSphere() {
    for (int i = 0; i <= sphereStacks; ++i) {
        float phi = M_PI * i / sphereStacks; // vertical angle
        for (int j = 0; j <= sphereSlices; ++j) {
            float theta = 2.0f * M_PI * j / sphereSlices; // horizontal angle
            float x = sin(phi) * cos(theta);
            float y = cos(phi);
            float z = sin(phi) * sin(theta);

            sphereVertices.push_back(x);
            sphereVertices.push_back(y);
            sphereVertices.push_back(z);
            sphereVertices.push_back(1.0f); // Color red
            sphereVertices.push_back(1.0f); // Color green
            sphereVertices.push_back(1.0f); // Color blue
        }
    }

    for (int i = 0; i < sphereStacks; ++i) {
        for (int j = 0; j < sphereSlices; ++j) {
            sphereIndices.push_back(i * (sphereSlices + 1) + j);
            sphereIndices.push_back((i + 1) * (sphereSlices + 1) + j);
            sphereIndices.push_back(i * (sphereSlices + 1) + (j + 1));

            sphereIndices.push_back((i + 1) * (sphereSlices + 1) + j);
            sphereIndices.push_back((i + 1) * (sphereSlices + 1) + (j + 1));
            sphereIndices.push_back(i * (sphereSlices + 1) + (j + 1));
        }
    }
}


GLuint coneVAO, coneVBO, coneEBO;
GLuint cubeVAO, cubeVBO, cubeEBO;

GLuint pyramidVAO, pyramidVBO, pyramidEBO;
GLuint sphereVAO, sphereVBO, sphereEBO;

// Rotation angles and translation variables
int rotationDirection = 0;
float rotationAngleX = 0.0f;
float rotationAngleY = 0.0f;
float coneX = -1.0f, cubeX = 1.0f;
bool isPyramid = false;

void initShaders() {
    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Cleanup shaders (no longer needed after linking)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


// Initialize cube VAO, VBO, and EBO
void initCube() {
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(GLfloat), cubeVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeIndices.size() * sizeof(GLuint), cubeIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void initConeBuffers() {
    glGenVertexArrays(1, &coneVAO);
    glGenBuffers(1, &coneVBO);
    glGenBuffers(1, &coneEBO);

    glBindVertexArray(coneVAO);

    glBindBuffer(GL_ARRAY_BUFFER, coneVBO);
    glBufferData(GL_ARRAY_BUFFER, coneVertices.size() * sizeof(GLfloat), coneVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, coneEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, coneIndices.size() * sizeof(GLuint), coneIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void initPyramidBuffers() {
    glGenVertexArrays(1, &pyramidVAO);
    glGenBuffers(1, &pyramidVBO);
    glGenBuffers(1, &pyramidEBO);

    glBindVertexArray(pyramidVAO);

    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, pyramidVertices.size() * sizeof(GLfloat), pyramidVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pyramidIndices.size() * sizeof(GLuint), pyramidIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void initSphereBuffers() {
    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glGenBuffers(1, &sphereEBO);

    glBindVertexArray(sphereVAO);

    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(GLfloat), sphereVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(GLuint), sphereIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawCube() {
    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    if (rotationDirection == 3 || rotationDirection == -3) {
        model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    model = glm::translate(model, glm::vec3(cubeX, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);

    
    glBindVertexArray(0);
}

void drawCone() {
    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    if (rotationDirection == 3 || rotationDirection == -3) {
        model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    model = glm::translate(model, glm::vec3(coneX, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));


    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(coneVAO); 
    glDrawElements(GL_TRIANGLES, coneIndices.size(), GL_UNSIGNED_INT, 0);

    
    glBindVertexArray(0);
}

void drawSphere() {
    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    if (rotationDirection == 3 || rotationDirection == -3) {
        model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    model = glm::translate(model, glm::vec3(cubeX, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));


    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);


    glBindVertexArray(0);
}

void drawPyramid() {
    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    if (rotationDirection == 3 || rotationDirection == -3) {
        model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    model = glm::translate(model, glm::vec3(coneX, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));


    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(pyramidVAO);
    glDrawElements(GL_TRIANGLES, pyramidIndices.size(), GL_UNSIGNED_INT, 0);


    glBindVertexArray(0);
}

// Draw axes without transformations
void drawAxes() {
    glBegin(GL_LINES);

    // X-axis
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.75f, 0.0f, 0.0f);
    glVertex3f(0.75f, 0.0f, 0.0f);

    // Y-axis
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -0.75f, 0.0f);
    glVertex3f(0.0f, 0.75f, 0.0f);

    // Z-axis
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -0.6f);
    glVertex3f(0.0f, 0.0f, 0.6f);

    glEnd();
}

// Update the display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Draw the axes without transformations
    glUseProgram(0);
    glPushMatrix();
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    drawAxes();
    glPopMatrix();
    
    glUseProgram(shaderProgram);

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.5f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (isPyramid) {
        drawSphere();
        drawPyramid();
    }
    else {
        drawCube();
        drawCone();
    }

    glutSwapBuffers();
}

void updateAnimation() {
    const float rotationSpeed = 1.0f; // 초당 1도 회전
   
    if (rotationDirection == 1) {
        rotationAngleX += rotationSpeed;
    }
    else if (rotationDirection == -1) {
        rotationAngleX -= rotationSpeed;
    }
    else if (rotationDirection == 2) {
        rotationAngleY += rotationSpeed;
    }
    else if (rotationDirection == -2) {
        rotationAngleY -= rotationSpeed;
    }
    else if (rotationDirection == 3) {
        rotationAngleY += rotationSpeed;
    }
    else if (rotationDirection == -3) {
        rotationAngleY -= rotationSpeed;
    }

    rotationAngleX = fmod(rotationAngleX, 360.0f);


    glutPostRedisplay();
}

// Initialization function
void init() {
    glEnable(GL_DEPTH_TEST);
    initShaders();
    initCube();
    initCone();
    initSphere();
    initPyramidBuffers();
    initSphereBuffers();
    initConeBuffers();
    initCone();
}

void handleKeypress(unsigned char key, int x, int y) {
    const float translationSpeed = 0.1f;
    
    switch (key) {
    case 'x':
        rotationDirection = 1;
        break;
    case 'X':
        rotationDirection = -1;
        break;
    case 'y':
        rotationDirection = 2;
        break;
    case 'Y':
        rotationDirection = -2;
        break;
    case 'r':
        rotationDirection = 3;
        break;
    case 'R':
        rotationDirection = -3;
        break;
    case 'c':
        isPyramid = !isPyramid;
        break;
    case 's':
        rotationAngleX = 0.0f;
        rotationAngleY = 0.0f;
        rotationDirection = 0;
        coneX = -1.0f;
        cubeX = 1.0f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
     
// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Cone Example");

    glewInit();
    init();

    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutIdleFunc(updateAnimation);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();
    return 0;
}
