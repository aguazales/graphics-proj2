/*
 * proj2.cpp
 *
 *      Author: Jacob Payne
 *      Author: Shannon Jones
 *
 *  CIS 367 Project 2: Shading and Animation
 *  Winter 2013
 *
 *  Keyboard Controls:
 *  WASD                  = rotate the object around the x (WS) and y axes (AD)
 *  Up/Down/Left/Right    = translate the object
 *  p                     = pause/unpause the object animation
 *  esc                   = exit the program
 *  0                     = enable/disable the ambient white light source
 *  1                     = enable/disable the directional green light source
 */

 
#include	<stdlib.h>
#include	<C:\MinGW\include\GL\freeglut.h>
#include	<math.h>

/* =============== Variables ================== */
// cones that form the spikes coming out of our wheel with pewter shading
GLuint cone = 0;
	GLdouble cone_base = 1.00; // cone radius
	GLdouble cone_height = 8.00; // cone height
	GLuint cone_slices = 20; // the number of subdivisions *around* the z axis
	GLuint cone_stacks = 20; // the number of subdivisions *along* the z axis
	GLfloat cone_ambient[] = {0.105882, 0.058824, 0.113725, 1.0}; // ambient reflection
	GLfloat cone_diffuse[] = {0.427451, 0.470588, 0.541176, 1.0}; // diffuse reflection
	GLfloat cone_specular[] = {0.333333, 0.333333, 0.521569, 1.0}; // specular reflection
	GLfloat cone_shine = 9.846150;

// cones that form the spike coming around which the wheel orbits
GLuint spike = 0;
	GLdouble spike_base = 3.00; // cone radius
	GLdouble spike_height = 10.00; // cone height
	GLuint spike_slices = 20; // the number of subdivisions *around* the z axis
	GLuint spike_stacks = 20; // the number of subdivisions *along* the z axis
	GLfloat spike_ambient[] = {0.105882, 0.058824, 0.113725, 1.0}; // ambient reflection
	GLfloat spike_diffuse[] = {0.427451, 0.470588, 0.541176, 1.0}; // diffuse reflection
	GLfloat spike_specular[] = {0.333333, 0.333333, 0.521569, 1.0}; // specular reflection
	GLfloat spike_shine = 9.846150;

GLuint end_cap = 0;
	GLdouble end_cap_base = 4; // cone radius
	GLdouble end_cap_radius = 4; // cone radius
	GLdouble end_cap_height = 0.1; // cone height
	GLuint end_cap_slices = 20; // the number of subdivisions *around* the z axis
	GLuint end_cap_stacks = 20; // the number of subdivisions *along* the z axis
	GLfloat end_cap_ambient[] = {0.105882, 0.058824, 0.113725, 1.0}; // ambient reflection
	GLfloat end_cap_diffuse[] = {0.427451, 0.470588, 0.541176, 1.0}; // diffuse reflection
	GLfloat end_cap_specular[] = {0.333333, 0.333333, 0.521569, 1.0}; // specular reflection
	GLfloat end_cap_shine = 9.846150;

// cylinder (wheel body) with obsidian shading values
GLuint main_cylinder = 0;
	GLfloat cylinder_ambient[] = {0.05375, 0.05, 0.06625, 0.82}; // ambient reflection
	GLfloat cylinder_diffuse[] = {0.18275, 0.17, 0.22525, 0.82}; // diffuse reflection
	GLfloat cylinder_specular[] = {0.332741, 0.328634, 0.346435, 0.82}; // specular reflection
	GLfloat cylinder_shine = 38.400002;
GLUquadric* main_cylinder_quad = gluNewQuadric();
	GLdouble base = 4.00; // radius at z=0 (base of cylinder)
	GLdouble top = 4.00; // radius at z=height (top of cylinder)
	GLdouble height = 8.00; // cylinder height
	GLuint slices = 20; // the number of subdivisions *around* the z axis
	GLuint stacks = 20; // the number of subdivisions *along* the z axis

// wheel that contains the cylinder and spokes
GLuint wheel = 0;
GLuint xrot=0, yrot=0, zrot=0; // used to rotate the object with the keyboard
GLuint x_coord=25, y_coord=35;

// animation variables
GLuint frame_rate = 250;
bool pause = false;
GLuint anim_time = 0;

// light 1
GLfloat light0_pos[] = {25, 45, -46, 1}; // position
GLfloat light0_color[] = {1.0, 1.0, 1.0, 1.0}; // color
//light 2
GLfloat light1_pos[] = {0, -20, -46, 1}; // position
GLfloat light1_color[] = {0.5, 1.0, 0.06, 1.0}; // color
GLfloat light1_dir[] = {0, 1, 0}; // direction (spotlight)
/* ======================================= */



