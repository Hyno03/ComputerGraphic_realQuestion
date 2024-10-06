//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//struct Square {
//    float x, y;   // ��ġ
//    float width, height; // ũ��
//    float r, g, b; // ����
//    bool isMoving; // �̵� ����
//    int direction; // �̵� ����
//    bool isShrinking; // ��� ����
//};
//
//// ���� ����
//std::vector<Square> squares; // �簢���� ������ ����
//int windowWidth = 800, windowHeight = 600; // ������ ũ�� ����
//bool num1 = false, num2 = false, num4 = false;
//int num3 = 0;
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//void update(int value);
//void keyboard(unsigned char key, int x, int y);
//void createRandomSquares(int count); // ���� �簢�� ���� �Լ�
//void splitSquare(int index); // �簢���� �����ϴ� �Լ�
//int getSquareIndex(int x, int y); // Ŭ���� ��ġ�� �ִ� �簢�� �ε����� ��ȯ�ϴ� �Լ�
//void mouseClick(int button, int state, int x, int y); // mouseClick �Լ� ������Ÿ�� �߰�
//
//int main(int argc, char** argv)
//{
//    srand(static_cast<unsigned int>(time(0))); // ���� �õ� �ʱ�ȭ
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(windowWidth, windowHeight); // ������ ũ�� ����
//    glutCreateWindow("Random Squares Example");
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
//    // ������ �簢�� 5~10�� ���� (���α׷� ���� �� �� ����)
//    createRandomSquares(rand() % 6 + 5); // 5~10�� ����
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
//// ������ �簢���� �����ϴ� �Լ�
//void createRandomSquares(int count)
//{
//    squares.clear();
//    for (int i = 0; i < count; ++i) {
//        Square s;
//        s.x = rand() % (windowWidth - 120); // ������ ũ�� ���� ���� ��ġ ����
//        s.y = rand() % (windowHeight - 120);
//        s.width = rand() % 100 + 20; // 20 ~ 120 ������ ���� ũ��
//        s.height = rand() % 100 + 20;
//        s.r = static_cast<float>(rand()) / RAND_MAX; // ���� ���� (0.0 ~ 1.0)
//        s.g = static_cast<float>(rand()) / RAND_MAX;
//        s.b = static_cast<float>(rand()) / RAND_MAX;
//        s.isMoving = false; // �ʱ� ���¿��� �̵����� ����
//        s.isShrinking = false; // �ʱ� ���¿��� ������� ����
//        squares.push_back(s);
//    }
//}
//
//GLvoid drawScene()
//{
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // £�� ȸ�� ���
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // �簢�� �׸���
//    for (const auto& square : squares) {
//        glColor3f(square.r, square.g, square.b);
//        glBegin(GL_QUADS);
//        glVertex2f(square.x, square.y);                     // ���ϴ�
//        glVertex2f(square.x + square.width, square.y);       // ���ϴ�
//        glVertex2f(square.x + square.width, square.y + square.height); // ����
//        glVertex2f(square.x, square.y + square.height);      // �»��
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
//
//    // ������ ũ�� ����
//    windowWidth = w;
//    windowHeight = h;
//}
//
//void update(int value)
//{
//    // �� �簢���� ���ҵǾ� �̵��ϴ� �ִϸ��̼� ó��
//    for (size_t i = 0; i < squares.size(); ++i) {
//        if (squares[i].isMoving) { // �̵� ���� �簢���� ó��
//            float delta = 1.0f; // �̵� �ӵ�
//
//            if (num1)
//            {
//                // �̵� ���� ó��
//                switch (squares[i].direction)
//                {
//                case 0: // ���� �� ����
//                    squares[i].x -= delta; // �������� �̵�
//                    break;
//                case 1: // ���� �� ����
//                    squares[i].y += delta; // ���� �̵�
//                    break;
//                case 2: // ���� �Ʒ� ����
//                    squares[i].y -= delta; // �Ʒ��� �̵�
//                    break;
//                case 3: // ���� �Ʒ� ����
//                    squares[i].x += delta; // ���������� �̵�
//                    break;
//                }
//            }
//            else if (num2)
//            {
//                switch (squares[i].direction) {
//                case 0: // ���� �� ����
//                    squares[i].x -= delta * 0.707f; // x �������� �̵�
//                    squares[i].y += delta * 0.707f; // y �������� �̵�
//                    break;
//                case 1: // ���� �� ����
//                    squares[i].x += delta * 0.707f; // x �������� �̵�
//                    squares[i].y += delta * 0.707f; // y �������� �̵�
//                    break;
//                case 2: // ���� �Ʒ� ����
//                    squares[i].x -= delta * 0.707f; // x �������� �̵�
//                    squares[i].y -= delta * 0.707f; // y �������� �̵�
//                    break;
//                case 3: // ���� �Ʒ� ����
//                    squares[i].x += delta * 0.707f; // x �������� �̵�
//                    squares[i].y -= delta * 0.707f; // y �������� �̵�
//                    break;
//                }
//            }
//            else if (num3 == 1)
//            {
//                squares[i].x -= delta;
//            }
//            else if (num3 == 2)
//            {
//                squares[i].y -= delta;
//            }
//            else if (num3 == 3)
//            {
//                squares[i].x += delta;
//            }
//            else if (num3 == 4)
//            {
//                squares[i].y += delta;
//            }
//            else if (num3 == 5)
//            {
//                num3 = 0;
//            }
//            else if (num4)
//            {
//                switch (squares[i].direction)
//                {
//                case 0: // ���� �� ����
//                    squares[i].x -= delta; // �������� �̵�
//                    break;
//                case 1: // ���� �� ����
//                    squares[i].y += delta; // ���� �̵�
//                    break;
//                case 2: // ���� �Ʒ� ����
//                    squares[i].y -= delta; // �Ʒ��� �̵�
//                    break;
//                case 3: // ���� �Ʒ� ����
//                    squares[i].x += delta; // ���������� �̵�
//                    break;
//                case 4: // ���� �� ����
//                    squares[i].x -= delta * 0.707f; // x �������� �̵�
//                    squares[i].y += delta * 0.707f; // y �������� �̵�
//                    break;
//                case 5: // ���� �� ����
//                    squares[i].x += delta * 0.707f; // x �������� �̵�
//                    squares[i].y += delta * 0.707f; // y �������� �̵�
//                    break;
//                case 6: // ���� �Ʒ� ����
//                    squares[i].x -= delta * 0.707f; // x �������� �̵�
//                    squares[i].y -= delta * 0.707f; // y �������� �̵�
//                    break;
//                case 7: // ���� �Ʒ� ����
//                    squares[i].x += delta * 0.707f; // x �������� �̵�
//                    squares[i].y -= delta * 0.707f; // y �������� �̵�
//                    break;
//                }
//            }
//           
//        }
//
//        // ��� ���� ó��
//        if (squares[i].isShrinking) {
//            squares[i].width -= 0.5f; // �ʺ� ���
//            squares[i].height -= 0.5f; // ���� ���
//
//            // ���� ũ�� ���Ϸ� ��ҵǸ� ����
//            if (squares[i].width <= 0 || squares[i].height <= 0) {
//                squares.erase(squares.begin() + i);
//                --i; // ������ �� �ε��� ����
//            }
//        }
//    }
//
//    glutPostRedisplay(); // �ֱ������� ȭ�� ���� ��û
//    glutTimerFunc(16, update, 0); // �ٽ� Ÿ�̸� ����
//}
//
//// Ŭ���� ��ġ�� �ִ� �簢�� �ε����� ��ȯ�ϴ� �Լ�
//int getSquareIndex(int x, int y)
//{
//    for (size_t i = 0; i < squares.size(); ++i) {
//        if (x >= squares[i].x && x <= squares[i].x + squares[i].width &&
//            y >= squares[i].y && y <= squares[i].y + squares[i].height) {
//            return i; // �ε��� ��ȯ
//        }
//    }
//    return -1; // Ŭ���� ��ġ�� �簢���� ����
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case '1':
//        num1 = !num1;
//        break;
//    case '2':
//        num2 = !num2;
//        break;
//    case '3':
//        num3 += 1;
//        break;
//    case'4':
//        num4 = !num4;
//        break;
//    case'q':
//        exit(0);
//        break;
//    }
//}
// 
//// ���콺 Ŭ�� �̺�Ʈ ó�� �Լ�
//void mouseClick(int button, int state, int x, int y)
//{
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        // ���콺 Ŭ�� �� �簢���� Ŭ���ߴ��� Ȯ��
//        int squareIndex = getSquareIndex(x, windowHeight - y); // OpenGL ��ǥ�迡 �°� y ��ǥ ��ȯ
//        if (squareIndex != -1) {
//            splitSquare(squareIndex); // Ŭ���� �簢�� ����
//        }
//    }
//}
//
//// �簢���� 4����ϴ� �Լ�
//void splitSquare(int index)
//{
//    Square original = squares[index];
//    squares.erase(squares.begin() + index); // ���� �簢�� ����
//
//    // 4���� ���� ����
//    float newWidth = original.width / 2.0f;
//    float newHeight = original.height / 2.0f;
//
//    // ���� �� ����
//    squares.push_back({ original.x, original.y + newHeight, newWidth, newHeight, original.r, original.g, original.b, true, 0, true });
//    // ���� �� ����
//    squares.push_back({ original.x + newWidth, original.y + newHeight, newWidth, newHeight, original.r, original.g, original.b, true, 1, true });
//    // ���� �Ʒ� ����
//    squares.push_back({ original.x, original.y, newWidth, newHeight, original.r, original.g, original.b, true, 2, true });
//    // ���� �Ʒ� ����
//    squares.push_back({ original.x + newWidth, original.y, newWidth, newHeight, original.r, original.g, original.b, true, 3, true });
//
//
//    if (num4)
//    {
//        // ���� �� ����
//        squares.push_back({ original.x, original.y + newHeight, newWidth, newHeight, original.r, original.g, original.b, true, 4, true });
//        // ���� �� ����
//        squares.push_back({ original.x + newWidth, original.y + newHeight, newWidth, newHeight, original.r, original.g, original.b, true, 5, true });
//        // ���� �Ʒ� ����
//        squares.push_back({ original.x, original.y, newWidth, newHeight, original.r, original.g, original.b, true, 6, true });
//        // ���� �Ʒ� ����
//        squares.push_back({ original.x + newWidth, original.y, newWidth, newHeight, original.r, original.g, original.b, true, 7, true });
//    }
//}
