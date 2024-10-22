//#include <iostream>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//
//// ���̴� �ҽ� �ڵ� (������ ���)
//const char* vertexShaderSource = R"(
//#version 330 core
//layout(location = 0) in vec2 position;
//
//void main()
//{
//    gl_Position = vec4(position, 0.0, 1.0);
//}
//)";
//
//const char* fragmentShaderSource = R"(
//#version 330 core
//uniform vec3 shapeColor; // ������ ������ ���� �Է� ����
//out vec4 color;
//
//void main()
//{
//    color = vec4(shapeColor, 1.0); // ������ ���� ���
//}
//)";
//
//GLuint shaderProgram;
//GLuint colorLocation;
//
//// ���� ����
//enum Shape { LINE, TRIANGLE, RECTANGLE, PENTAGON };
//
//// �� ��и��� ������ ������ �迭 (0: 1��и�, 1: 2��и�, 2: 3��и�, 3: 4��и�)
//Shape shapes[4] = { LINE, TRIANGLE, RECTANGLE, PENTAGON };  // �� ��и鿡 �ʱ� ���� ����
//
//// �� ��и��� �ִϸ��̼� ���� ����
//float shapeSizes[4] = { 0.1f, 0.1f, 0.1f, 0.1f }; // �ʱ� ���� ũ�� (���� ũ�⿡�� ����)
//bool animating[4] = { false, false, false, false }; // �� ��и��� �ִϸ��̼� ����
//float animSpeeds[4] = { 0.005f, 0.005f, 0.005f, 0.005f }; // �� ��и��� �ִϸ��̼� �ӵ�
//float targetSize = 0.1f; // ������ ������ ���� ũ��
//
//// ���̴� �ʱ�ȭ �Լ�
//void initShaders() {
//    // Vertex Shader ����
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//    glCompileShader(vertexShader);
//
//    // Fragment Shader ����
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//    glCompileShader(fragmentShader);
//
//    // Shader Program ����
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    // Shader ����
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // ������ ������ ��ġ�� ã��
//    colorLocation = glGetUniformLocation(shaderProgram, "shapeColor");
//}
//
//// ���ڼ� �׸���
//void drawCrosshair() {
//    glUseProgram(0); // ���� �Լ� ���������� ��� (���̴� ��� �� ��)
//    glColor3f(1.0f, 1.0f, 1.0f); // ���
//    glBegin(GL_LINES);
//    glVertex2f(0.0f, -1.0f);
//    glVertex2f(0.0f, 1.0f);
//    glVertex2f(-1.0f, 0.0f);
//    glVertex2f(1.0f, 0.0f);
//    glEnd();
//}
//
//// ���� �׸��� �Լ�
//void drawShape(Shape shape, float size, float x, float y, float r, float g, float b) {
//    glUseProgram(shaderProgram); // ���̴� ���α׷� ���
//    glUniform3f(colorLocation, r, g, b); // ���������� ���� ����
//
//    switch (shape) {
//    case LINE:
//        glBegin(GL_LINES);
//        glVertex2f(x - size, y);
//        glVertex2f(x + size, y);
//        glEnd();
//        break;
//    case TRIANGLE:
//        glBegin(GL_TRIANGLES);
//        glVertex2f(x, y + size);        // ������ A
//        glVertex2f(x - size, y - size); // ������ B
//        glVertex2f(x + size, y - size); // ������ C
//        glEnd();
//        break;
//    case RECTANGLE:
//        glBegin(GL_QUADS);
//        glVertex2f(x - size, y + size); // ���� ��
//        glVertex2f(x + size, y + size); // ������ ��
//        glVertex2f(x + size, y - size); // ������ �Ʒ�
//        glVertex2f(x - size, y - size); // ���� �Ʒ�
//        glEnd();
//        break;
//    case PENTAGON:
//        glBegin(GL_POLYGON);
//        for (int i = 0; i < 5; i++) {
//            float angle = 2.0f * 3.1415926f * float(i) / 5.0f; // ���� ���
//            glVertex2f(x + size * cos(angle), y + size * sin(angle)); // ������ �׸���
//        }
//        glEnd();
//        break;
//    }
//}
//
//// ��и鿡 ���� �׸���
//void drawShapesInQuadrants() {
//    // �� ��и鿡 ���� ���� �׸��� (ũ�⵵ ���������� ����)
//    drawShape(shapes[0], shapeSizes[0], 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);  // 1��и�: ������
//    drawShape(shapes[1], shapeSizes[1], -0.5f, 0.5f, 0.0f, 1.0f, 0.0f); // 2��и�: �ʷϻ�
//    drawShape(shapes[2], shapeSizes[2], -0.5f, -0.5f, 0.0f, 0.0f, 1.0f); // 3��и�: �Ķ���
//    drawShape(shapes[3], shapeSizes[3], 0.5f, -0.5f, 1.0f, 1.0f, 0.0f);  // 4��и�: �����
//}
//
//// Ű �Է� ó��
//void handleKeypress(unsigned char key, int x, int y) {
//    for (int i = 0; i < 4; i++) {
//        switch (key) {
//        case 'l':
//            if (shapes[i] == LINE) {
//                shapes[i] = TRIANGLE; // ���̸� �ﰢ������ ��ȯ
//                shapeSizes[i] = 0.05f; // ũ�⸦ �ʱ�ȭ
//                animating[i] = true; // ��ȯ �� �ִϸ��̼� Ȱ��ȭ
//            }
//            break;
//        case 't':
//            if (shapes[i] == TRIANGLE) {
//                shapes[i] = RECTANGLE; // �ﰢ���̸� �簢������ ��ȯ
//                shapeSizes[i] = 0.05f; // ũ�⸦ �ʱ�ȭ
//                animating[i] = true; // ��ȯ �� �ִϸ��̼� Ȱ��ȭ
//            }
//            break;
//        case 'r':
//            if (shapes[i] == RECTANGLE) {
//                shapes[i] = PENTAGON; // �簢���̸� ���������� ��ȯ
//                shapeSizes[i] = 0.05f; // ũ�⸦ �ʱ�ȭ
//                animating[i] = true; // ��ȯ �� �ִϸ��̼� Ȱ��ȭ
//            }
//            break;
//        case 'p':
//            if (shapes[i] == PENTAGON) {
//                shapes[i] = LINE; // �������̸� ������ ��ȯ
//                shapeSizes[i] = 0.05f; // ũ�⸦ �ʱ�ȭ
//                animating[i] = true; // ��ȯ �� �ִϸ��̼� Ȱ��ȭ
//            }
//            break;
//        case 'a':
//            // ��ü ������ �ʱ� ���·� ����
//            shapes[0] = LINE;
//            shapes[1] = TRIANGLE;
//            shapes[2] = RECTANGLE;
//            shapes[3] = PENTAGON;
//            // ��� ũ�⸦ �ʱ� ���·� ����
//            for (int j = 0; j < 4; j++) {
//                shapeSizes[j] = 0.1f; // �ʱ� ũ��
//                animating[j] = false; // �ִϸ��̼� ����
//            }
//            break;
//        }
//    }
//}
//
//// �ִϸ��̼� ������Ʈ �Լ�
//void updateAnimation() {
//    for (int i = 0; i < 4; i++) {
//        if (animating[i]) {
//            shapeSizes[i] += animSpeeds[i]; // ũ�� ����
//            if (shapeSizes[i] >= targetSize) {
//                shapeSizes[i] = targetSize; // ��ǥ ũ�� ���� �� ����
//                animating[i] = false; // �ִϸ��̼� ���¸� false�� ����
//            }
//        }
//    }
//    glutPostRedisplay(); // ȭ�� ����
//}
//
//// ȭ�� �׸���
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    drawCrosshair();
//    drawShapesInQuadrants();
//    glutSwapBuffers();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Shapes in Quadrants");
//
//    glewInit();
//    initShaders();
//
//    glutDisplayFunc(display);
//    glutIdleFunc(updateAnimation); // �ִϸ��̼� ������Ʈ
//    glutKeyboardFunc(handleKeypress); // Ű �Է� ó��
//    glutMainLoop();
//    return 0;
//}
