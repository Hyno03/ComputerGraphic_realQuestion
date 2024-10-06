#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

struct Square {
    float x, y;
    float r, g, b; // ����
};

struct Line {
    float x1, y1, x2, y2; // ���� �������� ����
    float r, g, b;        // ����
};

struct Triangle {
    float x1, y1, x2, y2, x3, y3; // �ﰢ���� �� ��
    float r, g, b;                // ����
};

std::vector<Square> squares;    // �簢���� ������ ����
std::vector<Line> lines;        // ���� ������ ����
std::vector<Triangle> triangles; // �ﰢ���� ������ ����

bool isPointMode = false;       // �� ���� ��� ����
bool isLineMode = false;        // �� �׸��� ��� ����
bool isTriangleMode = false;    // �ﰢ�� �׸��� ��� ����
bool isSquareMode = false;      // �簢�� �׸��� ��� ����

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void mouseClick(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void update(int value);

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(0))); // ���� �õ� �ʱ�ȭ

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600); // ������ ũ�� ����
    glutCreateWindow("Example1");
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMouseFunc(mouseClick); // ���콺 Ŭ�� �̺�Ʈ ���
    glutKeyboardFunc(keyboard); // Ű���� �Է� ���
    glutTimerFunc(16, update, 0); // ������Ʈ �Լ� ȣ�� ����
    glutMainLoop();

    return 0;
}

GLvoid drawScene()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // £�� ȸ�� ���
    glClear(GL_COLOR_BUFFER_BIT);

    // ����� �簢���� ��� �׸���
    for (const auto& square : squares) {
        // �簢�� ���� ����
        glColor3f(square.r, square.g, square.b);
        glBegin(GL_QUADS);
        glVertex2f(square.x - 5, square.y - 5); // �簢�� ũ�� 10x10���� ����
        glVertex2f(square.x + 5, square.y - 5);
        glVertex2f(square.x + 5, square.y + 5);
        glVertex2f(square.x - 5, square.y + 5);
        glEnd();

        // �簢�� �׵θ� ����
        glColor3f(0.0f, 0.0f, 0.0f); // ������ �׵θ�
        glBegin(GL_LINE_LOOP); // ������ �׵θ� �׸���
        glVertex2f(square.x - 5, square.y - 5);
        glVertex2f(square.x + 5, square.y - 5);
        glVertex2f(square.x + 5, square.y + 5);
        glVertex2f(square.x - 5, square.y + 5);
        glEnd();
    }

    // ����� ���� ��� �׸���
    for (const auto& line : lines) {
        glColor3f(line.r, line.g, line.b); // �� ���� ����
        glBegin(GL_LINES);
        glVertex2f(line.x1, line.y1);
        glVertex2f(line.x2, line.y2);
        glEnd();
    }

    // ����� �ﰢ���� ��� �׸���
    for (const auto& triangle : triangles) {
        // �ﰢ�� ���� ����
        glColor3f(triangle.r, triangle.g, triangle.b);
        glBegin(GL_TRIANGLES);
        glVertex2f(triangle.x1, triangle.y1);
        glVertex2f(triangle.x2, triangle.y2);
        glVertex2f(triangle.x3, triangle.y3);
        glEnd();

        // �ﰢ�� �׵θ� ����
        glColor3f(0.0f, 0.0f, 0.0f); // ������ �׵θ�
        glBegin(GL_LINE_LOOP); // ������ �׵θ� �׸���
        glVertex2f(triangle.x1, triangle.y1);
        glVertex2f(triangle.x2, triangle.y2);
        glVertex2f(triangle.x3, triangle.y3);
        glEnd();
    }

    glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); // ���� ��� ��� ����
    glLoadIdentity(); // �⺻ ��ķ� �ʱ�ȭ
    glOrtho(0, w, 0, h, -1, 1); // ��ǥ�� ���� (���� �Ʒ��� 0, 0)
    glMatrixMode(GL_MODELVIEW); // �� �� ��� ���� ��ȯ
}

