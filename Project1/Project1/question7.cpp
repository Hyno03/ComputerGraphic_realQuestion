#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

struct Square {
    float x, y;
    float r, g, b; // 색상
};

struct Line {
    float x1, y1, x2, y2; // 선의 시작점과 끝점
    float r, g, b;        // 색상
};

struct Triangle {
    float x1, y1, x2, y2, x3, y3; // 삼각형의 세 점
    float r, g, b;                // 색상
};

std::vector<Square> squares;    // 사각형을 저장할 벡터
std::vector<Line> lines;        // 선을 저장할 벡터
std::vector<Triangle> triangles; // 삼각형을 저장할 벡터

bool isPointMode = false;       // 점 생성 모드 상태
bool isLineMode = false;        // 선 그리기 모드 상태
bool isTriangleMode = false;    // 삼각형 그리기 모드 상태
bool isSquareMode = false;      // 사각형 그리기 모드 상태

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void mouseClick(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void update(int value);

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(0))); // 랜덤 시드 초기화

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600); // 윈도우 크기 수정
    glutCreateWindow("Example1");
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMouseFunc(mouseClick); // 마우스 클릭 이벤트 등록
    glutKeyboardFunc(keyboard); // 키보드 입력 등록
    glutTimerFunc(16, update, 0); // 업데이트 함수 호출 설정
    glutMainLoop();

    return 0;
}

GLvoid drawScene()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f); // 짙은 회색 배경
    glClear(GL_COLOR_BUFFER_BIT);

    // 저장된 사각형을 모두 그리기
    for (const auto& square : squares) {
        // 사각형 내부 색상
        glColor3f(square.r, square.g, square.b);
        glBegin(GL_QUADS);
        glVertex2f(square.x - 5, square.y - 5); // 사각형 크기 10x10으로 설정
        glVertex2f(square.x + 5, square.y - 5);
        glVertex2f(square.x + 5, square.y + 5);
        glVertex2f(square.x - 5, square.y + 5);
        glEnd();

        // 사각형 테두리 색상
        glColor3f(0.0f, 0.0f, 0.0f); // 검은색 테두리
        glBegin(GL_LINE_LOOP); // 선으로 테두리 그리기
        glVertex2f(square.x - 5, square.y - 5);
        glVertex2f(square.x + 5, square.y - 5);
        glVertex2f(square.x + 5, square.y + 5);
        glVertex2f(square.x - 5, square.y + 5);
        glEnd();
    }

    // 저장된 선을 모두 그리기
    for (const auto& line : lines) {
        glColor3f(line.r, line.g, line.b); // 선 색상 설정
        glBegin(GL_LINES);
        glVertex2f(line.x1, line.y1);
        glVertex2f(line.x2, line.y2);
        glEnd();
    }

    // 저장된 삼각형을 모두 그리기
    for (const auto& triangle : triangles) {
        // 삼각형 내부 색상
        glColor3f(triangle.r, triangle.g, triangle.b);
        glBegin(GL_TRIANGLES);
        glVertex2f(triangle.x1, triangle.y1);
        glVertex2f(triangle.x2, triangle.y2);
        glVertex2f(triangle.x3, triangle.y3);
        glEnd();

        // 삼각형 테두리 색상
        glColor3f(0.0f, 0.0f, 0.0f); // 검은색 테두리
        glBegin(GL_LINE_LOOP); // 선으로 테두리 그리기
        glVertex2f(triangle.x1, triangle.y1);
        glVertex2f(triangle.x2, triangle.y2);
        glVertex2f(triangle.x3, triangle.y3);
        glEnd();
    }

    glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); // 투영 행렬 모드 설정
    glLoadIdentity(); // 기본 행렬로 초기화
    glOrtho(0, w, 0, h, -1, 1); // 좌표계 설정 (왼쪽 아래가 0, 0)
    glMatrixMode(GL_MODELVIEW); // 모델 뷰 행렬 모드로 전환
}

