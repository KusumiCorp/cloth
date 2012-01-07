/*******************************************************************
**
**	粒子データのアニメーション
**
**　作成開始日：2011/10/30
**	作成者：久住
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

//global変数宣言
/*----------------------------
 グローバル変数の設定
----------------------------*/
int winX		= 512;
int winY		= 512;
const char* winId	= "Particle Animation";
char* iFolderName	= "../CLOTH/result";
char* iExtensName = ".obj";
/*----------------------------
 ライトの設定
----------------------------*/
//緑
GLfloat green[] = { 0.0, 1.0, 1.0, 1.0 };
//青
GLfloat blue[] = { 0.0, 1.0, 1.0, 1.0 };
////赤
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
//黄色
GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
//黒
GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
//白
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0pos[] = { 0.0, 30.0, -30.0, 1.0 };
/*----------------------------
　パラメータ
----------------------------*/
int number = 0;
int numberMin = 0;
int numberMax = 50;
int dn = 1;
/*----------------------------
 インスタンスの生成
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
	//---ファイル名を作成
	char fname[100];
	char fnum[9];
	sprintf(fnum, "%08d", number);
	strcpy(fname, iFolderName);
	strcat(fname, fnum);
	strcat(fname, iExtensName);

	Vector3D *v;
	int pSize;
	
	//---ファイルの粒子データをコピー
	ObjLoader obj(fname);
	pSize = obj.getVertexSize();
	v = new Vector3D[pSize];
	obj.cpyData(v);
	int drawScale = 1;
	//---描画
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
// キーボード入力
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
// マウス操作
static void mouse_func ( int button, int state, int x, int y )
{
	cam.Mouse(button,state,x,y);
}
static void motion_func ( int x, int y )
{
	cam.Motion(x, y);
}
// ウィンドウ拡大縮小
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
// idle関数
static void idle_func ( void )
{
	//再描画
	glutPostRedisplay ();
}
// 描画関数
static void display_func ( void )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ライトの設定
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

	//描画
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
// main関数
int main ( int argc, char ** argv )
{
	glutInit ( &argc, argv );

	open_glut_window ();

	Init();

	glutMainLoop ();

	exit ( 0 );
}