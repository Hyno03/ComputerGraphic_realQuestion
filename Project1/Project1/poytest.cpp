#include <iostream>
#include <cstdlib>
#include <ctime>
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

struct RedSquare {
    float xPosition;
    float yPosition;
    float flySpeedX;
    float flySpeedY;
    float fallSpeedX;
    bool isMovingRight;
    bool isSliced;
    std::vector<glm::vec2> trajectory;
};

std::vector<RedSquare> redSquares;

// Basket position and size
const float basketY = -0.75f;
const float basketWidth = 0.4f; // From -0.2 to +0.2
float xOffset = 0.0f;
bool movingRight = true;
int score = 0;

// Gravity, positions, and horizontal movement for sliced triangles
glm::vec3 triangle1Position(0.0f, 0.0f, 0.0f);
glm::vec3 triangle2Position(0.0f, 0.0f, 0.0f);
float fallSpeed1 = 0.0f;
float fallSpeed2 = 0.0f;
float horizontalSpeed1 = -0.002f; // Leftward horizontal movement for the left triangle
float horizontalSpeed2 = 0.002f;  // Rightward horizontal movement for the right triangle

float speed = 0.01f; // ���ϴ� �ӵ� ��
bool isWireframe = false;
bool showTrajectory = false;

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

void spawnRedSquare() {
    RedSquare square;
    square.isMovingRight = (std::rand() % 2 == 0);
    square.xPosition = square.isMovingRight ? -1.0f : 1.0f;
    square.yPosition = -0.5f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.5f)); // y between 0.5 and 1.0

    // �밢������ �̵��ϵ��� x, y �ӵ��� �����ϰ� �����մϴ�.
    square.flySpeedX = square.isMovingRight ? speed * 2 : -speed*2;
    square.flySpeedY = speed/2;

    square.isSliced = false;

    redSquares.push_back(square);
}


