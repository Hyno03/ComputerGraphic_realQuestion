//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <glm/glm.hpp>
//
//int WIDTH = 800, HEIGHT = 600;
//GLuint ShaderProgram;
//GLuint VBO, VAO;
//
//// 다각형 구조체 정의
//struct Polygon {
//    glm::vec2 position;
//    glm::vec2 velocity;
//    std::vector<glm::vec2> vertices;
//    bool isCut = false;
//};
//
//// 폴리곤 리스트
//std::vector<Polygon> polygons;
//
//// 쉐이더 소스 코드
//const char* vertexShaderSource = R"(
//#version 330 core
//layout(location = 0) in vec2 aPos;
//void main() {
//    gl_Position = vec4(aPos, 0.0, 1.0);
//}
//)";
//
//const char* fragmentShaderSource = R"(
//#version 330 core
//out vec4 FragColor;
//void main() {
//    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
//}
//)";
//
//// 쉐이더 초기화 함수
//void InitShader() {
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//    glCompileShader(vertexShader);
//
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//    glCompileShader(fragmentShader);
//
//    ShaderProgram = glCreateProgram();
//    glAttachShader(ShaderProgram, vertexShader);
//    glAttachShader(ShaderProgram, fragmentShader);
//    glLinkProgram(ShaderProgram);
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//}
//
//// 임의의 다각형 생성
//Polygon CreatePolygon() {
//    Polygon polygon;
//    polygon.position = glm::vec2((rand() % WIDTH) / (float)WIDTH * 2 - 1, 1.0f); // 화면 상단에서 시작
//    polygon.velocity = glm::vec2(0.0f, -0.01f); // 아래로 이동
//
//    int sides = 6; // 육각형
//    float angle = 2 * M_PI / sides;
//    for (int i = 0; i < sides; ++i) {
//        polygon.vertices.push_back(glm::vec2(cos(i * angle) * 0.1f, sin(i * angle) * 0.1f));
//    }
//    return polygon;
//}
//
//// 폴리곤 생성 및 데이터 전송
//void InitPolygonBuffers(const Polygon& polygon) {
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, polygon.vertices.size() * sizeof(glm::vec2), &polygon.vertices[0], GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//// 폴리곤 그리기
//void DrawPolygon(const Polygon& polygon) {
//    if (polygon.isCut) return; // 잘린 폴리곤은 그리지 않음
//    glUseProgram(ShaderProgram);
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_LINE_LOOP, 0, polygon.vertices.size());
//    glBindVertexArray(0);
//}
//
//// 화면 렌더링 함수
//void Display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    for (auto& polygon : polygons) {
//        DrawPolygon(polygon);
//    }
//
//    glutSwapBuffers();
//}
//
//// 폴리곤 이동 및 충돌 검사
//void UpdatePolygons() {
//    for (auto& polygon : polygons) {
//        polygon.position += polygon.velocity;
//
//        // 화면 아래로 벗어나면 제거
//        if (polygon.position.y < -1.0f) {
//            polygon.isCut = true;
//        }
//    }
//    polygons.erase(std::remove_if(polygons.begin(), polygons.end(), [](const Polygon& p) { return p.isCut; }), polygons.end());
//}
//
//// 폴리곤 생성 함수
//void SpawnPolygon(int value) {
//    polygons.push_back(CreatePolygon());
//    glutTimerFunc(1000, SpawnPolygon, 0);
//}
//
//// 마우스 드래그로 잘라내기
//void MouseDrag(int x, int y) {
//    float mouseX = (2.0f * x / WIDTH) - 1.0f;
//    float mouseY = 1.0f - (2.0f * y / HEIGHT);
//
//    for (auto& polygon : polygons) {
//        if (polygon.isCut) continue;
//
//        // 마우스 좌표와 폴리곤 중심 간의 거리 계산
//        float distance = glm::length(glm::vec2(mouseX, mouseY) - polygon.position);
//        if (distance < 0.1f) { // 마우스와 폴리곤 중심이 가까우면 자르기
//            polygon.isCut = true;
//        }
//    }
//    glutPostRedisplay();
//}
//
//// 창 크기 조정 함수
//void Reshape(int width, int height) {
//    WIDTH = width;
//    HEIGHT = height;
//    glViewport(0, 0, width, height);
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowSize(WIDTH, HEIGHT);
//    glutCreateWindow("Fruit Ninja - Polygon Cut");
//
//    glewExperimental = GL_TRUE;
//    glewInit();
//
//    InitShader();
//
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//    glutDisplayFunc(Display);
//    glutReshapeFunc(Reshape);
//    glutMotionFunc(MouseDrag);
//    glutTimerFunc(1000, SpawnPolygon, 0);
//
//    glutIdleFunc(UpdatePolygons);
//    glutMainLoop();
//
//    return 0;
//}
