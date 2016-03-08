#include "../Source Files/Engine Core/Object/ObjLoader.h"
#include <iostream>

int main() {
	std::string inputFile = "../../object_pipeline/box.obj";
	std::string err;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	tinyobj::LoadObj(shapes,materials,inputFile.c_str(),NULL);
	if(!err.empty()) {
		std::cout << err << std::endl;
	}
	else {
		std::cout << ".obj file loaded successfully" << std::endl;
	}
}