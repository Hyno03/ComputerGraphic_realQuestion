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
//    float r, g, b; // ����
//    float dx, dy; // �̵� ����
//    bool moving; // �̵� ������ ����
//    float width; // �簢�� �ʺ�
//    float height; // �簢�� ����
//    float widthChangeRate; // �ʺ� ��ȭ ����
//    float heightChangeRate; // ���� ��ȭ ����
//    float initialX; // �ʱ� X ��ġ
//    float initialY; // �ʱ� Y ��ġ
//};
//
//std::vector<Square> squares; // �簢���� ������ ����
//bool isMoving = false; // �̵� ���� ����
//bool isZigzag = false; // ������� �̵� ���� ����
//bool isChangingSize = false; // ũ�� ��ȭ ���� ����
//bool isColorChange = false;
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Timer(int value);
//void mouseClick(int button, int state, int x, int y);
//void keyboard(unsigned char key, int x, int y);
//void update(int value);
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
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMouseFunc(mouseClick); // ���콺 Ŭ�� �̺�Ʈ ���
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
//    for (const auto& square : squares) {
//        glColor3f(square.r, square.g, square.b);
//        glBegin(GL_QUADS);
//        glVertex2f(square.x - square.width / 2, square.y - square.height / 2); // ���� �Ʒ�
//        glVertex2f(square.x + square.width / 2, square.y - square.height / 2); // ������ �Ʒ�
//        glVertex2f(square.x + square.width / 2, square.y + square.height / 2); // ������ ��
//        glVertex2f(square.x - square.width / 2, square.y + square.height / 2); // ���� ��
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
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        if (squares.size() < 5) { // �ִ� 5�� �簢��
//            Square newSquare;
//            newSquare.x = static_cast<float>(x);
//            newSquare.y = static_cast<float>(600 - y); // y��ǥ ����
//            newSquare.initialX = newSquare.x; // �ʱ� ��ġ ����
//            newSquare.initialY = newSquare.y; // �ʱ� ��ġ ����
//            newSquare.r = static_cast<float>(rand()) / RAND_MAX; // ���� ���� ����
//            newSquare.g = static_cast<float>(rand()) / RAND_MAX;
//            newSquare.b = static_cast<float>(rand()) / RAND_MAX;
//
//            newSquare.dx = (rand() % 2 == 0 ? 1 : -1) * 2; // ������ x ���� �ӵ�
//            newSquare.dy = (rand() % 2 == 0 ? 1 : -1) * 2; // ������ y ���� �ӵ�
//            newSquare.moving = false; // �⺻������ ���� ����
//            newSquare.width = 30.0f; // �ʱ� �ʺ�
//            newSquare.height = 30.0f; // �ʱ� ����
//            newSquare.widthChangeRate = (rand() % 2 == 0 ? 1 : -1) * 0.1f; // ������ �ʺ� ��ȭ ����
//            newSquare.heightChangeRate = (rand() % 2 == 0 ? 1 : -1) * 0.1f; // ������ ���� ��ȭ ����
//
//            squares.push_back(newSquare); // ���Ϳ� �߰�
//            glutPostRedisplay(); // ȭ�� �����
//        }
//    }
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case '1':
//        isMoving = !isMoving; // �̵� ���� ���
//        break;
//    case'2':
//        isZigzag = !isZigzag; // ������� ���� ���
//        break;
//    case'3':
//        isChangingSize = !isChangingSize; // ũ�� ��ȭ ���� ���
//        break;
//    case'4':
//        isColorChange = !isColorChange;
//        glutTimerFunc(500, Timer, 0);
//        break;
//    case's':
//        isMoving = false;
//        isZigzag = false;
//        isChangingSize = false;
//        isColorChange = false;
//        break;
//    case'm':
//        for (auto& square : squares) {
//            square.x = square.initialX; // �ʱ� X ��ġ�� �̵�
//            square.y = square.initialY; // �ʱ� Y ��ġ�� �̵�
//        }
//        glutPostRedisplay(); // ȭ�� �����
//        break;
//    case'r':
//        squares.clear(); // ��� �簢�� �����
//        glutPostRedisplay(); // ȭ�� �����
//        break;
//    case 'q':
//        exit(0);
//        break;
//    }
//}
//
//GLvoid Timer(int value)
//{
//    if (isColorChange)
//    {
//        for (auto& square : squares)
//        {
//            square.r = static_cast<float>(rand()) / RAND_MAX; // ���� ���� ����
//            square.g = static_cast<float>(rand()) / RAND_MAX;
//            square.b = static_cast<float>(rand()) / RAND_MAX;
//            glutPostRedisplay();
//            glutTimerFunc(500, Timer, 0);
//        }
//    }
//   
//}
//
//void update(int value)
//{
//    if (isMoving || isZigzag || isChangingSize)
//    {
//        for (auto& square : squares)
//        {
//            // ������� �̵� ó��
//            if (isZigzag)
//            {
//                square.x += square.dx;
//
//                // ���� ����� �� ���� ��ȯ
//                if (square.x < 15 || square.x > 785) { // �¿� �� üũ
//                    square.dx = -square.dx; // ���� ��ȯ
//                }
//            }
//
//            if (isMoving) {
//                for (auto& square : squares) {
//                    square.x += square.dx;
//                    square.y += square.dy;
//
//                    // ���� ����� �� ���� ��ȯ
//                    if (square.x < 15 || square.x > 785) { // �¿� �� üũ
//                        square.dx = -square.dx; // ���� ��ȯ
//                    }
//                    if (square.y < 15 || square.y > 585) { // ���� �� üũ
//                        square.dy = -square.dy; // ���� ��ȯ
//                    }
//                }
//            }
//            // ũ�� ��ȭ ó��
//            if (isChangingSize) {
//                square.width += square.widthChangeRate; // �ʺ� ����
//                square.height += square.heightChangeRate; // ���� ����
//
//                // �ʺ� ����
//                if (square.width > 50.0f) {
//                    square.width = 50.0f;          // �ִ� �ʺ� ����
//                    square.widthChangeRate = -0.1f; // ���� ����
//                }
//                else if (square.width < 10.0f) {
//                    square.width = 10.0f;          // �ּ� �ʺ� ����
//                    square.widthChangeRate = 0.1f;  // ���� ����
//                }
//
//                // ���� ����
//                if (square.height > 50.0f) {
//                    square.height = 50.0f;          // �ִ� ���� ����
//                    square.heightChangeRate = -0.1f; // ���� ����
//                }
//                else if (square.height < 10.0f) {
//                    square.height = 10.0f;          // �ּ� ���� ����
//                    square.heightChangeRate = 0.1f;  // ���� ����
//                }
//            }
//        }
//    }
//    glutPostRedisplay(); // ȭ�� �����
//    glutTimerFunc(16, update, 0); // 16ms �Ŀ� �ٽ� ȣ��
//}
