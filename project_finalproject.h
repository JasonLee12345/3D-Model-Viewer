#ifndef PROJECT_FINALPROJECT_H
#define PROJECT_FINALPROJECT_H

#include <QtWidgets/QMainWindow>
#include "ui_project_finalproject.h"


//QT_BEGIN_NAMESPACE
class QSlider;
//QT_END_NAMESPACE
class QMenu;

class MyClass_GLWidget;


class Project_FinalProject : public QMainWindow
{
	Q_OBJECT

public:
	Project_FinalProject(QWidget *parent = 0);
	~Project_FinalProject();

	
public slots:   
	 void on_enaLighting_clicked();
	 void on_disaLighting_clicked();
	 void on_light1On_clicked();
	 void on_light1Off_clicked();
	 void on_light2On_clicked();
	 void on_light2Off_clicked();
	 void on_middleLightOn_clicked();
	 void on_middleLightOff_clicked();

	 void mySlot00();
	 void mySlot01();
	 void mySlot02();
	 void mySlot03();
	 void mySlot04();
	 void mySlot05();
	 void mySlot06();
	 void mySlot07();
	 void mySlot08();
	 void mySlot09();

	 void mySlot11();
	 void mySlot12();
	 void mySlot13();
	 void mySlot14();
	 void mySlot15();
	 void mySlot16();
	 void mySlot17();
	 void mySlot18();
	 void mySlot19();

	 void mySlot21();
	 void mySlot22();
	 void mySlot23();
	 void mySlot24();
	 void mySlot25();
	 void mySlot26();
	 void mySlot27();
	 void mySlot28();
	 void mySlot29();

	 void mySlot31();
	 void mySlot32();
	 void mySlot33();
	 void mySlot34();
	 void mySlot35();
	 void mySlot36();
	 void mySlot37();
	 void mySlot38();
	 void mySlot39();	 
	 //void mySlot40();
	 void mySlot41();
	 

	 void actionSlot_Space_ship();
	 void actionSlot_action_Blend();
	 void actionSlot_action_Air_Cyph();
	 void actionSlot_action_Planet_Camera();
	 void actionSlot_action_Shovl();
	 void actionSlot_action_Shuttle();
	 void actionSlot_action_Zep();

	 void actionSlot_Per_Vertex();
	 void actionSlot_Per_Pixel();
	 void actionSlot_Multi_Texture();
	 void actionSlot_Spot_Light();

	 void actionSlot_About();
	 void actionSlot_Help();
	 void actionSlot_Exit();

	 void Radio_1_Slot();
	 void Radio_2_Slot();

	 void mySlotL1_X();
	 void mySlotL1_Y();
	 void mySlotL1_Z();

	 void mySlotL2_X();
	 void mySlotL2_Y();
	 void mySlotL2_Z();

	 /*void mySlotM_X();
	 void mySlotM_Y();
	 void mySlotM_Z();*/

private:
	Ui::topMainWindow ui;


protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QSlider *createSlider();

    MyClass_GLWidget *glWidget;
	////////////////////////////////////////////////////////////////////////////////////////////////////
     QSlider *slider00;//Material Shininess
	 QSlider *slider01;//Material
	 QSlider *slider02;
	 QSlider *slider03;
	 QSlider *slider04;
	 QSlider *slider05;
	 QSlider *slider06;
	 QSlider *slider07;
	 QSlider *slider08;
	 QSlider *slider09;

	 QSlider *slider11;//Light1
	 QSlider *slider12;
	 QSlider *slider13;
	 QSlider *slider14;
	 QSlider *slider15;
	 QSlider *slider16;
	 QSlider *slider17;
	 QSlider *slider18;
	 QSlider *slider19;

	 QSlider *slider21;//Light2
	 QSlider *slider22;
	 QSlider *slider23;
	 QSlider *slider24;
	 QSlider *slider25;
	 QSlider *slider26;
	 QSlider *slider27;
	 QSlider *slider28;
	 QSlider *slider29;

	 QSlider *slider31;//MiddleLight
	 QSlider *slider32;
	 QSlider *slider33;
	 QSlider *slider34;
	 QSlider *slider35;
	 QSlider *slider36;
	 QSlider *slider37;
	 QSlider *slider38;
	 QSlider *slider39;
	 //QSlider *slider40;//MiddleLight Direction
	 QSlider *slider41;//MiddleLight Attenuation

	 QSlider *sliderL1_X;
	 QSlider *sliderL1_Y;
	 QSlider *sliderL1_Z;

	 QSlider *sliderL2_X;
	 QSlider *sliderL2_Y;
	 QSlider *sliderL2_Z;

	 /*QSlider *sliderM_X;
	 QSlider *sliderM_Y;
	 QSlider *sliderM_Z;*/
	 ////////////////////////////////////////////////////////////////////////////////////////////////////
	 QAction *action_Space_Ship;
	 QAction *action_Space_Ship_2;
	 QAction *action_Blend;
	 QAction *action_Air_Cyph;
	 QAction *action_Planet_Camera;
	 QAction *action_Shovl;
	 QAction *action_Shuttle;
	 QAction *action_Zep;

	 QAction *action_Per_Vertex;
	 QAction *action_Per_Pixel;
	 QAction *action_Multi_Texture;
	 QAction *action_Spot_Light;

	 QAction *action_My_About;
	 QAction *action_My_Help;
	 QAction *action_My_Exit;
	 ////////////////////////////////////////////////////////////////////////////////////////////////////
	 QGroupBox *shaderControlGroup;
	 QRadioButton *radio1;
     QRadioButton *radio2;

};

#endif // PROJECT_FINALPROJECT_H
