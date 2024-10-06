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
//    float r, g, b; // 색상
//    bool isDragging = false; // 드래그 상태 여부
//};
//
//std::vector<Square> squares; // 사각형을 저장할 벡터
//Square dynamicSquare;        // 동적으로 생성되는 60*60 크기의 사각형
//bool isDynamicSquareActive = false; // 60*60 사각형 활성 상태
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//void mouseClick(int button, int state, int x, int y);
//void mouseMove(int x, int y);
//void keyboard(unsigned char key, int x, int y);
//void update(int value);
//void checkCollisions();
//void createRandomSquares(); // 랜덤 사각형 생성 함수
//
//int main(int argc, char** argv)
//{
//    srand(static_cast<unsigned int>(time(0))); // 랜덤 시드 초기화
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(800, 600); // 윈도우 크기 수정
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
//    createRandomSquares(); // 20~40개의 랜덤 사각형 생성
//
//    // 초기 동적 사각형 설정
//    dynamicSquare.size = 60;
//    dynamicSquare.r = 0.0f;
//    dynamicSquare.g = 0.0f;
//    dynamicSquare.b = 0.0f;
//
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMouseFunc(mouseClick); // 마우스 클릭 이벤트 등록
//    glutMotionFunc(mouseMove); // 마우스 드래그 이벤트 등록
//    glutKeyboardFunc(keyboard); // 키보드 입력 등록
//    glutTimerFunc(16, update, 0); // 업데이트 함수 호출 설정
//    glutMainLoop();
//
//    return 0;
//}
//
//GLvoid drawScene()
//{
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // 짙은 회색 배경
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // 기존 30*30 사각형들 그리기
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
//    // 동적 사각형(60*60)이 활성화되어 있으면 그리기
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
//    glutSwapBuffers(); // 화면에 출력하기
//}
//
//GLvoid Reshape(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION); // 투영 행렬 모드 설정
//    glLoadIdentity(); // 기본 행렬로 초기화
//    glOrtho(0, w, 0, h, -1, 1); // 좌표계 설정
//    glMatrixMode(GL_MODELVIEW); // 모델 뷰 행렬 모드로 전환
//}
//
//void mouseClick(int button, int state, int x, int y)
//{
//    y = 600 - y; // 윈도우 좌표계와 OpenGL 좌표계가 상반되므로 y축을 반전
//
//    if (button == GLUT_LEFT_BUTTON) {
//        if (state == GLUT_DOWN) {
//            // 왼쪽 마우스를 누르면 동적 사각형을 초기화하고 활성화
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
//            // 왼쪽 마우스를 떼면 동적 사각형을 비활성화
//            isDynamicSquareActive = false;
//        }
//    }
//
//    glutPostRedisplay();
//}
//
//void mouseMove(int x, int y)
//{
//    y = 600 - y; // 좌표계 변환
//
//    if (isDynamicSquareActive) {
//        // 동적 사각형을 마우스 위치로 이동
//        dynamicSquare.x = x - dynamicSquare.size / 2;
//        dynamicSquare.y = y - dynamicSquare.size / 2;
//
//        // 충돌 체크 및 처리
//        checkCollisions();
//
//        glutPostRedisplay(); // 화면 업데이트
//    }
//}
//
//void checkCollisions() {
//    // 동적 사각형과 충돌한 30*30 사각형을 제거하고, 크기 및 색상 업데이트
//    for (auto it = squares.begin(); it != squares.end();) {
//        if (dynamicSquare.x < it->x + it->size && dynamicSquare.x + dynamicSquare.size > it->x &&
//            dynamicSquare.y < it->y + it->size && dynamicSquare.y + dynamicSquare.size > it->y) {
//            // 사각형이 겹친다면
//            dynamicSquare.size += 10; // 크기를 10씩 증가
//            dynamicSquare.r = it->r;  // 마지막으로 지운 사각형의 색으로 변경
//            dynamicSquare.g = it->g;
//            dynamicSquare.b = it->b;
//            it = squares.erase(it); // 충돌한 사각형 제거
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
//        createRandomSquares(); // r키를 눌렀을 때 새로운 사각형 생성
//        break;
//    }
//}
//
//void update(int value)
//{
//    glutPostRedisplay(); // 화면 업데이트
//    glutTimerFunc(16, update, 0); // 16ms마다 다시 호출
//}
//
//void createRandomSquares() {
//    squares.clear(); // 기존 사각형 삭제
//
//    // 20~40개의 랜덤 사각형 생성
//    int squareCount = 20 + rand() % 21;
//    for (int i = 0; i < squareCount; ++i) {
//        Square square;
//        square.x = rand() % 770; // 800 너비에서 30 크기 빼기
//        square.y = rand() % 570; // 600 높이에서 30 크기 빼기
//        square.size = 30;
//        square.r = static_cast<float>(rand()) / RAND_MAX;
//        square.g = static_cast<float>(rand()) / RAND_MAX;
//        square.b = static_cast<float>(rand()) / RAND_MAX;
//        squares.push_back(square);
//    }
//
//    glutPostRedisplay(); // 화면 업데이트
//}
