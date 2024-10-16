#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <gl/glew.h>
#include <gl/freeglut.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void drawPoints();
void drawLines();
void drawTriangles();
void drawRectangles();
void drawPentagons();
void mouseButton(int button, int state, int x, int y);
void mouseMotion(int x, int y);

// Global variables for dragging
bool dragging = false;
std::pair<float, float> offset; // To track the offset between the mouse click and the shape position
int draggedShapeIndex = -1; // To keep track of which shape is being dragged
std::string draggedShapeType; // To keep track of the type of dragged shape

// Store the positions for shapes
std::vector<std::pair<float, float>> pointPositions;
std::vector<std::pair<float, float>> lineStartPositions;
std::vector<std::pair<float, float>> lineEndPositions;
std::vector<std::vector<std::pair<float, float>>> triangleVertices; // Each triangle has 3 vertices
std::vector<std::vector<std::pair<float, float>>> rectangleVertices; // Each rectangle has 4 vertices
std::vector<std::vector<std::pair<float, float>>> pentagonVertices;

// Function to check if a point is inside a circle (for points)
bool isPointInCircle(float px, float py, const std::pair<float, float>& point, float radius = 5.0f) {
    float dx = px - point.first;
    float dy = py - point.second;
    return (dx * dx + dy * dy <= radius * radius);
}

// Function to check if a point is on a line segment
bool isPointOnLine(float px, float py, const std::pair<float, float>& start, const std::pair<float, float>& end, float threshold = 5.0f) {
    float lineLength = std::hypot(end.first - start.first, end.second - start.second);
    float area = std::abs((end.first - start.first) * (py - start.second) - (px - start.first) * (end.second - start.second));
    return (area < threshold * lineLength); // Check if the area is small compared to line length
}

// Function to check for overlap with existing shapes
bool isOverlapping(float x, float y) {
    // Check against existing rectangles
    for (const auto& rectangle : rectangleVertices) {
        if (x >= rectangle[0].first && x <= rectangle[1].first &&
            y >= rectangle[2].second && y <= rectangle[0].second) {
            return true; // Overlaps with a rectangle
        }
    }

    // Check against existing triangles
    for (const auto& triangle : triangleVertices) {
        // Check if the centroid is inside the triangle
        float centroidX = (triangle[0].first + triangle[1].first + triangle[2].first) / 3.0f;
        float centroidY = (triangle[0].second + triangle[1].second + triangle[2].second) / 3.0f;
        float triangleSize = 50; // Adjust size threshold as necessary

        if (std::abs(centroidX - x) < triangleSize && std::abs(centroidY - y) < triangleSize) {
            return true; // Overlaps with another triangle
        }
    }

    // Check against existing points
    for (const auto& point : pointPositions) {
        if (isPointInCircle(x, y, point)) {
            return true; // Overlaps with a point
        }
    }

    // Check against existing lines (using midpoint)
    for (size_t i = 0; i < lineStartPositions.size(); ++i) {
        float midX = (lineStartPositions[i].first + lineEndPositions[i].first) / 2.0f;
        float midY = (lineStartPositions[i].second + lineEndPositions[i].second) / 2.0f;
        if (isPointInCircle(x, y, { midX, midY }, 15.0f)) { // 15.0f is the radius to check around the midpoint
            return true; // Overlaps with a line
        }
    }

    return false; // No overlap detected
}

