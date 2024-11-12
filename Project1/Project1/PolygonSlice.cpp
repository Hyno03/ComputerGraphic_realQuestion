//#include <iostream>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//const char* vertexShaderSource = R"(
//#version 330 core
//layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 color;
//
//uniform mat4 model;
//out vec3 fragColor;
//
//void main()
//{
//    gl_Position = model * vec4(position, 1.0);
//    fragColor = color;
//}
//)";
//
//const char* fragmentShaderSource = R"(
//#version 330 core
//in vec3 fragColor;
//out vec4 color;
//
//void main()
//{
//    color = vec4(fragColor, 1.0);
//}
//)";
//
//GLuint shaderProgram;
//float xOffset = 0.0f;
//bool movingRight = true;
//
//struct Shape {
//    glm::vec3 position;
//    glm::vec3 color;
//};
//
//std::vector<Shape> shapes;
//
//void initShaders() {
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//    glCompileShader(vertexShader);
//
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//    glCompileShader(fragmentShader);
//
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//}
//
//void drawScene() {
//    glUseProgram(shaderProgram);
//    // basket
//    float squareVertices[] = {
//    -0.2f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,
//        0.2f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,
//        0.2f,  -0.7f, 0.0f,  0.0f, 0.0f, 1.0f,
//    -0.2f,  -0.7f, 0.0f,  0.0f, 0.0f, 1.0f
//    };
//
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(xOffset, 0.0f, 0.0f));
//
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//    glEnableVertexAttribArray(0);
//    glEnableVertexAttribArray(1);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), squareVertices);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), squareVertices + 3);
//
//    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//
//    // triangles
//    for (const Shape& shape : shapes) {
//        float triangleVertices[] = {
//            shape.position.x, shape.position.y + 0.1f, 0.0f, shape.color.r, shape.color.g, shape.color.b,
//            shape.position.x + 0.1f, shape.position.y + 0.1f, 0.0f, shape.color.r, shape.color.g, shape.color.b,
//            shape.position.x + 0.05f, shape.position.y - 0.1f, 0.0f, shape.color.r, shape.color.g, shape.color.b
//        };
//
//        glm::mat4 model = glm::mat4(1.0f);
//        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//        glEnableVertexAttribArray(0);
//        glEnableVertexAttribArray(1);
//
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangleVertices);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), triangleVertices + 3);
//
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        glDisableVertexAttribArray(0);
//        glDisableVertexAttribArray(1);
//    }
//}
//
//void update(int value) {
//    if (movingRight) {
//        xOffset += 0.01f;
//        if (xOffset >= 0.8f) movingRight = false;
//    }
//    else {
//        xOffset -= 0.01f;
//        if (xOffset <= -0.8f) movingRight = true;
//    }
//
//    if (rand() % 100 < 1) {
//        Shape newShape;
//        newShape.position = glm::vec3(-1.0f, 0.8f, 0.0f); 
//        newShape.color = glm::vec3(1.0f, 0.647f, 0.0f); 
//        shapes.push_back(newShape);
//    }
//
//    for (size_t i = 0; i < shapes.size(); ++i) {
//        shapes[i].position.x += 0.01f; 
//        shapes[i].position.y -= 0.005f; 
//
//        if (shapes[i].position.x > 1.0f || shapes[i].position.y < -1.0f) {
//            shapes.erase(shapes.begin() + i);
//            --i;
//        }
//    }
//
//
//    glutPostRedisplay();
//    glutTimerFunc(16, update, 0);
//}
//
//void display() {
//    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    drawScene();
//
//    glutSwapBuffers();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Polygon Slice");
//
//    glewInit();
//    initShaders();
//
//    glutDisplayFunc(display);
//    glutTimerFunc(0, update, 0);
//    glutMainLoop();
//    return 0;
//}
