//#include <iostream>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <cstdlib> // for rand()
//
//// �簢���� ũ��
//GLfloat rectWidths[4] = { 180.0f, 180.0f, 180.0f, 180.0f };
//GLfloat rectHeights[4] = { 120.0f, 120.0f, 120.0f, 120.0f };
//
//// �簢���� �ּ� ũ��
//const GLfloat minRectWidth = 10.0f;
//const GLfloat minRectHeight = 10.0f;
//
//// �簢���� �߽� ��ǥ (����� 4����� �߾�)
//GLfloat rectCenters[4][2] = {
//    {200.0f, 150.0f}, // ���� ���
//    {600.0f, 150.0f}, // ������ ���
//    {200.0f, 450.0f}, // ���� �ϴ�
//    {600.0f, 450.0f}  // ������ �ϴ�
//};
//
//GLfloat rectColors[4][3] = { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f} };
//
//// ����
//GLfloat bgColor[3] = { 1.0f, 1.0f, 1.0f };
//
//// �簢���� �׸��� �Լ�
//void drawRectangles() {
//    for (int i = 0; i < 4; i++) {
//        glColor3f(rectColors[i][0], rectColors[i][1], rectColors[i][2]);
//        GLfloat left = rectCenters[i][0] - rectWidths[i] / 2;
//        GLfloat right = rectCenters[i][0] + rectWidths[i] / 2;
//        GLfloat bottom = rectCenters[i][1] - rectHeights[i] / 2;
//        GLfloat top = rectCenters[i][1] + rectHeights[i] / 2;
//        glRectf(left, bottom, right, top);
//    }
//}
//
//// ȭ���� �׸��� �Լ�
//GLvoid drawScene(GLvoid) {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // �簢�� �׸���
//    drawRectangles();
//
//    glFlush();
//}
//
//// â ũ�� ���� �� ȣ��Ǵ� �Լ�
//GLvoid Reshape(int w, int h) {
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, 800.0, 0.0, 600.0); // 800x600 ��ǥ�� ����
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
//// ���� ���� ���� �Լ�
//void randomColor(GLfloat* color) {
//    color[0] = static_cast<GLfloat>(rand()) / RAND_MAX;
//    color[1] = static_cast<GLfloat>(rand()) / RAND_MAX;
//    color[2] = static_cast<GLfloat>(rand()) / RAND_MAX;
//}
//
//// ���콺 Ŭ�� �̺�Ʈ ó�� �Լ�
//void mouse(int button, int state, int x, int y) {
//    if (state == GLUT_DOWN) {
//        // OpenGL ��ǥ��� ��ȯ
//        int mouseX = x;
//        int mouseY = 600 - y;
//
//        bool insideRect = false;
//
//        for (int i = 0; i < 4; i++) {
//            // �簢�� �»�ܰ� ���ϴ� ��ǥ ���
//            GLfloat left = rectCenters[i][0] - rectWidths[i] / 2;
//            GLfloat right = rectCenters[i][0] + rectWidths[i] / 2;
//            GLfloat bottom = rectCenters[i][1] - rectHeights[i] / 2;
//            GLfloat top = rectCenters[i][1] + rectHeights[i] / 2;
//
//            // ���콺�� �簢�� ���ο� �ִ��� Ȯ��
//            if (mouseX >= left && mouseX <= right && mouseY >= bottom && mouseY <= top) {
//                insideRect = true;
//
//                if (button == GLUT_LEFT_BUTTON) {
//                    // ���� ���콺 Ŭ�� �� �簢�� ���� ����
//                    randomColor(rectColors[i]);
//                }
//                else if (button == GLUT_RIGHT_BUTTON) {
//                    // ������ ���콺 Ŭ�� �� �簢�� ũ�� ���
//                    if (rectWidths[i] > minRectWidth && rectHeights[i] > minRectHeight) {
//                        rectWidths[i] -= 10.0f;
//                        rectHeights[i] -= 10.0f;
//                    }
//                }
//                break;
//            }
//        }
//
//        if (!insideRect) {
//            // �簢�� �ܺθ� Ŭ���� ���, �ش� ������ �ִ� �簢���� Ȯ��
//            for (int i = 0; i < 4; i++) {
//                if ((i == 0 && mouseX < 400 && mouseY < 300) ||  // ���� ���
//                    (i == 1 && mouseX >= 400 && mouseY < 300) || // ������ ���
//                    (i == 2 && mouseX < 400 && mouseY >= 300) || // ���� �ϴ�
//                    (i == 3 && mouseX >= 400 && mouseY >= 300))  // ������ �ϴ�
//                {
//                    if (button == GLUT_LEFT_BUTTON) {
//                        randomColor(bgColor); // ������ ���� (�ɼ�)
//                        glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
//                    }
//                    else if (button == GLUT_RIGHT_BUTTON) {
//                        // �ش� ���� �簢�� ũ�� Ȯ��
//                        rectWidths[i] += 10.0f;
//                        rectHeights[i] += 10.0f;
//                    }
//                }
//            }
//        }
//
//        glutPostRedisplay(); // ȭ�� ����
//    }
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("OpenGL Rectangle Example");
//
//    // �ʱ� ���� ����
//    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
//
//    // �ݹ� �Լ� ���
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMouseFunc(mouse);
//
//    glutMainLoop();
//    return 0;
//}
