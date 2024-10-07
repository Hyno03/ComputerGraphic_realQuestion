//#include <iostream>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//#include <cstdlib>
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid Keyboard(unsigned char key, int x, int y);
//GLvoid Timer(int value);
//
//bool timerEnabled = false;
//float bgColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
//
//void setRandomColor() {
//	bgColor[0] = static_cast<float>(rand()) / RAND_MAX;
//	bgColor[1] = static_cast<float>(rand()) / RAND_MAX;
//	bgColor[2] = static_cast<float>(rand()) / RAND_MAX;
//}
//
//void stopTimerIfActive() {
//	if (timerEnabled) {
//		std::cout << "Stopping timer due to other key press\n";
//		timerEnabled = false;
//	}
//}
//
//void main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(0, 0);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("Example1");
//
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK)
//	{
//		std::cerr << "Unable to initialize GLEW" << std::endl;
//		exit(EXIT_FAILURE);
//	}
//	else
//		std::cout << "GLEW Initialized\n";
//
//	glutDisplayFunc(drawScene);
//	glutReshapeFunc(Reshape);
//	glutKeyboardFunc(Keyboard);
//	glutMainLoop();
//}
//
//GLvoid drawScene()
//{
//	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glutSwapBuffers(); // 화면에 출력하기
//}
//
//GLvoid Reshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//}
//
//GLvoid Timer(int value)
//{
//	if (timerEnabled) {
//		setRandomColor();
//		glutPostRedisplay();
//		glutTimerFunc(1000, Timer, 0); // 1초마다 타이머 실행
//	}
//}
//
//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//	std::cout << "Key pressed: " << key << std::endl; // 디버깅용 출력
//
//	// 't'가 아닌 키가 눌리면 타이머를 중지시킴
//	if (key != 't') {
//		stopTimerIfActive(); // 타이머 비활성화
//	}
//
//	switch (key)
//	{
//	case 'c': // 청록색
//		std::cout << "Changing to cyan\n";
//		bgColor[0] = 0.0f; bgColor[1] = 1.0f; bgColor[2] = 1.0f; bgColor[3] = 1.0f;
//		break;
//	case 'm': // 자홍색
//		std::cout << "Changing to magenta\n";
//		bgColor[0] = 1.0f; bgColor[1] = 0.0f; bgColor[2] = 1.0f; bgColor[3] = 1.0f;
//		break;
//	case 'y': // 노란색
//		std::cout << "Changing to yellow\n";
//		bgColor[0] = 1.0f; bgColor[1] = 1.0f; bgColor[2] = 0.0f; bgColor[3] = 1.0f;
//		break;
//	case 'a': // 랜덤 색상
//		std::cout << "Changing to random color\n";
//		setRandomColor();
//		break;
//	case 'w': // 백색
//		std::cout << "Changing to white\n";
//		bgColor[0] = 1.0f; bgColor[1] = 1.0f; bgColor[2] = 1.0f; bgColor[3] = 1.0f;
//		break;
//	case 'k': // 검정색
//		std::cout << "Changing to black\n";
//		bgColor[0] = 0.0f; bgColor[1] = 0.0f; bgColor[2] = 0.0f; bgColor[3] = 1.0f;
//		break;
//	case 't': // 타이머 시작
//		std::cout << "Starting timer\n";
//		timerEnabled = true;
//		glutTimerFunc(1000, Timer, 0); // 1초마다 색 변경
//		break;
//	case 's': // 타이머 종료
//		std::cout << "Stopping timer\n";
//		timerEnabled = false;
//		break;
//	case 'q': // 프로그램 종료
//		std::cout << "Exiting program\n";
//		exit(0);
//		break;
//	}
//
//	glutPostRedisplay();
//}
