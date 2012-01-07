#ifndef _JT_MOUSE_CAMERA_H_
#define _JT_MOUSE_CAMERA_H_

/*
説明：
	マウスによって、カメラを回転、ズームする。
	クォータニオンを用いているため、ジンバルロックが生じないという利点がある。
	クォータニオンを用いるために、GLUTのサンプル「trackball.h」および「trackball.c」を用いた。

使用方法：
	メインプログラムからインクルードし、
	GLUTのResize, Mouse, Motion関数に
	それぞれ
	Resize(int w, int h), Mouse(int button, int state, int x, int y), Motion(int x, int y)
	を記述する。
	左ドラッグで回転、右ドラッグでズーム。

Author: Junichi Tatsumi
*/
#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

//
//　link
//
#pragma comment(lib, "glew32.lib")

const double PI = 3.141592653589793238;

class MouseCamera
{
protected:
	int _MousePos_x, _MousePos_y;
	double _CamPos[3];
	double _CamR;//視点の回転半径
	double _CamUp[3];//カメラの上方向ベクトル
	int _WindowWidth,_WindowHight;
	int _Button;
	double _LookAt[3];//注視点
	float _m[4][4];//回転行列用

public:
	MouseCamera();
	~MouseCamera();

	void Resize(int width, int height);
	void Motion(int x, int y);
	void Mouse(int button, int state, int x, int y);

	double GetCamPos_X() {return _CamPos[0];}//正確性不明
	double GetCamPos_Y() {return _CamPos[1];}//正確性不明
	double GetCamPos_Z() {return _CamPos[2];}//正確性不明
	const double GetCamUp(int xyz) {return _CamUp[xyz];}
	double GetR() {return _CamR;}
	float GetRotMatrix(int i, int j) {return _m[i][j];}
	void SetLookAt(double x, double y, double z) {_LookAt[0]=x;_LookAt[1]=y;_LookAt[2]=z;}
	void CameraView();
	
};


//-----------以下、glutの「trackball.h」のコピー　------------------//


/*
 * (c) Copyright 1993, 1994, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 */
/*
 * trackball.h
 * A virtual trackball implementation
 * Written by Gavin Bell for Silicon Graphics, November 1988.
 */

/*
 * Pass the x and y coordinates of the last and current positions of
 * the mouse, scaled so they are from (-1.0 ... 1.0).
 *
 * The resulting rotation is returned as a quaternion rotation in the
 * first paramater.
 */
void
trackball(float q[4], float p1x, float p1y, float p2x, float p2y);

/*
 * Given two quaternions, add them together to get a third quaternion.
 * Adding quaternions to get a compound rotation is analagous to adding
 * translations to get a compound translation.  When incrementally
 * adding rotations, the first argument here should be the new
 * rotation, the second and third the total rotation (which will be
 * over-written with the resulting new total rotation).
 */
void
add_quats(float *q1, float *q2, float *dest);

/*
 * A useful function, builds a rotation matrix in Matrix based on
 * given quaternion.
 */
void
build_rotmatrix(float m[4][4], float q[4]);

/*
 * This function computes a quaternion based on an axis (defined by
 * the given vector) and an angle about which to rotate.  The angle is
 * expressed in radians.  The result is put into the third argument.
 */
void
axis_to_quat(float a[3], float phi, float q[4]);



#endif