/******************************************************************************/
/*!
\file	Assignment02.cpp
\author Team NoticeMeSenpai
\brief
Set up and Build model keroro 
*/
/******************************************************************************/
#include "Scene_SuperMarket.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "GLFW\glfw3.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Light.h"
#include "Utility.h"
#include "MyMath.h"
#include "LoadTGA.h"

/******************************************************************************/
/*!
\brief
Default constructor - initialise variables 
*/
/******************************************************************************/
Scene_SuperMarket::Scene_SuperMarket()
{

}


/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Scene_SuperMarket::~Scene_SuperMarket()
{
}

/******************************************************************************/
/*!
\brief
Initialise OPENGL or variables
*/
/******************************************************************************/
void Scene_SuperMarket::Init()
{
    // Init VBO here
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //Enable depth buffer and depth testing
    glEnable(GL_DEPTH_TEST);

    //Enable back face culling
    glEnable(GL_CULL_FACE);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Default to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //Load vertex and fragment shaders
    m_programID = LoadShaders("Shader//Texture.vertexshader","Shader//Blending.fragmentshader" );
    m_parameters[U_MVP] = glGetUniformLocation(m_programID,"MVP");
    m_parameters[U_SCENEVIEW] = glGetUniformLocation(m_programID,"MV");
    m_parameters[U_SCENEVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
    m_parameters[U_MATERIAL_AMBIENT] =  glGetUniformLocation(m_programID, "material.kAmbient");
    m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
    m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
    m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
    m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
    m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID,"lights[0].color");
    m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID,"lights[0].power");
    m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID,"lights[0].kC");
    m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID,"lights[0].kL");
    m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID,"lights[0].kQ");
    m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID,"lightEnabled");

    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
    m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
    m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
    m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
    m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
    m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Use our shader
    glUseProgram(m_programID);

    // Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

    //Number of lights in Shader
    glUniform1i(m_parameters[U_NUMLIGHTS], 1);

    light[0].type = Light::LIGHT_POINT;
    light[0].position.Set(0,20,0);
    light[0].color.Set(1,1,0);
    light[0].power = 10;   //light is strong if increase 
    light[0].kC = 1.0f;
    light[0].kL = 0.1f;     //light is weak if increase
    light[0].kQ = 0.001f;     //distance of the lightball will affect the light, lesser num, long distance will be no problem
    light[0].cosCutoff = cos(Math::DegreeToRadian(45));
    light[0].cosInner = cos(Math::DegreeToRadian(35));
    light[0].exponent = 10.f;
    light[0].spotDirection.Set(0.f, 1.f, 0.f);

    glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
    glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
    glUniform1f(m_parameters[U_LIGHT0_KC] , light[0].kC);
    glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
    glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
    glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
    glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
    glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
    for(unsigned i = 0; i < NUM_GEOMETRY; ++i)
        meshList[i] = NULL;

    //Initialize camera settings
    camera.Init(Vector3(80, 60, 60), Vector3(10, 0, -10), Vector3(0, 1, 0));

    //Initialize all meshes here
    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", Color(0.65f,0.50f,0.39f), 1000, 1000, 1000);

    meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0.25f, 1.0f, 0.25f), 1.f);

    meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//MineCraftText.tga");
    glGenerateMipmap(GL_TEXTURE_2D);
   
    Mtx44 projection;
    projection.SetToPerspective(45.f, 4.f / 3.f , 0.1f, 1000.f);
    projectionStack.LoadMatrix(projection);
}

