//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <algorithm> 
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//enum Shape { LINE, TRIANGLE, RECTANGLE, PENTAGON };
//
//struct DrawableShape {
//    float x, y;  // 도형의 위치
//    Shape shapeType;  // 도형의 종류
//    bool isAnimating;  // 애니메이션 진행 여부
//    float animationProgress; // 애니메이션 진행 정도 (0.0f ~ 1.0f)
//};
//
//std::vector<DrawableShape> shapes;  // 화면에 그려진 모든 도형을 저장하는 벡터
//bool currentFillMode = true;  // 채우기 여부 (true: 채워진 도형, false: 테두리만 그리기)
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//void keyboardInput(unsigned char key, int x, int y);
//void drawGrid(int width, int height);
//void drawShape(const DrawableShape& shape);
//void drawLine(float x, float y, float progress);
//void drawTriangle(float x, float y, float progress); // Progress 추가
//void drawRectangle(float x, float y, float progress);
//void drawPentagon(float x, float y, float progress);
//void animateShapes();  // 애니메이션 진행 함수
//
//int main(int argc, char** argv)
//{
//    srand(static_cast<unsigned int>(time(0)));
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Shape Transformation Example");
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
//    // 초기 도형들
//    shapes.push_back({ 600, 450, LINE, false, 0.0f });
//    shapes.push_back({ 200, 450, TRIANGLE, false, 1.0f });
//    shapes.push_back({ 200, 150, RECTANGLE, false, 1.0f });
//    shapes.push_back({ 600, 150, PENTAGON, false, 1.0f });
//
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutKeyboardFunc(keyboardInput);
//    glutIdleFunc(animateShapes);  // 애니메이션 업데이트를 위해 Idle 함수 설정
//    glutMainLoop();
//
//    return 0;
//}
//
//GLvoid drawScene()
//{
//    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    drawGrid(800, 600);  // 화면 분할용 그리드
//
//    // 저장된 모든 도형 그리기
//    for (const auto& shape : shapes) {
//        drawShape(shape);
//    }
//
//    glutSwapBuffers();
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
//void keyboardInput(unsigned char key, int x, int y)
//{
//    if (key == 'l') {
//        // 모든 선(LINE)을 삼각형(TRIANGLE)으로 변경
//        for (auto& shape : shapes) {
//            if (shape.shapeType == LINE) {
//                shape.shapeType = TRIANGLE;
//                shape.isAnimating = true;  // 애니메이션 시작
//                shape.animationProgress = 0.0f; // 애니메이션 초기화
//            }
//        }
//    }
//    else if (key == 't') {
//        // 모든 삼각형(TRIANGLE)을 사각형(RECTANGLE)으로 변경
//        for (auto& shape : shapes) {
//            if (shape.shapeType == TRIANGLE) {
//                shape.shapeType = RECTANGLE;
//                shape.isAnimating = true;  // 애니메이션 시작
//                shape.animationProgress = 0.0f; // 애니메이션 초기화
//            }
//        }
//    }
//    else if (key == 'r') {
//        // 모든 사각형(RECTANGLE)을 오각형(PENTAGON)으로 변경
//        for (auto& shape : shapes) {
//            if (shape.shapeType == RECTANGLE) {
//                shape.shapeType = PENTAGON;
//                shape.isAnimating = true;  // 애니메이션 시작
//                shape.animationProgress = 0.0f; // 애니메이션 초기화
//            }
//        }
//    }
//    else if (key == 'p') {
//        // 모든 오각형(PENTAGON)을 선(LINE)으로 변경
//        for (auto& shape : shapes) {
//            if (shape.shapeType == PENTAGON) {
//                shape.shapeType = LINE;
//                shape.isAnimating = true;  // 애니메이션 시작
//                shape.animationProgress = 0.0f; // 애니메이션 초기화
//            }
//        }
//    }
//    else if (key == 'a') {
//        // 'a' 키를 누르면 도형을 초기 상태로 재설정
//        shapes.clear();  // 기존 도형 삭제
//        // 초기 도형 추가
//        shapes.push_back({ 600, 450, LINE, false, 0.0f });
//        shapes.push_back({ 200, 450, TRIANGLE, false, 1.0f });
//        shapes.push_back({ 200, 150, RECTANGLE, false, 1.0f });
//        shapes.push_back({ 600, 150, PENTAGON, false, 1.0f });
//    }
//
//    glutPostRedisplay();  // 화면 다시 그리기
//}
//
//void animateShapes() {
//    for (auto& shape : shapes) {
//        if (shape.isAnimating) {
//            shape.animationProgress += 0.01f;  // 진행 정도 증가
//            if (shape.animationProgress >= 1.0f) {
//                shape.animationProgress = 1.0f;  // 최대값으로 고정
//                shape.isAnimating = false;  // 애니메이션 멈춤
//            }
//        }
//    }
//    glutPostRedisplay();  // 화면 다시 그리기
//}
//
//
//void drawGrid(int width, int height)
//{
//    glColor3f(0.0f, 0.0f, 0.0f);
//    glBegin(GL_LINES);
//
//    // Vertical line
//    glVertex2f(width / 2.0f, 0);
//    glVertex2f(width / 2.0f, height);
//
//    // Horizontal line
//    glVertex2f(0, height / 2.0f);
//    glVertex2f(width, height / 2.0f);
//
//    glEnd();
//}
//
//void drawShape(const DrawableShape& shape)
//{
//    switch (shape.shapeType) {
//    case LINE:
//        drawLine(shape.x, shape.y, shape.animationProgress);
//        break;
//    case TRIANGLE:
//        drawTriangle(shape.x, shape.y, shape.animationProgress);  // Progress 전달
//        break;
//    case RECTANGLE:
//        drawRectangle(shape.x, shape.y, shape.animationProgress); // Progress 전달
//        break;
//    case PENTAGON:
//        drawPentagon(shape.x, shape.y, shape.animationProgress);
//        break;
//    }
//}
//
//void drawLine(float x, float y, float progress) {
//    glColor3f(1.0f, 0.0f, 0.0f);
//    if (progress < 1.0f) {
//        // Draw a line
//        glBegin(GL_LINES);
//        glVertex2f(x - 50, y);
//        glVertex2f(x + 50, y);
//        glEnd();
//    }
//    else {
//        // Draw a triangle when fully animated
//        drawTriangle(x, y, 1.0f);  // Fully formed triangle
//    }
//}
//
//void drawTriangle(float x, float y, float progress) {
//    glColor3f(0.0f, 1.0f, 0.0f);
//    if (currentFillMode)
//        glBegin(GL_TRIANGLES);
//    else
//        glBegin(GL_LINE_LOOP);
//
//    // 삼각형의 높이를 애니메이션 진행 정도에 따라 조절
//    glVertex2f(x, y + 50 * progress);          // 꼭짓점 A
//    glVertex2f(x - 50 * progress, y - 50);     // 꼭짓점 B
//    glVertex2f(x + 50 * progress, y - 50);     // 꼭짓점 C
//
//    glEnd();
//}
//
//void drawRectangle(float x, float y, float progress) {
//    glColor3f(0.0f, 0.0f, 1.0f);
//    if (currentFillMode)
//        glBegin(GL_QUADS);
//    else
//        glBegin(GL_LINE_LOOP);
//
//    // 사각형의 크기를 애니메이션 진행 정도에 따라 조절
//    float width = 100 * progress;  // 애니메이션에 따라 width 조절
//    float height = 100 * progress; // 애니메이션에 따라 height 조절
//
//    glVertex2f(x - width / 2, y + height / 2);
//    glVertex2f(x + width / 2, y + height / 2);
//    glVertex2f(x + width / 2, y - height / 2);
//    glVertex2f(x - width / 2, y - height / 2);
//
//    glEnd();
//}
//
//void drawPentagon(float x, float y, float progress)
//{
//    glColor3f(1.0f, 1.0f, 0.0f);
//    const float radius = 50.0f * progress;  // Scale radius based on progress
//    const int numSides = 5;
//    float angle = 2.0f * 3.1415926f / numSides;
//
//    if (currentFillMode)
//        glBegin(GL_POLYGON);
//    else
//        glBegin(GL_LINE_LOOP);
//
//    float startAngle = 3.1415926f / 2.0f;
//
//    for (int i = 0; i < numSides; ++i) {
//        float dx = radius * cosf(startAngle + i * angle);
//        float dy = radius * sinf(startAngle + i * angle);
//        glVertex2f(x + dx, y + dy);
//    }
//
//    glEnd();
//}
//