// Initialize positions
void initializePositions() {
    for (int i = 0; i < 3; ++i) {
        float x, y;

        // Ensure unique positions for points
        do {
            x = rand() % 800;
            y = rand() % 600;
        } while (isOverlapping(x, y));

        pointPositions.emplace_back(x, y);

        // Lines
        float x1, y1, x2, y2;
        do {
            x1 = rand() % 800;
            y1 = rand() % 600;
            x2 = rand() % 800;
            y2 = rand() % 600;
        } while (isOverlapping((x1 + x2) / 2, (y1 + y2) / 2)); // Midpoint check
        lineStartPositions.emplace_back(x1, y1);
        lineEndPositions.emplace_back(x2, y2);

        // Triangles
        std::vector<std::pair<float, float>> triangle;
        do {
            x = rand() % 800;
            y = rand() % 600;
            triangle.clear();
            triangle.emplace_back(x, y);
            triangle.emplace_back(x + 50, y);
            triangle.emplace_back(x + 25, y + 50);
        } while (isOverlapping(x, y));
        triangleVertices.push_back(triangle);

        // Rectangles
        std::vector<std::pair<float, float>> rectangle;
        do {
            x = rand() % 800;
            y = rand() % 600;
            rectangle.clear();
            rectangle.emplace_back(x - 50, y + 50);
            rectangle.emplace_back(x + 50, y + 50);
            rectangle.emplace_back(x + 50, y - 50);
            rectangle.emplace_back(x - 50, y - 50);
        } while (isOverlapping(x, y)); // Ensure random position does not overlap
        rectangleVertices.push_back(rectangle);

        // Pentagons
        std::vector<std::pair<float, float>> pentagon;
        const float radius = 50.0f;
        const int numSides = 5;
        float angle = 2.0f * 3.1415926f / numSides;
        float startAngle = 3.1415926f / 2.0f;

        // Adjust pentagon's position to be away from other shapes
        float pentagonX, pentagonY;
        do {
            pentagonX = rand() % 800;
            pentagonY = rand() % 600;
            pentagon.clear();
            for (int j = 0; j < numSides; ++j) {
                float dx = radius * cosf(startAngle + j * angle);
                float dy = radius * sinf(startAngle + j * angle);
                pentagon.emplace_back(pentagonX + dx, pentagonY + dy);
            }
        } while (isOverlapping(pentagonX, pentagonY)); // Ensure random position does not overlap
        pentagonVertices.push_back(pentagon);
    }
}

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(0)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Shape Transformation Example");
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    initializePositions();  // Initialize positions once

    glutMouseFunc(mouseButton);   // Register mouse button handler
    glutMotionFunc(mouseMotion);   // Register mouse motion handler
    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMainLoop();

    return 0;
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert mouse coordinates to OpenGL coordinates
        float mouseX = static_cast<float>(x);
        float mouseY = static_cast<float>(600 - y); // Invert Y coordinate

        // Check if any shape is clicked
        for (size_t i = 0; i < pointPositions.size(); ++i) {
            if (isPointInCircle(mouseX, mouseY, pointPositions[i])) {
                dragging = true;
                draggedShapeIndex = i;
                draggedShapeType = "point"; // Track dragged shape type
                offset = { mouseX - pointPositions[i].first, mouseY - pointPositions[i].second }; // Store offset
                return;
            }
        }

        for (size_t i = 0; i < lineStartPositions.size(); ++i) {
            // Check for line click
            if (isPointOnLine(mouseX, mouseY, lineStartPositions[i], lineEndPositions[i])) {
                dragging = true;
                draggedShapeIndex = i;
                draggedShapeType = "line"; // Track dragged shape type
                offset = { mouseX - lineStartPositions[i].first, mouseY - lineStartPositions[i].second }; // Store offset
                return;
            }
        }

        for (size_t i = 0; i < rectangleVertices.size(); ++i) {
            // Check for rectangle click (use the top-left vertex for offset calculation)
            if (isPointInCircle(mouseX, mouseY, rectangleVertices[i][0], 30.0f)) {
                dragging = true;
                draggedShapeIndex = i;
                draggedShapeType = "rectangle"; // Track dragged shape type
                // Rectangles (Use the center point for offset calculation)
                offset = { mouseX - ((rectangleVertices[i][0].first + rectangleVertices[i][2].first) / 2),
                           mouseY - ((rectangleVertices[i][0].second + rectangleVertices[i][2].second) / 2) };

                return;
            }
        }

        for (size_t i = 0; i < triangleVertices.size(); ++i) {
            // Check for triangle click
            if (isPointInCircle(mouseX, mouseY, triangleVertices[i][0], 30.0f)) { // Using a radius for click detection
                dragging = true;
                draggedShapeIndex = i;
                draggedShapeType = "triangle"; // Track dragged shape type
                offset = { mouseX - triangleVertices[i][0].first, mouseY - triangleVertices[i][0].second }; // Store offset
                return;
            }
        }

        for (size_t i = 0; i < pentagonVertices.size(); ++i) {
            // Check for pentagon click
            if (isPointInCircle(mouseX, mouseY, pentagonVertices[i][0], 30.0f)) { // Using a radius for click detection
                dragging = true;
                draggedShapeIndex = i;
                draggedShapeType = "pentagon"; // Track dragged shape type
                offset = { mouseX - pentagonVertices[i][0].first, mouseY - pentagonVertices[i][0].second }; // Store offset
                return;
            }
        }
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        dragging = false;
        draggedShapeIndex = -1; // Reset dragged shape index
    }
}

