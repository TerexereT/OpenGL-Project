#include "Application.h"


//#include <EasyDIPAPI\Loaders.cpp>





//extern Shader* bwShader;

Application::Application() {

	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		__debugbreak();
		return;
	}

	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	 window = glfwCreateWindow(windowWidth, windowHeight, "Despliegue 3D - Armando Rivas", NULL, NULL);
	 if (window == NULL) {
		__debugbreak();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync


	bool err = gladLoadGL() == 0;

	printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		__debugbreak();
		return;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);







	//CG::Model model = CG::Load("../Models/modelo.obj", );
	//models.push_back(model);
	//	Scene.LoadModel("pelota.obj")

	//	Scene.add("pelota");

	//Scene.Save("escena_de_prueba");
	//Scene.Load("escena_de_prueba.graficas");
	//
	//void Scene::Load(std::string path) {
	//	LoadScene(path);
	//}

	// (optional) set browser properties
	//fileDialog.SetTitle("title");
	//fileDialog.SetTypeFilters({ ".jpg", ".png", ".jpeg" });
	Init();
}

Application::~Application() {

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	//delete img;
	//delete composite;
	//delete bw;
}

void Application::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		//Cambiar color de fondo
		glClearColor(colorFondo[0], colorFondo[1], colorFondo[2],1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		//if (show_demo_window)
			//ImGui::ShowDemoWindow(&show_demo_window);

		ImGui();

		// Rendering
		ImGui::Render();
		Render();


		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}
}

void Application::Render()
{
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f));
	shader->setMat4("proj", proj);
	shader->setMat4("view", view);

	if(picked!=-1)
	{

		for (int i = 0; i <= picked; i++)
		{
			CModel* modelo = models[i];
			modelo->Bind();
			glm::mat4 modl = modelo->getMatModel();// = glm::mat4(1.0f);
			shader->setMat4("modl", modl);
			
			shader->setFloat("mColorR", colorPoint[0]);
			shader->setFloat("mColorG", colorPoint[1]);
			shader->setFloat("mColorB", colorPoint[2]);
			modelo->DrawP();
			
			shader->setFloat("mColorR", colorLine[0]);
			shader->setFloat("mColorG", colorLine[1]);
			shader->setFloat("mColorB", colorLine[2]);
			modelo->DrawL();
			
			float* modelColor = modelo->getMColor();
			shader->setFloat("mColorR", modelColor[0]);
			shader->setFloat("mColorG", modelColor[1]);
			shader->setFloat("mColorB", modelColor[2]);
			modelo->DrawT();
		
		}

	}
	if (lightSwitch)
	{
		for (int i = 0; i <= 1; i++)
		{
			CModel* luz = lights[i];
			luz->Bind();
			glm::mat4 modl = luz->getMatModel();// = glm::mat4(1.0f);
			shader->setMat4("modl", modl);
			float* modelColor = luz->getMColor();
			shader->setFloat("mColorR", modelColor[0]);
			shader->setFloat("mColorG", modelColor[1]);
			shader->setFloat("mColorB", modelColor[2]);
			luz->DrawT();

		}
	}

	shader->use();
	
	/*Quad *quad = Quad::Instance();
	if (bwShader) {
		bwShader->use();
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, texId);
		bwShader->setInt("tex", 0);
		bwShader->setFloat("test", test);
		quad->Bind();
		quad->Draw();

	}*/

}

