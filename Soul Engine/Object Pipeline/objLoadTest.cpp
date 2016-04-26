#include"objLoadTest.h"

int main() {
	char* inputFile = "../../Box.obj";
	std::string err;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	processFile(shapes, materials, inputFile);
	tesselate(shapes, CENTIMETER*5);
	getchar();
	
	return 0;
}