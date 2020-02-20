#include "EDpch.h"
#include "Model.h"
#include "Off.h"
#include "Obj.h"



namespace CG
{
	std::string openfilename();
	CModel* Load();
	static void LoadObj(const std::string path);
	static void LoadOff(const std::string path);
}