void Application::ImGui()
{
	/*
	Multicomponents para slider float3
	PopUp & Modal Windows para file menu
	*/
	ImGui::Begin("Despliegue 3D");

	if (ImGui::Button("File"))
		ImGui::OpenPopup("Options");
	if (ImGui::BeginPopup("Options"))
	{
		if (ImGui::MenuItem("Load"))
		{
			CModel* newM = CG::Load();
			if (newM !=NULL)
			{
				picked++;
				models.push_back(newM);

				glm::vec3 traslation0;
				glm::vec4 scale0;
				glm::vec3 rotate0;

				traslation0[0] = traslation0[1] = 0.0f;
				traslation0[2] = 0.0f;
				scale0.x = scale0.y = scale0.z = scale0.w = 1.0f;
				rotate0.x = rotate0.y = rotate0.z = 0.0f;


				models[picked]->setTranslation(traslation0);
				models[picked]->setScale(scale0);
				models[picked]->setRotate(rotate0);
				models[picked]->calculateNormals();


			}
		}
		ImGui::Separator();
		
		if (ImGui::MenuItem("Exit", "Alt+F4"))
		{	
			exit(0);
		}
		ImGui::EndPopup();
	}
	ImGui::Separator();

	//Elegir modelo cargado
	ImGui::InputInt("Model Number", &picked);
	ImGui::Text("+/- para desplazarte entre figuras cargadas");
	ImGui::Separator();
	//if(ImGui::TreeNode("Screen Options"))
	//{
		
		if (ImGui::ColorEdit3("Background Color", colorFondo))
		{	
		}

		//Model::setDespliegue(items1[despliegue_current]) para el modelo picked
		const char* despliegues[Element_COUNT] = { "Perspective", "Orthogonal"};
		const char* current_element_name = (projectionActual >= 0 && projectionActual < Element_COUNT) ? despliegues[projectionActual] : "Unknown";
		ImGui::SliderInt("Deployment", &projectionActual, 0, Element_COUNT - 1, current_element_name);
		if (projectionActual == PERSPECTIVE)
		{
			//Perspective
			proj = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, NCP, 100.0f);
		}
		else
		{
			//Orthogonal
			proj = glm::ortho(-(float)windowWidth / 800.0f, (float)windowWidth / 800.0f, -(float)windowHeight / 800.0f, (float)windowHeight / 800.0f, NCP, 100.0f);
		}


		ImGui::PushItemWidth(100);
		if (ImGui::DragFloat("Near Clipping Plane", &NCP, 0.01f));
		ImGui::PopItemWidth();
	
		//Aqui va CheckBox para backface culling 
		ImGui::Checkbox("BackFace Culling", &backFace);

		if (backFace)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else
		{ 
			glDisable(GL_CULL_FACE);
		}

		//Aqui va CheckBox para z-buffer 
		ImGui::Checkbox("Z-Buffer", &zBuffer);
		if (zBuffer)
		{
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		else 
		{
			glDisable(GL_DEPTH_TEST);
		}
		ImGui::Checkbox("Lights Switch", &lightSwitch);

	//ImGui::TreePop();
	//}
	ImGui::Separator();

	if (ImGui::TreeNode("Model")) 
	{
		if (picked > -1)
		{
			bool actP = models[picked]->getShowPuntos();
			if (ImGui::Checkbox("Points", &actP))models[picked]->setShowPuntos();
			ImGui::SameLine();

			bool actL = models[picked]->getShowLineas();
			if(ImGui::Checkbox("Wire-frame", &actL))models[picked]->setShowLineas();
			ImGui::SameLine();

			bool actT = models[picked]->getShowTriangulos();
			if(ImGui::Checkbox("Triangles", &actT))models[picked]->setShowTriangulos();
		
			static float colorModelo[4] = { 1.f,1.f,1.f,1.f };
			//float* colorModelo = models[picked]->getMColor();
			if(ImGui::ColorEdit4("Model Color", colorModelo))models[picked]->setMColor(colorModelo[0], colorModelo[1], colorModelo[2], colorModelo[3]);
				//models[picked]->setMColor(colorModelo[0], colorModelo[1], colorModelo[2], colorModelo[3]);
			
			if (actP)
			{

				if (ImGui::ColorEdit3("Point Color", colorPoint));
			}

			if (actL)
			{
				//models[picked]->BoundingBox();
				
				if (ImGui::ColorEdit3("Line Color", colorLine));
			}

			static float distanciaN = models[picked]->getDisN();
			ImGui::PushItemWidth(100);
			if (ImGui::DragFloat("Normal Distance", &distanciaN, 0.01f))models[picked]->setDisN(distanciaN);
			ImGui::PopItemWidth();

			bool actB = models[picked]->getShowBox();
			if (ImGui::Checkbox("Bounding Box", &actB))models[picked]->setShowBox();
			if (actB)
			{
				static float colorNormalsB[3] = { 0.6f,1.0f,1.0f };
				//models[picked]->setNFColor(colorNormalsF[0], colorNormalsF[1], colorNormalsF[2]);
				if (ImGui::ColorEdit3("Color B", colorNormalsB))
				{
					models[picked]->setBColor(colorNormalsB[0], colorNormalsB[1], colorNormalsB[2]);
				}
				shader->setFloat("mColorR", colorNormalsB[0]);
				shader->setFloat("mColorG", colorNormalsB[1]);
				shader->setFloat("mColorB", colorNormalsB[2]);
				models[picked]->BoundingBox();
			}

			if (ImGui::Checkbox("Normals Vertex", &shownormalsV));// models[picked]->displayNormalsVertex();
			if (shownormalsV)
			{
				static float colorNormalsV[3] = { 0.6f,1.0f,1.0f };
				//models[picked]->setNFColor(colorNormalsF[0], colorNormalsF[1], colorNormalsF[2]);
				if (ImGui::ColorEdit3("Color V", colorNormalsV))
				{
					models[picked]->setNVColor(colorNormalsV[0], colorNormalsV[1], colorNormalsV[2]);
				}
				shader->setFloat("mColorR", colorNormalsV[0]);
				shader->setFloat("mColorG", colorNormalsV[1]);
				shader->setFloat("mColorB", colorNormalsV[2]);
				models[picked]->displayNormalsVertex();
			}
			
			if(ImGui::Checkbox("Normals Faces", &shownormalsF));
			if (shownormalsF)
			{
				
				static float colorNormalsF[3] = { 0.5f,0.f,0.6f };
				//models[picked]->setNFColor(colorNormalsF[0], colorNormalsF[1], colorNormalsF[2]);
				if (ImGui::ColorEdit3("Color F", colorNormalsF))
				{
					models[picked]->setNFColor(colorNormalsF[0], colorNormalsF[1], colorNormalsF[2]);
				}
				shader->setFloat("mColorR", colorNormalsF[0]);
				shader->setFloat("mColorG", colorNormalsF[1]);
				shader->setFloat("mColorB", colorNormalsF[2]);
				models[picked]->displayNormalsFace();
			}
	
			if (ImGui::TreeNode("Translation"))
			{
				
				//static glm::vec3 translateAux = { 0,0,0 };
				glm::vec3 translateAux = getModelTranslation();
				ImGui::PushItemWidth(80);
				ImGui::DragFloat("X", &translateAux[0], 0.01f);
				ImGui::SameLine();
				ImGui::DragFloat("Y", &translateAux[1], 0.01f);
				ImGui::SameLine();
				ImGui::DragFloat("Z", &translateAux[2], 0.01f);
				ImGui::PopItemWidth();
			
				setModelTranslation(translateAux);
				//cout << translateAux[0]<<" " << translateAux[1] << " " << translateAux[2] << endl;

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Scale"))
			{
				
				//static glm::vec4 scaleAux = { 1,1,1,1 };
				glm::vec4 scaleAux = models[picked]->getScale();
				ImGui::PushItemWidth(80);
				ImGui::DragFloat("X", &scaleAux[0], 0.01f);
				ImGui::SameLine();
				ImGui::DragFloat("Y", &scaleAux[1], 0.01f);
				ImGui::SameLine();
				ImGui::DragFloat("Z", &scaleAux[2], 0.01f);
				ImGui::DragFloat("All", &scaleAux[3], 0.05f);
				ImGui::PopItemWidth();
				setModelScale(scaleAux);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Rotate"))
			{

				//static glm::vec4 scaleAux = { 1,1,1,1 };
				glm::vec3 rotateAux = models[picked]->getRotate();
				ImGui::PushItemWidth(80);
				ImGui::DragFloat("X", &rotateAux[0], 0.01f);
				ImGui::SameLine();
				ImGui::DragFloat("Y", &rotateAux[1], 0.01f);
				ImGui::SameLine();
				ImGui::DragFloat("Z", &rotateAux[2], 0.01f);
				ImGui::PopItemWidth();
				setModelRotate(rotateAux);

				ImGui::TreePop();
			}
			
			
	
		} //fin del fi picked !=-1
		ImGui::TreePop();
	}
	
	ImGui::Separator();

	ImGui::End();

}

void Application::Init() {

	shader = new Shader("bw.vert", "bw.frag");

	//Inicializar luces
	initLights();

}

void Application::setModelTranslation(glm::vec3 modelTranslation)
{
	models[picked]->setTranslation(modelTranslation);
}

glm::vec3 Application::getModelTranslation()
{
	return models[picked]->getTranslation();
}

void Application::setModelScale(glm::vec4 modelScale)
{
	models[picked]->setScale(modelScale);
}

glm::vec4 Application::getModelScale()
{
	return models[picked]->getScale();
}

void Application::setModelRotate(glm::vec3 quaternion)
{
	models[picked]->setRotate(quaternion);
}

glm::vec3 Application::getModelRotate()
{
	return  models[picked]->getRotate();
}

void Application::initLights()
{
	glm::vec3 traslation0;
	glm::vec4 scale0;
	glm::vec3 rotate0;

	CObj* light1 = new CObj();
	if (!light1->load("../Models/sphere.obj")) {
		cout << "No cargó";
		return;
	}

	scale0.x = scale0.y = scale0.z = scale0.w = 1.0f;
	rotate0.x = rotate0.y = rotate0.z = 0.0f;

	traslation0.x = lightposition1[0];
	traslation0.y = lightposition1[1];
	traslation0.z = lightposition1[2];
	lights.push_back(light1);

	lights[0]->setTranslation(traslation0);
	lights[0]->setScale(scale0);
	lights[0]->setRotate(rotate0);
	lights[0]->setShowTriangulos();
	lights[0]->setMColor(lightambient[0], lightambient[1], lightambient[2], lightambient[3]);
	lights[0]->calculateNormals();

	CObj* light2 = new CObj();
	if (!light2->load("../Models/sphere.obj"))
		return;

	traslation0.x = lightposition2[0];
	traslation0.y = lightposition2[1];
	traslation0.z = lightposition2[2];
	lights.push_back(light2);
	
	lights[1]->setTranslation(traslation0);
	lights[1]->setScale(scale0);
	lights[1]->setRotate(rotate0);
	lights[1]->setShowTriangulos();
	lights[1]->setMColor(lightambient[0], lightambient[1], lightambient[2], lightambient[3]);
	lights[1]->calculateNormals();

}

void Application::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
