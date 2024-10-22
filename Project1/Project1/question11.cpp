//#include <iostream>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//
//// 셰이더 소스 코드 (유니폼 사용)
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
//uniform vec3 shapeColor; // 유니폼 변수로 색상 입력 받음
//out vec4 color;
//
//void main()
//{
//    color = vec4(shapeColor, 1.0); // 유니폼 색상 사용
//}
//)";
//
//GLuint shaderProgram;
//GLuint colorLocation;
//
//// 도형 종류
//enum Shape { LINE, TRIANGLE, RECTANGLE, PENTAGON };
//
//// 각 사분면의 도형을 저장할 배열 (0: 1사분면, 1: 2사분면, 2: 3사분면, 3: 4사분면)
//Shape shapes[4] = { LINE, TRIANGLE, RECTANGLE, PENTAGON };  // 각 사분면에 초기 도형 설정
//
//// 각 사분면의 애니메이션 상태 변수
//float shapeSizes[4] = { 0.1f, 0.1f, 0.1f, 0.1f }; // 초기 도형 크기 (작은 크기에서 시작)
//bool animating[4] = { false, false, false, false }; // 각 사분면의 애니메이션 상태
//float animSpeeds[4] = { 0.005f, 0.005f, 0.005f, 0.005f }; // 각 사분면의 애니메이션 속도
//float targetSize = 0.1f; // 도형이 도달할 최종 크기
//
//// 셰이더 초기화 함수
//void initShaders() {
//    // Vertex Shader 생성
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//    glCompileShader(vertexShader);
//
//    // Fragment Shader 생성
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//    glCompileShader(fragmentShader);
//
//    // Shader Program 생성
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    // Shader 삭제
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // 유니폼 변수의 위치를 찾음
//    colorLocation = glGetUniformLocation(shaderProgram, "shapeColor");
//}
//
//// 십자선 그리기
//void drawCrosshair() {
//    glUseProgram(0); // 고정 함수 파이프라인 사용 (셰이더 사용 안 함)
//    glColor3f(1.0f, 1.0f, 1.0f); // 흰색
//    glBegin(GL_LINES);
//    glVertex2f(0.0f, -1.0f);
//    glVertex2f(0.0f, 1.0f);
//    glVertex2f(-1.0f, 0.0f);
//    glVertex2f(1.0f, 0.0f);
//    glEnd();
//}
//
//// 도형 그리기 함수
//void drawShape(Shape shape, float size, float x, float y, float r, float g, float b) {
//    glUseProgram(shaderProgram); // 셰이더 프로그램 사용
//    glUniform3f(colorLocation, r, g, b); // 유니폼으로 색상 전달
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
//        glVertex2f(x, y + size);        // 꼭짓점 A
//        glVertex2f(x - size, y - size); // 꼭짓점 B
//        glVertex2f(x + size, y - size); // 꼭짓점 C
//        glEnd();
//        break;
//    case RECTANGLE:
//        glBegin(GL_QUADS);
//        glVertex2f(x - size, y + size); // 왼쪽 위
//        glVertex2f(x + size, y + size); // 오른쪽 위
//        glVertex2f(x + size, y - size); // 오른쪽 아래
//        glVertex2f(x - size, y - size); // 왼쪽 아래
//        glEnd();
//        break;
//    case PENTAGON:
//        glBegin(GL_POLYGON);
//        for (int i = 0; i < 5; i++) {
//            float angle = 2.0f * 3.1415926f * float(i) / 5.0f; // 각도 계산
//            glVertex2f(x + size * cos(angle), y + size * sin(angle)); // 오각형 그리기
//        }
//        glEnd();
//        break;
//    }
//}
//
//// 사분면에 도형 그리기
//void drawShapesInQuadrants() {
//    // 각 사분면에 개별 도형 그리기 (크기도 개별적으로 적용)
//    drawShape(shapes[0], shapeSizes[0], 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);  // 1사분면: 빨간색
//    drawShape(shapes[1], shapeSizes[1], -0.5f, 0.5f, 0.0f, 1.0f, 0.0f); // 2사분면: 초록색
//    drawShape(shapes[2], shapeSizes[2], -0.5f, -0.5f, 0.0f, 0.0f, 1.0f); // 3사분면: 파란색
//    drawShape(shapes[3], shapeSizes[3], 0.5f, -0.5f, 1.0f, 1.0f, 0.0f);  // 4사분면: 노란색
//}
//
//// 키 입력 처리
//void handleKeypress(unsigned char key, int x, int y) {
//    for (int i = 0; i < 4; i++) {
//        switch (key) {
//        case 'l':
//            if (shapes[i] == LINE) {
//                shapes[i] = TRIANGLE; // 선이면 삼각형으로 변환
//                shapeSizes[i] = 0.05f; // 크기를 초기화
//                animating[i] = true; // 변환 시 애니메이션 활성화
//            }
//            break;
//        case 't':
//            if (shapes[i] == TRIANGLE) {
//                shapes[i] = RECTANGLE; // 삼각형이면 사각형으로 변환
//                shapeSizes[i] = 0.05f; // 크기를 초기화
//                animating[i] = true; // 변환 시 애니메이션 활성화
//            }
//            break;
//        case 'r':
//            if (shapes[i] == RECTANGLE) {
//                shapes[i] = PENTAGON; // 사각형이면 오각형으로 변환
//                shapeSizes[i] = 0.05f; // 크기를 초기화
//                animating[i] = true; // 변환 시 애니메이션 활성화
//            }
//            break;
//        case 'p':
//            if (shapes[i] == PENTAGON) {
//                shapes[i] = LINE; // 오각형이면 선으로 변환
//                shapeSizes[i] = 0.05f; // 크기를 초기화
//                animating[i] = true; // 변환 시 애니메이션 활성화
//            }
//            break;
//        case 'a':
//            // 전체 도형을 초기 상태로 리셋
//            shapes[0] = LINE;
//            shapes[1] = TRIANGLE;
//            shapes[2] = RECTANGLE;
//            shapes[3] = PENTAGON;
//            // 모든 크기를 초기 상태로 리셋
//            for (int j = 0; j < 4; j++) {
//                shapeSizes[j] = 0.1f; // 초기 크기
//                animating[j] = false; // 애니메이션 중지
//            }
//            break;
//        }
//    }
//}
//
//// 애니메이션 업데이트 함수
//void updateAnimation() {
//    for (int i = 0; i < 4; i++) {
//        if (animating[i]) {
//            shapeSizes[i] += animSpeeds[i]; // 크기 증가
//            if (shapeSizes[i] >= targetSize) {
//                shapeSizes[i] = targetSize; // 목표 크기 도달 시 멈춤
//                animating[i] = false; // 애니메이션 상태를 false로 설정
//            }
//        }
//    }
//    glutPostRedisplay(); // 화면 갱신
//}
//
//// 화면 그리기
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
//    glutIdleFunc(updateAnimation); // 애니메이션 업데이트
//    glutKeyboardFunc(handleKeypress); // 키 입력 처리
//    glutMainLoop();
//    return 0;
//}
