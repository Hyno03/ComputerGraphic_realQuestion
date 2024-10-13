//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <algorithm> // Include for std::remove_if
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//#define M_PI 3.14159265358979323846
//
//const int numInitialTriangles = 4; // Number of initial triangles
//const int maxTrianglesPerQuadrant = 3; // 사분면당 최대 삼각형 개수
//int triangleCountPerQuadrant[4] = { 0, 0, 0, 0 }; // 각 사분면의 삼각형 개수를 추적
//bool isFilled = true; // 기본적으로 삼각형은 면이 채워진 형태로 그려짐
//bool currentFillMode = true; // 현재 그리기 모드 (true: 채워짐, false: 테두리)
//bool isMoving = false; // 삼각형이 움직이는지 여부 (1번 키를 누르면 true)
//bool isZigzagging = false; // 지그재그 모드 상태
//bool isSpiraling = false;  // 스파이럴 모드 상태
//float spiralStep = 20.0f;  // 스파이럴의 한 단계당 이동 거리
//int spiralDirection = 0;   // 0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽
//float spiralDistance = 0.0f;  // 한 방향으로 이동한 거리
//float currentSpiralLimit = 100.0f; // 현재 방향으로 움직일 최대 거리
//float spiralIncrement = 20.0f; // 각 나선 회전마다 거리가 증가하는 값
//float minSpiralDistance = 50.0f; // 스파이럴 모드에서 멈출 최소 거리
//int spiralTurns = 0; // 스파이럴 회전 횟수
//bool isCircularSpiraling = false; // 원형 스파이럴 모드 상태
//float radius = 20.0f; // 초기 반지름
//float radiusIncrement = 2.0f; // 반지름 증가량
//float angle = 0.0f; // 각도
//
//struct Triangle {
//    float vertices[6]; // 2D 좌표
//    float color[3];    // RGB 색상
//    bool isFilled;     // 삼각형이 채워진 상태인지 여부
//    float velocity[2]; // 속도 (x, y 방향)
//};
//
//std::vector<Triangle> triangles; // Store triangles
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//void mouseClick(int button, int state, int x, int y);
//void update(int value);
//void drawTriangle(const Triangle& triangle);
//void generateTriangleAt(float x, float y); // Updated function signature
//void drawGrid(int width, int height);
//void keyboardInput(unsigned char key, int x, int y);
//int getQuadrant(float x, float y, int windowWidth, int windowHeight); // New function to get quadrant
//
//int main(int argc, char** argv)
//{
//    srand(static_cast<unsigned int>(time(0)));
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(800, 600);
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
//    // Generate initial triangles in each quadrant
//    generateTriangleAt(100, 100);      // First quadrant (top-right)
//    generateTriangleAt(100, 500);      // Second quadrant (top-left)
//    generateTriangleAt(500, 500);      // Third quadrant (bottom-left)
//    generateTriangleAt(500, 100);      // Fourth quadrant (bottom-right)
//
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMouseFunc(mouseClick);
//    glutKeyboardFunc(keyboardInput); // 키보드 입력 처리 추가
//    glutTimerFunc(16, update, 0);
//    glutMainLoop();
//
//    return 0;
//}
//
//GLvoid drawScene()
//{
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // Dark gray background
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    drawGrid(800, 600); // Draw grid to divide the screen
//
//    // Draw all triangles
//    for (const auto& triangle : triangles) {
//        drawTriangle(triangle);
//    }
//
//    glutSwapBuffers(); // Display the drawn frame
//}
//
//GLvoid Reshape(int w, int h)
//{
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0, w, 0, h, -1, 1);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void mouseClick(int button, int state, int x, int y)
//{
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        int quadrant = getQuadrant(static_cast<float>(x), static_cast<float>(600 - y), 800, 600);
//
//        // 같은 사분면의 삼각형 삭제
//        triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
//            [quadrant](const Triangle& triangle) {
//                float triangleCenterX = (triangle.vertices[0] + triangle.vertices[2]) / 2.0f;
//                float triangleCenterY = (triangle.vertices[1] + triangle.vertices[5]) / 2.0f;
//                int triangleQuadrant = getQuadrant(triangleCenterX, triangleCenterY, 800, 600);
//                return triangleQuadrant == quadrant;
//            }), triangles.end());
//
//        // 새로운 삼각형 생성
//        generateTriangleAt(static_cast<float>(x), static_cast<float>(600 - y)); // OpenGL 좌표계로 y 조정
//        glutPostRedisplay();
//    }
//
//    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
//        int quadrant = getQuadrant(static_cast<float>(x), static_cast<float>(600 - y), 800, 600);
//
//        if (triangleCountPerQuadrant[quadrant - 1] < maxTrianglesPerQuadrant) {
//            // 사분면에 삼각형이 3개 미만일 때만 추가
//            generateTriangleAt(static_cast<float>(x), static_cast<float>(600 - y));
//            triangleCountPerQuadrant[quadrant - 1]++;
//        }
//
//        glutPostRedisplay();
//    }
//}
//
//void update(int value)
//{
//    if (isMoving) {
//        for (auto& triangle : triangles) {
//            // 삼각형의 모든 좌표를 속도에 따라 업데이트
//            float offsetX = triangle.velocity[0];
//            float offsetY = triangle.velocity[1];
//
//            // 삼각형의 모든 꼭짓점을 속도에 따라 이동
//            for (int i = 0; i < 6; i += 2) {
//                triangle.vertices[i] += offsetX; // x 좌표 업데이트
//                triangle.vertices[i + 1] += offsetY; // y 좌표 업데이트
//            }
//
//            // 삼각형의 중심 좌표를 계산 (중심은 꼭짓점의 평균)
//            float centerX = (triangle.vertices[0] + triangle.vertices[2] + triangle.vertices[4]) / 3.0f;
//            float centerY = (triangle.vertices[1] + triangle.vertices[3] + triangle.vertices[5]) / 3.0f;
//
//            // 좌우 경계에 부딪혔을 때 x 방향 반전
//            if (centerX <= 0 || centerX >= 800) {
//                triangle.velocity[0] = -triangle.velocity[0];
//            }
//
//            // 상하 경계에 부딪혔을 때 y 방향 반전
//            if (centerY <= 0 || centerY >= 600) {
//                triangle.velocity[1] = -triangle.velocity[1];
//            }
//        }
//    }
//    if (isZigzagging) {
//        for (auto& triangle : triangles) {
//            float offsetX = triangle.velocity[0];
//
//            // 삼각형의 모든 꼭짓점을 좌우로만 이동
//            for (int i = 0; i < 6; i += 2) {
//                triangle.vertices[i] += offsetX; // x 좌표만 업데이트
//            }
//
//            // 삼각형의 중심 좌표를 계산
//            float centerX = (triangle.vertices[0] + triangle.vertices[2] + triangle.vertices[4]) / 3.0f;
//            float centerY = (triangle.vertices[1] + triangle.vertices[3] + triangle.vertices[5]) / 3.0f;
//
//            // 사분면에 따른 경계 조건 (좌우로만 움직임)
//            if (centerX <= 0 || centerX >= 800) {
//                triangle.velocity[0] = -triangle.velocity[0]; // x 방향 반전
//            }
//        }
//    }
//    if (isSpiraling) {
//        for (auto& triangle : triangles) {
//            float offsetX = 0.0f;
//            float offsetY = 0.0f;
//
//            // 현재 스파이럴 방향에 따라 offset 설정
//            if (spiralDirection == 0) {       // 오른쪽으로 이동
//                offsetX = spiralStep;
//            }
//            else if (spiralDirection == 1) { // 아래쪽으로 이동
//                offsetY = -spiralStep;
//            }
//            else if (spiralDirection == 2) { // 왼쪽으로 이동
//                offsetX = -spiralStep;
//            }
//            else if (spiralDirection == 3) { // 위쪽으로 이동
//                offsetY = spiralStep;
//            }
//
//            // 삼각형의 모든 꼭짓점을 이동
//            for (int i = 0; i < 6; i += 2) {
//                triangle.vertices[i] += offsetX;     // x 좌표 업데이트
//                triangle.vertices[i + 1] += offsetY; // y 좌표 업데이트
//            }
//
//            // 삼각형의 중심 좌표 계산
//            float centerX = (triangle.vertices[0] + triangle.vertices[2] + triangle.vertices[4]) / 3.0f;
//            float centerY = (triangle.vertices[1] + triangle.vertices[3] + triangle.vertices[5]) / 3.0f;
//
//            // 경계 처리: 각 사분면의 가장자리에 부딪혔는지 확인
//            if ((spiralDirection == 0 && centerX >= 800) || (spiralDirection == 1 && centerY <= 0) ||
//                (spiralDirection == 2 && centerX <= 0) || (spiralDirection == 3 && centerY >= 600)) {
//                spiralDirection = (spiralDirection + 1) % 4; // 방향을 90도 회전
//                spiralTurns++; // 회전 횟수 증가
//            }
//        }
//
//        // 4번 회전 후 스파이럴 모드 비활성화
//        if (spiralTurns >= 30) {
//            isSpiraling = false; // 스파이럴 모드 비활성화
//        }
//    }
//    if (isCircularSpiraling) {
//        for (auto& triangle : triangles) {
//            // 현재 각도를 라디안으로 변환
//            float radian = angle * (M_PI / 180.0f);
//
//            // 원형 궤적에 따라 삼각형 위치 업데이트
//            float offsetX = radius * cos(radian);
//            float offsetY = radius * sin(radian);
//
//            // 삼각형의 모든 꼭짓점을 원형 궤적에 따라 이동
//            for (int i = 0; i < 6; i += 2) {
//                triangle.vertices[i] += offsetX;     // x 좌표 업데이트
//                triangle.vertices[i + 1] += offsetY; // y 좌표 업데이트
//            }
//
//            // 각도 증가 (각 회전마다 5도씩 증가)
//            angle += 5.0f;
//
//            // 원 궤적을 유지하기 위해 각도 초기화 (360도 이상일 때)
//            if (angle >= 360.0f) {
//                angle -= 360.0f;
//                radius += radiusIncrement; // 각 회전 후 반지름 증가
//            }
//        }
//    }
//
//    glutPostRedisplay(); // 화면 다시 그리기 요청
//    glutTimerFunc(16, update, 0); // 16ms마다 update 함수 호출
//}
//
//
//void keyboardInput(unsigned char key, int x, int y)
//{
//    if (key == 'a') {
//        currentFillMode = true;  // 'a'를 누르면 채워진 삼각형 모드
//    }
//    else if (key == 'b') {
//        currentFillMode = false; // 'b'를 누르면 테두리만 있는 삼각형 모드
//    }
//    else if (key == '1') {
//        isMoving = !isMoving;  // '1'을 누르면 삼각형들이 움직이기 시작
//    }
//    else if (key == '2') {
//        isZigzagging = true;  // '2'를 누르면 지그재그 모드 활성화
//    }
//    else if (key == '3') {
//        isSpiraling = !isSpiraling;   // '3'을 누르면 스파이럴 모드 활성화
//        spiralDirection = 0;  // 스파이럴 시작 방향은 오른쪽
//        spiralDistance = 0.0f; // 초기 이동 거리 리셋
//        currentSpiralLimit = 100.0f; // 처음 스파이럴 이동 제한 거리
//    }
//    else if (key == '4') {
//        isCircularSpiraling = !isCircularSpiraling;  // '4'를 누르면 원 스파이럴 모드 활성화
//    }
//}
//
//
//void drawTriangle(const Triangle& triangle)
//{
//    glColor3f(triangle.color[0], triangle.color[1], triangle.color[2]);
//
//    if (triangle.isFilled) {
//        glBegin(GL_TRIANGLES); // 면이 채워진 삼각형
//    }
//    else {
//        glBegin(GL_LINE_LOOP); // 테두리만 있는 삼각형
//    }
//
//    glVertex2f(triangle.vertices[0], triangle.vertices[1]);
//    glVertex2f(triangle.vertices[2], triangle.vertices[3]);
//    glVertex2f(triangle.vertices[4], triangle.vertices[5]);
//    glEnd();
//}
//
//
//void generateTriangleAt(float x, float y)
//{
//    float baseLength = 20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (100.0f - 20.0f)));
//    float height = baseLength + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (baseLength * 2.0f - baseLength)));
//
//    float r = static_cast<float>(rand()) / RAND_MAX;
//    float g = static_cast<float>(rand()) / RAND_MAX;
//    float b = static_cast<float>(rand()) / RAND_MAX;
//
//    Triangle triangle;
//    triangle.vertices[0] = x;
//    triangle.vertices[1] = y;
//    triangle.vertices[2] = x + baseLength;
//    triangle.vertices[3] = y;
//    triangle.vertices[4] = x + (baseLength / 2);
//    triangle.vertices[5] = y + height;
//
//    triangle.color[0] = r;
//    triangle.color[1] = g;
//    triangle.color[2] = b;
//    triangle.isFilled = currentFillMode; // 현재 설정된 모드에 따라 채우기 또는 테두리 설정
//
//    // 임의의 속도를 설정
//    triangle.velocity[0] = (rand() % 5 + 1) * ((rand() % 2 == 0) ? 1 : -1); // x 방향 속도
//    triangle.velocity[1] = (rand() % 5 + 1) * ((rand() % 2 == 0) ? 1 : -1); // y 방향 속도
//
//    triangles.push_back(triangle);
//}
//
//
//int getQuadrant(float x, float y, int windowWidth, int windowHeight) // New function to get quadrant
//{
//    if (x > windowWidth / 2.0f && y > windowHeight / 2.0f) {
//        return 1; // First quadrant
//    }
//    else if (x < windowWidth / 2.0f && y > windowHeight / 2.0f) {
//        return 2; // Second quadrant
//    }
//    else if (x < windowWidth / 2.0f && y < windowHeight / 2.0f) {
//        return 3; // Third quadrant
//    }
//    else {
//        return 4; // Fourth quadrant
//    }
//}
//
//void drawGrid(int width, int height)
//{
//    glColor3f(0.0f, 0.0f, 0.0f); // Black color for grid
//    glBegin(GL_LINES);
//
//    // Vertical lines
//    glVertex2f(width / 2.0f, 0);
//    glVertex2f(width / 2.0f, height);
//
//    // Horizontal lines
//    glVertex2f(0, height / 2.0f);
//    glVertex2f(width, height / 2.0f);
//
//    glEnd();
//}