int squaresCount = 0;
void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        int transformedY = windowHeight - y; // 윈도우 좌표계를 OpenGL 좌표계로 변환

        int totalShapes = squares.size() + lines.size() + (triangles.size() - squaresCount*2) + squaresCount;

        if (totalShapes < 10) {
            if (isPointMode) {
                // 점 생성 모드일 때
                Square newSquare;
                newSquare.x = x;
                newSquare.y = transformedY;
                newSquare.r = static_cast<float>(rand()) / RAND_MAX;
                newSquare.g = static_cast<float>(rand()) / RAND_MAX;
                newSquare.b = static_cast<float>(rand()) / RAND_MAX;
                squares.push_back(newSquare);
            }
            if (isLineMode) {
                // 랜덤 크기와 색상으로 선을 그리기
                Line newLine;
                newLine.r = static_cast<float>(rand()) / RAND_MAX;
                newLine.g = static_cast<float>(rand()) / RAND_MAX;
                newLine.b = static_cast<float>(rand()) / RAND_MAX;

                // 선의 길이를 랜덤으로 설정
                float length = 50.0f + static_cast<float>(rand() % 100); // 50 ~ 150 길이의 선

                // 선의 방향은 랜덤한 각도로 설정
                float angle = static_cast<float>(rand()) / RAND_MAX * 360.0f;
                float radians = angle * 3.14159f / 180.0f;

                // 클릭한 위치를 중심으로 선의 시작점과 끝점 계산
                newLine.x1 = x - length / 2 * cos(radians);
                newLine.y1 = transformedY - length / 2 * sin(radians);
                newLine.x2 = x + length / 2 * cos(radians);
                newLine.y2 = transformedY + length / 2 * sin(radians);

                lines.push_back(newLine); // 벡터에 선 추가
            }
            if (isTriangleMode) {
                // 랜덤 크기와 색상으로 삼각형을 그리기
                Triangle newTriangle;
                newTriangle.r = static_cast<float>(rand()) / RAND_MAX;
                newTriangle.g = static_cast<float>(rand()) / RAND_MAX;
                newTriangle.b = static_cast<float>(rand()) / RAND_MAX;

                // 삼각형의 크기를 랜덤으로 설정
                float size = 30.0f + static_cast<float>(rand() % 50); // 30 ~ 80 크기의 삼각형

                // 클릭한 위치를 기준으로 랜덤 크기의 삼각형의 꼭짓점 설정
                newTriangle.x1 = x;
                newTriangle.y1 = transformedY + size;  // 위쪽 점
                newTriangle.x2 = x - size / 2;
                newTriangle.y2 = transformedY - size / 2;  // 왼쪽 아래 점
                newTriangle.x3 = x + size / 2;
                newTriangle.y3 = transformedY - size / 2;  // 오른쪽 아래 점

                triangles.push_back(newTriangle); // 벡터에 삼각형 추가
            }
            if (isSquareMode) {
                // 랜덤 크기와 색상으로 사각형을 그리기
                Triangle triangle1, triangle2; // 두 개의 삼각형으로 사각형을 구성
                triangle1.r = static_cast<float>(rand()) / RAND_MAX;
                triangle1.g = static_cast<float>(rand()) / RAND_MAX;
                triangle1.b = static_cast<float>(rand()) / RAND_MAX;
                triangle2.r = triangle1.r;
                triangle2.g = triangle1.g;
                triangle2.b = triangle1.b;
                float size = 30.0f + static_cast<float>(rand() % 50); // 30 ~ 80 크기의 사각형

                // 클릭한 위치를 기준으로 사각형의 두 삼각형 설정
                triangle1.x1 = x - size / 2;       triangle1.y1 = transformedY + size / 2; // 왼쪽 위
                triangle1.x2 = x + size / 2;       triangle1.y2 = transformedY + size / 2; // 오른쪽 위
                triangle1.x3 = x - size / 2;       triangle1.y3 = transformedY - size / 2; // 왼쪽 아래

                triangle2.x1 = x + size / 2;       triangle2.y1 = transformedY + size / 2; // 오른쪽 위
                triangle2.x2 = x + size / 2;       triangle2.y2 = transformedY - size / 2; // 오른쪽 아래
                triangle2.x3 = x - size / 2;       triangle2.y3 = transformedY - size / 2; // 왼쪽 아래

                triangles.push_back(triangle1); // 첫 번째 삼각형 추가
                triangles.push_back(triangle2); // 두 번째 삼각형 추가
                
                squaresCount += 1;
            }
        }
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
        isPointMode = !isPointMode; // 점 그리기 모드 토글
        isLineMode = false;        // 점 모드에서는 선 모드 비활성화
        isTriangleMode = false;    // 점 모드에서는 삼각형 모드 비활성화
        isSquareMode = false;      // 점 모드에서는 사각형 모드 비활성화
        break;
    case 'l':
        isLineMode = !isLineMode; // 선 그리기 모드 토글
        isPointMode = false;       // 선 모드에서는 점 모드 비활성화
        isTriangleMode = false;    // 선 모드에서는 삼각형 모드 비활성화
        isSquareMode = false;      // 선 모드에서는 사각형 모드 비활성화
        break;
    case 't':
        isTriangleMode = !isTriangleMode; // 삼각형 그리기 모드 토글
        isPointMode = false;              // 삼각형 모드에서는 점 모드 비활성화
        isLineMode = false;               // 삼각형 모드에서는 선 모드 비활성화
        isSquareMode = false;             // 삼각형 모드에서는 사각형 모드 비활성화
        break;
    case 'r':
        isSquareMode = !isSquareMode; // 사각형 그리기 모드 토글
        isPointMode = false;           // 사각형 모드에서는 점 모드 비활성화
        isLineMode = false;            // 사각형 모드에서는 선 모드 비활성화
        isTriangleMode = false;        // 사각형 모드에서는 삼각형 모드 비활성화
        break;
    case 'c':
        // 모든 도형 삭제
        squares.clear();
        lines.clear();
        triangles.clear();
        break;
    case 'w':
        // 랜덤하게 도형 하나 선택하여 위로 이동
        if (!squares.empty() || !lines.empty() || !triangles.empty()) {
            int totalShapes = squares.size() + lines.size() + triangles.size();
            int randomIndex = rand() % totalShapes; // 랜덤 인덱스 생성

            if (randomIndex < squares.size()) {
                // 사각형을 선택한 경우
                squares[randomIndex].y += 10; // 사각형을 위로 10만큼 이동
            }
            else if (randomIndex < squares.size() + lines.size()) {
                // 선을 선택한 경우
                int lineIndex = randomIndex - squares.size();
                lines[lineIndex].y1 += 10; // 선의 시작점 위로 10만큼 이동
                lines[lineIndex].y2 += 10; // 선의 끝점 위로 10만큼 이동
            }
            else {
                // 삼각형을 선택한 경우
                int triangleIndex = randomIndex - squares.size() - lines.size();
                triangles[triangleIndex].y1 += 10; // 삼각형의 첫 번째 점 위로 10만큼 이동
                triangles[triangleIndex].y2 += 10; // 삼각형의 두 번째 점 위로 10만큼 이동
                triangles[triangleIndex].y3 += 10; // 삼각형의 세 번째 점 위로 10만큼 이동
            }
        }
        break;
    case 'a':
        // 랜덤하게 도형 하나 선택하여 위로 이동
        if (!squares.empty() || !lines.empty() || !triangles.empty()) {
            int totalShapes = squares.size() + lines.size() + triangles.size();
            int randomIndex = rand() % totalShapes; // 랜덤 인덱스 생성

            if (randomIndex < squares.size()) {
                // 사각형을 선택한 경우
                squares[randomIndex].x -= 10; // 사각형을 위로 10만큼 이동
            }
            else if (randomIndex < squares.size() + lines.size()) {
                // 선을 선택한 경우
                int lineIndex = randomIndex - squares.size();
                lines[lineIndex].x1 -= 10; // 선의 시작점 위로 10만큼 이동
                lines[lineIndex].x2 -= 10; // 선의 끝점 위로 10만큼 이동
            }
            else {
                // 삼각형을 선택한 경우
                int triangleIndex = randomIndex - squares.size() - lines.size();
                triangles[triangleIndex].x1 -= 10; // 삼각형의 첫 번째 점 위로 10만큼 이동
                triangles[triangleIndex].x2 -= 10; // 삼각형의 두 번째 점 위로 10만큼 이동
                triangles[triangleIndex].x3 -= 10; // 삼각형의 세 번째 점 위로 10만큼 이동
            }
        }
        break;
    case 's':
        // 랜덤하게 도형 하나 선택하여 위로 이동
        if (!squares.empty() || !lines.empty() || !triangles.empty()) {
            int totalShapes = squares.size() + lines.size() + triangles.size();
            int randomIndex = rand() % totalShapes; // 랜덤 인덱스 생성

            if (randomIndex < squares.size()) {
                // 사각형을 선택한 경우
                squares[randomIndex].y -= 10; // 사각형을 위로 10만큼 이동
            }
            else if (randomIndex < squares.size() + lines.size()) {
                // 선을 선택한 경우
                int lineIndex = randomIndex - squares.size();
                lines[lineIndex].y1 -= 10; // 선의 시작점 위로 10만큼 이동
                lines[lineIndex].y2 -= 10; // 선의 끝점 위로 10만큼 이동
            }
            else {
                // 삼각형을 선택한 경우
                int triangleIndex = randomIndex - squares.size() - lines.size();
                triangles[triangleIndex].y1 -= 10; // 삼각형의 첫 번째 점 위로 10만큼 이동
                triangles[triangleIndex].y2 -= 10; // 삼각형의 두 번째 점 위로 10만큼 이동
                triangles[triangleIndex].y3 -= 10; // 삼각형의 세 번째 점 위로 10만큼 이동
            }
        }
        break;
    case 'd':
        // 랜덤하게 도형 하나 선택하여 위로 이동
        if (!squares.empty() || !lines.empty() || !triangles.empty()) {
            int totalShapes = squares.size() + lines.size() + triangles.size();
            int randomIndex = rand() % totalShapes; // 랜덤 인덱스 생성

            if (randomIndex < squares.size()) {
                // 사각형을 선택한 경우
                squares[randomIndex].x += 10; // 사각형을 위로 10만큼 이동
            }
            else if (randomIndex < squares.size() + lines.size()) {
                // 선을 선택한 경우
                int lineIndex = randomIndex - squares.size();
                lines[lineIndex].x1 += 10; // 선의 시작점 위로 10만큼 이동
                lines[lineIndex].x2 += 10; // 선의 끝점 위로 10만큼 이동
            }
            else {
                // 삼각형을 선택한 경우
                int triangleIndex = randomIndex - squares.size() - lines.size();
                triangles[triangleIndex].x1 += 10; // 삼각형의 첫 번째 점 위로 10만큼 이동
                triangles[triangleIndex].x2 += 10; // 삼각형의 두 번째 점 위로 10만큼 이동
                triangles[triangleIndex].x3 += 10; // 삼각형의 세 번째 점 위로 10만큼 이동
            }
        }
        break;
    case 'q':
        exit(0); // 'q' 키를 눌러 프로그램 종료
        break;
    }
    glutPostRedisplay();
}

void update(int value)
{
    glutTimerFunc(16, update, 0); // 16ms마다 update 호출 (약 60FPS)
}
