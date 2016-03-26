#include "../Source Files/Engine Core/Object/ObjLoader.cpp"
#include <iostream>
#include<vector>
#include<string>

void processFile(std::vector<tinyobj::shape_t>& shapes, std::vector<tinyobj::material_t>& mat, char* file) {
	std::string err;
	err = tinyobj::LoadObj(shapes, mat, file, NULL);
	if (!err.empty()) {
		std::cout << err << std::endl;
	}
	else {
		std::cout << "File loaded successfully" << std::endl;
	}
}