/*******************************************************************
**
**	���q�f�[�^�̃A�j���[�V����
**
**�@�쐬�J�n���F2011/10/30
**	�쐬�ҁF�v�Z
**
**
*******************************************************************/

#include <iostream>
#include <GL/glut.h>
#include <fstream>
#include <Windows.h>
#include "MouseCamera.h"
#include "ObjLoader.h"

using namespace std;

//global�ϐ��錾
/*----------------------------
 �O���[�o���ϐ��̐ݒ�
----------------------------*/
int winX		= 512;
int winY		= 512;
const char* winId	= "Particle Animation";
char* iFolderName	= "../CLOTH/result";
char* iExtensName = ".obj";
/*----------------------------
 ���C�g�̐ݒ�
----------------------------*/
//��
GLfloat green[] = { 0.0, 1.0, 1.0, 1.0 };
//��
GLfloat blue[] = { 0.0, 1.0, 1.0, 1.0 };
////��
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
//���F
GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
//��
GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
//��
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0pos[] = { 0.0, 30.0, -30.0, 1.0 };
/*----------------------------
�@�p�����[�^
----------------------------*/
int number = 0;
int numberMin = 0;
int numberMax = 50;
int dn = 1;
/*----------------------------
 �C���X�^���X�̐���
----------------------------*/
MouseCamera cam;

void Initialize(){
}
void Init(){

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	Initialize();
}
void Cube(int number, GLfloat *color){
	//---�t�@�C�������쐬
	char fname[100];
	char fnum[9];
	sprintf(fnum, "%08d", number);
	strcpy(fname, iFolderName);
	strcat(fname, fnum);
	strcat(fname, iExtensName);

	Vector3D *v;
	int pSize;
	
	//---�t�@�C���̗��q�f�[�^���R�s�[
	ObjLoader obj(fname);
	pSize = obj.getVertexSize();
	v = new Vector3D[pSize];
	obj.cpyData(v);
	int drawScale = 1;
	//---�`��
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
	for(int i = 0;i < pSize;i++){
			glPushMatrix();
			glTranslated(v[i].x*drawScale, v[i].y*drawScale, v[i].z*drawScale);
			glutSolidSphere(0.6 *drawScale, 20, 4);
			glPopMatrix();
	}
}
/*
  ----------------------------------------------------------------------
   OpenGL specific drawing routines
  ----------------------------------------------------------------------
*/
// �L�[�{�[�h����
static void key_func ( unsigned char key, int x, int y )
{
	switch ( key )
	{
		case 'c':
		case 'C':
			break;

		case 'q':
		case 'Q':
			exit ( 0 );
			break;

		case 'v':
		case 'V':
			break;
	}
}
// �}�E�X����
static void mouse_func ( int button, int state, int x, int y )
{
	cam.Mouse(button,state,x,y);
}
static void motion_func ( int x, int y )
{
	cam.Motion(x, y);
}
// �E�B���h�E�g��k��
static void reshape_func ( int width, int height )
{
	winX = width;
	winY = height;	
	
	glViewport ( 0, 0, winX, winY );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	gluPerspective(30.0, (double)winX/(double)winY, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	cam.Resize(width, height);
}
// idle�֐�
static void idle_func ( void )
{
	//�ĕ`��
	glutPostRedisplay ();
}
// �`��֐�
static void display_func ( void )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���C�g�̐ݒ�
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

	//�`��
	Cube(number, blue);
	number+=dn;
	if(number >= numberMax){
		Sleep(1000);
		number = numberMin;
	}

	glutSwapBuffers ();
}
// open_glut_window --- open a glut compatible window and set callbacks
static void open_glut_window ( void )
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition ( 0, 0 );
	glutInitWindowSize ( winX, winY );
	
	glutCreateWindow( winId );

	glutKeyboardFunc ( key_func );
	glutMouseFunc ( mouse_func );
	glutMotionFunc ( motion_func );
	glutReshapeFunc ( reshape_func );
	glutIdleFunc ( idle_func );
	glutDisplayFunc ( display_func );
}
// main�֐�
int main ( int argc, char ** argv )
{
	glutInit ( &argc, argv );

	open_glut_window ();

	Init();

	glutMainLoop ();

	exit ( 0 );
}