#include <QtOpenGL>
//#include <GL/freeglut.h>

//#include <windows.h>
//#include <math.h>

#include "MyClass_GLWidget.h"
#include "textfile.h"


#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


static GLfloat vdata[12][3] = { {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
								{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
								{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
							  };

static GLint tindices[20][3] = { {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
								 {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
								 {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
								 {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} 
							    };

float camCenter[]		= {0.0, 0.0, 150.0};
float camDelta[]		= {0.0, 10.0, 0.0};
float centerCoords[]	= {0.0, 10.0, 0.0};
float lookAtDelta[]		= {0.0, 0.0, 0.0};

float time = 0.0;


//! [0]
MyClass_GLWidget::MyClass_GLWidget(QWidget *parent) : QGLWidget(parent)
 //QGLWidget(QGLFormat(QGL::SampleBuffers), parent), 
{
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

	rotate_flag = 0;
	right_rotate_flag = 0;
	this->setFocusPolicy(Qt::StrongFocus);
	this->setFocus();

	//frames = 0;
	//timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));  
    //timer->start(10);
	/////////////////////////////////////////////////////////////////////////////////////
	material_shininess	= 20;

	material_ambient[0] = 0.5;
	material_ambient[1] = 0.0;
	material_ambient[2] = 0.0;
	material_ambient[3] = 1.0;

	material_diffuse[0] = 1.0;
	material_diffuse[1] = 1.0;
	material_diffuse[2] = 1.0;
	material_diffuse[3] = 1.0;

	material_specular[0] = 1.0;
	material_specular[1] = 1.0;
	material_specular[2] = 1.0;
	material_specular[3] = 1.0;
	/////////////////////////////////////////////////////////////////////////////////////
	light_ambient[0] = 0.0;
	light_ambient[1] = 0.0;
	light_ambient[2] = 0.0;
	light_ambient[3] = 1.0;

	light_diffuse[0] = 1.0;
	light_diffuse[1] = 0.0;
	light_diffuse[2] = 0.0;
	light_diffuse[3] = 1.0;

    light_specular[0] = 0.1;
	light_specular[1] = 0.1;
	light_specular[2] = 0.1;
	light_specular[3] = 1.0;
    
	light_position[0] = 1000.0;
	light_position[1] = 0.0;
	light_position[2] = 0.0;
	light_position[3] = 0.0;
	/////////////////////////////////////////////////////////////////////////////////////
	light_ambient1[0] = 0.0;
	light_ambient1[1] = 0.0;
	light_ambient1[2] = 0.0;
	light_ambient1[3] = 1.0;

	light_diffuse1[0] = 0.0;
	light_diffuse1[1] = 0.0;
	light_diffuse1[2] = 0.6;
	light_diffuse1[3] = 1.0;

	light_specular1[0] = 0.1;
	light_specular1[1] = 0.1;
	light_specular1[2] = 0.1;
	light_specular1[3] = 1.0;

	light_position1[0] = -1000.0;
	light_position1[1] = 0.0;
	light_position1[2] = 0.0;
	light_position1[3] = 0.0;
	/////////////////////////////////////////////////////////////////////////////////////
	light_ambient2[0] = 0.0;
	light_ambient2[1] = 0.0;
	light_ambient2[2] = 0.0;
	light_ambient2[3] = 1.0;

	light_diffuse2[0] = 0.0;
	light_diffuse2[1] = 0.5;
	light_diffuse2[2] = 0.0;
	light_diffuse2[3] = 1.0;

	light_specular2[0] = 0.4;
	light_specular2[1] = 0.4;
	light_specular2[2] = 0.4;
	light_specular2[3] = 1.0;

	light_position2[0] = 0.0;
	light_position2[1] = 0.0;
	light_position2[2] = 150.0;
	light_position2[3] = 1.0;

	spot_direction[0] = 0.0;
	spot_direction[1] = 0.0;
	spot_direction[2] = -1.0;
	/////////////////////////////////////////////////////////////////////////////////////

}
//! [0]


//! [1]
MyClass_GLWidget::~MyClass_GLWidget()
{
}
//! [1]


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


//! [4]
void MyClass_GLWidget::initializeGL()
{
	initializeGLFunctions();
	//glClearColor (0.0, 0.0, 0.0, 0.5);
	qglClearColor(qtPurple.dark());
	glColor3f(1.0, 1.0, 1.0);


	//////////////////////////////////////////////////////////////////////////////////Material
    glMaterialfv(GL_FRONT, GL_AMBIENT,		material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,		material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,		material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS,	   material_shininess);
   //////////////////////////////////////////////////////////////////////////////////light1 
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	/////////////////////////////////////////////////////////////////////////////////light2
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	/////////////////////////////////////////////////////////////////////////////////Middlelight
    glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 5.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);
	/////////////////////////////////////////////////////////////////////////////////
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
    glEnable(GL_LIGHTING);
	/////////////////////////////////////////////////////////////////////////////////
	
    glEnable(GL_AUTO_NORMAL);//after enabled this, the light can be reflected to every directions
    glEnable(GL_NORMALIZE);//enable users to use nornals
	glFrontFace(GL_CW);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_MULTISAMPLE);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
    glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

	loadCheckModelAndTexture("spaceship.3ds","spaceshiptexture.bmp", BITMAP_TEXTURE);
	//loadCheckModelAndTwoTexture("spaceship.3ds","spaceshiptexture.bmp", "hbltel_2.bmp", BITMAP_TEXTURE, BITMAP_TEXTURE);

	SetupShaders("per_pixel.vert", "per_pixel.frag");

}
//! [4]


//! [2]
void MyClass_GLWidget::paintGL()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glLoadIdentity();
	gluLookAt(camCenter[0]+camDelta[0], camCenter[1]+camDelta[1], camCenter[2]+camDelta[2],
			  centerCoords[0]+lookAtDelta[0], centerCoords[1]+lookAtDelta[1], centerCoords[2]+lookAtDelta[2],
			  0, 1, 0);
	
    glPushMatrix();
		glRotatef(rotation_axis[0] , rotation_axis[1], rotation_axis[2], rotation_axis[3]);
		//time += 0.1;
		useModel();	
		//drawModel();
	glPopMatrix();

	drawGround(200,200,-50);
    
}
//! [2]


//! [3]
void MyClass_GLWidget::resizeGL(int width, int height)
{
    //int side = qMin(width, height);
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(65.0, (GLfloat)width/(GLfloat)height, 1.0, 10000.0); 
	/*
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
	*/
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0.0 , 0.0 , 30.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0);
	//gluLookAt(camCenter[0]+camDelta[0], camCenter[1]+camDelta[1], camCenter[2]+camDelta[2],
		//	  centerCoords[0]+lookAtDelta[0], centerCoords[1]+lookAtDelta[1], centerCoords[2]+lookAtDelta[2],
		//	  0, 1, 0);
	global_h = height;
}
//! [3]


void MyClass_GLWidget::SetupShaders(char * vert, char *frag)
{
	//char *g_VertexShaderText, *g_FragmentShaderText;
	//g_VertexShaderText = textFileRead("minimal.vert");
	//g_FragmentShaderText = textFileRead("minimal.frag");

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QGLShader::Vertex, vert))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QGLShader::Fragment, frag))
        close();


    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

	//program.setUniformValue("shader_time",time);

}


