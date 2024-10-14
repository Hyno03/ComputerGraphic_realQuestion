//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <cstdlib>
//#include <ctime>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//#define M_PI 3.14159265358979323846
//
//// Constants
//const float SPIRAL_RADIUS_INCREMENT = 0.5f; // Distance between loops
//const float SPIRAL_ANGLE_INCREMENT = 0.1f;   // Angle increment for spiral
//const int SPIRAL_LOOPS = 3;                   // Number of loops
//bool drawAsPoints = false; // Flag to track if drawing as points
//
//// Global Variables
//std::vector<std::pair<float, float>> spiralPoints; // Vector to store spiral points
//std::vector<std::vector<std::pair<float, float>>> allSpiralPoints; // Vector of spirals
//std::vector<int> pointCounts; // Number of points drawn for each spiral
//float spiralStartX = 0.0f;
//float spiralStartY = 0.0f;
//bool isDrawing = false; // Flag to check if drawing is active
//
//// Random background color
//float backgroundColor[3] = { 0.3f, 0.3f, 0.3f }; // Default background color (dark gray)
//
//// Function declarations
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//void mouseClick(int button, int state, int x, int y);
//void update(int value);
//void keyboardInput(unsigned char key, int x, int y);
//void drawSpiral();
//std::pair<float, float> getRandomPosition(int width, int height);
//
//// Function to generate random background color
//void generateRandomBackgroundColor()
//{
//    backgroundColor[0] = static_cast<float>(rand()) / RAND_MAX; // Random red
//    backgroundColor[1] = static_cast<float>(rand()) / RAND_MAX; // Random green
//    backgroundColor[2] = static_cast<float>(rand()) / RAND_MAX; // Random blue
//}
//
//int main(int argc, char** argv)
//{
//    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
//
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Spiral Drawing");
//
//    glewInit(); // Initialize GLEW
//
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(Reshape);
//    glutMouseFunc(mouseClick);
//    glutKeyboardFunc(keyboardInput); // Handle keyboard input
//    glutTimerFunc(16, update, 0);
//    glutMainLoop();
//
//    return 0;
//}
//
//GLvoid drawScene()
//{
//    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f); // Set random background color
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    for (int i = 0; i < allSpiralPoints.size(); ++i)
//    {
//        if (drawAsPoints)
//        {
//            glBegin(GL_POINTS); // Draw as points
//            for (int j = 0; j < allSpiralPoints[i].size() && j < pointCounts[i]; ++j)
//            {
//                glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
//                glVertex2f(allSpiralPoints[i][j].first, allSpiralPoints[i][j].second);
//            }
//            glEnd();
//        }
//        else
//        {
//            glBegin(GL_LINE_STRIP); // Draw as lines
//            for (int j = 0; j < allSpiralPoints[i].size() && j < pointCounts[i]; ++j)
//            {
//                glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
//                glVertex2f(allSpiralPoints[i][j].first, allSpiralPoints[i][j].second);
//            }
//            glEnd();
//        }
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
//std::pair<float, float> getRandomPosition(int width, int height)
//{
//    float x = static_cast<float>(rand() % width);
//    float y = static_cast<float>(rand() % height);
//    return { x, height - y }; // Invert y-coordinate for OpenGL
//}
//
//void mouseClick(int button, int state, int x, int y)
//{
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//    {
//        // Save the starting point for the spiral
//        spiralStartX = (float)x;
//        spiralStartY = (float)(glutGet(GLUT_WINDOW_HEIGHT) - y); // Invert y-coordinate
//        spiralPoints.clear(); // Clear previous spiral points
//        isDrawing = true; // Start drawing
//        drawSpiral();
//    }
//}
//
//void drawSpiral()
//{
//    float angle = 0.0f;
//    float radius = 0.0f;
//
//    // Generate a random background color for each new spiral
//    generateRandomBackgroundColor();
//
//    // Randomly choose which spiral points to generate
//    int randomChoice = rand() % 2; // Randomly select 0 or 1
//
//    std::vector<std::pair<float, float>> spiral; // Local vector to hold this spiral's points
//
//    if (randomChoice == 0) {
//        // Spiral Points 1
//        for (int i = 0; i < SPIRAL_LOOPS * (2 * M_PI / SPIRAL_ANGLE_INCREMENT); ++i)
//        {
//            radius += SPIRAL_RADIUS_INCREMENT; // Increase radius at each step
//            angle += SPIRAL_ANGLE_INCREMENT; // Increase angle
//            float x = spiralStartX + radius * cos(angle);
//            float y = spiralStartY + radius * sin(angle);
//            spiral.emplace_back(x, y);
//        }
//
//        for (int i = 0; i < SPIRAL_LOOPS * (2 * M_PI / SPIRAL_ANGLE_INCREMENT); ++i)
//        {
//            radius -= SPIRAL_RADIUS_INCREMENT; // Decrease radius at each step
//            angle -= SPIRAL_ANGLE_INCREMENT; // Decrease angle
//            float x = spiralStartX + 189 - radius * cos(angle);
//            float y = spiralStartY - radius * sin(angle);
//            spiral.emplace_back(x, y);
//        }
//    }
//    else {
//        // Spiral Points 2
//        for (int i = 0; i < SPIRAL_LOOPS * (2 * M_PI / SPIRAL_ANGLE_INCREMENT); ++i)
//        {
//            radius -= SPIRAL_RADIUS_INCREMENT; // Increase radius at each step
//            angle -= SPIRAL_ANGLE_INCREMENT; // Increase angle
//            float x = spiralStartX - radius * cos(angle);
//            float y = spiralStartY - radius * sin(angle);
//            spiral.emplace_back(x, y);
//        }
//
//        for (int i = 0; i < SPIRAL_LOOPS * (2 * M_PI / SPIRAL_ANGLE_INCREMENT); ++i)
//        {
//            radius += SPIRAL_RADIUS_INCREMENT; // Decrease radius at each step
//            angle += SPIRAL_ANGLE_INCREMENT; // Decrease angle
//            float x = spiralStartX + 189 + radius * cos(angle);
//            float y = spiralStartY + radius * sin(angle);
//            spiral.emplace_back(x, y);
//        }
//    }
//
//    allSpiralPoints.push_back(spiral); // Add this spiral to the collection
//    pointCounts.push_back(0); // Initialize point count for this new spiral
//}
//
//void update(int value)
//{
//    for (int i = 0; i < pointCounts.size(); ++i)
//    {
//        // Increment the number of points drawn for each spiral
//        if (pointCounts[i] < allSpiralPoints[i].size())
//        {
//            pointCounts[i]++; // Reveal one more point
//        }
//    }
//
//    glutPostRedisplay(); // Request redraw
//    glutTimerFunc(16, update, 0); // Update every 16ms (about 60 FPS)
//}
//
//void keyboardInput(unsigned char key, int x, int y)
//{
//    if (key == 'c' || key == 'C') // Clear all spirals on 'c' key press
//    {
//        allSpiralPoints.clear();
//        pointCounts.clear(); // Clear point counts as well
//        isDrawing = false;
//        glutPostRedisplay();
//    }
//    else if (key >= '1' && key <= '5') // Handle number keys for spiral count
//    {
//        int numSpirals = key - '0'; // Convert char to int (1 to 5)
//        for (int i = 0; i < numSpirals; ++i)
//        {
//            auto position = getRandomPosition(800, 600); // Get random position
//            spiralStartX = position.first;
//            spiralStartY = position.second;
//            drawSpiral(); // Draw spiral at random position
//        }
//        glutPostRedisplay();
//    }
//    else if (key == 'p' || key == 'P') // Toggle drawing as points
//    {
//        drawAsPoints = true;
//        glutPostRedisplay();
//    }
//    else if (key == 'l' || key == 'L') // Toggle drawing as line
//    {
//        drawAsPoints = false;
//        glutPostRedisplay();
//    }
//}
