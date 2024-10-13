//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <algorithm> // Include for std::remove_if
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//const int numInitialTriangles = 4; // Number of initial triangles
//const int maxTrianglesPerQuadrant = 3; // 사분면당 최대 삼각형 개수
//int triangleCountPerQuadrant[4] = { 0, 0, 0, 0 }; // 각 사분면의 삼각형 개수를 추적
//bool isFilled = true; // 기본적으로 삼각형은 면이 채워진 형태로 그려짐
//bool currentFillMode = true; // 현재 그리기 모드 (true: 채워짐, false: 테두리)
//
//struct Triangle {
//    float vertices[6]; // 2D 좌표
//    float color[3];    // RGB 색상
//    bool isFilled;     // 삼각형이 채워진 상태인지 여부
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
//    glutTimerFunc(16, update, 0); // Call update every 16 ms
//}
//
//void keyboardInput(unsigned char key, int x, int y)
//{
//    if (key == 'a') {
//        currentFillMode = true;  // 'a'를 누르면 채워진 삼각형 모드
//    }
//    else if (key == 'b') {
//        currentFillMode = false; // 'b'를 누르면 테두리만 있는 삼각형 모드
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
