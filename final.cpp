#define _CRT_SECURE_NO_WARNINGS // ignore warnings
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <fstream>
#include <Windows.h>

// global parameters
// view-related parameters
int screenWidth = 600;
int screenHeight = 600;

float cameraAngleX = 0; // not used
float cameraAngleY = 0;	// not used
// texture-related parameters
unsigned int texVec[10]; // preset memory space for textures

// texture loading function
unsigned int loadGLTexture(const char* filename)
{
	unsigned int texture;	// assign memory space to store texture

	// texture information
	static GLint   imagewidth;
	static GLint   imageheight;
	static GLint   pixellength;
	static GLubyte* pixeldata;

	FILE* pfile = fopen(filename, "rb");
	if (pfile == 0) exit(0);

	fseek(pfile, 0x0012, SEEK_SET); // skip 16 bits from beginning for bmp files
	// get the width of image
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	// get the height of image
	fread(&imageheight, sizeof(imageheight), 1, pfile);
	// count the length of in the image by pixel
	// pixel data consists of three colors red, green and blue (Windows implement BGR)
	pixellength = imagewidth * 3;
	// pixel data width should be an integral multiple of 4, which is required by the .bmp file
	while (pixellength % 4 != 0)
		pixellength++;
	// pixel data length = width * height
	pixellength *= imageheight;
	
	// malloc for the image by pixel
	pixeldata = (GLubyte*)malloc(pixellength); // memory allocation
	if (pixeldata == 0)
		exit(0);
	
	// read the data of image as pixel
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);
	// close file
	fclose(pfile);

	// GL texture settings
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth, imageheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);

	return texture;
}

