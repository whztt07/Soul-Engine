#include "../Source Files/Engine Core/Object/ObjLoader.cpp"
#include <iostream>
#include<vector>
#include<string>
#include "../Include Files/Metrics.h"

//Load .obj file and populate shape and material vectors
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

//Tesselate the shapes into triangles whose size are given by argument "metric"
void tesselate(const std::vector<tinyobj::shape_t>& shapes, float metric) {
	for (size_t i = 0; i < shapes.size(); i++) {
		
	}
}