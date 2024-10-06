//#include <iostream>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <cstdlib> // for rand()
//
//// 사각형의 크기
//GLfloat rectWidths[4] = { 180.0f, 180.0f, 180.0f, 180.0f };
//GLfloat rectHeights[4] = { 120.0f, 120.0f, 120.0f, 120.0f };
//
//// 사각형의 최소 크기
//const GLfloat minRectWidth = 10.0f;
//const GLfloat minRectHeight = 10.0f;
//
//// 사각형의 중심 좌표 (배경을 4등분한 중앙)
//GLfloat rectCenters[4][2] = {
//    {200.0f, 150.0f}, // 왼쪽 상단
//    {600.0f, 150.0f}, // 오른쪽 상단
//    {200.0f, 450.0f}, // 왼쪽 하단
//    {600.0f, 450.0f}  // 오른쪽 하단
//};
//
//GLfloat rectColors[4][3] = { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f} };
//
//// 배경색
//GLfloat bgColor[3] = { 1.0f, 1.0f, 1.0f };
//
//// 사각형을 그리는 함수
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
//// 화면을 그리는 함수
//GLvoid drawScene(GLvoid) {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // 사각형 그리기
//    drawRectangles();
//
//    glFlush();
//}
//
//// 창 크기 변경 시 호출되는 함수
//GLvoid Reshape(int w, int h) {
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, 800.0, 0.0, 600.0); // 800x600 좌표계 설정
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
//// 랜덤 색상 생성 함수
//void randomColor(GLfloat* color) {
//    color[0] = static_cast<GLfloat>(rand()) / RAND_MAX;
//    color[1] = static_cast<GLfloat>(rand()) / RAND_MAX;
//    color[2] = static_cast<GLfloat>(rand()) / RAND_MAX;
//}
//
//// 마우스 클릭 이벤트 처리 함수
//void mouse(int button, int state, int x, int y) {
//    if (state == GLUT_DOWN) {
//        // OpenGL 좌표계로 변환
//        int mouseX = x;
//        int mouseY = 600 - y;
//
//        bool insideRect = false;
//
//        for (int i = 0; i < 4; i++) {
//            // 사각형 좌상단과 우하단 좌표 계산
//            GLfloat left = rectCenters[i][0] - rectWidths[i] / 2;
//            GLfloat right = rectCenters[i][0] + rectWidths[i] / 2;
//            GLfloat bottom = rectCenters[i][1] - rectHeights[i] / 2;
//            GLfloat top = rectCenters[i][1] + rectHeights[i] / 2;
//
//            // 마우스가 사각형 내부에 있는지 확인
//            if (mouseX >= left && mouseX <= right && mouseY >= bottom && mouseY <= top) {
//                insideRect = true;
//
//                if (button == GLUT_LEFT_BUTTON) {
//                    // 왼쪽 마우스 클릭 시 사각형 색상 변경
//                    randomColor(rectColors[i]);
//                }
//                else if (button == GLUT_RIGHT_BUTTON) {
//                    // 오른쪽 마우스 클릭 시 사각형 크기 축소
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
//            // 사각형 외부를 클릭한 경우, 해당 구역에 있는 사각형만 확대
//            for (int i = 0; i < 4; i++) {
//                if ((i == 0 && mouseX < 400 && mouseY < 300) ||  // 왼쪽 상단
//                    (i == 1 && mouseX >= 400 && mouseY < 300) || // 오른쪽 상단
//                    (i == 2 && mouseX < 400 && mouseY >= 300) || // 왼쪽 하단
//                    (i == 3 && mouseX >= 400 && mouseY >= 300))  // 오른쪽 하단
//                {
//                    if (button == GLUT_LEFT_BUTTON) {
//                        randomColor(bgColor); // 배경색도 변경 (옵션)
//                        glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
//                    }
//                    else if (button == GLUT_RIGHT_BUTTON) {
//                        // 해당 구역 사각형 크기 확대
//                        rectWidths[i] += 10.0f;
//                        rectHeights[i] += 10.0f;
//                    }
//                }
//            }
//        }
//
//        glutPostRedisplay(); // 화면 갱신
//    }
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("OpenGL Rectangle Example");
//
//    // 초기 배경색 설정
//    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
//
//    // 콜백 함수 등록
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMouseFunc(mouse);
//
//    glutMainLoop();
//    return 0;
//}
