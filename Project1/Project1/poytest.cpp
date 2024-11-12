#include <iostream>
#include <vector>
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
bool isMouseDragged = false;
float dragStartX = 0.0f;

struct Shape {
    glm::vec3 position;
    glm::vec3 color;
};

std::vector<Shape> shapes;

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

void drawScene() {
    glUseProgram(shaderProgram);

    // Draw moving basket shape (lines instead of filled faces)
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

    glLineWidth(2.0f);  // Use lines instead of filled shapes
    glDrawArrays(GL_LINE_LOOP, 0, 4);  // Draw as lines

    // Draw the red square in the center
    float redSquareVertices[] = {
        -0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.1f,  0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.1f,  0.1f, 0.0f, 1.0f, 0.0f, 0.0f
    };

    model = glm::mat4(1.0f); // Reset model matrix for the new square
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), redSquareVertices);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), redSquareVertices + 3);

    glLineWidth(2.0f);  // Use lines for the square
    glDrawArrays(GL_LINE_LOOP, 0, 4);  // Draw red square as lines

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
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

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void display() {
    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawScene();

    glutSwapBuffers();
}

void mouseMotion(int x, int y) {
    if (isMouseDragged) {
        // Convert mouse x position to OpenGL coordinates (-1 to 1 range)
        float normalizedX = (x - 400) / 400.0f;

        // Split the blue square (moving shape) if the mouse is past the red square
        if (normalizedX > 0.1f) {  // Mouse past the right side of the red square
            xOffset += 0.05f;
        }
        else if (normalizedX < -0.1f) {  // Mouse past the left side of the red square
            xOffset -= 0.05f;
        }
    }
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isMouseDragged = true;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        isMouseDragged = false;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Polygon Slice");

    glewInit();
    initShaders();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMotionFunc(mouseMotion);  // Register mouse motion callback
    glutMouseFunc(mouseButton);   // Register mouse button callback

    glutMainLoop();
    return 0;
}