void MyClass_GLWidget::DestroyShaders()
{
	program.removeAllShaders();
}


void MyClass_GLWidget::BindShader()
{
	program.bind();

}


void MyClass_GLWidget::ReleaseShader()
{
	program.release();

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void MyClass_GLWidget::mousePressEvent(QMouseEvent *event)
{
	if ( event->button() == Qt::LeftButton )
	{
		lastPos = event->pos();
		rotate_flag = 1;
	}
	else if(event->button() == Qt::RightButton)
		{
			right_rotate_flag = 1;
		}
}


void MyClass_GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if ( event->button() == Qt::LeftButton )
	{
		rotate_flag = 0;
	}
	else if(event->button() == Qt::RightButton)
		{
			right_rotate_flag = 0;
		}
	
}


void MyClass_GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	float length;
	
	if(event->buttons()&Qt::LeftButton) 
	{
		int current_x = event->x();
		int current_y = global_h - event->y();
		length = sqrt( (double)(  (lastPos.y() - current_y)*(lastPos.y() - current_y)  +  (lastPos.x() - current_x)*(lastPos.x() - current_x)  ) );
		length /=2;
		//if( (last_x - current_x) >=3)
		makeLineEquationSlope(length, lastPos.x(), lastPos.y(), current_x, current_y);
	
		if(rotate_flag == 1)
		{
			updateGL();
		}

	}else if(event->buttons()&Qt::RightButton) 
			{
				if(right_rotate_flag)
				{
					/*
					glLoadIdentity();
					gluLookAt(0.0 , 0.0 , 200.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 , 0.0);
					updateGL();
					*/
				}

			}else if(event->buttons()&Qt::MiddleButton)
						{


						}
	
}