void drawText(const std::string& text, float x, float y) {
    glRasterPos2f(x, y);
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

// Function to detect slicing by checking mouse motion
void mouseMotion(int x, int y) {
    float normalizedX = (float)x / 400.0f - 1.0f;
    float normalizedY = 1.0f - (float)y / 300.0f;

    // Check if mouse is over the red square's area to slice
    for (auto& square : redSquares) {
        if (!square.isSliced && normalizedX > square.xPosition - 0.1f && normalizedX < square.xPosition + 0.1f &&
            normalizedY > square.yPosition - 0.1f && normalizedY < square.yPosition + 0.1f) {
            square.isSliced = true; // Trigger slicing
            square.flySpeedY = 0.02f;  // Initial upward speed after slicing

            // Assign opposite horizontal speeds for the two pieces
            square.fallSpeedX = 0.01f;  // Right piece moves right
            square.flySpeedX = -0.01f;  // Left piece moves left
        }
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

    glm::mat4 basketModel = glm::mat4(1.0f);
    basketModel = glm::translate(basketModel, glm::vec3(xOffset, 0.0f, 0.0f));

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(basketModel));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), squareVertices);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), squareVertices + 3);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Render either the full red square or the sliced triangles
    for (const auto& square : redSquares) {
        if (!square.isSliced) {
            // Render full red square
            float redSquareVertices[] = {
                -0.1f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
                 0.1f, -0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
                 0.1f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f,
                -0.1f,  0.1f, 0.0f,  1.0f, 0.0f, 0.0f
            };

            glm::mat4 redSquareModel = glm::mat4(1.0f);
            redSquareModel = glm::translate(redSquareModel, glm::vec3(square.xPosition, square.yPosition, 0.0f));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(redSquareModel));

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), redSquareVertices);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), redSquareVertices + 3);

            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        }
        else {
            // Render the two triangles after slicing
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

            // First triangle (left side)
            glm::mat4 triangle1Model = glm::translate(glm::mat4(1.0f), glm::vec3(square.xPosition - 0.05f, square.yPosition, 0.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(triangle1Model));

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangle1Vertices);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangle1Vertices + 3);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            // Second triangle (right side)
            glm::mat4 triangle2Model = glm::translate(glm::mat4(1.0f), glm::vec3(square.xPosition + 0.05f, square.yPosition, 0.0f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(triangle2Model));

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangle2Vertices);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangle2Vertices + 3);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        if (showTrajectory) {
            glUseProgram(0);  // Trajectory�� �⺻ OpenGL ���� �׸���
            glColor3f(0.0f, 1.0f, 0.0f);  // Trajectory ���� (���)

            glBegin(GL_LINE_STRIP);  // ��θ� ������ ����
            for (const auto& point : square.trajectory) {
                glVertex2f(point.x, point.y);
            }
            glEnd();

            // ���� �ٽ� shaderProgram�� ����Ͽ� ����� ���¸� ������� ����
            glUseProgram(shaderProgram);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(basketModel));
        }
    }
   
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q') {
        exit(0);  // ���α׷� ����
    }
    else if (key == '+') {
        speed = 0.02f;  // �ӵ� ����
        // ��� �簢���� �ӵ��� �� speed ���� ���� ������Ʈ
        for (auto& square : redSquares) {
            square.flySpeedX = square.isMovingRight ? speed * 2 : -speed * 2;
            square.flySpeedY = speed / 2;
        }
    }
    else if (key == '-') {
        speed = 0.006f;  // �ӵ� ����
        // ��� �簢���� �ӵ��� �� speed ���� ���� ������Ʈ
        for (auto& square : redSquares) {
            square.flySpeedX = square.isMovingRight ? speed * 2 : -speed * 2;
            square.flySpeedY = speed / 2;
        }
    }
    else if (key == 'l' || key == 'L') {
        isWireframe = !isWireframe;  // ���� ����
        if (isWireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // �� ���
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // �� ���
        }
    }
    else if (key == 't' || key == 'T') {
        showTrajectory = !showTrajectory;  // ��� ǥ�� ���� ���
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

    static int spawnCounter = 0;
    if (spawnCounter++ > 60) {  // ��: 30�����Ӹ��� �� �簢�� ����
        spawnRedSquare();
        spawnCounter = 0;
    }

    for (auto it = redSquares.begin(); it != redSquares.end();) {
        if (!it->isSliced) {
            // �߸��� ���� ���ڴ� �밢������ �̵�
            it->xPosition += it->flySpeedX;
            it->yPosition += it->flySpeedY;

            if (showTrajectory) {
                it->trajectory.push_back(glm::vec2(it->xPosition, it->yPosition));
                if (it->trajectory.size() > 50) {  // ��� ���� ����
                    it->trajectory.erase(it->trajectory.begin());
                }
            }

            // ȭ���� ����� ���ڸ� �����ϰ� ���ο� ���ڸ� ����
            if (it->xPosition > 1.2f || it->xPosition < -1.2f || it->yPosition > 1.2f || it->yPosition < -1.0f) {
                it = redSquares.erase(it);
            }
            else {
                ++it;
            }
        }else {
            // �߸� ������ �밢�� �̵��� �߷� ȿ�� ����
            it->xPosition += it->fallSpeedX;  // x ���� �̵�
            it->yPosition += it->flySpeedY;   // y ���� �̵� (�߷� ����)
            it->flySpeedY += -0.0005f;        // �߷� ���ӵ�

            // �߸� ������ �ٱ��Ͽ� �����ϸ� ���� ����
            if (it->yPosition <= basketY && 
                it->xPosition >= xOffset - basketWidth / 2 && 
                it->xPosition <= xOffset + basketWidth / 2) {
                score++;  // ���� ����
                it = redSquares.erase(it);  // �ٱ��Ͽ� ������ ����
            }
            // �߸� ������ ȭ�� �Ʒ��� ����� ����
            else if (it->yPosition < -1.0f) {
                it = redSquares.erase(it);
            } else {
                ++it;
            }
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
    std::srand(static_cast<unsigned int>(std::time(0)));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Polygon Slice");

    glewInit();
    initShaders();


    glutDisplayFunc(display);
    glutMotionFunc(mouseMotion); // Detect mouse motion
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
