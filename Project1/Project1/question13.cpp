//#include <iostream>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <cstdlib>
//#include <ctime>
//
//// Shader source code (with uniforms)
//const char* vertexShaderSource = R"(
//#version 330 core
//layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 color;
//
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
//
//out vec3 fragColor;
//
//void main()
//{
//    gl_Position = projection * view * model * vec4(position, 1.0);
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
//GLuint colorLocation;
//
//int faceToDraw = -1;
//int randomFace1 = -1;
//int randomFace2 = -1;
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
//std::vector<GLfloat> tetrahedronVertices = {
//    // Positions         // Colors
//    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // Vertex 0
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // Vertex 1
//     0.0f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // Vertex 2
//     0.0f,  0.0f,  0.5f,  1.0f, 1.0f, 0.0f  // Vertex 3 (Apex)
//};
//
//std::vector<GLuint> tetrahedronIndices = {
//    0, 1, 2,  // Base face
//    0, 1, 3,  // Side face 1
//    1, 2, 3,  // Side face 2
//    2, 0, 3   // Side face 3
//};
//
//std::pair<int, int> getRandomFaces(int faceCount) {
//    int firstFace = rand() % faceCount;
//    int secondFace;
//
//    do {
//        secondFace = rand() % faceCount;
//    } while (secondFace == firstFace); // Ensure the second face is different
//
//    return { firstFace, secondFace };
//}
//
//GLuint cubeVAO, cubeVBO, cubeEBO;
//GLuint tetrahedronVAO, tetrahedronVBO, tetrahedronEBO;
//
//// Shader initialization function
//void initShaders() {
//    // Vertex Shader creation
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//    glCompileShader(vertexShader);
//
//    // Fragment Shader creation
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//    glCompileShader(fragmentShader);
//
//    // Shader Program creation
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    // Shader deletion
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//}
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
//void initTetrahedron() {
//    glGenVertexArrays(1, &tetrahedronVAO);
//    glGenBuffers(1, &tetrahedronVBO);
//    glGenBuffers(1, &tetrahedronEBO);
//
//    glBindVertexArray(tetrahedronVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, tetrahedronVBO);
//    glBufferData(GL_ARRAY_BUFFER, tetrahedronVertices.size() * sizeof(GLfloat), tetrahedronVertices.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tetrahedronEBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tetrahedronIndices.size() * sizeof(GLuint), tetrahedronIndices.data(), GL_STATIC_DRAW);
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
//// Draw the cube and the axes
//void drawCube() {
//    glUseProgram(shaderProgram);
//
//    // Set up transformations
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 1.0f, 0.0f)); // Rotate around x and y axes
//
//    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.5f)); // Move camera back
//    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Perspective projection
//
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
//    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
//    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
//
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//    glBindVertexArray(cubeVAO);
//
//    // Draw the bottom face if 1 is pressed, otherwise draw all faces
//    if (faceToDraw == 0) {
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));
//    }
//    else if (faceToDraw == 1){
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(GLuint)));
//    }
//    else if (faceToDraw == 2) {
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(GLuint)));
//    }
//    else if (faceToDraw == 3) {
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(GLuint)));
//    }
//    else if (faceToDraw == 4) {
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(GLuint)));
//    }
//    else if (faceToDraw == 5) {
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
//    }
//    else if (randomFace1 >= 0 && randomFace1 < 6) {
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(randomFace1 * 6 * sizeof(GLuint)));
//    }
//
//    if (randomFace2 >= 0 && randomFace2 < 6) {
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(randomFace2 * 6 * sizeof(GLuint)));
//    }
//    glBindVertexArray(0);
//}
//
//void drawTetrahedron() {
//    glUseProgram(shaderProgram);
//
//    // Apply the same model, view, projection transformations
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(10.0f), glm::vec3(1.0f, 1.0f, 0.0f));
//
//    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
//    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
//    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
//    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
//
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//    glBindVertexArray(tetrahedronVAO);
//
//    if (faceToDraw == 6) {
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
//    }
//    else if (faceToDraw == 7) {
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)));
//    }
//    else if (faceToDraw == 8) {
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));
//    }
//    else if (faceToDraw == 9) {
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(9 * sizeof(GLuint)));
//    }
//    else if (randomFace1 >= 6 && randomFace1 < 10) {
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)((randomFace1 - 6) * 3 * sizeof(GLuint)));
//    }
//
//    if (randomFace2 >= 6 && randomFace2 < 10) {
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)((randomFace2 - 6) * 3 * sizeof(GLuint)));
//    }
//    glBindVertexArray(0);
//}
//
//// Draw axes
//void drawAxes() {
//    glBegin(GL_LINES);
//    // X-axis (Red)
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glVertex3f(-1.0f, 0.0f, 0.0f);
//    glVertex3f(1.0f, 0.0f, 0.0f);
//    
//    // Y-axis (Green)
//    glColor3f(0.0f, 1.0f, 0.0f);
//    glVertex3f(0.0f, -1.0f, 0.0f);
//    glVertex3f(0.0f, 1.0f, 0.0f);
//    
//    glEnd();
//}
//
//// Display function
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear depth buffer as well
//    drawAxes();
//    drawCube();
//    drawTetrahedron();
//    glutSwapBuffers();
//}
//
//void handleKeypress(unsigned char key, int x, int y) {
//    if (key == '1') {
//        faceToDraw = 0;
//    }
//    else if (key == '2'){
//        faceToDraw = 1;
//    }
//    else if (key == '3'){
//        faceToDraw = 2;
//    }
//    else if (key == '4'){
//        faceToDraw = 3;
//    }
//    else if (key == '5') {
//        faceToDraw = 4;
//    }
//    else if (key == '6'){
//        faceToDraw = 5;
//    }
//    else if (key == '7') {
//        faceToDraw = 6;
//    }
//    else if (key == '8') {
//        faceToDraw = 7;
//    }
//    else if (key == '9') {
//        faceToDraw = 8;
//    }
//    else if (key == '0') {
//        faceToDraw = 9;
//    }
//    else if (key == 'c') {
//        auto faces = getRandomFaces(6); // Get random cube faces
//        randomFace1 = faces.first; // Store first random face
//        randomFace2 = faces.second; // Store second random face
//    }
//    else if (key == 't') {
//        auto faces = getRandomFaces(4); // Get random tetrahedron faces
//        randomFace1 = faces.first + 6; // Store first random face
//        randomFace2 = faces.second + 6; // Store second random face
//    }
//    else {
//        faceToDraw = -1;
//        randomFace1 = -1; // Reset random faces
//        randomFace2 = -1; // Reset random faces
//    }
//    glutPostRedisplay();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("3D Cube with Axes");
//
//    glewInit();
//    initShaders();
//    initCube();
//    initTetrahedron();
//    
//    glEnable(GL_DEPTH_TEST); // Enable depth testing
//
//    glutDisplayFunc(display);
//    glutIdleFunc(display); // Continuously update the display
//    glutKeyboardFunc(handleKeypress);
//    glutMainLoop();
//    return 0;
//}