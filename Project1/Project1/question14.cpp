//#include <iostream>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
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
//GLuint colorLocation;
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
//std::vector<GLfloat> pyramidVertices = {
//    // Positions         // Colors
//    -0.5f, 0.0f, -0.5f,  1.0f, 0.0f, 0.0f, // Base Vertex 0
//     0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f, // Base Vertex 1
//     0.5f, 0.0f,  0.5f,  0.0f, 0.0f, 1.0f, // Base Vertex 2
//    -0.5f, 0.0f,  0.5f,  1.0f, 1.0f, 0.0f, // Base Vertex 3
//     0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 1.0f  // Apex Vertex 4
//};
//
//std::vector<GLuint> pyramidIndices = {
//    0, 1, 4,  // Side face 1
//    1, 2, 4,  // Side face 2
//    2, 3, 4,  // Side face 3
//    3, 0, 4,  // Side face 4
//    0, 1, 2,  // Base face
//    2, 3, 0   // Base face (closing the square)
//};
//
//GLuint cubeVAO, cubeVBO, cubeEBO;
//GLuint pyramidVAO, pyramidVBO, pyramidEBO;
//
//bool showCube = true;
//bool drawHiddenFace = true;
//bool isWireframe = false;
//int rotationDirection = 0;
//float rotationAngleX = 30.0f;
//float rotationAngleY = 45.0f;
//float translationX = 0.0f;
//float translationY = 0.0f;
//
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
//void initPyramid() {
//    glGenVertexArrays(1, &pyramidVAO);
//    glGenBuffers(1, &pyramidVBO);
//    glGenBuffers(1, &pyramidEBO);
//
//    glBindVertexArray(pyramidVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
//    glBufferData(GL_ARRAY_BUFFER, pyramidVertices.size() * sizeof(GLfloat), pyramidVertices.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidEBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pyramidIndices.size() * sizeof(GLuint), pyramidIndices.data(), GL_STATIC_DRAW);
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
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
//    model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
//    model = glm::translate(model, glm::vec3(translationX, translationY, 0.0f));
//
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
//
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//    glBindVertexArray(cubeVAO);
//    glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
//}
//
//void drawPyramid() {
//    glUseProgram(shaderProgram);
//
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::rotate(model, glm::radians(rotationAngleX), glm::vec3(1.0f, 1.0f, 0.0f));
//    model = glm::rotate(model, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
//    model = glm::translate(model, glm::vec3(translationX, translationY, 0.0f));
//
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
//
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//    glBindVertexArray(pyramidVAO);
//    glDrawElements(GL_TRIANGLES, pyramidIndices.size(), GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
//}
//
//// Draw axes
//void drawAxes() {
//    glBegin(GL_LINES);
//    // X-axis (Red)
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glVertex3f(-5.0f, 0.0f, 0.0f);
//    glVertex3f(5.0f, 0.0f, 0.0f);
//    
//    // Y-axis (Green)
//    glColor3f(1.0f, 0.0f, 0.0f);
//    glVertex3f(0.0f, -5.0f, 0.0f);
//    glVertex3f(0.0f, 5.0f, 0.0f);
//    
//    glEnd();
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear depth buffer
//
//    // --- 1. Draw the axes first, without any transformations ---
//    glUseProgram(0);  // Disable shader program for fixed-function pipeline
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity(); // No transformations for axes
//    drawAxes();       // Draw axes
//
//    // --- 2. Use shaders to draw the cube or pyramid ---
//    glUseProgram(shaderProgram);
//
//    // Set up the view and projection matrices (shared between cube/pyramid)
//    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.5f)); // Move camera back
//    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // Perspective projection
//
//    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
//    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
//
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//    // Apply rotation transformation to the model (cube or pyramid)
//    glm::mat4 modelTransform = glm::mat4(1.0f);
//    modelTransform = glm::rotate(modelTransform, glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around X-axis
//    modelTransform = glm::rotate(modelTransform, glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis
//
//    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelTransform");
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransform));
//
//    // Draw cube or pyramid based on the current mode
//    if (showCube) {
//        drawCube();
//    }
//    else {
//        drawPyramid();
//    }
//
//    glutSwapBuffers(); // Swap buffers for smooth rendering
//}
//
//void updateAnimation() {
//    const float rotationSpeed = 1.0f; // 초당 1도 회전
//
//    if (rotationDirection == 1) {
//        rotationAngleX += rotationSpeed;
//    }
//    else if (rotationDirection == -1) {
//        rotationAngleX -= rotationSpeed;
//    }
//    else if (rotationDirection == 2) {
//        rotationAngleY += rotationSpeed;
//    }
//    else if (rotationDirection == -2) {
//        rotationAngleY -= rotationSpeed;
//    }
//
//    glm::mat4 modelTransform = glm::mat4(1.0f);
//    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(translationX, translationY, 0.0f));
//    modelTransform = translation * modelTransform;
//
//    if (rotationAngleX >= 360.0f) rotationAngleX -= 360.0f;
//    if (rotationAngleX < 0.0f) rotationAngleX += 360.0f;
//    if (rotationAngleY >= 360.0f) rotationAngleY -= 360.0f;
//    if (rotationAngleY < 0.0f) rotationAngleY += 360.0f;
//
//    glutPostRedisplay();
//}
//
//void handleKeypress(unsigned char key, int x, int y) {
//    const float translationSpeed = 0.1f;
//
//    if (key == 'c') {
//        showCube = true;
//    }
//    else if (key == 'p') {
//        showCube = false;
//    }
//    else if (key == 'h') {
//        drawHiddenFace = !drawHiddenFace;
//        if (drawHiddenFace) {
//            glEnable(GL_DEPTH_TEST);
//        }
//        else {
//            glDisable(GL_DEPTH_TEST);
//        }
//    }
//    else if (key == 'w' || key == 'W') {
//        isWireframe = !isWireframe;
//        if (isWireframe) {
//            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        }
//        else {
//            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//        }
//    }
//    else if (key == 'x') {
//        rotationDirection = 1;
//    }
//    else if (key == 'X') {
//        rotationDirection = -1;
//    }
//    else if (key == 'y') {
//        rotationDirection = 2;
//    }
//    else if (key == 'Y') { 
//        rotationDirection = -2;
//    }
//    else if(key == 's'){
//        rotationDirection = 0;
//        translationY = 0.0f;
//        translationX = 0.0f;
//    }
//    glutPostRedisplay();
//}
//
//void handleSpecialKeypress(int key, int x, int y) {
//    const float translationSpeed = 0.1f; // Translation speed
//
//    if (key == GLUT_KEY_UP) {
//        translationY += translationSpeed; // Move up
//    }
//    else if (key == GLUT_KEY_DOWN) {
//        translationY -= translationSpeed; // Move down
//    }
//    else if (key == GLUT_KEY_LEFT) {
//        translationX -= translationSpeed; // Move left
//    }
//    else if (key == GLUT_KEY_RIGHT) {
//        translationX += translationSpeed; // Move right
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
//    initPyramid();
//
//    glCullFace(GL_BACK);
//    glFrontFace(GL_CCW);
//
//    glutDisplayFunc(display);
//    glutIdleFunc(display);
//    glutIdleFunc(updateAnimation);
//    glutKeyboardFunc(handleKeypress);
//    glutSpecialFunc(handleSpecialKeypress);
//    glutMainLoop();
//    return 0;
//}