// drawing functions
void drawGround() {
	glPushMatrix();
	glColor3f(1, 1, 1);
	// load ground texture (stored in texVec[0]) and map it to ground component
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texVec[0]);
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0f);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2d(0.0, 0.0); glVertex3f(-50, -0, 50);
		glTexCoord2d(1.0, 0.0); glVertex3f(+50, -0, 50);
		glTexCoord2d(1.0, 1.0); glVertex3f(+50, +0.0, -50);
		glTexCoord2d(0.0, 1.0); glVertex3f(-50, +0.0, -50);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Cube(float scale) {
	glPushMatrix();
	glScaled(scale, scale, scale);

	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2d(0.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2d(1.0, 0.0); glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2d(1.0, 1.0); glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2d(0.0, 1.0); glVertex3f(-0.5f, 0.5f, 0.5f);

		glNormal3f(0, 0, -1);
		glTexCoord2d(0.0, 0.0); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2d(1.0, 0.0); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2d(1.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2d(0.0, 1.0); glVertex3f(0.5f, 0.5f, -0.5f);


		glNormal3f(-1, 0, 0);
		glTexCoord2d(0.0, 0.0); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2d(1.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2d(1.0, 1.0); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2d(0.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);

		glNormal3f(1, 0, 0);
		glTexCoord2d(0.0, 0.0); glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2d(1.0, 0.0); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2d(1.0, 1.0); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2d(0.0, 1.0); glVertex3f(0.5f, 0.5f, 0.5f);


		glNormal3f(0, 1, 0);
		glTexCoord2d(0.0, 0.0); glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2d(1.0, 0.0); glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2d(1.0, 1.0); glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2d(0.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);

		glNormal3f(0, -1, 0);
		glTexCoord2d(0.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2d(1.0, 0.0); glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2d(1.0, 1.0); glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2d(0.0, 1.0); glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();
	glPopMatrix();

}

void drawBrick() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texVec[1]);

	glPushMatrix();
	glTranslated(0, 2, 0);
	glScaled(25, 4, 10);
	Cube(1.f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 18, 0);
	glScaled(25, 4, 10);
	Cube(1.f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-10.5, 10, 0);
	glScaled(4, 20, 10);
	Cube(1.f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(10.5, 10, 0);
	glScaled(4, 20, 10);
	Cube(1.f);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawWall() {
	glPushMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(50, 0, -37.5);
	glRotated(90, 0, 1, 0);
	drawBrick();
	glPopMatrix();

	glPushMatrix();
	glTranslated(50, 0, -12.5);
	glRotated(90, 0, 1, 0);
	drawBrick();
	glPopMatrix();

	glPushMatrix();
	glTranslated(50, 0, 12.5);
	glRotated(90, 0, 1, 0);
	drawBrick();
	glPopMatrix();

	glPushMatrix();
	glTranslated(50, 0, 37.5);
	glRotated(90, 0, 1, 0);
	drawBrick();
	glPopMatrix();

	glPopMatrix();
}

void drawTable() {
	glPushMatrix();

	glColor3ub(82, 58, 45);
	glTranslated(0, 0, 20);

	// draw table legs
	glPushMatrix();
	glTranslatef(0, 30, 0);
	glPushMatrix();
	glTranslatef(4, 0, 0);
	glRotatef(30, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glutSolidCylinder(2, 34, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glRotatef(120, 0, 1, 0);
	glTranslatef(4, 0, 0);
	glRotatef(30, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glutSolidCylinder(2, 34, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glRotatef(240, 0, 1, 0);
	glTranslatef(4, 0, 0);
	glRotatef(30, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	glutSolidCylinder(2, 34, 32, 32);
	glPopMatrix();
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(0, 35, 0);
	glRotatef(90, 1, 0, 0);
	//glutSolidCylinder(18, 10, 32, 32);

	// draw table top
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texVec[2]);
	GLUquadric* obj = gluNewQuadric();
	gluQuadricNormals(obj, GL_SMOOTH);
	gluQuadricTexture(obj, GL_TRUE);
	gluCylinder(obj, 18, 18, 5, 32, 32);

	gluDisk(obj, 0, 18, 32, 32);

	glTranslated(0, 0, 10);
	glPushMatrix();
	glRotated(180, 1, 0, 0);
	//gluDisk(obj, 0, 18, 32, 32);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPopMatrix();
}

void drawTellurian() { // globe
	glPushMatrix();

	glTranslated(0, 34, 20);

	glColor3ub(0, 30, 65);
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScaled(20, 1, 20);
	glutSolidCube(1.f);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 10, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(0.5, 9, 32, 32);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(0, 18, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texVec[3]);
	GLUquadric* obj = gluNewQuadric();
	gluQuadricNormals(obj, GL_SMOOTH);
	gluQuadricTexture(obj, GL_TRUE);
	gluSphere(obj, 8, 32, 32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPopMatrix();
}

void drawTelescope() {
	glPushMatrix();

	glTranslated(-10, 0, -20);

	glPushMatrix();
	glTranslatef(0, 3, 0);
	glRotated(90, 1, 0, 0);
	glColor3ub(35, 35, 35);
	glutSolidCylinder(10, 3, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 53, 0);
	glRotated(90, 1, 0, 0);
	glColor3ub(50, 50, 50);
	glutSolidCylinder(1, 50, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 55, 0);
	glRotatef(15, 0, 0, 1);
	glPushMatrix();
	GLUquadric* obj = gluNewQuadric();
	gluQuadricNormals(obj, GL_SMOOTH);
	glTranslated(0, 0, 0);
	glRotated(90, 0, 1, 0);
	glTranslated(0, 0, -1);
	glColor3ub(20, 20, 20);
	gluCylinder(obj, 2, 2, 3, 32, 32);
	glPopMatrix();

	glColor3ub(60, 60, 70);

	glPushMatrix();
	glTranslated(-11, 0, 0);
	glRotated(90, 0, 1, 0);
	glTranslated(0, 0, -10);
	gluCylinder(obj, 6, 2, 20, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslated(25.2, 0, 0);
	glRotated(90, 0, 1, 0);
	glTranslated(0, 0, -25);
	gluCylinder(obj, 2, 12, 50, 32, 32);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}

void drawMoon() {
	glPushMatrix();
	glTranslated(110, 100, 30);
	glColor3f(1, 1, 0.75);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texVec[4]);
	GLUquadric* obj = gluNewQuadric();
	gluQuadricNormals(obj, GL_SMOOTH);
	gluQuadricTexture(obj, GL_TRUE);
	gluSphere(obj, 10, 32, 32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void display() {
	glShadeModel(GL_SMOOTH);
	// 4-byte pixel alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	// background color
	glClearColor(0, 0, 0, 1.f);
	// clear stencil buffer
	glClearStencil(0);	
	glClearDepth(1.0f); // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);

	GLfloat lightKa[] = { .2f, .2f, .2f, 1.0f };  // ambient light
	GLfloat lightKd[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // diffuse light
	GLfloat lightKs[] = { 1.0f, 1.0f, 1.0f, 1 };           // specular light
	GLfloat lightPos[4] = { 110, 100, 0, 1 }; // directional light
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// set material
	float ambient[] = { 0.2, 0.2, 0.2, 1 };
	float diffuse[] = { 1.0, 1.0, 1.0, 1 };
	float specular[] = { 1.0f, 1.0f, 1.0f, 1 };
	float shininess = 32;
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_COLOR_MATERIAL);

	texVec[0] = loadGLTexture("ground.bmp");
	texVec[1] = loadGLTexture("wall.bmp");
	texVec[2] = loadGLTexture("table.bmp");
	texVec[3] = loadGLTexture("map.bmp");
	texVec[4] = loadGLTexture("moon.bmp");
	texVec[5] = loadGLTexture("background.bmp");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// background texture
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texVec[5]);
	glColor3f(1.0, 1.0, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
		glTexCoord2d(1.0, 0.0); glVertex2d(+1.0, -1.0);
		glTexCoord2d(1.0, 1.0); glVertex2d(+1.0, +1.0);
		glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, +1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)(screenWidth) / screenHeight, 0.1, 500.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 50, 135, 0, 30, 0, 0, 1, 0);

	glPushMatrix();
	// tramsform camera
	glRotatef(60, 0, 1, 0);

	drawMoon();
	drawGround();
	drawTelescope();
	drawTable();
	drawTellurian();
	drawWall();
	glPopMatrix();
	glutSwapBuffers();
}

// press ESC to quit
void keyboardCB(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:;
	}
}

// window reshape function
void reshapeCB(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	// set viewport to be the entire window
	glViewport(0, 0, (GLsizei)screenWidth, (GLsizei)screenHeight);

	// set perspective viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -150, 150);

	// switch to modelview matrix in order to set scene
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Work");

	glutDisplayFunc(&display);
	glutReshapeFunc(reshapeCB);
	glutKeyboardFunc(keyboardCB);
	glutMainLoop();

	return 0;
}