/* =======================================
 * Function called to animate display
 * ======================================= */
void animate(int value)
{
	// if the animation isn't paused
	if (!pause)
	{
		// rotate the wheel
		zrot++;

//		// move the wheel in an ellipse shape
//		GLuint radius = 5; // radius of circle
//		GLuint speed = 1;
//		GLfloat speedScale = (0.001*2*M_PI)/speed; //
//		GLfloat angle = time*speedScale;
//		x_coord = 25 + 1.5*((sin(angle)*radius))*4;
//		y_coord = 25 + ((cos(angle)*radius))*4;
		if (anim_time>359) anim_time=0;

		//for(j)
		float theta = anim_time * (M_PI/180.0f);

		x_coord = 5+2*(sin(theta)+1)*10;
		y_coord = 8+(cos(theta)+2)*10;

		anim_time++;
		// mark the window for refreshing
		glutPostRedisplay();
	}

	glutTimerFunc(10, animate, anim_time);
}



/* =======================================
 * Function called to update rendering
 * ======================================= */
void display(void)
{
	/* Clear the buffer, clear the matrix */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glLightfv (GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv (GL_LIGHT1, GL_POSITION, light1_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);

	gluLookAt(25, 25, 5, 25, 25, 0, 0, 1, 0);

	glPushMatrix();
		glTranslatef(25, 27, -50);
		//glRotatef(-90, 1, 0, 0);
		glCallList(spike);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(x_coord, y_coord, -50);
		glRotatef(xrot, 1, 0, 0);
		glRotatef(yrot, 0, 1, 0);
		glRotatef(zrot, 0, 0, 1);
		glScalef(0.5, 0.5, 0.5);
		glCallList(wheel);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
} // END display



/* =======================================
 * Called when the window is created or resized
 * ======================================= */
void resize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45, width / (float) height, 0.1, 100);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
} // END resize



/* =======================================
 * Initialize display lists for display function
 * ======================================= */
void init()
{
	main_cylinder = glGenLists(1);
	cone = glGenLists(1);
	wheel = glGenLists(1);
	end_cap = glGenLists(1);
	spike = glGenLists(1);

	// set options for main_cylinder quadric rendering
	gluQuadricOrientation(main_cylinder_quad, GLU_OUTSIDE);
	gluQuadricDrawStyle(main_cylinder_quad, GLU_FILL);
	gluQuadricNormals(main_cylinder_quad, GLU_SMOOTH);

	// display list for the spike around which the wheel orbits
	glNewList(spike, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cylinder_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cylinder_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cylinder_diffuse);
			glColor3ub(0, 127, 254);
			glutSolidCone(spike_base, spike_height, spike_slices, spike_stacks);
		glPopMatrix();
	glEndList();

	// display list for cylinder forming the main body of the wheel
	glNewList(main_cylinder, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cylinder_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cylinder_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cylinder_diffuse);
			glColor3ub(105, 35, 135);
			gluCylinder(main_cylinder_quad, base, top, height, slices, stacks);
		glPopMatrix();
	glEndList();

	// delete the memory used by the quadric
	gluDeleteQuadric(main_cylinder_quad);

	// display list for the cones comprising the spikes coming off the wheel
	glNewList(cone, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_SPECULAR, cylinder_specular);
			glMaterialfv(GL_FRONT, GL_AMBIENT, cylinder_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, cylinder_diffuse);
			glColor3ub(192, 192, 135);
			glutSolidCone(cone_base, cone_height, cone_slices, cone_stacks);
		glPopMatrix();
	glEndList();

	// display list for the cone making the endcap of the cylinder
	glNewList(end_cap, GL_COMPILE);
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cylinder_specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cylinder_ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cylinder_diffuse);
			glColor3ub(105, 35, 135);
			glutSolidCone(end_cap_base, end_cap_height, end_cap_slices, end_cap_stacks);
		glPopMatrix();
	glEndList();

	/* display list for the wheel
	(contains main_cylinder, cone, and end_cap display lists) */
	glNewList(wheel, GL_COMPILE);
		glPushMatrix();
			glCallList(main_cylinder);
			// front endcap
			glPushMatrix();
				glTranslatef(0, 0, 8);
				// flip the cone around to present the flat bottom outward
				glRotatef(180, 0, 1, 0);
				glCallList(end_cap);
			glPopMatrix(); // front endcap pop
			// rear endcap
			glPushMatrix();
				glCallList(end_cap);
			glPopMatrix(); // rear endcap pop
			// cone 1
			glPushMatrix();
				glTranslatef(0, -4, 4);
				glRotatef(90, 1, 0, 0);
				glCallList(cone);
			glPopMatrix(); // cone 1 pop
			// cone 2
			glPushMatrix();
				glTranslatef(-4, 0, 4);
				glRotatef(-90, 0, 1, 0);
				glCallList(cone);
			glPopMatrix(); // cone 2 pop
			// cone 3
			glPushMatrix();
				glTranslatef(4, 0, 4);
				glRotatef(90, 0, 1, 0);
				glCallList(cone);
			glPopMatrix(); // cone 3 pop
			// cone 4
			glPushMatrix();
				glTranslatef(0, 4, 4);
				glRotatef(-90, 1, 0, 0);
				glCallList(cone);
			glPopMatrix(); // cone 4 pop
		glPopMatrix(); // wheel pop
	glEndList(); // END wheel

} // END init



