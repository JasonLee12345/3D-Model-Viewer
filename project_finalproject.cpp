#include <QtWidgets>

#include "project_finalproject.h"
#include "MyClass_GLWidget.h"
#include "textfile.h"


char *blendModelFile[6] = { "blendial.tga", 
							"blendis.tga", 
							"blendis2.tga", 
							"blendl2.tga", 
							"blenglas.tga", 
							"blenref.tga", 
						   };

char *sidemapModelFile[3] = {	"sidemap1.tga", 
								"sidemap2.tga", 
								"white.tga", 
							};

char *hbModelFile[3] = {"hbltel_1.bmp",
						"hbltel_2.bmp",
						"hbltel_w.bmp"};

int triggeredd_flag = 1;



Project_FinalProject::Project_FinalProject(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	glWidget = ui.glWidget1;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	action_Space_Ship		= ui.actionSpace_Ship;
	action_Space_Ship_2		= ui.actionSpace_Ship_2;
	action_Blend			= ui.actionBlend;
	action_Air_Cyph			= ui.actionAir_Cyph;
	action_Planet_Camera	= ui.actionPlanet_Camera;
	action_Shovl			= ui.actionShovl;
	action_Shuttle			= ui.actionShuttle;
	action_Zep				= ui.actionZep;

	connect(action_Space_Ship,		SIGNAL(triggered()), this, SLOT(actionSlot_Space_ship()));
	connect(action_Space_Ship_2,	SIGNAL(triggered()), this, SLOT(actionSlot_Space_ship()));
	connect(action_Blend,			SIGNAL(triggered()), this, SLOT(actionSlot_action_Blend()));
	connect(action_Air_Cyph,		SIGNAL(triggered()), this, SLOT(actionSlot_action_Air_Cyph()));
	connect(action_Planet_Camera,	SIGNAL(triggered()), this, SLOT(actionSlot_action_Planet_Camera()));
	connect(action_Shovl,			SIGNAL(triggered()), this, SLOT(actionSlot_action_Shovl()));
	connect(action_Shuttle,			SIGNAL(triggered()), this, SLOT(actionSlot_action_Shuttle()));
	connect(action_Zep,				SIGNAL(triggered()), this, SLOT(actionSlot_action_Zep()));
	////////////////////////////////////////////////////////////////////////////////////////////////////
	shaderControlGroup = ui.groupBox;
	shaderControlGroup->setChecked(true);
	radio1 = ui.EnableRadioButton;
	radio2 = ui.DisableRadioButton;
	radio1->setChecked(true);

	connect(radio1,		SIGNAL(clicked()), this, SLOT(Radio_1_Slot()));
	connect(radio2,		SIGNAL(clicked()), this, SLOT(Radio_2_Slot()));
	////////////////////////////////////////////////////////////////////////////////////////////////////
	action_Per_Vertex		= ui.actionPer_Vertex;
	action_Per_Pixel		= ui.actionPer_Pixel;
	action_Multi_Texture	= ui.actionMultiTexture;
	action_Spot_Light		= ui.actionSpot_Light_per_pixel;

	connect(action_Per_Vertex,		SIGNAL(triggered()), this, SLOT(actionSlot_Per_Vertex()));
	connect(action_Per_Pixel,		SIGNAL(triggered()), this, SLOT(actionSlot_Per_Pixel()));
	connect(action_Multi_Texture,	SIGNAL(triggered()), this, SLOT(actionSlot_Multi_Texture()));
	connect(action_Spot_Light,		SIGNAL(triggered()), this, SLOT(actionSlot_Spot_Light()));

	action_My_About	= ui.actionAbout;
	connect(action_My_About,		SIGNAL(triggered()), this, SLOT(actionSlot_About()));

	action_My_Help	= ui.actionHelp;
	connect(action_My_Help,			SIGNAL(triggered()), this, SLOT(actionSlot_Help()));

	action_My_Exit = ui.actionExit;
	connect(action_My_Exit,			SIGNAL(triggered()), this, SLOT(actionSlot_Exit()));
	////////////////////////////////////////////////////////////////////////////////////////////////////
	slider00 = ui.Material_Shininess;//Material
	slider01 = ui.Material_A_R;
	slider02 = ui.Material_A_G;
	slider03 = ui.Material_A_B; 
	slider04 = ui.Material_D_R;
	slider05 = ui.Material_D_G;
	slider06 = ui.Material_D_B;
	slider07 = ui.Material_S_R;
	slider08 = ui.Material_S_G;
	slider09 = ui.Material_S_B;

	slider00->setRange(0, 255);
	slider01->setRange(0, 10);
	slider02->setRange(0, 10);
	slider03->setRange(0, 10);
	slider04->setRange(0, 10);
	slider05->setRange(0, 10);
	slider06->setRange(0, 10);
	slider07->setRange(0, 10);
	slider08->setRange(0, 10);
	slider09->setRange(0, 10);

	slider00->setValue(20);
	slider01->setValue(5);
	
	connect(slider00, SIGNAL(sliderMoved(int)), this, SLOT(mySlot00()));
	connect(slider01, SIGNAL(sliderMoved(int)), this, SLOT(mySlot01()));
	connect(slider02, SIGNAL(sliderMoved(int)), this, SLOT(mySlot02()));
	connect(slider03, SIGNAL(sliderMoved(int)), this, SLOT(mySlot03()));
	connect(slider04, SIGNAL(sliderMoved(int)), this, SLOT(mySlot04()));
	connect(slider05, SIGNAL(sliderMoved(int)), this, SLOT(mySlot05()));
	connect(slider06, SIGNAL(sliderMoved(int)), this, SLOT(mySlot06()));
	connect(slider07, SIGNAL(sliderMoved(int)), this, SLOT(mySlot07()));
	connect(slider08, SIGNAL(sliderMoved(int)), this, SLOT(mySlot08()));
	connect(slider09, SIGNAL(sliderMoved(int)), this, SLOT(mySlot09()));
	///////////////////////////////////////////////
	slider11 = ui.Light1_A_R;//Light1
	slider12 = ui.Light1_A_G;
	slider13 = ui.Light1_A_B; 
	slider14 = ui.Light1_D_R;
	slider15 = ui.Light1_D_G;
	slider16 = ui.Light1_D_B;
	slider17 = ui.Light1_S_R;
	slider18 = ui.Light1_S_G;
	slider19 = ui.Light1_S_B;


	slider11->setRange(0, 10);
	slider12->setRange(0, 10);
	slider13->setRange(0, 10);
	slider14->setRange(0, 10);
	slider15->setRange(0, 10);
	slider16->setRange(0, 10);
	slider17->setRange(0, 10);
	slider18->setRange(0, 10);
	slider19->setRange(0, 10);

	connect(slider11, SIGNAL(sliderMoved(int)), this, SLOT(mySlot11()));
	connect(slider12, SIGNAL(sliderMoved(int)), this, SLOT(mySlot12()));
	connect(slider13, SIGNAL(sliderMoved(int)), this, SLOT(mySlot13()));
	connect(slider14, SIGNAL(sliderMoved(int)), this, SLOT(mySlot14()));
	connect(slider15, SIGNAL(sliderMoved(int)), this, SLOT(mySlot15()));
	connect(slider16, SIGNAL(sliderMoved(int)), this, SLOT(mySlot16()));
	connect(slider17, SIGNAL(sliderMoved(int)), this, SLOT(mySlot17()));
	connect(slider18, SIGNAL(sliderMoved(int)), this, SLOT(mySlot18()));
	connect(slider19, SIGNAL(sliderMoved(int)), this, SLOT(mySlot19()));
	///////////////////////////////////////////////
	slider21 = ui.Light2_A_R;//Light2
	slider22 = ui.Light2_A_G;
	slider23 = ui.Light2_A_B; 
	slider24 = ui.Light2_D_R;
	slider25 = ui.Light2_D_G;
	slider26 = ui.Light2_D_B;
	slider27 = ui.Light2_S_R;
	slider28 = ui.Light2_S_G;
	slider29 = ui.Light2_S_B;

	slider21->setRange(0, 10);
	slider22->setRange(0, 10);
	slider23->setRange(0, 10);
	slider24->setRange(0, 10);
	slider25->setRange(0, 10);
	slider26->setRange(0, 10);
	slider27->setRange(0, 10);
	slider28->setRange(0, 10);
	slider29->setRange(0, 10);

	connect(slider21, SIGNAL(sliderMoved(int)), this, SLOT(mySlot21()));
	connect(slider22, SIGNAL(sliderMoved(int)), this, SLOT(mySlot22()));
	connect(slider23, SIGNAL(sliderMoved(int)), this, SLOT(mySlot23()));
	connect(slider24, SIGNAL(sliderMoved(int)), this, SLOT(mySlot24()));
	connect(slider25, SIGNAL(sliderMoved(int)), this, SLOT(mySlot25()));
	connect(slider26, SIGNAL(sliderMoved(int)), this, SLOT(mySlot26()));
	connect(slider27, SIGNAL(sliderMoved(int)), this, SLOT(mySlot27()));
	connect(slider28, SIGNAL(sliderMoved(int)), this, SLOT(mySlot28()));
	connect(slider29, SIGNAL(sliderMoved(int)), this, SLOT(mySlot29()));
	///////////////////////////////////////////////
	slider31 = ui.MiddleLight_A_R;//MiddleLight
	slider32 = ui.MiddleLight_A_G;
	slider33 = ui.MiddleLight_A_B; 
	slider34 = ui.MiddleLight_D_R;
	slider35 = ui.MiddleLight_D_G;
	slider36 = ui.MiddleLight_D_B;
	slider37 = ui.MiddleLight_S_R;
	slider38 = ui.MiddleLight_S_G;
	slider39 = ui.MiddleLight_S_B;
	//slider40 = ui.MiddleLight_Direction;
	slider41 = ui.MiddleLight_Attenuation;


	slider31->setRange(0, 10);
	slider32->setRange(0, 10);
	slider33->setRange(0, 10);
	slider34->setRange(0, 10);
	slider35->setRange(0, 10);
	slider36->setRange(0, 10);
	slider37->setRange(0, 10);
	slider38->setRange(0, 10);
	slider39->setRange(0, 10);
	//slider40->setRange(-1000, 1000);	slider40->setValue(0);
	slider41->setRange(0, 10);			slider41->setValue(2);
	
	
	connect(slider31, SIGNAL(sliderMoved(int)), this, SLOT(mySlot31()));
	connect(slider32, SIGNAL(sliderMoved(int)), this, SLOT(mySlot32()));
	connect(slider33, SIGNAL(sliderMoved(int)), this, SLOT(mySlot33()));
	connect(slider34, SIGNAL(sliderMoved(int)), this, SLOT(mySlot34()));
	connect(slider35, SIGNAL(sliderMoved(int)), this, SLOT(mySlot35()));
	connect(slider36, SIGNAL(sliderMoved(int)), this, SLOT(mySlot36()));
	connect(slider37, SIGNAL(sliderMoved(int)), this, SLOT(mySlot37()));
	connect(slider38, SIGNAL(sliderMoved(int)), this, SLOT(mySlot38()));
	connect(slider39, SIGNAL(sliderMoved(int)), this, SLOT(mySlot39()));
	//connect(slider40, SIGNAL(sliderMoved(int)), this, SLOT(mySlot40()));
	connect(slider41, SIGNAL(sliderMoved(int)), this, SLOT(mySlot41()));	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	sliderL1_X = ui.L1_X;	sliderL1_X->setRange(-2000,2000);	sliderL1_X->setValue(1000);
	sliderL1_Y = ui.L1_Y;	sliderL1_Y->setRange(-2000,2000);	sliderL1_Y->setValue(0);
	sliderL1_Z = ui.L1_Z;	sliderL1_Z->setRange(-2000,2000);	sliderL1_Z->setValue(0);
	connect(sliderL1_X, SIGNAL(sliderMoved(int)), this, SLOT(mySlotL1_X()));
	connect(sliderL1_Y, SIGNAL(sliderMoved(int)), this, SLOT(mySlotL1_Y()));
	connect(sliderL1_Z, SIGNAL(sliderMoved(int)), this, SLOT(mySlotL1_Z()));

	sliderL2_X = ui.L2_X;	sliderL2_X->setRange(-2000,2000);	sliderL2_X->setValue(-1000);
	sliderL2_Y = ui.L2_Y;	sliderL2_Y->setRange(-2000,2000);	sliderL2_Y->setValue(0);
	sliderL2_Z = ui.L2_Z;	sliderL2_Z->setRange(-2000,2000);	sliderL2_Z->setValue(0);
	connect(sliderL2_X, SIGNAL(sliderMoved(int)), this, SLOT(mySlotL2_X()));
	connect(sliderL2_Y, SIGNAL(sliderMoved(int)), this, SLOT(mySlotL2_Y()));
	connect(sliderL2_Z, SIGNAL(sliderMoved(int)), this, SLOT(mySlotL2_Z()));

	/*sliderM_X = ui.M_X;	sliderM_X->setRange(-2000,2000);	sliderM_X->setValue(0);
	sliderM_Y = ui.M_Y;	sliderM_Y->setRange(-2000,2000);	sliderM_Y->setValue(0);
	sliderM_Z = ui.M_Z;	sliderM_Z->setRange(-2000,2000);	sliderM_Z->setValue(150);
	connect(sliderM_X, SIGNAL(sliderMoved(int)), this, SLOT(sliderM_X()));
	connect(sliderM_Y, SIGNAL(sliderMoved(int)), this, SLOT(sliderM_Y()));
	connect(sliderM_Z, SIGNAL(sliderMoved(int)), this, SLOT(sliderM_Z()));*/
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
    setWindowTitle(tr("Final Project"));

}


