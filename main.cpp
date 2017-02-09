#include "project_finalproject.h"
#include <QtWidgets/QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	/*
	if ( ( QGLFormat::openGLVersionFlags( ) &
            QGLFormat::OpenGL_Version_2_0 ) == 0 )
    {
        QMessageBox::warning( 0, QObject::tr( "Program Information" ),
                              QObject::tr( "This system does not support OpenGL2.0, however this example guarantees the functionalities of these OpenGL higher API." ) );
    }
	*/
	Project_FinalProject w;
	w.show();
	return a.exec();
}