void MyClass_GLWidget::wheelEvent(QWheelEvent *event)
 {
	 camDelta[2] += (event->delta() / 8.0 / 15.0) * 8;// * WHEEL_DELTA;
     //lookAtDelta[2] += (event->delta() / 8.0 / 15.0) * WHEEL_DELTA;
     updateGL();
	 /*
     if (event->orientation() == Qt::Horizontal) {       
         scrollHorizontally(numSteps);       //水平滚动
     } else {
         scrollVertically(numSteps);       //垂直滚动
     }
     event->accept();      //接收该事件
	 */
 }


void MyClass_GLWidget::keyPressEvent( QKeyEvent *k ) 
{ 
	if (k->type() == QEvent::KeyPress) 
	{
		if(k->key() == Qt::Key_W) 
		{ 
			 camDelta[2] -= 5;
			 updateGL();
		}

		if(k->key() == Qt::Key_S) 
		{ 
			 camDelta[2] += 5;
			 updateGL();
		}

		if(k->key() == Qt::Key_A) 
		{ 
			 camDelta[0] -= 5;
			 lookAtDelta[0] -= 5;
			 updateGL();
		}

		if(k->key() == Qt::Key_D) 
		{ 
			 camDelta[0] += 5;
			 lookAtDelta[0] += 5;
			 updateGL();
		}

		if(k->key() == Qt::Key_Up) 
		{ 
			 lookAtDelta[1] += 5;
			 updateGL();
		}

		if(k->key() == Qt::Key_Down) 
		{ 
			 lookAtDelta[1] -= 5;
			 updateGL();
		}

		if(k->key() == Qt::Key_Left) 
		{ 
			 lookAtDelta[0] += 5;
			 updateGL();
		}

		if(k->key() == Qt::Key_Right) 
		{ 
			 lookAtDelta[0] -= 5;
			 updateGL();
		}

	}
    
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void MyClass_GLWidget::subdivision(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], GLint depth)
{
	depth++;
	if(depth <= recursion_flag)
	{
		GLfloat v12[3];
		GLfloat v23[3];
		GLfloat v31[3];

		for(int i=0;i<3;i++)
		{
			v12[i]=(v1[i]+v2[i])/2;
			v23[i]=(v2[i]+v3[i])/2;
			v31[i]=(v3[i]+v1[i])/2;
		}

		normalize(v12);
		normalize(v23);
		normalize(v31);

			
			subdivision(v1,v12,v31,depth);
			drawTriangle(v1,v12,v31);

			
			subdivision(v2,v12,v23,depth);
			drawTriangle(v2,v12,v23);

			
			subdivision(v3,v23,v31,depth);
			drawTriangle(v3,v23,v31);

			
			subdivision(v12,v23,v31,depth);
			drawTriangle(v12,v23,v31);
	}
	else
	{
		drawTriangle(v1,v2,v3);
		//return;
	}

}


void MyClass_GLWidget::drawTriangle(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3])
{
	glBegin(GL_TRIANGLES);    
			glNormal3fv( v1 );
			glVertex3fv( v1 );
			
			glNormal3fv( v2 );
			glVertex3fv( v2 );
			
			glNormal3fv( v3 );
			glVertex3fv( v3 );	
	glEnd(); 
	
}


void MyClass_GLWidget::makeVector(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], GLfloat out1[3], GLfloat out2[3])
{
	for(int i=0;i<3;i++)
	{
		out1[i] = v2[i] -v1[i];
	}

	for(int i=0;i<3;i++)
	{
		out2[i] = v3[i] -v1[i];
	}

}


void MyClass_GLWidget::normCrossProd(GLfloat v1[3], GLfloat v2[3], GLfloat out[3]) 
{ 
   GLint i, j; 
   GLfloat length;

   out[0] = v1[1]*v2[2] - v1[2]*v2[1]; 
   out[1] = v1[2]*v2[0] - v1[0]*v2[2]; 
   out[2] = v1[0]*v2[1] - v1[1]*v2[0]; 
   normalize(out); 
}


