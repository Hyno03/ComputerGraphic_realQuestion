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
//bool timerEnabled = false; // 타이머 활성화 여부
//float bgColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 기본 배경색 (파랑)
//
//// 구조체 이름 변경
//struct Rect {
//    float x, y; // 사각형의 중심 좌표
//    float width, height; // 사각형의 크기
//    float r, g, b; // 사각형의 색상
//};
//
//int numRects = 10; // 사각형의 개수
//Rect rects[10]; // 사각형 배열
//bool drawRects = false; // 사각형 그리기 여부
//int selectedRect = -1;  // 선택된 사각형
//int windowWidth = 800, windowHeight = 600; // 윈도우 크기
//
//// 랜덤 색상 생성 함수
//void setRandomColor(float& r, float& g, float& b) {
//    r = static_cast<float>(rand()) / RAND_MAX;
//    g = static_cast<float>(rand()) / RAND_MAX;
//    b = static_cast<float>(rand()) / RAND_MAX;
//}
//
//// 랜덤 사각형 생성 함수
//void generateRandomRects() {
//    for (int i = 0; i < numRects; i++) {
//        rects[i].x = static_cast<float>(rand()) / RAND_MAX * 1.8f - 0.9f; // -0.9 ~ 0.9 범위의 x 좌표
//        rects[i].y = static_cast<float>(rand()) / RAND_MAX * 1.8f - 0.9f; // -0.9 ~ 0.9 범위의 y 좌표
//        rects[i].width = 0.2f;
//        rects[i].height = 0.2f;
//        setRandomColor(rects[i].r, rects[i].g, rects[i].b); // 랜덤한 색상
//    }
//}
//
//// 충돌 감지 함수
//bool checkCollision(Rect& a, Rect& b) {
//    return abs(a.x - b.x) < (a.width + b.width) / 2 &&
//        abs(a.y - b.y) < (a.height + b.height) / 2;
//}
//
//// 사각형 합치기 함수
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
//    setRandomColor(a.r, a.g, a.b); // 색상 변경
//    b = rects[--numRects]; // 배열에서 b를 제거
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
//    glutMouseFunc(Mouse);       // 마우스 클릭 이벤트 처리
//    glutMotionFunc(Motion);     // 마우스 드래그 이벤트 처리
//    glutMainLoop();
//}
//
//GLvoid drawScene()
//{
//    glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // 사각형을 그리기
//    if (drawRects) {
//        for (int i = 0; i < numRects; i++) {
//            glColor3f(rects[i].r, rects[i].g, rects[i].b);
//            glBegin(GL_QUADS);
//            // 사각형의 네 꼭짓점을 지정
//            glVertex2f(rects[i].x - rects[i].width / 2, rects[i].y - rects[i].height / 2); // 왼쪽 아래
//            glVertex2f(rects[i].x + rects[i].width / 2, rects[i].y - rects[i].height / 2); // 오른쪽 아래
//            glVertex2f(rects[i].x + rects[i].width / 2, rects[i].y + rects[i].height / 2); // 오른쪽 위
//            glVertex2f(rects[i].x - rects[i].width / 2, rects[i].y + rects[i].height / 2); // 왼쪽 위
//            glEnd();
//        }
//    }
//
//    glutSwapBuffers(); // 화면에 출력하기
//}
//
//GLvoid Reshape(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    windowWidth = w;
//    windowHeight = h;
//}
//
//// 마우스 클릭 이벤트 처리 함수
//GLvoid Mouse(int button, int state, int x, int y)
//{
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        float normX = (static_cast<float>(x) / windowWidth) * 2.0f - 1.0f;
//        float normY = 1.0f - (static_cast<float>(y) / windowHeight) * 2.0f;
//
//        for (int i = 0; i < numRects; i++) {
//            if (abs(normX - rects[i].x) < rects[i].width / 2 && abs(normY - rects[i].y) < rects[i].height / 2) {
//                selectedRect = i; // 사각형이 선택됨
//                break;
//            }
//        }
//    }
//    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
//        // 마우스 버튼이 떼어졌을 때 충돌 감지 및 합치기 처리
//        if (selectedRect != -1) {
//            float normX = (static_cast<float>(x) / windowWidth) * 2.0f - 1.0f;
//            float normY = 1.0f - (static_cast<float>(y) / windowHeight) * 2.0f;
//            rects[selectedRect].x = normX;
//            rects[selectedRect].y = normY;
//
//            // 충돌 감지 및 합치기
//            for (int i = 0; i < numRects; i++) {
//                if (i != selectedRect && checkCollision(rects[selectedRect], rects[i])) {
//                    mergeRects(rects[selectedRect], rects[i]);
//                    break;
//                }
//            }
//        }
//        selectedRect = -1; // 선택 해제
//    }
//}
//
//// 마우스 드래그 이벤트 처리 함수
//GLvoid Motion(int x, int y)
//{
//    if (selectedRect != -1) {
//        float normX = (static_cast<float>(x) / windowWidth) * 2.0f - 1.0f;
//        float normY = 1.0f - (static_cast<float>(y) / windowHeight) * 2.0f;
//        rects[selectedRect].x = normX;
//        rects[selectedRect].y = normY;
//
//        glutPostRedisplay(); // 화면 갱신 요청
//    }
//}
//
//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case 'a':
//        generateRandomRects(); // 랜덤 사각형 생성
//        drawRects = true; // 사각형을 그리도록 설정
//        break;
//    case 'q':
//        exit(0);
//        break;
//    }
//
//    glutPostRedisplay(); // 화면 갱신 요청
//}
