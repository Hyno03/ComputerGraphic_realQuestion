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
//	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
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
//		glutTimerFunc(1000, Timer, 0); // 1�ʸ��� Ÿ�̸� ����
//	}
//}
//
//GLvoid Keyboard(unsigned char key, int x, int y)
//{
//	std::cout << "Key pressed: " << key << std::endl; // ������ ���
//
//	// 't'�� �ƴ� Ű�� ������ Ÿ�̸Ӹ� ������Ŵ
//	if (key != 't') {
//		stopTimerIfActive(); // Ÿ�̸� ��Ȱ��ȭ
//	}
//
//	switch (key)
//	{
//	case 'c': // û�ϻ�
//		std::cout << "Changing to cyan\n";
//		bgColor[0] = 0.0f; bgColor[1] = 1.0f; bgColor[2] = 1.0f; bgColor[3] = 1.0f;
//		break;
//	case 'm': // ��ȫ��
//		std::cout << "Changing to magenta\n";
//		bgColor[0] = 1.0f; bgColor[1] = 0.0f; bgColor[2] = 1.0f; bgColor[3] = 1.0f;
//		break;
//	case 'y': // �����
//		std::cout << "Changing to yellow\n";
//		bgColor[0] = 1.0f; bgColor[1] = 1.0f; bgColor[2] = 0.0f; bgColor[3] = 1.0f;
//		break;
//	case 'a': // ���� ����
//		std::cout << "Changing to random color\n";
//		setRandomColor();
//		break;
//	case 'w': // ���
//		std::cout << "Changing to white\n";
//		bgColor[0] = 1.0f; bgColor[1] = 1.0f; bgColor[2] = 1.0f; bgColor[3] = 1.0f;
//		break;
//	case 'k': // ������
//		std::cout << "Changing to black\n";
//		bgColor[0] = 0.0f; bgColor[1] = 0.0f; bgColor[2] = 0.0f; bgColor[3] = 1.0f;
//		break;
//	case 't': // Ÿ�̸� ����
//		std::cout << "Starting timer\n";
//		timerEnabled = true;
//		glutTimerFunc(1000, Timer, 0); // 1�ʸ��� �� ����
//		break;
//	case 's': // Ÿ�̸� ����
//		std::cout << "Stopping timer\n";
//		timerEnabled = false;
//		break;
//	case 'q': // ���α׷� ����
//		std::cout << "Exiting program\n";
//		exit(0);
//		break;
//	}
//
//	glutPostRedisplay();
//}