void MyClass_GLWidget::normalize(GLfloat v[3])
{    
   GLfloat d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]); 
   if (d == 0.0) 
   {
      throw d;    
      return;
   }
   v[0] /= d; v[1] /= d; v[2] /= d; 
   //v[0] *= 2; v[1] *= 2; v[2] *= 2;
}


/*
 * n is the grids' line number in every demention
 * length is the grid line's length
 * y is the y-axis value of those grids in the world space
*/
void MyClass_GLWidget::drawGround(GLint n, GLint length,GLfloat y)
{
	for(register int i=0;i<=n;i++)
	{
		GLfloat start[3];
		GLfloat end[3];

		start[0]=i-n/2; 
		start[1]=y; 
		start[2]=length/2;

		end[0]=i-n/2;
		end[1]=y;
		end[2]=-length/2;

		glBegin(GL_LINES);    
			glVertex3fv(start);
			glVertex3fv(end);
		glEnd(); 
	}

	for(register int i=0;i<=n;i++)
	{
		GLfloat start[3];
		GLfloat end[3];

		start[0]=length/2;
		start[1]=y;
		start[2]=i-n/2;

		end[0]=-length/2;
		end[1]=y;
		end[2]=i-n/2;

		glBegin(GL_LINES);    
			glVertex3fv(start);
			glVertex3fv(end);
		glEnd(); 
	}
}


void MyClass_GLWidget::makeLineEquationSlope(float angle, int x, int y, int current_x, int current_y)
{
	float k1;
	float k2;
	if(x == current_x)
	{
		rotation_axis[0] = angle;
		rotation_axis[1] = 1.0;
 		rotation_axis[2] = 0.0;
		rotation_axis[3] = 0.0; 
		
	}
	else 
	{
		if(y == current_y)
		{		
			rotation_axis[0] = angle;
			rotation_axis[1] = 0.0;
 			rotation_axis[2] = 1.0;
			rotation_axis[3] = 0.0;
			
		}
		else
		{
			k1 = ((float)y - (float)current_y)/((float)x - (float)current_x);
			k2 = (float)-1/k1;	

			if( ( current_x>x && k1>0 ) || ( current_x<x && k1<0 ) )
			{
				angle_direction = false;
				rotation_axis[0] = -angle;
			}
			else
			{
				angle_direction = true;
				rotation_axis[0] = angle;
			}

			rotation_axis[1] = 1.0;
 			rotation_axis[2] = k2;
			rotation_axis[3] = 0.0;
		}
	}

}


void MyClass_GLWidget::drawModel()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY); 
	/*
	GLfloat  fColors[] = {-1,0,0,
						   -1,0,0,
						   -1,0,0,
						   -1,0,0};
*/
	GLfloat fVertices[MAX_VERTICES * 3];
	//GLfloat *fVertices = (GLfloat *) malloc(object.vertices_qty * 3);
	//memset(fVertices, 0, object.vertices_qty * 3);

	for(int i=0; i < object.polygons_qty; i++)
	{
			fVertices[i*9]   = object.vertex[ object.polygon[i].a ].x;
			fVertices[i*9+1] = object.vertex[ object.polygon[i].a ].y;
			fVertices[i*9+2] = object.vertex[ object.polygon[i].a ].z;

			fVertices[i*9+3] = object.vertex[ object.polygon[i].b ].x;
			fVertices[i*9+4] = object.vertex[ object.polygon[i].b ].y;
			fVertices[i*9+5] = object.vertex[ object.polygon[i].b ].z;

			fVertices[i*9+6] = object.vertex[ object.polygon[i].c ].x;
			fVertices[i*9+7] = object.vertex[ object.polygon[i].c ].y;
			fVertices[i*9+8] = object.vertex[ object.polygon[i].c ].z;
			
			int j =0;
	}
	
	//glColorPointer(3, GL_FLOAT, 0, fColors); 
	glVertexPointer(3, GL_FLOAT, 0, fVertices); 
	
	static GLubyte byRectIndices[3];
	for(GLubyte count=0; count < object.polygons_qty/2; count++)
	{
		byRectIndices[0] = 3*count;
		byRectIndices[1] = 3*count+1;
		byRectIndices[2] = 3*count+2;
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, byRectIndices);
	}
	
}


