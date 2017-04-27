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
	
	//Loop over triangles
	for (size_t i = 0; i < shapes.size(); i++) {
		printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
		printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());

		//Store index information
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f,
				shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1],
				shapes[i].mesh.indices[3 * f + 2], shapes[i].mesh.material_ids[f]);
			indices.push_back(glm::vec3(shapes[i].mesh.indices[3 * f + 0],
				shapes[i].mesh.indices[3 * f + 1],
				shapes[i].mesh.indices[3 * f + 2]));
		}
		
		//Store vertex information
		printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			printf("  v[%ld] = (%f, %f, %f)\n", v,
				shapes[i].mesh.positions[3 * v + 0],
				shapes[i].mesh.positions[3 * v + 1],
				shapes[i].mesh.positions[3 * v + 2]);
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
	std::cout << "Press enter to exit ..." << std::endl;
	getchar(); //keep terminal window open until keypress
	
	return 0;
}