int squaresCount = 0;
void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        int transformedY = windowHeight - y; // ������ ��ǥ�踦 OpenGL ��ǥ��� ��ȯ

        int totalShapes = squares.size() + lines.size() + (triangles.size() - squaresCount*2) + squaresCount;

        if (totalShapes < 10) {
            if (isPointMode) {
                // �� ���� ����� ��
                Square newSquare;
                newSquare.x = x;
                newSquare.y = transformedY;
                newSquare.r = static_cast<float>(rand()) / RAND_MAX;
                newSquare.g = static_cast<float>(rand()) / RAND_MAX;
                newSquare.b = static_cast<float>(rand()) / RAND_MAX;
                squares.push_back(newSquare);
            }
            if (isLineMode) {
                // ���� ũ��� �������� ���� �׸���
                Line newLine;
                newLine.r = static_cast<float>(rand()) / RAND_MAX;
                newLine.g = static_cast<float>(rand()) / RAND_MAX;
                newLine.b = static_cast<float>(rand()) / RAND_MAX;

                // ���� ���̸� �������� ����
                float length = 50.0f + static_cast<float>(rand() % 100); // 50 ~ 150 ������ ��

                // ���� ������ ������ ������ ����
                float angle = static_cast<float>(rand()) / RAND_MAX * 360.0f;
                float radians = angle * 3.14159f / 180.0f;

                // Ŭ���� ��ġ�� �߽����� ���� �������� ���� ���
                newLine.x1 = x - length / 2 * cos(radians);
                newLine.y1 = transformedY - length / 2 * sin(radians);
                newLine.x2 = x + length / 2 * cos(radians);
                newLine.y2 = transformedY + length / 2 * sin(radians);

                lines.push_back(newLine); // ���Ϳ� �� �߰�
            }
            if (isTriangleMode) {
                // ���� ũ��� �������� �ﰢ���� �׸���
                Triangle newTriangle;
                newTriangle.r = static_cast<float>(rand()) / RAND_MAX;
                newTriangle.g = static_cast<float>(rand()) / RAND_MAX;
                newTriangle.b = static_cast<float>(rand()) / RAND_MAX;

                // �ﰢ���� ũ�⸦ �������� ����
                float size = 30.0f + static_cast<float>(rand() % 50); // 30 ~ 80 ũ���� �ﰢ��

                // Ŭ���� ��ġ�� �������� ���� ũ���� �ﰢ���� ������ ����
                newTriangle.x1 = x;
                newTriangle.y1 = transformedY + size;  // ���� ��
                newTriangle.x2 = x - size / 2;
                newTriangle.y2 = transformedY - size / 2;  // ���� �Ʒ� ��
                newTriangle.x3 = x + size / 2;
                newTriangle.y3 = transformedY - size / 2;  // ������ �Ʒ� ��

                triangles.push_back(newTriangle); // ���Ϳ� �ﰢ�� �߰�
            }
            if (isSquareMode) {
                // ���� ũ��� �������� �簢���� �׸���
                Triangle triangle1, triangle2; // �� ���� �ﰢ������ �簢���� ����
                triangle1.r = static_cast<float>(rand()) / RAND_MAX;
                triangle1.g = static_cast<float>(rand()) / RAND_MAX;
                triangle1.b = static_cast<float>(rand()) / RAND_MAX;
                triangle2.r = triangle1.r;
                triangle2.g = triangle1.g;
                triangle2.b = triangle1.b;
                float size = 30.0f + static_cast<float>(rand() % 50); // 30 ~ 80 ũ���� �簢��

                // Ŭ���� ��ġ�� �������� �簢���� �� �ﰢ�� ����
                triangle1.x1 = x - size / 2;       triangle1.y1 = transformedY + size / 2; // ���� ��
                triangle1.x2 = x + size / 2;       triangle1.y2 = transformedY + size / 2; // ������ ��
                triangle1.x3 = x - size / 2;       triangle1.y3 = transformedY - size / 2; // ���� �Ʒ�

                triangle2.x1 = x + size / 2;       triangle2.y1 = transformedY + size / 2; // ������ ��
                triangle2.x2 = x + size / 2;       triangle2.y2 = transformedY - size / 2; // ������ �Ʒ�
                triangle2.x3 = x - size / 2;       triangle2.y3 = transformedY - size / 2; // ���� �Ʒ�

                triangles.push_back(triangle1); // ù ��° �ﰢ�� �߰�
                triangles.push_back(triangle2); // �� ��° �ﰢ�� �߰�
                
                squaresCount += 1;
            }
        }
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
        isPointMode = !isPointMode; // �� �׸��� ��� ���
        isLineMode = false;        // �� ��忡���� �� ��� ��Ȱ��ȭ
        isTriangleMode = false;    // �� ��忡���� �ﰢ�� ��� ��Ȱ��ȭ
        isSquareMode = false;      // �� ��忡���� �簢�� ��� ��Ȱ��ȭ
        break;
    case 'l':
        isLineMode = !isLineMode; // �� �׸��� ��� ���
        isPointMode = false;       // �� ��忡���� �� ��� ��Ȱ��ȭ
        isTriangleMode = false;    // �� ��忡���� �ﰢ�� ��� ��Ȱ��ȭ
        isSquareMode = false;      // �� ��忡���� �簢�� ��� ��Ȱ��ȭ
        break;
    case 't':
        isTriangleMode = !isTriangleMode; // �ﰢ�� �׸��� ��� ���
        isPointMode = false;              // �ﰢ�� ��忡���� �� ��� ��Ȱ��ȭ
        isLineMode = false;               // �ﰢ�� ��忡���� �� ��� ��Ȱ��ȭ
        isSquareMode = false;             // �ﰢ�� ��忡���� �簢�� ��� ��Ȱ��ȭ
        break;
    case 'r':
        isSquareMode = !isSquareMode; // �簢�� �׸��� ��� ���
        isPointMode = false;           // �簢�� ��忡���� �� ��� ��Ȱ��ȭ
        isLineMode = false;            // �簢�� ��忡���� �� ��� ��Ȱ��ȭ
        isTriangleMode = false;        // �簢�� ��忡���� �ﰢ�� ��� ��Ȱ��ȭ
        break;
    case 'c':
        // ��� ���� ����
        squares.clear();
        lines.clear();
        triangles.clear();
        break;
    case 'w':
        // �����ϰ� ���� �ϳ� �����Ͽ� ���� �̵�
        if (!squares.empty() || !lines.empty() || !triangles.empty()) {
            int totalShapes = squares.size() + lines.size() + triangles.size();
            int randomIndex = rand() % totalShapes; // ���� �ε��� ����

            if (randomIndex < squares.size()) {
                // �簢���� ������ ���
                squares[randomIndex].y += 10; // �簢���� ���� 10��ŭ �̵�
            }
            else if (randomIndex < squares.size() + lines.size()) {
                // ���� ������ ���
                int lineIndex = randomIndex - squares.size();
                lines[lineIndex].y1 += 10; // ���� ������ ���� 10��ŭ �̵�
                lines[lineIndex].y2 += 10; // ���� ���� ���� 10��ŭ �̵�
            }
            else {
                // �ﰢ���� ������ ���
                int triangleIndex = randomIndex - squares.size() - lines.size();
                triangles[triangleIndex].y1 += 10; // �ﰢ���� ù ��° �� ���� 10��ŭ �̵�
                triangles[triangleIndex].y2 += 10; // �ﰢ���� �� ��° �� ���� 10��ŭ �̵�
                triangles[triangleIndex].y3 += 10; // �ﰢ���� �� ��° �� ���� 10��ŭ �̵�
            }
        }
        break;
    case 'a':
        // �����ϰ� ���� �ϳ� �����Ͽ� ���� �̵�
        if (!squares.empty() || !lines.empty() || !triangles.empty()) {
            int totalShapes = squares.size() + lines.size() + triangles.size();
            int randomIndex = rand() % totalShapes; // ���� �ε��� ����

            if (randomIndex < squares.size()) {
                // �簢���� ������ ���
                squares[randomIndex].x -= 10; // �簢���� ���� 10��ŭ �̵�
            }
            else if (randomIndex < squares.size() + lines.size()) {
                // ���� ������ ���
                int lineIndex = randomIndex - squares.size();
                lines[lineIndex].x1 -= 10; // ���� ������ ���� 10��ŭ �̵�
                lines[lineIndex].x2 -= 10; // ���� ���� ���� 10��ŭ �̵�
            }
            else {
                // �ﰢ���� ������ ���
                int triangleIndex = randomIndex - squares.size() - lines.size();
                triangles[triangleIndex].x1 -= 10; // �ﰢ���� ù ��° �� ���� 10��ŭ �̵�
                triangles[triangleIndex].x2 -= 10; // �ﰢ���� �� ��° �� ���� 10��ŭ �̵�
                triangles[triangleIndex].x3 -= 10; // �ﰢ���� �� ��° �� ���� 10��ŭ �̵�
            }
        }
        break;
    case 's':
        // �����ϰ� ���� �ϳ� �����Ͽ� ���� �̵�
        if (!squares.empty() || !lines.empty() || !triangles.empty()) {
            int totalShapes = squares.size() + lines.size() + triangles.size();
            int randomIndex = rand() % totalShapes; // ���� �ε��� ����

            if (randomIndex < squares.size()) {
                // �簢���� ������ ���
                squares[randomIndex].y -= 10; // �簢���� ���� 10��ŭ �̵�
            }
            else if (randomIndex < squares.size() + lines.size()) {
                // ���� ������ ���
                int lineIndex = randomIndex - squares.size();
                lines[lineIndex].y1 -= 10; // ���� ������ ���� 10��ŭ �̵�
                lines[lineIndex].y2 -= 10; // ���� ���� ���� 10��ŭ �̵�
            }
            else {
                // �ﰢ���� ������ ���
                int triangleIndex = randomIndex - squares.size() - lines.size();
                triangles[triangleIndex].y1 -= 10; // �ﰢ���� ù ��° �� ���� 10��ŭ �̵�
                triangles[triangleIndex].y2 -= 10; // �ﰢ���� �� ��° �� ���� 10��ŭ �̵�
                triangles[triangleIndex].y3 -= 10; // �ﰢ���� �� ��° �� ���� 10��ŭ �̵�
            }
        }
        break;
    case 'd':
        // �����ϰ� ���� �ϳ� �����Ͽ� ���� �̵�
        if (!squares.empty() || !lines.empty() || !triangles.empty()) {
            int totalShapes = squares.size() + lines.size() + triangles.size();
            int randomIndex = rand() % totalShapes; // ���� �ε��� ����

            if (randomIndex < squares.size()) {
                // �簢���� ������ ���
                squares[randomIndex].x += 10; // �簢���� ���� 10��ŭ �̵�
            }
            else if (randomIndex < squares.size() + lines.size()) {
                // ���� ������ ���
                int lineIndex = randomIndex - squares.size();
                lines[lineIndex].x1 += 10; // ���� ������ ���� 10��ŭ �̵�
                lines[lineIndex].x2 += 10; // ���� ���� ���� 10��ŭ �̵�
            }
            else {
                // �ﰢ���� ������ ���
                int triangleIndex = randomIndex - squares.size() - lines.size();
                triangles[triangleIndex].x1 += 10; // �ﰢ���� ù ��° �� ���� 10��ŭ �̵�
                triangles[triangleIndex].x2 += 10; // �ﰢ���� �� ��° �� ���� 10��ŭ �̵�
                triangles[triangleIndex].x3 += 10; // �ﰢ���� �� ��° �� ���� 10��ŭ �̵�
            }
        }
        break;
    case 'q':
        exit(0); // 'q' Ű�� ���� ���α׷� ����
        break;
    }
    glutPostRedisplay();
}

void update(int value)
{
    glutTimerFunc(16, update, 0); // 16ms���� update ȣ�� (�� 60FPS)
}