void mouseMotion(int x, int y) {
    if (dragging && draggedShapeIndex != -1) {
        float mouseX = static_cast<float>(x);
        float mouseY = static_cast<float>(600 - y); // Invert Y coordinate

        // Update the position of the dragged shape based on the mouse position and the offset
        if (draggedShapeType == "rectangle") {
            float newX = mouseX - offset.first;
            float newY = mouseY - offset.second;

            // Update rectangle positions
            rectangleVertices[draggedShapeIndex][0] = { newX - 50, newY + 50 };
            rectangleVertices[draggedShapeIndex][1] = { newX + 50, newY + 50 };
            rectangleVertices[draggedShapeIndex][2] = { newX + 50, newY - 50 };
            rectangleVertices[draggedShapeIndex][3] = { newX - 50, newY - 50 };
        }
        else if (draggedShapeType == "triangle") {
            float newX = mouseX - offset.first;
            float newY = mouseY - offset.second;

            // Update triangle positions
            triangleVertices[draggedShapeIndex][0] = { newX, newY };
            triangleVertices[draggedShapeIndex][1] = { newX + 50, newY };
            triangleVertices[draggedShapeIndex][2] = { newX + 25, newY + 50 };
        }
        else if (draggedShapeType == "pentagon") {
            float newX = mouseX - offset.first;
            float newY = mouseY - offset.second;

            // Update pentagon positions
            const float radius = 50.0f;
            const int numSides = 5;
            float angle = 2.0f * 3.1415926f / numSides;
            float startAngle = 3.1415926f / 2.0f;

            pentagonVertices[draggedShapeIndex].clear();
            for (int j = 0; j < numSides; ++j) {
                float dx = radius * cosf(startAngle + j * angle);
                float dy = radius * sinf(startAngle + j * angle);
                pentagonVertices[draggedShapeIndex].emplace_back(newX + dx, newY + dy);
            }
        }
        else if (draggedShapeType == "point") {
            // Update point position
            pointPositions[draggedShapeIndex] = { mouseX, mouseY };
        }
        else if (draggedShapeType == "line") {
            // Update line position by moving both ends
            float newX = mouseX - offset.first;
            float newY = mouseY - offset.second;

            lineStartPositions[draggedShapeIndex] = { newX, newY };
            lineEndPositions[draggedShapeIndex] = { newX + 50, newY + 50 }; // Adjust as necessary
        }

        // Redraw the scene
        glutPostRedisplay();
    }
}

GLvoid drawScene(GLvoid) {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the window

    drawPoints();
    drawLines();
    drawTriangles();
    drawRectangles();
    drawPentagons();

    glutSwapBuffers(); // Swap buffers
}

GLvoid Reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
}

void drawPoints() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red for points
    glBegin(GL_POINTS);
    for (const auto& point : pointPositions) {
        glVertex2f(point.first, point.second);
    }
    glEnd();
}

void drawLines() {
    glColor3f(0.0f, 1.0f, 0.0f); // Green for lines
    glBegin(GL_LINES);
    for (size_t i = 0; i < lineStartPositions.size(); ++i) {
        glVertex2f(lineStartPositions[i].first, lineStartPositions[i].second);
        glVertex2f(lineEndPositions[i].first, lineEndPositions[i].second);
    }
    glEnd();
}

void drawTriangles() {
    glColor3f(0.0f, 0.0f, 1.0f); // Blue for triangles
    for (const auto& triangle : triangleVertices) {
        glBegin(GL_TRIANGLES);
        for (const auto& vertex : triangle) {
            glVertex2f(vertex.first, vertex.second);
        }
        glEnd();
    }
}

void drawRectangles() {
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow for rectangles
    for (const auto& rectangle : rectangleVertices) {
        glBegin(GL_QUADS);
        for (const auto& vertex : rectangle) {
            glVertex2f(vertex.first, vertex.second);
        }
        glEnd();
    }
}

void drawPentagons() {
    glColor3f(1.0f, 0.5f, 0.0f); // Orange for pentagons
    for (const auto& pentagon : pentagonVertices) {
        glBegin(GL_POLYGON);
        for (const auto& vertex : pentagon) {
            glVertex2f(vertex.first, vertex.second);
        }
        glEnd();
    }
}
