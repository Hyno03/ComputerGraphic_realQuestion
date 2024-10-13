//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <algorithm> // Include for std::remove_if
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//const int numInitialTriangles = 4; // Number of initial triangles
//const int maxTrianglesPerQuadrant = 3; // ��и�� �ִ� �ﰢ�� ����
//int triangleCountPerQuadrant[4] = { 0, 0, 0, 0 }; // �� ��и��� �ﰢ�� ������ ����
//bool isFilled = true; // �⺻������ �ﰢ���� ���� ä���� ���·� �׷���
//bool currentFillMode = true; // ���� �׸��� ��� (true: ä����, false: �׵θ�)
//
//struct Triangle {
//    float vertices[6]; // 2D ��ǥ
//    float color[3];    // RGB ����
//    bool isFilled;     // �ﰢ���� ä���� �������� ����
//};
//
//std::vector<Triangle> triangles; // Store triangles
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//void mouseClick(int button, int state, int x, int y);
//void update(int value);
//void drawTriangle(const Triangle& triangle);
//void generateTriangleAt(float x, float y); // Updated function signature
//void drawGrid(int width, int height);
//void keyboardInput(unsigned char key, int x, int y);
//int getQuadrant(float x, float y, int windowWidth, int windowHeight); // New function to get quadrant
//
//int main(int argc, char** argv)
//{
//    srand(static_cast<unsigned int>(time(0)));
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Example1");
//    glewExperimental = GL_TRUE;
//
//    if (glewInit() != GLEW_OK)
//    {
//        std::cerr << "Unable to initialize GLEW" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    else
//        std::cout << "GLEW Initialized\n";
//
//    // Generate initial triangles in each quadrant
//    generateTriangleAt(100, 100);      // First quadrant (top-right)
//    generateTriangleAt(100, 500);      // Second quadrant (top-left)
//    generateTriangleAt(500, 500);      // Third quadrant (bottom-left)
//    generateTriangleAt(500, 100);      // Fourth quadrant (bottom-right)
//
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMouseFunc(mouseClick);
//    glutKeyboardFunc(keyboardInput); // Ű���� �Է� ó�� �߰�
//    glutTimerFunc(16, update, 0);
//    glutMainLoop();
//
//    return 0;
//}
//
//GLvoid drawScene()
//{
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // Dark gray background
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    drawGrid(800, 600); // Draw grid to divide the screen
//
//    // Draw all triangles
//    for (const auto& triangle : triangles) {
//        drawTriangle(triangle);
//    }
//
//    glutSwapBuffers(); // Display the drawn frame
//}
//
//GLvoid Reshape(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0, w, 0, h, -1, 1);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void mouseClick(int button, int state, int x, int y)
//{
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        int quadrant = getQuadrant(static_cast<float>(x), static_cast<float>(600 - y), 800, 600);
//
//        // ���� ��и��� �ﰢ�� ����
//        triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
//            [quadrant](const Triangle& triangle) {
//                float triangleCenterX = (triangle.vertices[0] + triangle.vertices[2]) / 2.0f;
//                float triangleCenterY = (triangle.vertices[1] + triangle.vertices[5]) / 2.0f;
//                int triangleQuadrant = getQuadrant(triangleCenterX, triangleCenterY, 800, 600);
//                return triangleQuadrant == quadrant;
//            }), triangles.end());
//
//        // ���ο� �ﰢ�� ����
//        generateTriangleAt(static_cast<float>(x), static_cast<float>(600 - y)); // OpenGL ��ǥ��� y ����
//        glutPostRedisplay();
//    }
//
//    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
//        int quadrant = getQuadrant(static_cast<float>(x), static_cast<float>(600 - y), 800, 600);
//
//        if (triangleCountPerQuadrant[quadrant - 1] < maxTrianglesPerQuadrant) {
//            // ��и鿡 �ﰢ���� 3�� �̸��� ���� �߰�
//            generateTriangleAt(static_cast<float>(x), static_cast<float>(600 - y));
//            triangleCountPerQuadrant[quadrant - 1]++;
//        }
//
//        glutPostRedisplay();
//    }
//}
//
//void update(int value)
//{
//    glutTimerFunc(16, update, 0); // Call update every 16 ms
//}
//
//void keyboardInput(unsigned char key, int x, int y)
//{
//    if (key == 'a') {
//        currentFillMode = true;  // 'a'�� ������ ä���� �ﰢ�� ���
//    }
//    else if (key == 'b') {
//        currentFillMode = false; // 'b'�� ������ �׵θ��� �ִ� �ﰢ�� ���
//    }
//}
//
//
//void drawTriangle(const Triangle& triangle)
//{
//    glColor3f(triangle.color[0], triangle.color[1], triangle.color[2]);
//
//    if (triangle.isFilled) {
//        glBegin(GL_TRIANGLES); // ���� ä���� �ﰢ��
//    }
//    else {
//        glBegin(GL_LINE_LOOP); // �׵θ��� �ִ� �ﰢ��
//    }
//
//    glVertex2f(triangle.vertices[0], triangle.vertices[1]);
//    glVertex2f(triangle.vertices[2], triangle.vertices[3]);
//    glVertex2f(triangle.vertices[4], triangle.vertices[5]);
//    glEnd();
//}
//
//
//void generateTriangleAt(float x, float y)
//{
//    float baseLength = 20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (100.0f - 20.0f)));
//    float height = baseLength + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (baseLength * 2.0f - baseLength)));
//
//    float r = static_cast<float>(rand()) / RAND_MAX;
//    float g = static_cast<float>(rand()) / RAND_MAX;
//    float b = static_cast<float>(rand()) / RAND_MAX;
//
//    Triangle triangle;
//    triangle.vertices[0] = x;
//    triangle.vertices[1] = y;
//    triangle.vertices[2] = x + baseLength;
//    triangle.vertices[3] = y;
//    triangle.vertices[4] = x + (baseLength / 2);
//    triangle.vertices[5] = y + height;
//
//    triangle.color[0] = r;
//    triangle.color[1] = g;
//    triangle.color[2] = b;
//    triangle.isFilled = currentFillMode; // ���� ������ ��忡 ���� ä��� �Ǵ� �׵θ� ����
//
//    triangles.push_back(triangle);
//}
//
//
//int getQuadrant(float x, float y, int windowWidth, int windowHeight) // New function to get quadrant
//{
//    if (x > windowWidth / 2.0f && y > windowHeight / 2.0f) {
//        return 1; // First quadrant
//    }
//    else if (x < windowWidth / 2.0f && y > windowHeight / 2.0f) {
//        return 2; // Second quadrant
//    }
//    else if (x < windowWidth / 2.0f && y < windowHeight / 2.0f) {
//        return 3; // Third quadrant
//    }
//    else {
//        return 4; // Fourth quadrant
//    }
//}
//
//void drawGrid(int width, int height)
//{
//    glColor3f(0.0f, 0.0f, 0.0f); // Black color for grid
//    glBegin(GL_LINES);
//
//    // Vertical lines
//    glVertex2f(width / 2.0f, 0);
//    glVertex2f(width / 2.0f, height);
//
//    // Horizontal lines
//    glVertex2f(0, height / 2.0f);
//    glVertex2f(width, height / 2.0f);
//
//    glEnd();
//}
