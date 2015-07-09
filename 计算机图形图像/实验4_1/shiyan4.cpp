#define GLUT_DISABLE_ATEXIT_HACK 
#include<gl\GLUT.H>
int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (250, 250);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("hello");
	glutMainLoop();
	return 0;
}