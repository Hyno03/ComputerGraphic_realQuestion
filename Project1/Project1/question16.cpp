//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#define M_PI 3.14159265358979323846
//
//// Shader source code (with uniforms)
//const char* vertexShaderSource = R"(
//#version 330 core
//layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 color;
//
//uniform mat4 modelTransform;
//uniform mat4 view;
//uniform mat4 projection;
//
//out vec3 fragColor;
//
//void main()
//{
//    gl_Position = projection * view * modelTransform * vec4(position, 1.0);
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
//    color = vec4(fragColor, 1.0); // use fragment color
//}
//)";
//
//GLuint shaderProgram;
//
//std::vector<GLfloat> axisVertices = {
//    // Positions             // Colors (RGB)
//    -2.0f, 0.0f, 0.0f,       1.0f, 0.0f, 0.0f, // X-axis (Red)
//    5.0f, 0.0f, 0.0f,       1.0f, 0.0f, 0.0f, // X-axis end point
//
//    0.0f, -2.0f, 0.0f,       0.0f, 1.0f, 0.0f, // Y-axis (Green)
//    0.0f, 2.0f, 0.0f,       0.0f, 1.0f, 0.0f, // Y-axis end point
//
//    0.0f, 0.0f, -5.0f,       0.0f, 0.0f, 1.0f, // Z-axis (Blue)
//    0.0f, 0.0f, 2.0f,       0.0f, 0.0f, 1.0f  // Z-axis end point
//};
//
//// Cube vertices and colors
//std::vector<GLfloat> cubeVertices = {
//    // Positions          // Colors
//    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
//};
//
//std::vector<GLuint> cubeIndices = {
//    0, 1, 2, 2, 3, 0, // back face
//    4, 5, 6, 6, 7, 4, // front face
//    0, 1, 5, 5, 4, 0, // bottom face
//    2, 3, 7, 7, 6, 2, // top face
//    0, 3, 7, 7, 4, 0, // left face
//    1, 2, 6, 6, 5, 1  // right face
//};
//
//const int sphereSlices = 20;
//const int sphereStacks = 20;
//std::vector<GLfloat> sphereVertices;
//std::vector<GLuint> sphereIndices;
//
//void initSphere() {
//    for (int i = 0; i <= sphereStacks; ++i) {
//        float phi = M_PI * i / sphereStacks; // vertical angle
//        for (int j = 0; j <= sphereSlices; ++j) {
//            float theta = 2.0f * M_PI * j / sphereSlices; // horizontal angle
//            float x = sin(phi) * cos(theta);
//            float y = cos(phi);
//            float z = sin(phi) * sin(theta);
//
//            sphereVertices.push_back(x);
//            sphereVertices.push_back(y);
//            sphereVertices.push_back(z);
//            sphereVertices.push_back(1.0f); // Color red
//            sphereVertices.push_back(1.0f); // Color green
//            sphereVertices.push_back(1.0f); // Color blue
//        }
//    }
//
//    for (int i = 0; i < sphereStacks; ++i) {
//        for (int j = 0; j < sphereSlices; ++j) {
//            sphereIndices.push_back(i * (sphereSlices + 1) + j);
//            sphereIndices.push_back((i + 1) * (sphereSlices + 1) + j);
//            sphereIndices.push_back(i * (sphereSlices + 1) + (j + 1));
//
//            sphereIndices.push_back((i + 1) * (sphereSlices + 1) + j);
//            sphereIndices.push_back((i + 1) * (sphereSlices + 1) + (j + 1));
//            sphereIndices.push_back(i * (sphereSlices + 1) + (j + 1));
//        }
//    }
//}
//
//GLuint cubeVAO, cubeVBO, cubeEBO;
//GLuint sphereVAO, sphereVBO, sphereEBO;
//GLuint axisVAO, axisVBO;
//
//void initAxis() {
//    glGenVertexArrays(1, &axisVAO);
//    glGenBuffers(1, &axisVBO);
//
//    glBindVertexArray(axisVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
//    glBufferData(GL_ARRAY_BUFFER, axisVertices.size() * sizeof(GLfloat), axisVertices.data(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//// Rotation angles and translation variables
//int rotationDirection = 0;
//float rotationAngleX = 0.0f;
//float rotationAngleY = 0.0f;
//
//void initShaders() {
//    // Create vertex shader
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//    glCompileShader(vertexShader);
//
//    // Create fragment shader
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//    glCompileShader(fragmentShader);
//
//    // Create shader program
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    // Cleanup shaders (no longer needed after linking)
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//}
//
//
//// Initialize cube VAO, VBO, and EBO
//void initCube() {
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glGenBuffers(1, &cubeEBO);
//
//    glBindVertexArray(cubeVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(GLfloat), cubeVertices.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeIndices.size() * sizeof(GLuint), cubeIndices.data(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//void initSphereBuffers() {
//    glGenVertexArrays(1, &sphereVAO);
//    glGenBuffers(1, &sphereVBO);
//    glGenBuffers(1, &sphereEBO);
//
//    glBindVertexArray(sphereVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
//    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(GLfloat), sphereVertices.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(GLuint), sphereIndices.data(), GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//glm::vec3 cubePosition = glm::vec3(-1.0f, 0.2f, -2.0f);
//glm::vec3 spherePosition = glm::vec3(0.8f, 0.5f, 0.5f);
//glm::vec3 targetPosition = spherePosition;
//float interpolationSpeed = 0.05f;
//
//void drawCube() {
//    glUseProgram(shaderProgram);
//
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(-1.0f, 0.2f, -2.0f));
//    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
//
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//    glBindVertexArray(cubeVAO);
//    glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
//
//    
//    glBindVertexArray(0);
//}
//
//void drawSphere() {
//    glUseProgram(shaderProgram);
//
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(0.8f, -0.2f, 0.0f));
//    model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
//
//
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//    glBindVertexArray(sphereVAO);
//    glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, 0);
//
//
//    glBindVertexArray(0);
//}
//
//void drawAxes() {
//    glUseProgram(shaderProgram);
//
//    // Apply the same model, view, projection transformations as your cube or tetrahedron
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//
//    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.03f, 0.0f, -3.0f));
//    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
//    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
//    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
//
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//    glBindVertexArray(axisVAO);
//
//    glDrawArrays(GL_LINES, 0, 2); // X-axis
//    glDrawArrays(GL_LINES, 2, 2); // Y-axis
//    glDrawArrays(GL_LINES, 4, 2); // Z-axis
//
//    glBindVertexArray(0);
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//
//    // Draw the axes without transformations
//    glUseProgram(0);
//    glPushMatrix();
//    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
//    drawAxes();
//    glPopMatrix();
//    
//    glUseProgram(shaderProgram);
//
//    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.5f));
//    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//
//    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
//    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
//
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    drawSphere();
//    drawCube();
//
//    glutSwapBuffers();
//}
//
//void updateSpherePosition() {
//    // If the sphere hasn't reached the target position, move it closer to the target
//    if (glm::distance(spherePosition, targetPosition) > 0.01f) {
//        spherePosition = glm::mix(spherePosition, targetPosition, interpolationSpeed);
//        glutPostRedisplay(); // Request a redraw
//    }
//}
//
//// Initialization function
//void init() {
//    glEnable(GL_DEPTH_TEST);
//    initShaders();
//    initCube();
//    initSphere();
//    initSphereBuffers();
//}
//
//void handleKeypress(unsigned char key, int x, int y) {
//    switch (key) {
//    case '1':
//        break;
//    case '2':
//        targetPosition = cubePosition;
//        break;
//    case '3':
//        break;
//    case '4':
//        break;
//    case '5':
//        break;
//    default:
//        break;
//    }
//    glutPostRedisplay();
//}
//     
//// Main function
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("OpenGL Cone Example");
//
//    glewInit();
//    init();
//    initAxis();
//    glutDisplayFunc(display);
//    glutKeyboardFunc(handleKeypress);
//    glutIdleFunc(updateSpherePosition);
//    glutMainLoop();
//    return 0;
//}
