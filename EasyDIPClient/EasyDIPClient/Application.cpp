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
	
	if(picked!=-1){
		
		glm::mat4 modl = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		CModel* modelo = models[picked];
		/*float *modelColor = modelo->getMColor();
		shader->setFloat("mColorR", modelColor[0]);
		shader->setFloat("mColorG", modelColor[1]);
		shader->setFloat("mColorB", modelColor[2]);*/
		//shader->setFloat("mColorA", modelColor[3]);
		if (projectionActual == PERSPECTIVE)
		{
			//Perspective
			proj = glm::mat4(1.0f);
			proj = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, NCP, 100.0f);
		}
		else
		{
			//Orthogonal
			proj = glm::mat4(1.0f);
			proj = glm::ortho(-(float)windowWidth / 800.0f, (float)windowWidth / 800.0f, -(float)windowHeight / 800.0f, (float)windowHeight / 800.0f, NCP, 100.0f);
		}

		glm::vec3 rotacion= modelo->getRotate();

		glm::mat4 rotXm = glm::rotate(rotacion.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotYm = glm::rotate(rotacion.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZm = glm::rotate(rotacion.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 R = rotZm * rotYm * rotXm;
		
		glm::vec4 vecScale= modelo->getScale();
		glm::mat4 S;
		if(vecScale.w!=1.0f)
		{
			S = glm::scale(glm::vec3(vecScale.w, vecScale.w, vecScale.w));
		}
		else {
			S = glm::scale(glm::vec3(vecScale.x, vecScale.y, vecScale.z));
		}
		
		glm::mat4 T = glm::translate(modelo->getTranslation());

		modl = T * S * R;

		view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 2.0f, 0.0f));

		shader->setMat4("proj", proj);
		shader->setMat4("view", view);
		shader->setMat4("modl", modl);
		shader->use();

		int numVert = modelo->getnumVert();
		int cantidad = modelo->getCaras().size()*3;
		unsigned* indices = modelo->getIndex();
		//cout << numVert << " " << numIn << endl;
		vector<glm::vec3> vertices = modelo->getVertices();
	
		unsigned int VBO, VAO, IBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * cantidad, indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindVertexArray(VAO);

		if (actP)
		{
			//glEnable(GL_POLYGON_OFFSET_POINT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			shader->setFloat("mColorR", colorPoint[0]);
			shader->setFloat("mColorG", colorPoint[1]);
			shader->setFloat("mColorB", colorPoint[2]);
			//glPolygonOffset(0.0f, 0.0f);
			glPointSize(2.3f);
			glDrawElements(GL_TRIANGLES, cantidad, GL_UNSIGNED_INT, nullptr);
			//glDisable(GL_POLYGON_OFFSET_POINT);
			glPointSize(1.0f);
		}
		if(actL)
		{
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			shader->setFloat("mColorR", colorLine[0]);
			shader->setFloat("mColorG", colorLine[1]);
			shader->setFloat("mColorB", colorLine[2] );
			glPolygonOffset(4.0f, 4.0f);
			glDrawElements(GL_TRIANGLES, cantidad, GL_UNSIGNED_INT, nullptr);
			glDisable(GL_POLYGON_OFFSET_LINE);
		}
		if (actT)
		{
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			float *modelColor = modelo->getMColor();
			shader->setFloat("mColorR", modelColor[0]);
			shader->setFloat("mColorG", modelColor[1]);
			shader->setFloat("mColorB", modelColor[2]);
			glPolygonOffset(8.0f, 8.0f);
			glDrawElements(GL_TRIANGLES, cantidad, GL_UNSIGNED_INT, nullptr);
			glDisable(GL_POLYGON_OFFSET_FILL);
		}
		//glDrawElements(GL_TRIANGLES, cantidad, GL_UNSIGNED_INT, nullptr);
	}

	

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
	if(ImGui::TreeNode("Screen Options"))
	{
		
		if (ImGui::ColorEdit3("Background Color", colorFondo))
		{	
		}

		//Model::setDespliegue(items1[despliegue_current]) para el modelo picked
		const char* despliegues[Element_COUNT] = { "Perspective", "Orthogonal"};
		const char* current_element_name = (projectionActual >= 0 && projectionActual < Element_COUNT) ? despliegues[projectionActual] : "Unknown";
		ImGui::SliderInt("Deployment", &projectionActual, 0, Element_COUNT - 1, current_element_name);

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

	ImGui::TreePop();
	}
	ImGui::Separator();

	if (ImGui::TreeNode("Model")) 
	{
		if (picked > -1)
		{
			//bool actP = models[picked]->getShowPuntos();
			if(ImGui::Checkbox("Points", &actP)); 
			ImGui::SameLine();

			//bool actL = models[picked]->getShowLineas();
			if(ImGui::Checkbox("Wire-frame", &actL));
			ImGui::SameLine();

			//bool actT = models[picked]->getShowTriangulos();
			if(ImGui::Checkbox("Triangles", &actT));
		
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
				models[picked]->BoundingBox();
			}

			if (ImGui::Checkbox("Normals Vertex", &shownormalsV));// models[picked]->displayNormalsVertex();
			if (shownormalsV)
			{
				models[picked]->displayNormalsVertex();
			}
			
			if(ImGui::Checkbox("Normals Faces", &shownormalsF));
			if (shownormalsF)
			{
				models[picked]->displayNormalsFace();
				//static float colorNormalsF[3] = { 0.5f,0.f,0.6f };
				//models[picked]->setNFColor(colorNormalsF[0], colorNormalsF[1], colorNormalsF[2]);
				//if(ImGui::ColorEdit3("Color", colorNormalsF))models[picked]->setNFColor(colorNormalsF[0], colorNormalsF[1], colorNormalsF[2]);

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
	/*vec4 vec;
	quat qt = models[picked]->getRotate();
	vec[0] = qt.x;
	vec[1] = qt.y;
	vec[2] = qt.z;
	vec[3] = qt.w;*/
	return  models[picked]->getRotate();
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
