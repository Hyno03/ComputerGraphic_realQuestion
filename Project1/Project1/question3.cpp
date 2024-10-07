//#include <iostream>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <cstdlib> // for rand()
//#include <cmath>   // for abs()
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Keyboard(unsigned char key, int x, int y);
//GLvoid Mouse(int button, int state, int x, int y);
//GLvoid Motion(int x, int y);
//
//bool timerEnabled = false; // Ÿ�̸� Ȱ��ȭ ����
//float bgColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // �⺻ ���� (�Ķ�)
//
//// ����ü �̸� ����
//struct Rect {
//    float x, y; // �簢���� �߽� ��ǥ
//    float width, height; // �簢���� ũ��
//    float r, g, b; // �簢���� ����
//};
//
//int numRects = 10; // �簢���� ����
//Rect rects[10]; // �簢�� �迭
//bool drawRects = false; // �簢�� �׸��� ����
//int selectedRect = -1;  // ���õ� �簢��
//int windowWidth = 800, windowHeight = 600; // ������ ũ��
//
//// ���� ���� ���� �Լ�
//void setRandomColor(float& r, float& g, float& b) {
//    r = static_cast<float>(rand()) / RAND_MAX;
//    g = static_cast<float>(rand()) / RAND_MAX;
//    b = static_cast<float>(rand()) / RAND_MAX;
//}
//
//// ���� �簢�� ���� �Լ�
//void generateRandomRects() {
//    for (int i = 0; i < numRects; i++) {
//        rects[i].x = static_cast<float>(rand()) / RAND_MAX * 1.8f - 0.9f; // -0.9 ~ 0.9 ������ x ��ǥ
//        rects[i].y = static_cast<float>(rand()) / RAND_MAX * 1.8f - 0.9f; // -0.9 ~ 0.9 ������ y ��ǥ
//        rects[i].width = 0.2f;
//        rects[i].height = 0.2f;
//        setRandomColor(rects[i].r, rects[i].g, rects[i].b); // ������ ����
//    }
//}
//
//// �浹 ���� �Լ�
//bool checkCollision(Rect& a, Rect& b) {
//    return abs(a.x - b.x) < (a.width + b.width) / 2 &&
//        abs(a.y - b.y) < (a.height + b.height) / 2;
//}
//
//// �簢�� ��ġ�� �Լ�
//void mergeRects(Rect& a, Rect& b) {
//    if (b.x > a.x)
//    {
//        a.width = (b.x + b.width / 2) - (a.x - a.width / 2);
//    }
//    else if (a.x > b.x)
//    {
//        a.width = (a.x + a.width / 2) - (b.x - b.width / 2);
//    }
//
//    if (b.y > a.y)
//    {
//        a.height = (b.y + b.height / 2) - (a.y - a.height / 2);
//    }
//    else if (a.y > b.y)
//    {
//        a.height = (a.y + a.height / 2) - (b.y - b.height / 2);
//    }
//    
//    setRandomColor(a.r, a.g, a.b); // ���� ����
//    b = rects[--numRects]; // �迭���� b�� ����
//}
//
//void stopTimerIfActive() {
//    if (timerEnabled) {
//        std::cout << "Stopping timer due to other key press\n";
//        timerEnabled = false;
//    }
//}
//
//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(0, 0);
//    glutInitWindowSize(windowWidth, windowHeight);
//    glutCreateWindow("Rectangle Drag & Merge");
//
//    glewExperimental = GL_TRUE;
//    if (glewInit() != GLEW_OK)
//    {
//        std::cerr << "Unable to initialize GLEW" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    else
//        std::cout << "GLEW Initialized\n";
//
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutKeyboardFunc(Keyboard);
//    glutMouseFunc(Mouse);       // ���콺 Ŭ�� �̺�Ʈ ó��
//    glutMotionFunc(Motion);     // ���콺 �巡�� �̺�Ʈ ó��
//    glutMainLoop();
//}
//
//GLvoid drawScene()
//{
//    glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // �簢���� �׸���
//    if (drawRects) {
//        for (int i = 0; i < numRects; i++) {
//            glColor3f(rects[i].r, rects[i].g, rects[i].b);
//            glBegin(GL_QUADS);
//            // �簢���� �� �������� ����
//            glVertex2f(rects[i].x - rects[i].width / 2, rects[i].y - rects[i].height / 2); // ���� �Ʒ�
//            glVertex2f(rects[i].x + rects[i].width / 2, rects[i].y - rects[i].height / 2); // ������ �Ʒ�
//            glVertex2f(rects[i].x + rects[i].width / 2, rects[i].y + rects[i].height / 2); // ������ ��
//            glVertex2f(rects[i].x - rects[i].width / 2, rects[i].y + rects[i].height / 2); // ���� ��
//            glEnd();
//        }
//    }
//
//    glutSwapBuffers(); // ȭ�鿡 ����ϱ�
//}
//
//GLvoid Reshape(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    windowWidth = w;
//    windowHeight = h;
//}
//
//// ���콺 Ŭ�� �̺�Ʈ ó�� �Լ�
//GLvoid Mouse(int button, int state, int x, int y)
//{
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        float normX = (static_cast<float>(x) / windowWidth) * 2.0f - 1.0f;
//        float normY = 1.0f - (static_cast<float>(y) / windowHeight) * 2.0f;
//
//        for (int i = 0; i < numRects; i++) {
//            if (abs(normX - rects[i].x) < rects[i].width / 2 && abs(normY - rects[i].y) < rects[i].height / 2) {
//                selectedRect = i; // �簢���� ���õ�
//                break;
//            }
//        }
//    }
//    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
//        // ���콺 ��ư�� �������� �� �浹 ���� �� ��ġ�� ó��
//        if (selectedRect != -1) {
//            float normX = (static_cast<float>(x) / windowWidth) * 2.0f - 1.0f;
//            float normY = 1.0f - (static_cast<float>(y) / windowHeight) * 2.0f;
//            rects[selectedRect].x = normX;
//            rects[selectedRect].y = normY;
//
//            // �浹 ���� �� ��ġ��
//            for (int i = 0; i < numRects; i++) {
//                if (i != selectedRect && checkCollision(rects[selectedRect], rects[i])) {
//                    mergeRects(rects[selectedRect], rects[i]);
//                    break;
//                }
//            }
//        }
//        selectedRect = -1; // ���� ����
//    }
//}
//
//// ���콺 �巡�� �̺�Ʈ ó�� �Լ�
//GLvoid Motion(int x, int y)
//{
//    if (selectedRect != -1) {
//        float normX = (static_cast<float>(x) / windowWidth) * 2.0f - 1.0f;
//        float normY = 1.0f - (static_cast<float>(y) / windowHeight) * 2.0f;
//        rects[selectedRect].x = normX;
//        rects[selectedRect].y = normY;
//
//        glutPostRedisplay(); // ȭ�� ���� ��û
//    }
//}
//
//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case 'a':
//        generateRandomRects(); // ���� �簢�� ����
//        drawRects = true; // �簢���� �׸����� ����
//        break;
//    case 'q':
//        exit(0);
//        break;
//    }
//
//    glutPostRedisplay(); // ȭ�� ���� ��û
//}
