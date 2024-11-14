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
//// �ٰ��� ����ü ����
//struct Polygon {
//    glm::vec2 position;
//    glm::vec2 velocity;
//    std::vector<glm::vec2> vertices;
//    bool isCut = false;
//};
//
//// ������ ����Ʈ
//std::vector<Polygon> polygons;
//
//// ���̴� �ҽ� �ڵ�
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
//// ���̴� �ʱ�ȭ �Լ�
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
//// ������ �ٰ��� ����
//Polygon CreatePolygon() {
//    Polygon polygon;
//    polygon.position = glm::vec2((rand() % WIDTH) / (float)WIDTH * 2 - 1, 1.0f); // ȭ�� ��ܿ��� ����
//    polygon.velocity = glm::vec2(0.0f, -0.01f); // �Ʒ��� �̵�
//
//    int sides = 6; // ������
//    float angle = 2 * M_PI / sides;
//    for (int i = 0; i < sides; ++i) {
//        polygon.vertices.push_back(glm::vec2(cos(i * angle) * 0.1f, sin(i * angle) * 0.1f));
//    }
//    return polygon;
//}
//
//// ������ ���� �� ������ ����
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
//// ������ �׸���
//void DrawPolygon(const Polygon& polygon) {
//    if (polygon.isCut) return; // �߸� �������� �׸��� ����
//    glUseProgram(ShaderProgram);
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_LINE_LOOP, 0, polygon.vertices.size());
//    glBindVertexArray(0);
//}
//
//// ȭ�� ������ �Լ�
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
//// ������ �̵� �� �浹 �˻�
//void UpdatePolygons() {
//    for (auto& polygon : polygons) {
//        polygon.position += polygon.velocity;
//
//        // ȭ�� �Ʒ��� ����� ����
//        if (polygon.position.y < -1.0f) {
//            polygon.isCut = true;
//        }
//    }
//    polygons.erase(std::remove_if(polygons.begin(), polygons.end(), [](const Polygon& p) { return p.isCut; }), polygons.end());
//}
//
//// ������ ���� �Լ�
//void SpawnPolygon(int value) {
//    polygons.push_back(CreatePolygon());
//    glutTimerFunc(1000, SpawnPolygon, 0);
//}
//
//// ���콺 �巡�׷� �߶󳻱�
//void MouseDrag(int x, int y) {
//    float mouseX = (2.0f * x / WIDTH) - 1.0f;
//    float mouseY = 1.0f - (2.0f * y / HEIGHT);
//
//    for (auto& polygon : polygons) {
//        if (polygon.isCut) continue;
//
//        // ���콺 ��ǥ�� ������ �߽� ���� �Ÿ� ���
//        float distance = glm::length(glm::vec2(mouseX, mouseY) - polygon.position);
//        if (distance < 0.1f) { // ���콺�� ������ �߽��� ������ �ڸ���
//            polygon.isCut = true;
//        }
//    }
//    glutPostRedisplay();
//}
//
//// â ũ�� ���� �Լ�
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
