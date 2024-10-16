//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <algorithm> 
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//enum Shape { LINE, TRIANGLE, RECTANGLE, PENTAGON };
//
//struct DrawableShape {
//    float x, y;  // ������ ��ġ
//    Shape shapeType;  // ������ ����
//    bool isAnimating;  // �ִϸ��̼� ���� ����
//    float animationProgress; // �ִϸ��̼� ���� ���� (0.0f ~ 1.0f)
//};
//
//std::vector<DrawableShape> shapes;  // ȭ�鿡 �׷��� ��� ������ �����ϴ� ����
//bool currentFillMode = true;  // ä��� ���� (true: ä���� ����, false: �׵θ��� �׸���)
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//void keyboardInput(unsigned char key, int x, int y);
//void drawGrid(int width, int height);
//void drawShape(const DrawableShape& shape);
//void drawLine(float x, float y, float progress);
//void drawTriangle(float x, float y, float progress); // Progress �߰�
//void drawRectangle(float x, float y, float progress);
//void drawPentagon(float x, float y, float progress);
//void animateShapes();  // �ִϸ��̼� ���� �Լ�
//
//int main(int argc, char** argv)
//{
//    srand(static_cast<unsigned int>(time(0)));
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Shape Transformation Example");
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
//    // �ʱ� ������
//    shapes.push_back({ 600, 450, LINE, false, 0.0f });
//    shapes.push_back({ 200, 450, TRIANGLE, false, 1.0f });
//    shapes.push_back({ 200, 150, RECTANGLE, false, 1.0f });
//    shapes.push_back({ 600, 150, PENTAGON, false, 1.0f });
//
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutKeyboardFunc(keyboardInput);
//    glutIdleFunc(animateShapes);  // �ִϸ��̼� ������Ʈ�� ���� Idle �Լ� ����
//    glutMainLoop();
//
//    return 0;
//}
//
//GLvoid drawScene()
//{
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    drawGrid(800, 600);  // ȭ�� ���ҿ� �׸���
//
//    // ����� ��� ���� �׸���
//    for (const auto& shape : shapes) {
//        drawShape(shape);
//    }
//
//    glutSwapBuffers();
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
//void keyboardInput(unsigned char key, int x, int y)
//{
//    if (key == 'l') {
//        // ��� ��(LINE)�� �ﰢ��(TRIANGLE)���� ����
//        for (auto& shape : shapes) {
//            if (shape.shapeType == LINE) {
//                shape.shapeType = TRIANGLE;
//                shape.isAnimating = true;  // �ִϸ��̼� ����
//                shape.animationProgress = 0.0f; // �ִϸ��̼� �ʱ�ȭ
//            }
//        }
//    }
//    else if (key == 't') {
//        // ��� �ﰢ��(TRIANGLE)�� �簢��(RECTANGLE)���� ����
//        for (auto& shape : shapes) {
//            if (shape.shapeType == TRIANGLE) {
//                shape.shapeType = RECTANGLE;
//                shape.isAnimating = true;  // �ִϸ��̼� ����
//                shape.animationProgress = 0.0f; // �ִϸ��̼� �ʱ�ȭ
//            }
//        }
//    }
//    else if (key == 'r') {
//        // ��� �簢��(RECTANGLE)�� ������(PENTAGON)���� ����
//        for (auto& shape : shapes) {
//            if (shape.shapeType == RECTANGLE) {
//                shape.shapeType = PENTAGON;
//                shape.isAnimating = true;  // �ִϸ��̼� ����
//                shape.animationProgress = 0.0f; // �ִϸ��̼� �ʱ�ȭ
//            }
//        }
//    }
//    else if (key == 'p') {
//        // ��� ������(PENTAGON)�� ��(LINE)���� ����
//        for (auto& shape : shapes) {
//            if (shape.shapeType == PENTAGON) {
//                shape.shapeType = LINE;
//                shape.isAnimating = true;  // �ִϸ��̼� ����
//                shape.animationProgress = 0.0f; // �ִϸ��̼� �ʱ�ȭ
//            }
//        }
//    }
//    else if (key == 'a') {
//        // 'a' Ű�� ������ ������ �ʱ� ���·� �缳��
//        shapes.clear();  // ���� ���� ����
//        // �ʱ� ���� �߰�
//        shapes.push_back({ 600, 450, LINE, false, 0.0f });
//        shapes.push_back({ 200, 450, TRIANGLE, false, 1.0f });
//        shapes.push_back({ 200, 150, RECTANGLE, false, 1.0f });
//        shapes.push_back({ 600, 150, PENTAGON, false, 1.0f });
//    }
//
//    glutPostRedisplay();  // ȭ�� �ٽ� �׸���
//}
//
//void animateShapes() {
//    for (auto& shape : shapes) {
//        if (shape.isAnimating) {
//            shape.animationProgress += 0.01f;  // ���� ���� ����
//            if (shape.animationProgress >= 1.0f) {
//                shape.animationProgress = 1.0f;  // �ִ밪���� ����
//                shape.isAnimating = false;  // �ִϸ��̼� ����
//            }
//        }
//    }
//    glutPostRedisplay();  // ȭ�� �ٽ� �׸���
//}
//
//
//void drawGrid(int width, int height)
//{
//    glColor3f(0.0f, 0.0f, 0.0f);
//    glBegin(GL_LINES);
//
//    // Vertical line
//    glVertex2f(width / 2.0f, 0);
//    glVertex2f(width / 2.0f, height);
//
//    // Horizontal line
//    glVertex2f(0, height / 2.0f);
//    glVertex2f(width, height / 2.0f);
//
//    glEnd();
//}
//
//void drawShape(const DrawableShape& shape)
//{
//    switch (shape.shapeType) {
//    case LINE:
//        drawLine(shape.x, shape.y, shape.animationProgress);
//        break;
//    case TRIANGLE:
//        drawTriangle(shape.x, shape.y, shape.animationProgress);  // Progress ����
//        break;
//    case RECTANGLE:
//        drawRectangle(shape.x, shape.y, shape.animationProgress); // Progress ����
//        break;
//    case PENTAGON:
//        drawPentagon(shape.x, shape.y, shape.animationProgress);
//        break;
//    }
//}
//
//void drawLine(float x, float y, float progress) {
//    glColor3f(1.0f, 0.0f, 0.0f);
//    if (progress < 1.0f) {
//        // Draw a line
//        glBegin(GL_LINES);
//        glVertex2f(x - 50, y);
//        glVertex2f(x + 50, y);
//        glEnd();
//    }
//    else {
//        // Draw a triangle when fully animated
//        drawTriangle(x, y, 1.0f);  // Fully formed triangle
//    }
//}
//
//void drawTriangle(float x, float y, float progress) {
//    glColor3f(0.0f, 1.0f, 0.0f);
//    if (currentFillMode)
//        glBegin(GL_TRIANGLES);
//    else
//        glBegin(GL_LINE_LOOP);
//
//    // �ﰢ���� ���̸� �ִϸ��̼� ���� ������ ���� ����
//    glVertex2f(x, y + 50 * progress);          // ������ A
//    glVertex2f(x - 50 * progress, y - 50);     // ������ B
//    glVertex2f(x + 50 * progress, y - 50);     // ������ C
//
//    glEnd();
//}
//
//void drawRectangle(float x, float y, float progress) {
//    glColor3f(0.0f, 0.0f, 1.0f);
//    if (currentFillMode)
//        glBegin(GL_QUADS);
//    else
//        glBegin(GL_LINE_LOOP);
//
//    // �簢���� ũ�⸦ �ִϸ��̼� ���� ������ ���� ����
//    float width = 100 * progress;  // �ִϸ��̼ǿ� ���� width ����
//    float height = 100 * progress; // �ִϸ��̼ǿ� ���� height ����
//
//    glVertex2f(x - width / 2, y + height / 2);
//    glVertex2f(x + width / 2, y + height / 2);
//    glVertex2f(x + width / 2, y - height / 2);
//    glVertex2f(x - width / 2, y - height / 2);
//
//    glEnd();
//}
//
//void drawPentagon(float x, float y, float progress)
//{
//    glColor3f(1.0f, 1.0f, 0.0f);
//    const float radius = 50.0f * progress;  // Scale radius based on progress
//    const int numSides = 5;
//    float angle = 2.0f * 3.1415926f / numSides;
//
//    if (currentFillMode)
//        glBegin(GL_POLYGON);
//    else
//        glBegin(GL_LINE_LOOP);
//
//    float startAngle = 3.1415926f / 2.0f;
//
//    for (int i = 0; i < numSides; ++i) {
//        float dx = radius * cosf(startAngle + i * angle);
//        float dy = radius * sinf(startAngle + i * angle);
//        glVertex2f(x + dx, y + dy);
//    }
//
//    glEnd();
//}
//