/******************************************************************************/
/*!
\brief
Update screen

\param dt - time
*/
/******************************************************************************/
void Scene_SuperMarket::Update(double dt)
{
    if(Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if(Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if(Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if(Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
    
    if(Application::IsKeyPressed('L'))
    {
        light[0].position.z -= (float)(10 * dt);
    }
    if(Application::IsKeyPressed('J'))
    {
        light[0].position.z += (float)(10 * dt);
    }
    if(Application::IsKeyPressed('I'))
    {
        light[0].position.x -= (float)(10 * dt);
    }
    if(Application::IsKeyPressed('K'))
    {
        light[0].position.x += (float)(10 * dt);
    }
    if(Application::IsKeyPressed('O'))
    {
        light[0].position.y -= (float)(10 * dt);
    }
    if(Application::IsKeyPressed('P'))
    {
        light[0].position.y += (float)(10 * dt);
    }

    camera.Update(dt);

    deltaTime = static_cast<float>(dt);
}

/******************************************************************************/
/*!
\brief
Render mesh code

\param mesh
\param enableLight - turn on or off lightning on the object
*/
/******************************************************************************/
void Scene_SuperMarket::RenderMesh(Mesh *mesh, bool enableLight)
{
    Mtx44 MVP, objView, objView_inverse_transpose;

    MVP = projectionStack.Top() * viewStack.Top() * sceneStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

    if(enableLight)
    {
        glUniform1i(m_parameters[U_LIGHTENABLED], 1);
        objView = viewStack.Top() * sceneStack.Top();
        glUniformMatrix4fv(m_parameters[U_SCENEVIEW], 1, GL_FALSE, &objView.a[0]);
        objView_inverse_transpose = objView.GetInverse().GetTranspose();
        glUniformMatrix4fv(m_parameters[U_SCENEVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &objView_inverse_transpose.a[0]);

        //load material
        glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
        glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
        glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
        glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
    }
    else
    {	
        glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    }

    if(mesh->textureID > 0)
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
        glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    }

    else
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
    }

    mesh->Render();

    if(mesh->textureID > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

/******************************************************************************/
/*!
\brief
Render text in 3D world

\param mesh
    mesh list

\param text
    text to be render on the screen

\param color
    color of the text
*/
/******************************************************************************/
void Scene_SuperMarket::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;
	
	glDisable(GL_DEPTH_TEST);

    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

    float offset = 0;

	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
        characterSpacing.SetToTranslation(i * 0.55f, 0, 0); //1.0f is the spacing of each character, you may change this value
        Mtx44 MVP = projectionStack.Top() * viewStack.Top() * sceneStack.Top() * characterSpacing;
	    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

/******************************************************************************/
/*!
\brief
Render text on screen

\param mesh
    mesh list

\param text
    text to be render on the screen

\param color
    color of the text

\param size 
    size of the text

\param x
    x position of the text

\param y
    y position of the text
*/
/******************************************************************************/
void Scene_SuperMarket::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
    if(!mesh || mesh->textureID <= 0) //Proper error check
		return;
	
	glDisable(GL_DEPTH_TEST);

    //Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	sceneStack.PushMatrix();
	sceneStack.LoadIdentity(); //Reset modelStack
	sceneStack.Scale(size, size, size);
	sceneStack.Translate(x, y, 0);

    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.55f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * sceneStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}

    sceneStack.PopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

    projectionStack.PopMatrix();
	viewStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

/******************************************************************************/
/*!
\brief
convert float number to string, and then round off

\param number
    take in float value
*/
/******************************************************************************/

string Convert (float number){
    std::ostringstream buff;
    buff << setprecision(0) << fixed << number;
    return buff.str(); 
}

/******************************************************************************/
/*!
\brief
checking for direction and then return string

\param n
    take in camera north value

\param e
    take in camera east value
*/
/******************************************************************************/
string direction(int n, int e)
{
    if (n == 0)
    {
        return "North (Towards negative Z)";
    }

    else if(e == 0)
    {
        return "East (Towards positive X)";
    }
    else if (n == 1)
    {
        return "South (Towards positive Z)";
    }
    else if(e == 1)
    {
        return "West (Towards negative X)";
    }

    else
    {
        return "meh";
    }
}

/******************************************************************************/
/*!
\brief
render all obj or models here
*/
/******************************************************************************/
void Scene_SuperMarket::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    viewStack.LoadIdentity();
    viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);

    if(light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}

	else if(light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}

	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

    sceneStack.LoadIdentity();

    sceneStack.PushMatrix();
    RenderMesh(meshList[GEO_AXES], false);
    sceneStack.PopMatrix();

    sceneStack.PushMatrix();
    sceneStack.Scale(5, 5, 5);
    RenderMesh(meshList[GEO_QUAD], true);
    sceneStack.PopMatrix();

    // FPS
    RenderTextOnScreen(meshList[GEO_TEXT], Convert(1/deltaTime)+" fps", Color(1, 1, 1), 2, 2, 27);
    
    // coordinate
    RenderTextOnScreen(meshList[GEO_TEXT], "XYZ:"+ Convert(camera.position.x) + " / " + Convert(camera.position.y) +" / " + Convert(camera.position.z ), Color(1, 0,0), 2, 2, 25);

    // facing
    RenderTextOnScreen(meshList[GEO_TEXT], "Facing: " + direction(camera.NORTH(camera.north), camera.EAST(camera.east)) + " (" + Convert(camera.yaw) + "/" + Convert(camera.pitch) + ")", Color(1, 0, 0), 2, 2, 23);
}

/******************************************************************************/
/*!
\brief
Delete buffers
*/
/******************************************************************************/
void Scene_SuperMarket::Exit()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}