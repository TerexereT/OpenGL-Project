#include "EDClientpch.h"

#include "../imGuIZMO.quat/imGuIZMOquat.h"
#include "EasyDIPAPI/Loaders.h"



#ifndef __ED_CLIENT_APPLICATION__
#define __ED_CLIENT_APPLICATION__

class Application
{
	
	float test = 0;
	//template <typename TT> using ptr = std::shared_ptr<TT>;
	//ImGui::FileBrowser fileDialog;
	GLFWwindow *window;

	unsigned int texId = 0;
	unsigned int texOGImg = 0;

	int picked = -1;
	int totalmodels = 0;
	int windowWidth = 1920;		//1280,1920
	int windowHeight = 1080;	//720,1080
	int widthConv = 1;
	int heightConv = 1;
	int pivotX = 0, pivotY = 0;
	int projectionActual = PERSPECTIVE;

	float color[7][7][4];
	float colorFondo[3] = { 0.1f,0.1f,0.1f };
	float colorPoint[3] = { 0.0f,0.0f,1.0f};
	float colorLine[3] = { 1.0f,0.0f,0.0f };
	float NCP = 0.1f;

	bool show_demo_window = true;
	bool shownormalsF = false, shownormalsV = false, showBBox = false, showlights = false, backFace = false, zBuffer = true, actP = false, actL = false, actT = false;

	vector <CModel*> models;
	Shader* shader;


	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::quat rot;


	//typeShading shadeactual = FLAT; //Para tarea 4

public:
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

	void Application::setModelRotate(glm::vec3 quaternion);
	glm::vec3 Application::getModelRotate();
	
	static void HelpMarker(const char* desc);

};

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
#endif // !1

