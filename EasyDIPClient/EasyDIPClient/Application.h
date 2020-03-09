#include "EDClientpch.h"

#include "../imGuIZMO.quat/imGuIZMOquat.h"
#include "EasyDIPAPI/Loaders.h"
#include "../Camera.h"



#ifndef __ED_CLIENT_APPLICATION__
#define __ED_CLIENT_APPLICATION__

class Application
{
public:
	float test = 0;
	//template <typename TT> using ptr = std::shared_ptr<TT>;
	//ImGui::FileBrowser fileDialog;
	GLFWwindow *window;
	Camera *camara = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));

	unsigned int texId = 0;
	unsigned int texOGImg = 0;

	int picked = -1;
	int modelsCount = -1;
	int totalmodels = 0;
	int windowWidth = 1920;		//1280,1920
	int windowHeight = 1080;	//720,1080
	int widthConv = 1;
	int heightConv = 1;
	int pivotX = 0, pivotY = 0;
	int projectionActual = PERSPECTIVE;

	float color[7][7][4];
	float colorFondo[3] = { 0.01f,0.01f,0.01f };
	float colorPoint[3] = { 0.0f,0.0f,1.0f};
	float colorLine[3] = { 1.0f,0.0f,0.0f };
	float NCP = 0.1f;
	float lastX = windowWidth/2.0f, lastY = windowHeight/2.0f;

	bool show_demo_window = true;
	bool shownormalsF = false, shownormalsV = false, showBBox = false, showlights = false, backFace = false, zBuffer = true, lightSwitch = false, Navigate = false, firstMouse = true;

	vector <CModel*> models;
	vector <CModel*> lights;
	Shader* shader;
	Shader* shaderL;


	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::quat rot;

	glm::vec4 lightambient = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec4 lightdiffuse = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec4 lightspecular = { 1.0, 1.0, 1.0, 1.0 };
	glm::vec3 lightposition1 = { 2.0, -2.0, 5.0};
	glm::vec3 lightposition2 = { -2.0, 2.0, -7.0};

	//typeShading shadeactual = FLAT; //Para tarea 4


	Application();
	~Application();
	
	void MainLoop();
	void Render();
	void ImGui();
	void Init();

	void Application::setModelTranslation(glm::vec3 modelTranslation);
	glm::vec3 Application::getModelTranslation();

	void Application::setModelScale(glm::vec4 modelScale);
	glm::vec4 Application::getModelScale();

	void Application::setModelRotate(glm::quat quaternion);
	glm::quat Application::getModelRotate();

	void initLights();
	void initScene();
	
	static void HelpMarker(const char* desc);

};

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
#endif // !1

