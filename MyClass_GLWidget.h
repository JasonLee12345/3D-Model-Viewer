#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLFunctions>
//#include <QOpenGLFunctions>
#include <QGLShaderProgram>

#include "3dsloader.h"
#include "texture.h"

extern "C"{
#include "tga.h"
}

/* In case your <GL/gl.h> does not advertise EXT_texture_lod_bias... */
#ifndef GL_EXT_texture_lod_bias
# define GL_MAX_TEXTURE_LOD_BIAS_EXT         0x84fd
# define GL_TEXTURE_FILTER_CONTROL_EXT       0x8500
# define GL_TEXTURE_LOD_BIAS_EXT             0x8501
#endif

/* In case your <GL/gl.h> does not advertise EXT_texture_cube_map... */
#ifndef GL_EXT_texture_cube_map
# define GL_NORMAL_MAP_EXT                   0x8511
# define GL_REFLECTION_MAP_EXT               0x8512
# define GL_TEXTURE_CUBE_MAP_EXT             0x8513
# define GL_TEXTURE_BINDING_CUBE_MAP_EXT     0x8514
# define GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT  0x8515
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT  0x8516
# define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT  0x8517
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT  0x8518
# define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT  0x8519
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT  0x851A
# define GL_PROXY_TEXTURE_CUBE_MAP_EXT       0x851B
# define GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT    0x851C
#endif

#define X 1.2//.525731112119133606
#define Z 1.6//.850650808352039932

#define BITMAP_TEXTURE 0
#define TGA_TEXTURE 1

class QOpenGLShader;


class MyClass_GLWidget : public QGLWidget, protected QGLFunctions 
{
    Q_OBJECT
//! [0]
public:
    MyClass_GLWidget(QWidget *parent = 0);
    ~MyClass_GLWidget();

	void normCrossProd(GLfloat[3], GLfloat[3], GLfloat[3]);
	void normalize(GLfloat[3]);
	void subdivision(GLfloat[3],GLfloat[3],GLfloat[3],GLint);
	void drawTriangle(GLfloat[3],GLfloat[3],GLfloat[3]);
	void drawGround(GLint,GLint,GLfloat);
	void makeLineEquationSlope(float, int, int, int, int);
	//void SceneInit(GLfloat[3], GLfloat[3], GLfloat[3], GLfloat[3]);
	void useModel();
	void drawModel();
	//void loadFace(GLenum target, char *filename);
	//void makeCubeMap(void);
	void loadCheckModelAndTexture(char *, char *, int);
	void loadCheckModelAndTwoTexture(char *, char *, char *, int, int);
	void makeVector(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], GLfloat out1[3], GLfloat out2[3]);
	void SetupShaders(char * vert, char *frag);
	void DestroyShaders();
	void BindShader();
	void ReleaseShader();

public:
	int recursion_flag;
	GLfloat material_ambient[4];
	GLfloat material_diffuse[4];	
	GLfloat material_specular[4];		
	GLfloat material_shininess;

	GLfloat light_ambient[4];
    GLfloat light_diffuse[4];
    GLfloat light_specular[4];
    GLfloat light_position[4];

	GLfloat light_ambient1[4];
    GLfloat light_diffuse1[4];
    GLfloat light_specular1[4];
    GLfloat light_position1[4];

	GLfloat light_ambient2[4];
	GLfloat light_diffuse2[4];
	GLfloat light_specular2[4];
    GLfloat light_position2[4];
	GLfloat spot_direction[3];//spot light
	//int shutdown;
//! [0]


//! [1]
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent( QKeyEvent *k );
	
//! [1]

//! [2]
private:
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;
	GLfloat global_h;
	float rotation_axis[4];
	GLboolean angle_direction;
	int rotate_flag;
	int right_rotate_flag;
	obj_type object;

	int frames;
	QTimer *timer; 

    //QOpenGLShader m_pVertexShader, m_pFragmentShader;

	QGLShaderProgram program;

	GLint shaderParaLoc, shaderParaLoc0, shaderParaLoc1, shaderParaLoc2;

	
};
//! [2]

#endif