/* =======================================
 * Initialize OpenGL parameters
 * ======================================= */
void paramInit ()
{
    glClearColor (0.0, 0.0, 0.0, 1.0); /* black background */

    /* fill front-facing polygon */
    glPolygonMode (GL_FRONT, GL_FILL);
    /* draw outline of back-facing polygon */
    glPolygonMode (GL_BACK, GL_LINE);

    /* Enable depth test for hidden surface removal */
    glEnable (GL_DEPTH_TEST);

    /* enable back-face culling */
    glEnable (GL_CULL_FACE);
    glCullFace (GL_BACK);

    /* Enable shading */
    glEnable (GL_LIGHTING);
    glEnable (GL_NORMALIZE); /* Tell OpenGL to renormalize normal vector
                              after transformation */
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    /* initialize two light sources */
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT0, GL_AMBIENT, light0_color);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_color);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light0_color);
    glEnable (GL_LIGHT1);
    glLightfv (GL_LIGHT1, GL_AMBIENT, light1_color);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light1_color);
    glLightfv (GL_LIGHT1, GL_SPECULAR, light1_color);
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 40);
}



/* =======================================
 * Main function
 * ======================================= */
void fkeyCallback (int key, int x, int y)
{
        switch (key) {
            case GLUT_KEY_UP: /* move the object positively along the y-axis */
            	y_coord = y_coord+1;
            	glutPostRedisplay();
            	break;
            case GLUT_KEY_DOWN: /* move the object negatively along the y-axis */
            	y_coord = y_coord-1;
            	glutPostRedisplay();
            	break;
            case GLUT_KEY_LEFT: /* move the object positively along the x-axis */
            	x_coord = x_coord-1;
            	glutPostRedisplay();
                break;

            case GLUT_KEY_RIGHT: /* move the object negatively along the x-axis */
            	x_coord = x_coord+1;
            	glutPostRedisplay();
                break;

            default:
                break;
        }

}



void keyCallback (unsigned char key, int, int)
{
    switch (key)
    {
        case 0x1B:
            exit(0);
        case '0':
            if (glIsEnabled(GL_LIGHT0))
                glDisable(GL_LIGHT0);
            else
                glEnable(GL_LIGHT0);
            break;
        case '1':
            if (glIsEnabled(GL_LIGHT1))
                glDisable(GL_LIGHT1);
            else
                glEnable(GL_LIGHT1);
            break;
        case 's': /* rotate object around the x-axis */
        	xrot=xrot+5;
            if (xrot>360) xrot = 0;
            glutPostRedisplay();
            break;
        case 'w': /* rotate object around the x-axis */
            xrot=xrot-5;
            if (xrot>360) xrot = 359;
            glutPostRedisplay();
            break;
        case 'a': /* rotate object around the y-axis */
            yrot=yrot-5;
            if (yrot>360) yrot = 359;
            glutPostRedisplay();
            break;

        case 'd': /* rotate object around the y-axis */
            yrot=yrot+5;
            if (yrot>360) yrot = 0;
            glutPostRedisplay();
            break;

        case 'p': /* pause the animation */
            if (pause)
                pause = false;
            else
                pause = true;
            break;
    }
    glutPostRedisplay();
}



/* =======================================
 * Main function
 * ======================================= */
int	main(int argc, char **argv)
{
	/* Creation of the window */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 700);
	glutCreateWindow("CIS 367 Proj 2: Animation and Shading");

	/* OpenGL settings */
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	// initialize display lists
	init();
	paramInit();

	/* Declaration of the callbacks */
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutSpecialFunc(fkeyCallback);
	glutKeyboardFunc (keyCallback);
	glutTimerFunc(frame_rate, animate, 0);

	/* Loop */
	glutMainLoop();

	/* Never reached */
	return 0;
} // END main


/* ===========================EOF============================================= */

