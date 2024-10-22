//#include <iostream>
//#include <vector>
//#include <cstdlib> // For random numbers
//#include <ctime>   // For seeding random
//#include <cmath>   // For trigonometric functions (for pentagon)
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//
//#define M_PI 3.14159265358979323846
//
//// Shader source code (using uniform for color input)
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
//uniform vec3 shapeColor; // uniform variable for color input
//out vec4 color;
//
//void main()
//{
//    color = vec4(shapeColor, 1.0); // Use the uniform color
//}
//)";
//
//std::vector<std::vector<GLfloat>> shapesPositions;
//std::vector<GLfloat> shapesColors;
//bool isDragging = false;
//int draggedShapeIndex = -1; // To keep track of which shape is dragged
//int screenWidth = 800, screenHeight = 600; // Window dimensions
//
//GLuint shaderProgram;
//GLuint colorLocation;
//
//// Random float generator between min and max
//float randFloat(float min, float max) {
//    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
//}
//
//void generateShapesPositions() {
//    for (int i = 0; i < 3; ++i) {
//        // Generate line vertices
//        std::vector<GLfloat> lineVertices = {
//            randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f),
//            randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f)
//        };
//        shapesPositions.push_back(lineVertices);
//        // Store color for the line
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//
//        // Generate triangle vertices
//        float centerX = randFloat(-0.8f, 0.8f);
//        float centerY = randFloat(-0.8f, 0.8f);
//        float size = 0.1f;
//        std::vector<GLfloat> triangleVertices = {
//            centerX, centerY + size,  // Top
//            centerX - size, centerY - size, // Bottom left
//            centerX + size, centerY - size  // Bottom right
//        };
//        shapesPositions.push_back(triangleVertices);
//        // Store color for the triangle
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//
//        // Generate rectangle vertices
//        float rectCenterX = randFloat(-0.8f, 0.8f);
//        float rectCenterY = randFloat(-0.8f, 0.8f);
//        float width = 0.1f;
//        float height = 0.1f;
//        std::vector<GLfloat> rectangleVertices = {
//            rectCenterX - width, rectCenterY + height, // Top left
//            rectCenterX + width, rectCenterY + height, // Top right
//            rectCenterX + width, rectCenterY - height, // Bottom right
//            rectCenterX - width, rectCenterY - height  // Bottom left
//        };
//        shapesPositions.push_back(rectangleVertices);
//        // Store color for the rectangle
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//
//        // Generate pentagon vertices
//        float pentagonCenterX = randFloat(-0.8f, 0.8f);
//        float pentagonCenterY = randFloat(-0.8f, 0.8f);
//        float radius = 0.1f;
//        std::vector<GLfloat> pentagonVertices;
//        for (int j = 0; j < 5; ++j) {
//            float angle = j * (2.0f * M_PI / 5.0f);
//            pentagonVertices.push_back(pentagonCenterX + radius * cos(angle));
//            pentagonVertices.push_back(pentagonCenterY + radius * sin(angle));
//        }
//        shapesPositions.push_back(pentagonVertices);
//        // Store color for the pentagon
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//        shapesColors.push_back(randFloat(0.0f, 1.0f));
//    }
//}
//
//// Shader initialization function
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
//    // Delete shaders after linking
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // Get the location of the color uniform variable
//    colorLocation = glGetUniformLocation(shaderProgram, "shapeColor");
//}
//
//void drawShapesInQuadrants() {
//    for (size_t i = 0; i < shapesPositions.size(); ++i) {
//        GLuint VBO, VAO;
//        glGenVertexArrays(1, &VAO);
//        glGenBuffers(1, &VBO);
//
//        glBindVertexArray(VAO);
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(shapesPositions[i][0]) * shapesPositions[i].size(), shapesPositions[i].data(), GL_STATIC_DRAW);
//
//        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(0);
//
//        glUseProgram(shaderProgram);
//
//        // Use stored color for the shape
//        glUniform3f(colorLocation, shapesColors[i * 3], shapesColors[i * 3 + 1], shapesColors[i * 3 + 2]);
//
//        switch (i % 4) { // 0 = line, 1 = triangle, 2 = rectangle, 3 = pentagon
//        case 0: glDrawArrays(GL_LINES, 0, 2); break;
//        case 1: glDrawArrays(GL_TRIANGLES, 0, 3); break;
//        case 2: glDrawArrays(GL_QUADS, 0, 4); break;
//        case 3: glDrawArrays(GL_POLYGON, 0, 5); break;
//        }
//
//        glDeleteBuffers(1, &VBO);
//        glDeleteVertexArrays(1, &VAO);
//    }
//}
//
//// Display function
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    drawShapesInQuadrants();
//    glutSwapBuffers();
//}
//
//// Function to detect if a point is inside a shape
//bool isPointInShape(int shapeIndex, float x, float y) {
//    const auto& vertices = shapesPositions[shapeIndex];
//
//    // Determine if the click is within the shape bounds
//    if (shapeIndex % 4 == 0) { // Line
//        // For lines, check if point is near the line segment (simple bounding box check)
//        return (x >= std::min(vertices[0], vertices[2]) && x <= std::max(vertices[0], vertices[2]) &&
//            y >= std::min(vertices[1], vertices[3]) && y <= std::max(vertices[1], vertices[3]));
//    }
//    else if (shapeIndex % 4 == 1) { // Triangle
//        // Simple check for triangle bounding box
//        return (x >= std::min(std::min(vertices[0], vertices[2]), vertices[4]) &&
//            x <= std::max(std::max(vertices[0], vertices[2]), vertices[4]) &&
//            y >= std::min(std::min(vertices[1], vertices[3]), vertices[5]) &&
//            y <= std::max(std::max(vertices[1], vertices[3]), vertices[5]));
//    }
//    else if (shapeIndex % 4 == 2) { // Rectangle
//        float left = vertices[0];
//        float right = vertices[2];
//        float top = vertices[1];
//        float bottom = vertices[3];
//
//        return (x >= left && x <= right && y >= bottom && y <= top);
//    }
//    else if (shapeIndex % 4 == 3) { // Pentagon
//        // Simple bounding box check
//        return (x >= std::min(std::min(vertices[0], vertices[2]), std::min(vertices[4], vertices[6])) &&
//            x <= std::max(std::max(vertices[0], vertices[2]), std::max(vertices[4], vertices[6])) &&
//            y >= std::min(std::min(vertices[1], vertices[3]), std::min(vertices[5], vertices[7])) &&
//            y <= std::max(std::max(vertices[1], vertices[3]), std::max(vertices[5], vertices[7])));
//    }
//
//    return false;
//}
//
//void mouseClick(int button, int state, int x, int y) {
//    y = screenHeight - y; // Flip y coordinate
//
//    if (button == GLUT_LEFT_BUTTON) {
//        if (state == GLUT_DOWN) {
//            // Check for shape selection
//            for (size_t i = 0; i < shapesPositions.size(); ++i) {
//                if (isPointInShape(i, (float)x / (screenWidth / 2) - 1.0f, (float)y / (screenHeight / 2) - 1.0f)) {
//                    isDragging = true;
//                    draggedShapeIndex = i;
//                    break;
//                }
//            }
//        }
//        else if (state == GLUT_UP) {
//            isDragging = false;
//            draggedShapeIndex = -1;
//        }
//    }
//
//    glutPostRedisplay();
//}
//
//void mouseMove(int x, int y) {
//    y = screenHeight - y; // Flip y coordinate
//
//    if (isDragging && draggedShapeIndex != -1) {
//        // Update the position of the dragged shape
//        auto& vertices = shapesPositions[draggedShapeIndex];
//        float offsetX = (float)x / (screenWidth / 2) - 1.0f;
//        float offsetY = (float)y / (screenHeight / 2) - 1.0f;
//
//        if (draggedShapeIndex % 4 == 0) { // Line
//            vertices[0] = offsetX; // Update line position
//            vertices[1] = offsetY;
//        }
//        else if (draggedShapeIndex % 4 == 1) { // Triangle
//            vertices[0] = offsetX; // Update triangle position
//            vertices[1] = offsetY + 0.1f; // Keep the top vertex above
//            vertices[2] = offsetX - 0.1f; // Bottom left
//            vertices[3] = offsetY - 0.1f; // Bottom left
//            vertices[4] = offsetX + 0.1f; // Bottom right
//            vertices[5] = offsetY - 0.1f; // Bottom right
//        }
//        else if (draggedShapeIndex % 4 == 2) { // Rectangle
//            float width = 0.1f;
//            float height = 0.1f;
//            vertices[0] = offsetX - width; // Update rectangle position
//            vertices[1] = offsetY + height; // Top left
//            vertices[2] = offsetX + width; // Top right
//            vertices[3] = offsetY - height; // Bottom left
//            vertices[4] = offsetX + width; // Bottom right
//            vertices[5] = offsetY - height; // Bottom right
//            vertices[6] = offsetX - width; // Bottom left
//            vertices[7] = offsetY + height; // Bottom left
//        }
//        else if (draggedShapeIndex % 4 == 3) { // Pentagon
//            float radius = 0.1f;
//            for (int i = 0; i < 5; ++i) {
//                float angle = i * (2.0f * M_PI / 5.0f);
//                vertices[i * 2] = offsetX + radius * cos(angle); // Update pentagon position
//                vertices[i * 2 + 1] = offsetY + radius * sin(angle);
//            }
//        }
//
//        glutPostRedisplay(); // Redraw the scene
//    }
//}
//
//void init() {
//    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//    initShaders();
//    generateShapesPositions();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(screenWidth, screenHeight);
//    glutCreateWindow("OpenGL Shapes with Drag and Drop");
//
//    glewInit();
//
//    init();
//
//    glutDisplayFunc(display);
//    glutMouseFunc(mouseClick);
//    glutMotionFunc(mouseMove); // Mouse motion function for dragging
//    glutPassiveMotionFunc(mouseMove); // To track the mouse when moving without clicking
//
//    glutMainLoop();
//    return 0;
//}
