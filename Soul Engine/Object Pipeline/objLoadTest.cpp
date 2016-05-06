#include "objLoadTest.h"
#include "..\Libraries\glm\glm\glm.hpp"
#include <list>

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
//TODO: Subdivide triangles
void tesselate(std::list<glm::vec3>& indices, std::list<glm::vec3>& vertices, std::vector<tinyobj::shape_t>& shapes, float metric) {
	for (size_t i = 0; i < shapes.size(); i++) {
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			indices.push_back(glm::vec3(shapes[i].mesh.indices[3 * f + 0],
				shapes[i].mesh.indices[3 * f + 1],
				shapes[i].mesh.indices[3 * f + 2]));
		}
		
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			vertices.push_back(glm::vec3(shapes[i].mesh.positions[3 * v + 0],
				shapes[i].mesh.positions[3 * v + 1],
				shapes[i].mesh.positions[3 * v + 2]));
		}
	}
}

int main() {
	char* inputFile = "../../Box.obj";
	std::string err;
	std::vector<tinyobj::shape_t> shapes; //vector to store triangulated object
	std::vector<tinyobj::material_t> materials; //vector to store material mesh
	processFile(shapes, materials, inputFile);
	std::list<glm::vec3> indices;
	std::list<glm::vec3> vertices;
	tesselate(indices, vertices, shapes, CENTIMETER*5);
	std::cout << "Press any key to exit ..." << std::endl;
	getchar(); //keep terminal window open until keypress
	
	return 0;
}