Project_FinalProject::~Project_FinalProject()
{

}


void Project_FinalProject::on_enaLighting_clicked()
{
	glEnable(GL_LIGHTING); 
	glWidget->updateGL();
}


void Project_FinalProject::on_disaLighting_clicked()
{
	glDisable(GL_LIGHTING); 
	glWidget->updateGL();
}



void Project_FinalProject::on_light1On_clicked()
{
	glEnable(GL_LIGHT0);
	glWidget->updateGL();
}


void Project_FinalProject::on_light1Off_clicked()
{
	glDisable(GL_LIGHT0);
	glWidget->updateGL();
}


void Project_FinalProject::on_light2On_clicked()
{
	glEnable(GL_LIGHT1);
	glWidget->updateGL();
}


void  Project_FinalProject::on_light2Off_clicked()
{
	glDisable(GL_LIGHT1);
	glWidget->updateGL();
}


void  Project_FinalProject::on_middleLightOn_clicked()
{
	glEnable(GL_LIGHT2);
	glWidget->updateGL();
}


void  Project_FinalProject::on_middleLightOff_clicked()
{
	glDisable(GL_LIGHT2);
	glWidget->updateGL();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void Project_FinalProject::mySlot00()
{
	glWidget->material_shininess = slider00->value();
	glMaterialf(GL_FRONT, GL_SHININESS, glWidget->material_shininess);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot01()
{
	glWidget->material_ambient[0] = (float)slider01->value() / 10;
	glMaterialfv(GL_FRONT, GL_AMBIENT, glWidget->material_ambient);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot02()
{
	glWidget->material_ambient[1] = (float)slider02->value() / 10;
	glMaterialfv(GL_FRONT, GL_AMBIENT, glWidget->material_ambient);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot03()
{
	glWidget->material_ambient[2] = (float)slider03->value() / 10;
	glMaterialfv(GL_FRONT, GL_AMBIENT, glWidget->material_ambient);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot04()
{
	glWidget->material_diffuse[0] = (float)slider04->value() / 10;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glWidget->material_diffuse);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot05()
{
	glWidget->material_diffuse[1] = (float)slider05->value() / 10;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glWidget->material_diffuse);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot06()
{
	glWidget->material_diffuse[2] = (float)slider06->value() / 10;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, glWidget->material_diffuse);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot07()
{
	glWidget->material_specular[0] = (float)slider07->value() / 10;
	glMaterialfv(GL_FRONT, GL_SPECULAR, glWidget->material_specular);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot08()
{
	glWidget->material_specular[1] = (float)slider08->value() / 10;
	glMaterialfv(GL_FRONT, GL_SPECULAR, glWidget->material_specular);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot09()
{
	glWidget->material_specular[2] = (float)slider09->value() / 10;
	glMaterialfv(GL_FRONT, GL_SPECULAR, glWidget->material_specular);
	glWidget->updateGL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Project_FinalProject::mySlot11()
{
	glWidget->light_ambient[0] = (float)slider11->value() / 10;
	glLightfv(GL_LIGHT0, GL_AMBIENT,  glWidget->light_ambient);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot12()
{
	glWidget->light_ambient[1] = (float)slider12->value() / 10;
	glLightfv(GL_LIGHT0, GL_AMBIENT,  glWidget->light_ambient);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot13()
{
	glWidget->light_ambient[2] = (float)slider13->value() / 10;
	glLightfv(GL_LIGHT0, GL_AMBIENT,  glWidget->light_ambient);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot14()
{
	glWidget->light_diffuse[0] = (float)slider14->value() / 10;
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  glWidget->light_diffuse);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot15()
{
	glWidget->light_diffuse[1] = (float)slider15->value() / 10;
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  glWidget->light_diffuse);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot16()
{
	glWidget->light_diffuse[2] = (float)slider16->value() / 10;
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  glWidget->light_diffuse);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot17()
{
	glWidget->light_specular[0] = (float)slider17->value() / 10;
	glLightfv(GL_LIGHT0, GL_SPECULAR,  glWidget->light_specular);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot18()
{
	glWidget->light_specular[1] = (float)slider18->value() / 10;
	glLightfv(GL_LIGHT0, GL_SPECULAR,  glWidget->light_specular);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot19()
{
	glWidget->light_specular[2] = (float)slider19->value() / 10;
	glLightfv(GL_LIGHT0, GL_SPECULAR,  glWidget->light_specular);
	glWidget->updateGL();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void Project_FinalProject::mySlot21()
{
	glWidget->light_ambient1[0] = (float)slider21->value() / 10;
	glLightfv(GL_LIGHT1, GL_AMBIENT,  glWidget->light_ambient1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot22()
{
	glWidget->light_ambient1[1] = (float)slider22->value() / 10;
	glLightfv(GL_LIGHT1, GL_AMBIENT,  glWidget->light_ambient1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot23()
{
	glWidget->light_ambient1[2] = (float)slider23->value() / 10;
	glLightfv(GL_LIGHT1, GL_AMBIENT,  glWidget->light_ambient1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot24()
{
	glWidget->light_diffuse1[0] = (float)slider24->value() / 10;
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  glWidget->light_diffuse1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot25()
{
	glWidget->light_diffuse1[1] = (float)slider25->value() / 10;
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  glWidget->light_diffuse1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot26()
{
	glWidget->light_diffuse1[2] = (float)slider26->value() / 10;
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  glWidget->light_diffuse1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot27()
{
	glWidget->light_specular1[0] = (float)slider27->value() / 10;
	glLightfv(GL_LIGHT1, GL_SPECULAR,  glWidget->light_specular1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot28()
{
	glWidget->light_specular1[1] = (float)slider28->value() / 10;
	glLightfv(GL_LIGHT1, GL_SPECULAR,  glWidget->light_specular1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot29()
{
	glWidget->light_specular1[2] = (float)slider29->value() / 10;
	glLightfv(GL_LIGHT1, GL_SPECULAR,  glWidget->light_specular1);
	glWidget->updateGL();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void Project_FinalProject::mySlot31()
{
	glWidget->light_ambient2[0] = (float)slider31->value() / 10;
	glLightfv(GL_LIGHT2, GL_AMBIENT,  glWidget->light_ambient2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot32()
{
	glWidget->light_ambient2[1] = (float)slider32->value() / 10;
	glLightfv(GL_LIGHT2, GL_AMBIENT,  glWidget->light_ambient2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot33()
{
	glWidget->light_ambient2[2] = (float)slider33->value() / 10;
	glLightfv(GL_LIGHT2, GL_AMBIENT,  glWidget->light_ambient2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot34()
{
	glWidget->light_diffuse2[0] = (float)slider34->value() / 10;
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  glWidget->light_diffuse2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot35()
{
	glWidget->light_diffuse2[1] = (float)slider35->value() / 10;
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  glWidget->light_diffuse2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot36()
{
	glWidget->light_diffuse2[2] = (float)slider36->value() / 10;
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  glWidget->light_diffuse2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot37()
{
	glWidget->light_specular2[0] = (float)slider37->value() / 10;
	glLightfv(GL_LIGHT2, GL_SPECULAR,  glWidget->light_specular2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot38()
{
	glWidget->light_specular2[1] = (float)slider38->value() / 10;
	glLightfv(GL_LIGHT2, GL_SPECULAR,  glWidget->light_specular2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlot39()
{
	glWidget->light_specular2[2] = (float)slider39->value() / 10;
	glLightfv(GL_LIGHT2, GL_SPECULAR,  glWidget->light_specular2);
	glWidget->updateGL();
}

/*
void Project_FinalProject::mySlot40()
{
	//glWidget->spot_direction[0] = (float)slider40->value();
	//glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,  glWidget->spot_direction);
	glWidget->updateGL();
}
*/

void Project_FinalProject::mySlot41()
{
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, (float)slider41->value());
	glWidget->updateGL();
}


////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////
void Project_FinalProject::actionSlot_Space_ship()
{
	glWidget->loadCheckModelAndTexture("spaceship.3ds", "spaceshiptexture.bmp", BITMAP_TEXTURE);
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_action_Blend()
{
	glWidget->loadCheckModelAndTexture("a3dblend.3ds", blendModelFile[0], TGA_TEXTURE);
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_action_Air_Cyph()
{
	glWidget->loadCheckModelAndTexture("aircyph.3ds", sidemapModelFile[0], TGA_TEXTURE);
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_action_Planet_Camera()
{
	glWidget->loadCheckModelAndTexture("wfpc2.3ds", "hbltel_w.tga", TGA_TEXTURE);
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_action_Shovl()
{
	glWidget->loadCheckModelAndTexture("a3dshovl.3ds", "shovwd1.tga", TGA_TEXTURE);
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_action_Shuttle()
{
	glWidget->loadCheckModelAndTexture("shuttle.3ds", "shovwd1.tga", TGA_TEXTURE);
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_action_Zep()
{
	glWidget->loadCheckModelAndTexture("Zepplin2.3ds", "refmap.tga", TGA_TEXTURE);
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_Per_Vertex()
{
	glWidget->DestroyShaders();
	glWidget->SetupShaders("per_vertex.vert", "per_vertex.frag");
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_Per_Pixel()
{
	glWidget->DestroyShaders();
	glWidget->SetupShaders("per_pixel.vert", "per_pixel.frag");
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_Multi_Texture()
{
	glWidget->DestroyShaders();
	glWidget->SetupShaders("multi_texture.vert", "multi_texture.frag");
	glWidget->updateGL();
}


void Project_FinalProject::actionSlot_Spot_Light()
{
	glWidget->DestroyShaders();
	glWidget->SetupShaders("spot_light.vert", "spot_light.frag");
	glWidget->updateGL();
}


void Project_FinalProject::Radio_1_Slot()
{
	if(!triggeredd_flag)
	{
		glWidget->BindShader();
		glWidget->updateGL();
		triggeredd_flag = 1;
	}
}


void Project_FinalProject::Radio_2_Slot()
{
	if(triggeredd_flag)
	{
		glWidget->ReleaseShader();
		glWidget->updateGL();
		triggeredd_flag = 0;
	}
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void Project_FinalProject::mySlotL1_X()
{
	glWidget->light_position[0] = (float)sliderL1_X->value();
	glLightfv(GL_LIGHT0, GL_POSITION, glWidget->light_position);
	glWidget->updateGL();
}


void Project_FinalProject::mySlotL1_Y()
{
	glWidget->light_position[1] = (float)sliderL1_Y->value();
	glLightfv(GL_LIGHT0, GL_POSITION, glWidget->light_position);
	glWidget->updateGL();
}


void Project_FinalProject::mySlotL1_Z()
{
	glWidget->light_position[2] = (float)sliderL1_Z->value();
	glLightfv(GL_LIGHT0, GL_POSITION, glWidget->light_position);
	glWidget->updateGL();
}


///////////////////////////////////////////////
void Project_FinalProject::mySlotL2_X()
{
	glWidget->light_position1[0] = (float)sliderL2_X->value();
	glLightfv(GL_LIGHT1, GL_POSITION, glWidget->light_position1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlotL2_Y()
{
	glWidget->light_position1[1] = (float)sliderL2_Y->value();
	glLightfv(GL_LIGHT1, GL_POSITION, glWidget->light_position1);
	glWidget->updateGL();
}


void Project_FinalProject::mySlotL2_Z()
{
	glWidget->light_position1[2] = (float)sliderL2_Z->value();
	glLightfv(GL_LIGHT1, GL_POSITION, glWidget->light_position1);
	glWidget->updateGL();
}

/*
///////////////////////////////////////////////
void Project_FinalProject::mySlotM_X()
{
	glWidget->light_position2[0] = (float)sliderM_X->value();
	glLightfv(GL_LIGHT2, GL_POSITION, glWidget->light_position2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlotM_Y()
{
	glWidget->light_position2[1] = (float)sliderM_Y->value();
	glLightfv(GL_LIGHT2, GL_POSITION, glWidget->light_position2);
	glWidget->updateGL();
}


void Project_FinalProject::mySlotM_Z()
{
	glWidget->light_position2[2] = (float)sliderM_Z->value();
	glLightfv(GL_LIGHT2, GL_POSITION, glWidget->light_position2);
	glWidget->updateGL();
}
*/


void Project_FinalProject::actionSlot_About()
{
	char *readAboutText;
	readAboutText = textFileRead("about_info.txt");
	QMessageBox::information(NULL, "About",  readAboutText, QMessageBox::Ok, QMessageBox::Ok);
}


void Project_FinalProject::actionSlot_Help()
{
	char *readHelpText_1;
	readHelpText_1 = textFileRead("help_info_1.txt");
	char *readHelpText_2;
	readHelpText_2 = textFileRead("help_info_2.txt");
	char *readHelpText_3;
	readHelpText_3 = textFileRead("help_info_3.txt");
	QMessageBox::information(NULL, "Info_1",  readHelpText_1, QMessageBox::Ok, QMessageBox::Ok);
	QMessageBox::information(NULL, "Info_2",  readHelpText_2, QMessageBox::Ok, QMessageBox::Ok);
	QMessageBox::information(NULL, "Info_3",  readHelpText_3, QMessageBox::Ok, QMessageBox::Ok);
}


void Project_FinalProject::actionSlot_Exit()
{
	close();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void Project_FinalProject::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}