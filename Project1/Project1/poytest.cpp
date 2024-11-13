#include <iostream>
#include <vector>
#include <string>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 model;
out vec3 fragColor;

void main()
{
    gl_Position = model * vec4(position, 1.0);
    fragColor = color;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 fragColor;
out vec4 color;

void main()
{
    color = vec4(fragColor, 1.0);
}
)";

GLuint shaderProgram;
float xOffset = 0.0f;
bool movingRight = true;
bool isSliced = false;
int score = 0;

// Basket position and size
const float basketY = -0.75f;
const float basketWidth = 0.4f; // From -0.2 to +0.2

// Gravity, positions, and horizontal movement for sliced triangles
glm::vec3 triangle1Position(0.0f, 0.0f, 0.0f);
glm::vec3 triangle2Position(0.0f, 0.0f, 0.0f);
float fallSpeed1 = 0.0f;
float fallSpeed2 = 0.0f;
float gravity = -0.001f;
float horizontalSpeed1 = -0.002f; // Leftward horizontal movement for the left triangle
float horizontalSpeed2 = 0.002f;  // Rightward horizontal movement for the right triangle


void initShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void drawText(const std::string& text, float x, float y) {
    glRasterPos2f(x, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawScene() {
    glUseProgram(shaderProgram);

    // Basket
    float squareVertices[] = {
        -0.2f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.2f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.2f, -0.7f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.2f, -0.7f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(xOffset, 0.0f, 0.0f));

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), squareVertices);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), squareVertices + 3);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Draw the falling triangles or square before slicing
    if (!isSliced) {
        // Red Square before slicing
        float originalSquareVertices[] = {
            -0.1f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
             0.1f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
             0.1f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
            -0.1f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f
        };
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), originalSquareVertices);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), originalSquareVertices + 3);

        glm::mat4 centerModel = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(centerModel));

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    else {
        // Draw the two falling triangles after slicing
        float triangle1Vertices[] = {
            -0.1f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
             0.1f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
            -0.1f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f
        };

        float triangle2Vertices[] = {
             0.1f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
             0.1f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
            -0.1f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f
        };

        // Apply translation to the first triangle (left)
        glm::mat4 triangle1Model = glm::translate(glm::mat4(1.0f), triangle1Position);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(triangle1Model));
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangle1Vertices);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangle1Vertices + 3);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Apply translation to the second triangle (right)
        glm::mat4 triangle2Model = glm::translate(glm::mat4(1.0f), triangle2Position);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(triangle2Model));
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangle2Vertices);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangle2Vertices + 3);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void mouseMotion(int x, int y) {
    float normalizedX = (float)x / 400.0f - 1.0f;
    float normalizedY = 1.0f - (float)y / 300.0f;

    if (!isSliced && normalizedX > -0.1f && normalizedX < 0.1f && normalizedY > -0.1f && normalizedY < 0.1f) {
        isSliced = true;
    }
}

void update(int value) {
    if (movingRight) {
        xOffset += 0.01f;
        if (xOffset >= 0.8f) movingRight = false;
    }
    else {
        xOffset -= 0.01f;
        if (xOffset <= -0.8f) movingRight = true;
    }

    if (isSliced) {
        fallSpeed1 += gravity;
        fallSpeed2 += gravity;
        triangle1Position.x += horizontalSpeed1;
        triangle1Position.y += fallSpeed1;
        triangle2Position.x += horizontalSpeed2;
        triangle2Position.y += fallSpeed2;

        // Check if the first triangle lands in the basket
        if (triangle1Position.y <= basketY &&
            triangle1Position.x >= -basketWidth / 2 + xOffset &&
            triangle1Position.x <= basketWidth / 2 + xOffset) {
            score++;
            triangle1Position = glm::vec3(0.0f, 0.0f, 0.0f);
            fallSpeed1 = 0.0f;
        }

        // Check if the second triangle lands in the basket
        if (triangle2Position.y <= basketY &&
            triangle2Position.x >= -basketWidth / 2 + xOffset &&
            triangle2Position.x <= basketWidth / 2 + xOffset) {
            score++;
            triangle2Position = glm::vec3(0.0f, 0.0f, 0.0f);
            fallSpeed2 = 0.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}


void display() {
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawScene();

    // Draw the score at the top center of the screen, independent of transformations
    glUseProgram(0);  // Disable the shader program for simple 2D rendering
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // Set up a simple orthographic projection
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Set text color and position for the score
    glColor3f(0.0f, 0.0f, 0.0f);
    std::string scoreText = "Score: " + std::to_string(score);
    drawText(scoreText, -0.1f, 0.9f);  // Draw the score text at the top center

    // Restore transformations
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Polygon Slice");

    glewInit();
    initShaders();

    glutDisplayFunc(display);
    glutMotionFunc(mouseMotion); // Detect mouse motion
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
