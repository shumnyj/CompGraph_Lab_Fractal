// Lab work for computer graphics
// Fractal rendering
// By Troian Borys KV-62

#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <cmath>
#include <chrono>
#include <stdio.h>
#include <iostream>

const int XWin = 640;
const int YWin = 640;
double cos60 ,sin60;
double color[3] = { 1,0,1 };

void Mandelbrot(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	GLdouble Xk, Yk, Xnext, Ynext, dx,dy, Xi, Yi, cx, cy, m;
	int i,j;
	/*double color[3];
	color[0] = 1;
	color[1] = 0;
	color[2] = 1;*/
	cx = (x2 + x1) / 2;
	cy = (y2 + y1) / 2;

	Xi = x1; Yi = y1;
	dx = abs(x2 - x1) / 500;
	dy = abs(y2 - y1) / 500;
	if (dy > dx)
		m = dy * 1.0;
	else
		m = dx * 1.0;
	while (Yi < y2)
	{
		Xi = x1;
		glBegin(GL_POINTS);
		while (Xi < x2)
		{
			Xk = 0;
			Yk = 0;
			i = 0;
			
			while (Xk*Xk + Yk * Yk < 4 && i < 400)
			{
				Xnext = Xk*Xk - Yk*Yk + Xi;
				Ynext = Xk*Yk*2 + Yi;
				Xk = Xnext;
				Yk = Ynext;
				i++;
			}
			glColor3f(1 - 0.003*i, 1 - 0.008*i, 1 - 0.003*i);
			//glColor3f(0,0,0);
			glVertex2i((Xi-cx)/m, (Yi-cy)/m);
			
			Xi += dx;
		}
		glEnd();
		glFlush();
		Yi += dy;
	}
	
	getchar();
}

void Serpinsky(GLint Ax, GLint Ay, GLint Bx, GLint By, GLint Cx, GLint Cy, GLint iter)
{
	if (iter > 0)
	{
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2i(Ax, Ay);
		glVertex2i(Bx, By);
		glVertex2i(Cx, Cy);
		glEnd();
		glFlush();

		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		glVertex2i((Ax + Bx) / 2, (Ay + By) / 2);
		glVertex2i((Bx + Cx) / 2, (By + Cy) / 2);
		glVertex2i((Ax + Cx) / 2, (Ay + Cy) / 2);
		glEnd();
		glFlush();
		//getchar();
		Serpinsky(Ax, Ay, (Ax + Bx) / 2, (Ay + By) / 2, (Ax + Cx) / 2, (Ay + Cy) / 2, iter - 1);
		Serpinsky((Ax + Bx) / 2, (Ay + By) / 2, Bx, By, (Bx + Cx) / 2, (By + Cy) / 2, iter - 1);
		Serpinsky((Ax + Cx) / 2, (Ay + Cy) / 2, (Bx + Cx) / 2, (By + Cy) / 2, Cx, Cy, iter - 1);
	}
}

void KochRec(GLdouble Ax, GLdouble Ay, GLdouble Ex, GLdouble Ey, GLdouble iter)
{
	GLdouble Cx, Cy;
	GLdouble Dx, Dy;
	GLdouble Bx, By;

	if (iter > 0)
	{
		Bx = ((Ex - Ax) / 3) + Ax;
		By = ((Ey - Ay) / 3) + Ay;
		Dx = ((Ex - Ax) * 2 / 3) + Ax;
		Dy = ((Ey - Ay) * 2 / 3) + Ay;
		//Bx += Ax;
		//By += Ay;
		Cx = Bx + (Dx - Bx)*cos60 - (Dy - By)*sin60;
		Cy = By  + (Dx - Bx)*sin60 + (Dy - By)*cos60;

		glColor3f(1, 1, 1);
		glLineWidth(4);
		glBegin(GL_LINES);
		glVertex2i(Bx, By);
		glVertex2i(Dx, Dy);
		glEnd();
		glFlush();

		glColor3f(color[0], color[1], color[2]);
		glLineWidth(1);
		glBegin(GL_LINE_STRIP);
		glVertex2i(Bx, By);
		glVertex2i(Cx, Cy);
		glVertex2i(Dx, Dy);
		glEnd();

		glFlush();

		//getchar();
		KochRec(Ax, Ay, Bx, By, iter - 1);
		KochRec(Bx, By, Cx, Cy, iter - 1);
		KochRec(Cx, Cy, Dx, Dy, iter - 1);
		KochRec(Dx, Dy, Ex, Ey, iter - 1);
	}
}
void Koch(GLint Ax, GLint Ay, GLint Ex, GLint Ey, GLint iter)
{

	glColor3f(color[0], color[1], color[2]);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2i(Ax, Ay);
	glVertex2i(Ex, Ey);
	glEnd();
	glFlush();

	KochRec(Ax, Ay, Ex, Ey, iter);
}
/*void Tree(GLint Ax, GLint Ay, GLint Bx, GLint By, GLint iter)
{
	GLint Mx, My, Lx, Ly, Rx, Ry;
	if (iter > 0)
	{
		glColor3f(color[0], color[1], color[2]);
		glLineWidth(1);
		glBegin(GL_LINES);
		Mx = (Ax + Bx) / 2;
		My = (Ay + By) / 2;
		glVertex2i(Ax, Ay);
		glVertex2i(Mx, My);
		glEnd();
		glFlush();

		Lx = Mx + (Bx - Mx)*cos60 - (By - My)*sin60;
		Ly = My + (By - My)*sin60 + (Bx - Mx)*cos60;
		Rx = Mx + (Bx - Mx)*cos(M_PI * 7 / 3) - (By - My)*sin(M_PI * 7 / 3);
		Ry = My + (By - My)*sin(M_PI * 7 / 3) + (Bx - Mx)*cos(M_PI * 7 / 3);

		Tree(Mx, My, Lx, Ly, iter - 1);
		Tree(Mx, My, Rx, Ry, iter - 1);
	}
}*/
void Tree(GLint Ax, GLint Ay, GLint h, GLdouble ang, GLint iter)
{
	GLint Bx, By;
	if (iter > 0)
	{
		
		Bx = Ax + h/2  * cos(ang);
		By = Ay + h/2   * sin(ang);

		glColor3f(color[0], color[1], color[2]);
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2i(Ax, Ay);
		glVertex2i(Bx, By);
		glEnd();
		glFlush();

		Tree(Bx, By, h / 2, ang + M_PI_4, iter - 1);
		Tree(Bx, By, h / 2, ang - M_PI_4, iter - 1);
	}
	return;
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);		// clears the frame buffer and set values defined in glClearColor() function call
	Mandelbrot(-0.777815 , 0.131647, -0.777805, 0.131653);
	//Mandelbrot(-1.6,  -1, 0.8, 1);
	//Koch(-300, 0, 300, 0, 4);
	//Serpinsky(0, 347-100, 200, -100, -200, -100, 5);
	//Tree(0, -200, 400, M_PI_2,  4);
};

int main(int argc, char** argv)
{
	cos60 = 0.5;
	sin60 = sin(M_PI/3);

	glutInit(&argc, argv);
	glutInitWindowSize(XWin, YWin);
	glutInitWindowPosition(800, 50);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//creates a single frame buffer of RGB color capacity.	
	glutCreateWindow("Fractal");				//creates the window as specified by the user as above.

	glutDisplayFunc(display);						//links the display event with the display event handler(display)

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-XWin/2, XWin/2, -YWin/2, YWin/2);

	glutMainLoop();									//loops the current event
	getchar();
}

