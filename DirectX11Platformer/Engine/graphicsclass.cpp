////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "inputclass.h"
#include "levelSetup.h"
#include <xnamath.h>



GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;

	for (int x = 0; x < MaxTerrainCubes; x++)
	{
		Model_Terrain[x] = 0;
	}

	for (int x = 0; x < MaxPickups; x++)
	{
		Model_Pickup[x] = 0;
	}

	m_LightShader = 0;
	m_Light = 0;
	m_Input = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{

	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}



	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);


	// Create the model object.
	Model_Player = new ModelClass;
	if (!Model_Player)
	{
		return false;
	}

	// Initialize the model object.
	result = Model_Player->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/dev.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	Model_MoveableCube = new ModelClass;
	if (!Model_Player)
	{
		return false;
	}

	Model_MoveableCube->SetPositionZ(2);
	Model_MoveableCube->SetPositionX(5);
	// Initialize the model object.
	result = Model_MoveableCube->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/dev.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	// Create the model object.
	Model_Door = new ModelClass;
	if (!Model_Door)
	{
		return false;
	}

	Model_Door->SetPositionZ(2);
	Model_Door->SetPositionY(-4);
	Model_Door->SetPositionX(16);

	// Initialize the model object.
	result = Model_Door->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/dev.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}



	// Create the model object.
	Model_Button = new ModelClass;
	if (!Model_Player)
	{
		return false;
	}

	Model_Button->SetPositionZ(2);
	Model_Button->SetPositionY(-5.8);
	Model_Button->SetPositionX(12);
	// Initialize the model object.
	result = Model_Button->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/dev.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}



	for (int x = 0; x < MaxTerrainCubes; x++)
	{
		// Create the model object.
		Model_Terrain[x] = new ModelClass;
		if (!Model_Terrain[x])
		{
			return false;
		}

		// Initialize the model object.
		result = Model_Terrain[x]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/mud.png");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}

		// Create the model object.
		Model_Mud_Terrain[x] = new ModelClass;
		if (!Model_Mud_Terrain[x])
		{
			return false;
		}

		// Initialize the model object.
		result = Model_Mud_Terrain[x]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/grass.png");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}


	for (int x = 0; x < MaxPickups; x++)
	{
		// Create the model object.
		Model_Pickup[x] = new ModelClass;
		if (!Model_Pickup[x])
		{
			return false;
		}

		Model_Pickup[x]->SetScale(0.5);

		// Initialize the model object.
		result = Model_Pickup[x]->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/dev.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
	}


	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.3f, 0.3f, 0.3f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, -0.3f, 4.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if (Model_Player)
	{
		Model_Player->Shutdown();
		delete Model_Player;
		Model_Player = 0;
	}

	for (int x = 0; x < MaxTerrainCubes; x++)
	{
		// Release the model object.
		if (Model_Terrain[x])
		{
			Model_Terrain[x]->Shutdown();
			delete Model_Terrain[x];
			Model_Terrain[x] = 0;
		}

		// Release the model object.
		if (Model_Mud_Terrain[x])
		{
			Model_Mud_Terrain[x]->Shutdown();
			delete Model_Mud_Terrain[x];
			Model_Mud_Terrain[x] = 0;
		}
	}

	for (int x = 0; x < MaxPickups; x++)
	{
		// Release the model object.
		if (Model_Pickup[x])
		{
			Model_Pickup[x]->Shutdown();
			delete Model_Pickup[x];
			Model_Pickup[x] = 0;
		}
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool BoundingBoxCollision(XMVECTOR& firstObjBoundingBoxMinVertex,
	XMVECTOR& firstObjBoundingBoxMaxVertex,
	XMVECTOR& secondObjBoundingBoxMinVertex,
	XMVECTOR& secondObjBoundingBoxMaxVertex)
{
	//Is obj1's max X greater than obj2's min X? If not, obj1 is to the LEFT of obj2
	if (XMVectorGetX(firstObjBoundingBoxMaxVertex) > XMVectorGetX(secondObjBoundingBoxMinVertex))

		//Is obj1's min X less than obj2's max X? If not, obj1 is to the RIGHT of obj2
		if (XMVectorGetX(firstObjBoundingBoxMinVertex) < XMVectorGetX(secondObjBoundingBoxMaxVertex))

			//Is obj1's max Y greater than obj2's min Y? If not, obj1 is UNDER obj2
			if (XMVectorGetY(firstObjBoundingBoxMaxVertex) > XMVectorGetY(secondObjBoundingBoxMinVertex))

				//Is obj1's min Y less than obj2's max Y? If not, obj1 is ABOVE obj2
				if (XMVectorGetY(firstObjBoundingBoxMinVertex) < XMVectorGetY(secondObjBoundingBoxMaxVertex))

					//Is obj1's max Z greater than obj2's min Z? If not, obj1 is IN FRONT OF obj2
					if (XMVectorGetZ(firstObjBoundingBoxMaxVertex) > XMVectorGetZ(secondObjBoundingBoxMinVertex))

						//Is obj1's min Z less than obj2's max Z? If not, obj1 is BEHIND obj2
						if (XMVectorGetZ(firstObjBoundingBoxMinVertex) < XMVectorGetZ(secondObjBoundingBoxMaxVertex))

							//If we've made it this far, then the two bounding boxes are colliding
							return true;

	//If the two bounding boxes are not colliding, then return false
	return false;
}

bool CollisionCheck(ModelClass* input1, ModelClass* input2)
{
	//left
	if (input1->GetPositionX() > input2->GetPositionX() + 2.0f && input2->visible)
	{
		return false;
	}

	if (input1->GetPositionX() + 2.0f < input2->GetPositionX() && input2->visible)
	{
		return false;
	}

	if (input1->GetPositionY() > input2->GetPositionY() + 2.0f && input2->visible)
	{
		return false;
	}

	if (input1->GetPositionY() + 2.0f < input2->GetPositionY() && input2->visible)
	{
		return false;
	}


	return true;
}


bool checkCollisionXAxis(ModelClass* input1, ModelClass* input2)
{
	if (input2->visible)
	{
		if (input1->GetPositionY() + 1.5f > input2->GetPositionY() && input1->GetPositionY() + 1.5f < input2->GetPositionY() + 1.8f)
		{
			if (input1->GetPositionX() + 2.0f > input2->GetPositionX())
			{
				return true;
			}

			else if (input1->GetPositionX() < input2->GetPositionX() + 2.0f)
			{
				return true;
			}

			else
			{
				return false;
			}
		}

		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
}


bool IsRightSideBlocked(ModelClass* input1, ModelClass* input2)
{
	float player_Ypos = input1->GetPositionY();
	float terrain_Ypos = input2->GetPositionY();
	int player_Xpos = input1->GetPositionX();
	int terrain_Xpos = input2->GetPositionX();

	if (input2->visible == true)
	{
		if (player_Ypos + 1.0f < terrain_Ypos + 2.0f)
		{
			if (player_Xpos + 2 > terrain_Xpos)
			{
				return true;
			}
		}
	}

	else
	{
		return false;
	}
}

void CheckCollisionWithTerrain()
{

}



bool GraphicsClass::Update()
{
	bool result;
	static float rotation = 0.0f;
	static float bounce = 0.0f;

	static float cameraYpos = 1.5f;
	static float cameraXpos = -8.0f;
	static float cameraZpos = -15.0f;
	static float cameraRotation = 0.0f;

			static bool isPlayerJumping{};
		int maxCounter = 45;
		static int jumpCounter = 0;

	if (Model_Player->GetPositionY() < -12)
	{
		cameraYpos = 1.5f;
		cameraXpos = -8.0f;
	}

	Model_Player->SetPositionX(cameraXpos);
	Model_Player->SetPositionY(cameraYpos + -3.0f);


	static bool isGrounded;
	for (int x = 0; x < MaxTerrainCubes; x++)
	{
		if (CollisionCheck(Model_Player, Model_Terrain[x]) == true && Model_Terrain[x]->visible == true 
			|| CollisionCheck(Model_Player, Model_MoveableCube) == true && Model_MoveableCube->visible == true)
		{
			isGrounded = true;
			break;
		}


		else
		{
			isGrounded = false;
		}
	}

	if (!isGrounded)
	{
		cameraYpos += -0.1;
	}


	float JumpSpeet = 0.2f;
	if (isPlayerJumping)
	{
		jumpCounter++;
		if (jumpCounter < maxCounter)
		{
			cameraYpos = cameraYpos += JumpSpeet;
			JumpSpeet += -0.05f;
			Model_Player->SetPositionY(cameraYpos);
		}

		//else if(isGrounded == true && jumpCounter > maxCounter * 2)
		//{
		//	jumpCounter = 0;
		//	isPlayerJumping = false;
		//}
	}


	if (isGrounded == true && GetKeyState('Q') & 0x8000)
	{
		jumpCounter = 0;
		isPlayerJumping = true;
	}


	isGrounded;
	for (int x = 0; x < MaxTerrainCubes; x++)
	{
		if (CollisionCheck(Model_MoveableCube, Model_Terrain[x]) == true && Model_Terrain[x]->visible == true)
		{
			isGrounded = true;
			break;
		}

		else
		{
			isGrounded = false;
		}
	}

	if (!isGrounded)
	{
		float height = Model_MoveableCube->GetPositionY();
		height += -0.1;
		Model_MoveableCube->SetPositionY(height);
	}

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.001f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	//bounce cube
	if (counter > 30.0f)
	{
		bounce += (float)D3DX_PI * 0.003f;
		if (counter > 60.0f)
		{
			counter = 0.0f;
		}
		counter++;
	}

	else
	{
		counter++;
		bounce += (float)D3DX_PI * -0.003f;
	}

	float x = 0;
	float y = 0;
	float b = 0;

	bool isBlocked{};
	bool isBlockedRight{};
	bool isBlockedLeft{};

	bool isCubeBlockedRight{};
	bool isCubeBlockedLeft{};
	bool isCubeRight{};
	bool isCubeLeft{};

	for (int x = 0; x < MaxTerrainCubes; x++)
	{
		if (Model_Terrain[x]->visible)
		{
			if (checkCollisionXAxis(Model_Player, Model_Terrain[x]) == true)
			{
				isBlocked = true;
			}

			else
			{
				isBlocked = false;
			}
		}
	}

	if (Model_Door->visible == true
		&& Model_MoveableCube->GetPositionX() < Model_Button->GetPositionX() + 2.0f
		&& Model_MoveableCube->GetPositionX() > Model_Button->GetPositionX()
		&& Model_MoveableCube->GetPositionY() + 0.5f < Model_Button->GetPositionY() + 4.0f
		&& Model_MoveableCube->GetPositionY() + 0.5f > Model_Button->GetPositionY())
	{
		Model_Door->visible = false;
	}


		//terrain ground
		for (int x = 0; x < MaxTerrainCubes; x++)
		{

			if (Model_Terrain[x]->visible == true
				&& Model_MoveableCube->GetPositionX() < Model_Terrain[x]->GetPositionX() + 2.0f
				&& Model_MoveableCube->GetPositionX() > Model_Terrain[x]->GetPositionX()
				&& Model_MoveableCube->GetPositionY() + 0.5f < Model_Terrain[x]->GetPositionY() + 2.0f
				&& Model_MoveableCube->GetPositionY() + 0.5f > Model_Terrain[x]->GetPositionY())
			{
				isCubeBlockedLeft = true;
				break;
			}

			else
			{
				isCubeBlockedLeft = false;
			}

			if (Model_Terrain[x]->visible == true
				&& Model_MoveableCube->GetPositionX() + 2.0f > Model_Terrain[x]->GetPositionX()
				&& Model_MoveableCube->GetPositionX() + 2.0f < Model_Terrain[x]->GetPositionX() + 2.0f
				&& Model_MoveableCube->GetPositionY() + 0.5f < Model_Terrain[x]->GetPositionY() + 2.0f
				&& Model_MoveableCube->GetPositionY() + 0.5f > Model_Terrain[x]->GetPositionY())
			{
				isCubeBlockedRight = true;
				break;
			}

			else
			{
				isCubeBlockedRight = false;
			}
		}


		//terrain ground
		for (int x = 0; x < MaxTerrainCubes; x++)
		{
			if ( Model_Terrain[x]->visible == true 
				&&Model_Player->GetPositionX() < Model_Terrain[x]->GetPositionX() + 2.0f 
				&& Model_Player->GetPositionX() > Model_Terrain[x]->GetPositionX()
				&& Model_Player->GetPositionY() + 0.5f < Model_Terrain[x]->GetPositionY() + 2.0f 
				&& Model_Player->GetPositionY() + 0.5f > Model_Terrain[x]->GetPositionY())
			{
				isBlockedLeft = true;
				break;
			}

			else
			{
				isBlockedLeft = false;
			}

			if (Model_Terrain[x]->visible == true
				&& Model_Player->GetPositionX() + 2.0f > Model_Terrain[x]->GetPositionX()
				&& Model_Player->GetPositionX() + 2.0f < Model_Terrain[x]->GetPositionX() + 2.0f
				&& Model_Player->GetPositionY() + 0.5f < Model_Terrain[x]->GetPositionY() + 2.0f
				&& Model_Player->GetPositionY() + 0.5f > Model_Terrain[x]->GetPositionY())
			{
				isBlockedRight = true;
				break;
			}

			else
			{
				isBlockedRight = false;
			}
		}



		//moveable cube
		if (Model_MoveableCube->visible == true
			&& Model_Player->GetPositionX() < Model_MoveableCube->GetPositionX() + 2.0f
			&& Model_Player->GetPositionX() > Model_MoveableCube->GetPositionX()
			&& Model_Player->GetPositionY() + 0.5f < Model_MoveableCube->GetPositionY() + 2.0f
			&& Model_Player->GetPositionY() + 0.5f > Model_MoveableCube->GetPositionY())
		{
			isCubeLeft = true;
		}

		else
		{
			isCubeLeft = false;
		}

		if (Model_MoveableCube->visible == true
			&& Model_Player->GetPositionX() + 2.0f > Model_MoveableCube->GetPositionX()
			&& Model_Player->GetPositionX() + 2.0f < Model_MoveableCube->GetPositionX() + 2.0f
			&& Model_Player->GetPositionY() + 0.5f < Model_MoveableCube->GetPositionY() + 2.0f
			&& Model_Player->GetPositionY() + 0.5f > Model_MoveableCube->GetPositionY())
		{
			isCubeRight = true;
		}

		else
		{
			isCubeRight = false;
		}
	

	for (int x = 0; x < MaxPickups; x++)
	{
		if (CollisionCheck(Model_Player, Model_Pickup[x]) == true && Model_Pickup[x]->visible == true)
		{
			Model_Pickup[x]->visible = false;
			break;
		}
	}


		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			if (!isBlockedLeft)
			{

				if (isCubeLeft && !isCubeBlockedLeft || !isCubeLeft)
				{
					cameraXpos = cameraXpos -= 0.1f;
				}

				if (isCubeLeft && !isCubeBlockedLeft)
				{
					float cubePos = Model_MoveableCube->GetPositionX();
					cubePos -= 0.1;
					Model_MoveableCube->SetPositionX(cubePos);
				}
			}		
		}

		if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			if (!isBlockedRight)
			{
				if (isCubeRight && !isCubeBlockedRight || !isCubeRight)
				{
					cameraXpos = cameraXpos += 0.1f;
				}


				if (isCubeRight && !isCubeBlockedRight)
				{
					float cubePos = Model_MoveableCube->GetPositionX();
					cubePos += 0.1;
					Model_MoveableCube->SetPositionX(cubePos);
				}
			}
		}

	if (GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
	{
		cameraZpos++;
	}

	if (GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
	{
		cameraZpos--;
	}

	// Render the graphics scene.
	result = Render(rotation, bounce, cameraXpos, cameraZpos, cameraYpos, cameraRotation);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render(float rotation, float bounce, float cameraXpos, float cameraZpos, float cameraYpos, float cameraRotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix, scaleMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.2f, 0.5f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	m_Camera->SetPosition(cameraXpos, cameraYpos, cameraZpos);
	m_Camera->SetRotation(0, cameraRotation, 0);

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	Model_Player->Render(m_D3D->GetDeviceContext());

	// Setup the rotation and translation of the second model.
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixRotationY(&worldMatrix, 0);
	D3DXMatrixTranslation(&translateMatrix, cameraXpos, cameraYpos + -3.0f, 2);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), Model_Player->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		Model_Player->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	Model_Door->Render(m_D3D->GetDeviceContext());

	// Setup the rotation and translation of the second model.
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixRotationY(&worldMatrix, 0);
	D3DXMatrixTranslation(&translateMatrix, Model_Door->GetPositionX(), Model_Door->GetPositionY(), Model_Door->GetPositionZ());
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

	if (Model_Door->visible)
	{
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), Model_Door->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			Model_Door->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	}

	//render cube
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	Model_MoveableCube->Render(m_D3D->GetDeviceContext());

	// Setup the rotation and translation of the second model.
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixRotationY(&worldMatrix, 0);
	D3DXMatrixTranslation(&translateMatrix, Model_MoveableCube->GetPositionX(), Model_MoveableCube->GetPositionY(), Model_MoveableCube->GetPositionZ());
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), Model_MoveableCube->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		Model_MoveableCube->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());


	//render cube
// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	Model_Button->Render(m_D3D->GetDeviceContext());

	// Setup the rotation and translation of the second model.
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixRotationY(&worldMatrix, 0);
	D3DXMatrixTranslation(&translateMatrix, Model_Button->GetPositionX(), Model_Button->GetPositionY(), Model_Button->GetPositionZ());
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), Model_Button->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		Model_Button->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());


	int y = -4;
	for (int x = 0; x < MaxTerrainCubes; x++)
	{
		if (x == 30 || x == 60)
		{
			y = -4;
			Model_Terrain[x]->SetPositionY(-4.0f);
		}

		if (level1[x] == 1)
		{
			Model_Terrain[x]->visible = true;
		}

		else if (level1[x] == 0)
		{
			Model_Terrain[x]->visible = false;
		}

		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		Model_Terrain[x]->Render(m_D3D->GetDeviceContext());

		// Setup the rotation and translation of the second model.
		m_D3D->GetWorldMatrix(worldMatrix);
		D3DXMatrixRotationY(&worldMatrix, 0);


		D3DXMatrixTranslation(&translateMatrix, 2 * y, -6.0f, 2.0f);
		Model_Terrain[x]->SetPositionX(2 * y);
		Model_Terrain[x]->SetPositionY(-6.0f);

		if (x == 30 || x > 30)
		{
			D3DXMatrixTranslation(&translateMatrix, 2 * y, -8.0f, 2.0f);
			Model_Terrain[x]->SetPositionY(-8.0f);
		}

		if (x == 60 || x > 60)
		{
			D3DXMatrixTranslation(&translateMatrix, 2 * y, -10.0f, 2.0f);
			Model_Terrain[x]->SetPositionY(-10.0f);
		}

		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

		/*
				if (x == 5 || x == 4 || x == 8 || x == 12 || x == 16 || x == 17 || x == 18)
		{
			m_D3D->GetWorldMatrix(worldMatrix);
			D3DXMatrixRotationY(&worldMatrix, 0);
			D3DXMatrixTranslation(&translateMatrix, 2 * y, -6.0f, 0.0f);
			D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		}
		*/

		y++;
		if (Model_Terrain[x]->visible)
		{
			// Render the model using the light shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), Model_Terrain[x]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				Model_Terrain[x]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
		}
	}

	y = -0.4;
	for (int x = 0; x < MaxPickups; x++)
	{
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		Model_Pickup[x]->Render(m_D3D->GetDeviceContext());

		// Setup the rotation and translation of the second model.
		m_D3D->GetWorldMatrix(worldMatrix);
		D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&translateMatrix, 8 * y, -2.0f + bounce, 2.0f);

		Model_Pickup[x]->SetPositionX(8 * y);

		D3DXMatrixScaling(&scaleMatrix, Model_Pickup[x]->GetScale(), Model_Pickup[x]->GetScale(), Model_Pickup[x]->GetScale());
		D3DXMatrixMultiply(&worldMatrix, &scaleMatrix, &translateMatrix);
		y++;

		if (Model_Pickup[x]->visible)
		{
			// Render the model using the light shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), Model_Pickup[x]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				Model_Pickup[x]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
		}
	}

	for (int x = 0; x < MaxPickups; x++)
	{
		if (Model_Player->GetPositionX() == Model_Pickup[x]->GetPositionX())
		{
			Model_Pickup[x]->visible = false;
		}
	}

	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
