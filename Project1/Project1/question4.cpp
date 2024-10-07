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
//    float r, g, b; // 색상
//    float dx, dy; // 이동 방향
//    bool moving; // 이동 중인지 여부
//    float width; // 사각형 너비
//    float height; // 사각형 높이
//    float widthChangeRate; // 너비 변화 비율
//    float heightChangeRate; // 높이 변화 비율
//    float initialX; // 초기 X 위치
//    float initialY; // 초기 Y 위치
//};
//
//std::vector<Square> squares; // 사각형을 저장할 벡터
//bool isMoving = false; // 이동 상태 관리
//bool isZigzag = false; // 지그재그 이동 상태 관리
//bool isChangingSize = false; // 크기 변화 상태 관리
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
//GLvoid drawScene()
//{
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // 짙은 회색 배경
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    for (const auto& square : squares) {
//        glColor3f(square.r, square.g, square.b);
//        glBegin(GL_QUADS);
//        glVertex2f(square.x - square.width / 2, square.y - square.height / 2); // 왼쪽 아래
//        glVertex2f(square.x + square.width / 2, square.y - square.height / 2); // 오른쪽 아래
//        glVertex2f(square.x + square.width / 2, square.y + square.height / 2); // 오른쪽 위
//        glVertex2f(square.x - square.width / 2, square.y + square.height / 2); // 왼쪽 위
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
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        if (squares.size() < 5) { // 최대 5개 사각형
//            Square newSquare;
//            newSquare.x = static_cast<float>(x);
//            newSquare.y = static_cast<float>(600 - y); // y좌표 반전
//            newSquare.initialX = newSquare.x; // 초기 위치 저장
//            newSquare.initialY = newSquare.y; // 초기 위치 저장
//            newSquare.r = static_cast<float>(rand()) / RAND_MAX; // 랜덤 색상 생성
//            newSquare.g = static_cast<float>(rand()) / RAND_MAX;
//            newSquare.b = static_cast<float>(rand()) / RAND_MAX;
//
//            newSquare.dx = (rand() % 2 == 0 ? 1 : -1) * 2; // 랜덤한 x 방향 속도
//            newSquare.dy = (rand() % 2 == 0 ? 1 : -1) * 2; // 랜덤한 y 방향 속도
//            newSquare.moving = false; // 기본적으로 정지 상태
//            newSquare.width = 30.0f; // 초기 너비
//            newSquare.height = 30.0f; // 초기 높이
//            newSquare.widthChangeRate = (rand() % 2 == 0 ? 1 : -1) * 0.1f; // 랜덤한 너비 변화 비율
//            newSquare.heightChangeRate = (rand() % 2 == 0 ? 1 : -1) * 0.1f; // 랜덤한 높이 변화 비율
//
//            squares.push_back(newSquare); // 벡터에 추가
//            glutPostRedisplay(); // 화면 재출력
//        }
//    }
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//    switch (key)
//    {
//    case '1':
//        isMoving = !isMoving; // 이동 상태 토글
//        break;
//    case'2':
//        isZigzag = !isZigzag; // 지그재그 상태 토글
//        break;
//    case'3':
//        isChangingSize = !isChangingSize; // 크기 변화 상태 토글
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
//            square.x = square.initialX; // 초기 X 위치로 이동
//            square.y = square.initialY; // 초기 Y 위치로 이동
//        }
//        glutPostRedisplay(); // 화면 재출력
//        break;
//    case'r':
//        squares.clear(); // 모든 사각형 지우기
//        glutPostRedisplay(); // 화면 재출력
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
//            square.r = static_cast<float>(rand()) / RAND_MAX; // 랜덤 색상 생성
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
//            // 지그재그 이동 처리
//            if (isZigzag)
//            {
//                square.x += square.dx;
//
//                // 벽에 닿았을 때 방향 전환
//                if (square.x < 15 || square.x > 785) { // 좌우 벽 체크
//                    square.dx = -square.dx; // 방향 전환
//                }
//            }
//
//            if (isMoving) {
//                for (auto& square : squares) {
//                    square.x += square.dx;
//                    square.y += square.dy;
//
//                    // 벽에 닿았을 때 방향 전환
//                    if (square.x < 15 || square.x > 785) { // 좌우 벽 체크
//                        square.dx = -square.dx; // 방향 전환
//                    }
//                    if (square.y < 15 || square.y > 585) { // 상하 벽 체크
//                        square.dy = -square.dy; // 방향 전환
//                    }
//                }
//            }
//            // 크기 변화 처리
//            if (isChangingSize) {
//                square.width += square.widthChangeRate; // 너비 변경
//                square.height += square.heightChangeRate; // 높이 변경
//
//                // 너비 제한
//                if (square.width > 50.0f) {
//                    square.width = 50.0f;          // 최대 너비 제한
//                    square.widthChangeRate = -0.1f; // 방향 반전
//                }
//                else if (square.width < 10.0f) {
//                    square.width = 10.0f;          // 최소 너비 제한
//                    square.widthChangeRate = 0.1f;  // 방향 반전
//                }
//
//                // 높이 제한
//                if (square.height > 50.0f) {
//                    square.height = 50.0f;          // 최대 높이 제한
//                    square.heightChangeRate = -0.1f; // 방향 반전
//                }
//                else if (square.height < 10.0f) {
//                    square.height = 10.0f;          // 최소 높이 제한
//                    square.heightChangeRate = 0.1f;  // 방향 반전
//                }
//            }
//        }
//    }
//    glutPostRedisplay(); // 화면 재출력
//    glutTimerFunc(16, update, 0); // 16ms 후에 다시 호출
//}