void MyClass_GLWidget::useModel()
{
	int l_index;
	float myVertex[3][3];
	float vector1[3], vector2[3];
	float myNormal[3];

	glBegin(GL_TRIANGLES);
			for (l_index=0; l_index < object.polygons_qty; l_index++)
			{
				myVertex[0][0] = object.vertex[ object.polygon[l_index].a ].x;
				myVertex[0][1] = object.vertex[ object.polygon[l_index].a ].y;
				myVertex[0][2] = object.vertex[ object.polygon[l_index].a ].z;

				myVertex[1][0] = object.vertex[ object.polygon[l_index].b ].x;
				myVertex[1][1] = object.vertex[ object.polygon[l_index].b ].y;
				myVertex[1][2] = object.vertex[ object.polygon[l_index].b ].z;

				myVertex[2][0] = object.vertex[ object.polygon[l_index].c ].x;
				myVertex[2][1] = object.vertex[ object.polygon[l_index].c ].y;
				myVertex[2][2] = object.vertex[ object.polygon[l_index].c ].z;

				makeVector(myVertex[0], myVertex[1], myVertex[2], vector1, vector2);
				normCrossProd(vector1,vector2, myNormal);
				normalize(myNormal);
				glNormal3fv( myNormal );
				
				//----------------- FIRST VERTEX -----------------
				// Texture coordinates of the first vertex	  				
				glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
							  object.mapcoord[ object.polygon[l_index].a ].v);	  
				// Coordinates of the first vertex				
				glVertex3f( myVertex[0][0], myVertex[0][1], myVertex[0][2]); //Vertex definition

				//----------------- SECOND VERTEX -----------------
				// Texture coordinates of the second vertex
				glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
							  object.mapcoord[ object.polygon[l_index].b ].v);
				// Coordinates of the second vertex
				glVertex3f( myVertex[1][0], myVertex[1][1], myVertex[1][2]);
        
				//----------------- THIRD VERTEX -----------------
				// Texture coordinates of the third vertex		
				glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
							  object.mapcoord[ object.polygon[l_index].c ].v);
				// Coordinates of the Third vertex
				glVertex3f( myVertex[2][0], myVertex[2][1], myVertex[2][2]);
			}					
		glEnd();

}


void MyClass_GLWidget::loadCheckModelAndTexture(char *modelName, char *textureName, int mode)
{
	Load3DS (&object,modelName);
	
	if(mode)//TGA_TEXTRUE
		object.id_texture[0] = loadFace(GL_TEXTURE_2D, textureName);
	else//BITMAP_TEXTURE
		object.id_texture[0] = LoadBitmap(textureName);

	glBindTexture(GL_TEXTURE_2D, object.id_texture[0]); // We set the active texture
	

	if(object.polygons_qty>0)
		;
	else
		exit (0);

	char *info = "No such texture file exists!";
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (object.id_texture[0] == -1)
    {
        QMessageBox::information(NULL, "Caution",  info, QMessageBox::Ok, QMessageBox::Ok);
        //exit (0);
    }

}


void MyClass_GLWidget::loadCheckModelAndTwoTexture(char *modelName, char *textureName, char *textureName1, int mode, int mode1)
{
	Load3DS (&object,modelName);
	
	if(mode)//TGA_TEXTRUE
		object.id_texture[0] = loadFace(GL_TEXTURE_2D, textureName);
	else//BITMAP_TEXTURE
		object.id_texture[0] = LoadBitmap(textureName);

	if(mode1)//TGA_TEXTRUE
		object.id_texture[1] = loadFace(GL_TEXTURE_2D, textureName1);
	else//BITMAP_TEXTURE
		object.id_texture[1] = LoadBitmap(textureName1);

	glBindTexture(GL_TEXTURE_2D, object.id_texture[0]); // We set the active texture
	glBindTexture(GL_TEXTURE_2D, object.id_texture[1]); 
	glActiveTexture(object.id_texture[0]);
	glActiveTexture(object.id_texture[1]);

	if(object.polygons_qty>0)
		;
	else
		exit (0);

	char *info = "No such texture file exists!";
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (object.id_texture[0] == -1)
    {
        QMessageBox::information(NULL, "Caution",  info, QMessageBox::Ok, QMessageBox::Ok);
        //exit (0);
    }

}