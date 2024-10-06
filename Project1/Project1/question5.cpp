//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//struct Square {
//    float x, y;
//    float size;
//    float r, g, b; // ����
//    bool isDragging = false; // �巡�� ���� ����
//};
//
//std::vector<Square> squares; // �簢���� ������ ����
//Square dynamicSquare;        // �������� �����Ǵ� 60*60 ũ���� �簢��
//bool isDynamicSquareActive = false; // 60*60 �簢�� Ȱ�� ����
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//void mouseClick(int button, int state, int x, int y);
//void mouseMove(int x, int y);
//void keyboard(unsigned char key, int x, int y);
//void update(int value);
//void checkCollisions();
//void createRandomSquares(); // ���� �簢�� ���� �Լ�
//
//int main(int argc, char** argv)
//{
//    srand(static_cast<unsigned int>(time(0))); // ���� �õ� �ʱ�ȭ
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(800, 600); // ������ ũ�� ����
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
//    createRandomSquares(); // 20~40���� ���� �簢�� ����
//
//    // �ʱ� ���� �簢�� ����
//    dynamicSquare.size = 60;
//    dynamicSquare.r = 0.0f;
//    dynamicSquare.g = 0.0f;
//    dynamicSquare.b = 0.0f;
//
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMouseFunc(mouseClick); // ���콺 Ŭ�� �̺�Ʈ ���
//    glutMotionFunc(mouseMove); // ���콺 �巡�� �̺�Ʈ ���
//    glutKeyboardFunc(keyboard); // Ű���� �Է� ���
//    glutTimerFunc(16, update, 0); // ������Ʈ �Լ� ȣ�� ����
//    glutMainLoop();
//
//    return 0;
//}
//
//GLvoid drawScene()
//{
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // £�� ȸ�� ���
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // ���� 30*30 �簢���� �׸���
//    for (const auto& square : squares) {
//        glColor3f(square.r, square.g, square.b);
//        glBegin(GL_QUADS);
//        glVertex2f(square.x, square.y);
//        glVertex2f(square.x + square.size, square.y);
//        glVertex2f(square.x + square.size, square.y + square.size);
//        glVertex2f(square.x, square.y + square.size);
//        glEnd();
//    }
//
//    // ���� �簢��(60*60)�� Ȱ��ȭ�Ǿ� ������ �׸���
//    if (isDynamicSquareActive) {
//        glColor3f(dynamicSquare.r, dynamicSquare.g, dynamicSquare.b);
//        glBegin(GL_QUADS);
//        glVertex2f(dynamicSquare.x, dynamicSquare.y);
//        glVertex2f(dynamicSquare.x + dynamicSquare.size, dynamicSquare.y);
//        glVertex2f(dynamicSquare.x + dynamicSquare.size, dynamicSquare.y + dynamicSquare.size);
//        glVertex2f(dynamicSquare.x, dynamicSquare.y + dynamicSquare.size);
//        glEnd();
//    }
//
//    glutSwapBuffers(); // ȭ�鿡 ����ϱ�
//}
//
//GLvoid Reshape(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION); // ���� ��� ��� ����
//    glLoadIdentity(); // �⺻ ��ķ� �ʱ�ȭ
//    glOrtho(0, w, 0, h, -1, 1); // ��ǥ�� ����
//    glMatrixMode(GL_MODELVIEW); // �� �� ��� ���� ��ȯ
//}
//
//void mouseClick(int button, int state, int x, int y)
//{
//    y = 600 - y; // ������ ��ǥ��� OpenGL ��ǥ�谡 ��ݵǹǷ� y���� ����
//
//    if (button == GLUT_LEFT_BUTTON) {
//        if (state == GLUT_DOWN) {
//            // ���� ���콺�� ������ ���� �簢���� �ʱ�ȭ�ϰ� Ȱ��ȭ
//            dynamicSquare.size = 60;
//            dynamicSquare.r = 0.0f;
//            dynamicSquare.g = 0.0f;
//            dynamicSquare.b = 0.0f;
//            isDynamicSquareActive = true;
//            dynamicSquare.x = x - dynamicSquare.size / 2;
//            dynamicSquare.y = y - dynamicSquare.size / 2;
//
//        }
//        else if (state == GLUT_UP) {
//            // ���� ���콺�� ���� ���� �簢���� ��Ȱ��ȭ
//            isDynamicSquareActive = false;
//        }
//    }
//
//    glutPostRedisplay();
//}
//
//void mouseMove(int x, int y)
//{
//    y = 600 - y; // ��ǥ�� ��ȯ
//
//    if (isDynamicSquareActive) {
//        // ���� �簢���� ���콺 ��ġ�� �̵�
//        dynamicSquare.x = x - dynamicSquare.size / 2;
//        dynamicSquare.y = y - dynamicSquare.size / 2;
//
//        // �浹 üũ �� ó��
//        checkCollisions();
//
//        glutPostRedisplay(); // ȭ�� ������Ʈ
//    }
//}
//
//void checkCollisions() {
//    // ���� �簢���� �浹�� 30*30 �簢���� �����ϰ�, ũ�� �� ���� ������Ʈ
//    for (auto it = squares.begin(); it != squares.end();) {
//        if (dynamicSquare.x < it->x + it->size && dynamicSquare.x + dynamicSquare.size > it->x &&
//            dynamicSquare.y < it->y + it->size && dynamicSquare.y + dynamicSquare.size > it->y) {
//            // �簢���� ��ģ�ٸ�
//            dynamicSquare.size += 10; // ũ�⸦ 10�� ����
//            dynamicSquare.r = it->r;  // ���������� ���� �簢���� ������ ����
//            dynamicSquare.g = it->g;
//            dynamicSquare.b = it->b;
//            it = squares.erase(it); // �浹�� �簢�� ����
//        }
//        else {
//            ++it;
//        }
//    }
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case 'q':
//        exit(0);
//        break;
//    case 'r':
//        createRandomSquares(); // rŰ�� ������ �� ���ο� �簢�� ����
//        break;
//    }
//}
//
//void update(int value)
//{
//    glutPostRedisplay(); // ȭ�� ������Ʈ
//    glutTimerFunc(16, update, 0); // 16ms���� �ٽ� ȣ��
//}
//
//void createRandomSquares() {
//    squares.clear(); // ���� �簢�� ����
//
//    // 20~40���� ���� �簢�� ����
//    int squareCount = 20 + rand() % 21;
//    for (int i = 0; i < squareCount; ++i) {
//        Square square;
//        square.x = rand() % 770; // 800 �ʺ񿡼� 30 ũ�� ����
//        square.y = rand() % 570; // 600 ���̿��� 30 ũ�� ����
//        square.size = 30;
//        square.r = static_cast<float>(rand()) / RAND_MAX;
//        square.g = static_cast<float>(rand()) / RAND_MAX;
//        square.b = static_cast<float>(rand()) / RAND_MAX;
//        squares.push_back(square);
//    }
//
//    glutPostRedisplay(); // ȭ�� ������Ʈ
//}
