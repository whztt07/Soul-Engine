#pragma once
#include "../Source Files/Engine Core/Object/ObjLoader.h"
#include <vector>
#include <string>
#include <iostream>

void ExtractFromFile(const char* name){
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err = tinyobj::LoadObj(shapes, materials, name, NULL);

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}
}