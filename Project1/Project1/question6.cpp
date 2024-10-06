//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//struct Square {
//    float x, y;   // 위치
//    float width, height; // 크기
//    float r, g, b; // 색상
//    bool isMoving; // 이동 상태
//    int direction; // 이동 방향
//    bool isShrinking; // 축소 상태
//};
//
//// 전역 변수
//std::vector<Square> squares; // 사각형을 저장할 벡터
//int windowWidth = 800, windowHeight = 600; // 윈도우 크기 저장
//bool num1 = false, num2 = false, num4 = false;
//int num3 = 0;
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//void update(int value);
//void keyboard(unsigned char key, int x, int y);
//void createRandomSquares(int count); // 랜덤 사각형 생성 함수
//void splitSquare(int index); // 사각형을 분할하는 함수
//int getSquareIndex(int x, int y); // 클릭한 위치에 있는 사각형 인덱스를 반환하는 함수
//void mouseClick(int button, int state, int x, int y); // mouseClick 함수 프로토타입 추가
//
//int main(int argc, char** argv)
//{
//    srand(static_cast<unsigned int>(time(0))); // 랜덤 시드 초기화
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(windowWidth, windowHeight); // 윈도우 크기 수정
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
//    // 랜덤한 사각형 5~10개 생성 (프로그램 실행 시 한 번만)
//    createRandomSquares(rand() % 6 + 5); // 5~10개 생성
//
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMouseFunc(mouseClick); // 마우스 클릭 이벤트 등록
//    glutKeyboardFunc(keyboard); // 키보드 입력 등록
//    glutTimerFunc(16, update, 0); // 업데이트 함수 호출 설정
//    glutMainLoop();
//
//    return 0;
//}
//
//// 랜덤한 사각형을 생성하는 함수
//void createRandomSquares(int count)
//{
//    squares.clear();
//    for (int i = 0; i < count; ++i) {
//        Square s;
//        s.x = rand() % (windowWidth - 120); // 윈도우 크기 내에 랜덤 위치 설정
//        s.y = rand() % (windowHeight - 120);
//        s.width = rand() % 100 + 20; // 20 ~ 120 사이의 랜덤 크기
//        s.height = rand() % 100 + 20;
//        s.r = static_cast<float>(rand()) / RAND_MAX; // 랜덤 색상 (0.0 ~ 1.0)
//        s.g = static_cast<float>(rand()) / RAND_MAX;
//        s.b = static_cast<float>(rand()) / RAND_MAX;
//        s.isMoving = false; // 초기 상태에서 이동하지 않음
//        s.isShrinking = false; // 초기 상태에서 축소하지 않음
//        squares.push_back(s);
//    }
//}
//
//GLvoid drawScene()
//{
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // 짙은 회색 배경
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // 사각형 그리기
//    for (const auto& square : squares) {
//        glColor3f(square.r, square.g, square.b);
//        glBegin(GL_QUADS);
//        glVertex2f(square.x, square.y);                     // 좌하단
//        glVertex2f(square.x + square.width, square.y);       // 우하단
//        glVertex2f(square.x + square.width, square.y + square.height); // 우상단
//        glVertex2f(square.x, square.y + square.height);      // 좌상단
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
//
//    // 윈도우 크기 저장
//    windowWidth = w;
//    windowHeight = h;
//}
//
//void update(int value)
//{
//    // 각 사각형이 분할되어 이동하는 애니메이션 처리
//    for (size_t i = 0; i < squares.size(); ++i) {
//        if (squares[i].isMoving) { // 이동 중인 사각형만 처리
//            float delta = 1.0f; // 이동 속도
//
//            if (num1)
//            {
//                // 이동 방향 처리
//                switch (squares[i].direction)
//                {
//                case 0: // 좌측 위 조각
//                    squares[i].x -= delta; // 왼쪽으로 이동
//                    break;
//                case 1: // 우측 위 조각
//                    squares[i].y += delta; // 위로 이동
//                    break;
//                case 2: // 좌측 아래 조각
//                    squares[i].y -= delta; // 아래로 이동
//                    break;
//                case 3: // 우측 아래 조각
//                    squares[i].x += delta; // 오른쪽으로 이동
//                    break;
//                }
//            }
//            else if (num2)
//            {
//                switch (squares[i].direction) {
//                case 0: // 좌측 위 조각
//                    squares[i].x -= delta * 0.707f; // x 방향으로 이동
//                    squares[i].y += delta * 0.707f; // y 방향으로 이동
//                    break;
//                case 1: // 우측 위 조각
//                    squares[i].x += delta * 0.707f; // x 방향으로 이동
//                    squares[i].y += delta * 0.707f; // y 방향으로 이동
//                    break;
//                case 2: // 좌측 아래 조각
//                    squares[i].x -= delta * 0.707f; // x 방향으로 이동
//                    squares[i].y -= delta * 0.707f; // y 방향으로 이동
//                    break;
//                case 3: // 우측 아래 조각
//                    squares[i].x += delta * 0.707f; // x 방향으로 이동
//                    squares[i].y -= delta * 0.707f; // y 방향으로 이동
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
//                case 0: // 좌측 위 조각
//                    squares[i].x -= delta; // 왼쪽으로 이동
//                    break;
//                case 1: // 우측 위 조각
//                    squares[i].y += delta; // 위로 이동
//                    break;
//                case 2: // 좌측 아래 조각
//                    squares[i].y -= delta; // 아래로 이동
//                    break;
//                case 3: // 우측 아래 조각
//                    squares[i].x += delta; // 오른쪽으로 이동
//                    break;
//                case 4: // 좌측 위 조각
//                    squares[i].x -= delta * 0.707f; // x 방향으로 이동
//                    squares[i].y += delta * 0.707f; // y 방향으로 이동
//                    break;
//                case 5: // 우측 위 조각
//                    squares[i].x += delta * 0.707f; // x 방향으로 이동
//                    squares[i].y += delta * 0.707f; // y 방향으로 이동
//                    break;
//                case 6: // 좌측 아래 조각
//                    squares[i].x -= delta * 0.707f; // x 방향으로 이동
//                    squares[i].y -= delta * 0.707f; // y 방향으로 이동
//                    break;
//                case 7: // 우측 아래 조각
//                    squares[i].x += delta * 0.707f; // x 방향으로 이동
//                    squares[i].y -= delta * 0.707f; // y 방향으로 이동
//                    break;
//                }
//            }
//           
//        }
//
//        // 축소 상태 처리
//        if (squares[i].isShrinking) {
//            squares[i].width -= 0.5f; // 너비 축소
//            squares[i].height -= 0.5f; // 높이 축소
//
//            // 일정 크기 이하로 축소되면 삭제
//            if (squares[i].width <= 0 || squares[i].height <= 0) {
//                squares.erase(squares.begin() + i);
//                --i; // 삭제된 후 인덱스 조정
//            }
//        }
//    }
//
//    glutPostRedisplay(); // 주기적으로 화면 갱신 요청
//    glutTimerFunc(16, update, 0); // 다시 타이머 설정
//}
//
//// 클릭된 위치에 있는 사각형 인덱스를 반환하는 함수
//int getSquareIndex(int x, int y)
//{
//    for (size_t i = 0; i < squares.size(); ++i) {
//        if (x >= squares[i].x && x <= squares[i].x + squares[i].width &&
//            y >= squares[i].y && y <= squares[i].y + squares[i].height) {
//            return i; // 인덱스 반환
//        }
//    }
//    return -1; // 클릭한 위치에 사각형이 없음
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
//// 마우스 클릭 이벤트 처리 함수
//void mouseClick(int button, int state, int x, int y)
//{
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        // 마우스 클릭 시 사각형을 클릭했는지 확인
//        int squareIndex = getSquareIndex(x, windowHeight - y); // OpenGL 좌표계에 맞게 y 좌표 변환
//        if (squareIndex != -1) {
//            splitSquare(squareIndex); // 클릭된 사각형 분할
//        }
//    }
//}
//
//// 사각형을 4등분하는 함수
//void splitSquare(int index)
//{
//    Square original = squares[index];
//    squares.erase(squares.begin() + index); // 원래 사각형 삭제
//
//    // 4개의 조각 생성
//    float newWidth = original.width / 2.0f;
//    float newHeight = original.height / 2.0f;
//
//    // 좌측 위 조각
//    squares.push_back({ original.x, original.y + newHeight, newWidth, newHeight, original.r, original.g, original.b, true, 0, true });
//    // 우측 위 조각
//    squares.push_back({ original.x + newWidth, original.y + newHeight, newWidth, newHeight, original.r, original.g, original.b, true, 1, true });
//    // 좌측 아래 조각
//    squares.push_back({ original.x, original.y, newWidth, newHeight, original.r, original.g, original.b, true, 2, true });
//    // 우측 아래 조각
//    squares.push_back({ original.x + newWidth, original.y, newWidth, newHeight, original.r, original.g, original.b, true, 3, true });
//
//
//    if (num4)
//    {
//        // 좌측 위 조각
//        squares.push_back({ original.x, original.y + newHeight, newWidth, newHeight, original.r, original.g, original.b, true, 4, true });
//        // 우측 위 조각
//        squares.push_back({ original.x + newWidth, original.y + newHeight, newWidth, newHeight, original.r, original.g, original.b, true, 5, true });
//        // 좌측 아래 조각
//        squares.push_back({ original.x, original.y, newWidth, newHeight, original.r, original.g, original.b, true, 6, true });
//        // 우측 아래 조각
//        squares.push_back({ original.x + newWidth, original.y, newWidth, newHeight, original.r, original.g, original.b, true, 7, true });
//    }
//}
