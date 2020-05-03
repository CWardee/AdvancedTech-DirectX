////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "inputclass.h"



/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);



	void Shutdown();
	bool Update();
	int level1[99] = { 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
					   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
					   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };


	void InitialiseModels(ModelClass input);

private:
	bool Render(float, float, float, float, float, float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* Model_Player;
	ModelClass* Model_Door;
	ModelClass* Model_Button;
	ModelClass* Model_MoveableCube;
	ModelClass* Model_Terrain[99];
	int MaxTerrainCubes = 91;
	ModelClass* Model_Mud_Terrain[99];
	int MaxMudTerrainCubes = 91;
	ModelClass* Model_Pickup[99];
	int MaxPickups = 6;
	//ModelClass* m_Model;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	
	float counter = 0;
	InputClass* m_Input;


};

static GraphicsClass* Test = 0;


#endif