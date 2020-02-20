#include "Loaders.h"





namespace CG
{ 

	std::string openfilename()
	{
		OPENFILENAME ofn;
		wchar_t fileName[MAX_PATH] = L"";
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = L"All Files\0*.OBJ;*.OFF";
		ofn.lpstrFile = fileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = L"";
		std::string fileNameStr;

		if (GetOpenFileName(&ofn)){
			std::wstring aux (fileName);
			std::string str(aux.begin(), aux.end());
			fileNameStr = str;
		}

		return fileNameStr;
	}

	//void Load(const std::string path)
	CModel* Load()
	{
		std::string name = openfilename();
		////if path termina en .obj
		////else if path termina en .off
		if (name.substr(name.find_last_of(".") + 1) == "obj")
		{
			CObj* obj = new CObj();
			if (!obj->load(name))
				return NULL;

			CModel *newM = obj;
			return newM;

		}
		else if (name.substr(name.find_last_of(".") + 1) == "off")
		{
			COff* off = new COff();
			if (!off->load(name))
				return NULL;
			CModel* newM = off;
			return newM;
			
		}

	}

	void LoadObj(const std::string path) {
		glm::vec3 test;
	}

	void LoadOff(const std::string path) {
		glm::vec3 test;
	}
}
