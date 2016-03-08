#include <iostream>
#include <glm.hpp>
#include <gtx/rotate_vector.hpp>
#include "../Include Files/Metrics.h"
#include "extractor.h"

#include <cassert>
#include <fstream>


/*
#include <stdio.h>  // defines FILENAME_MAX 
#include <direct.h>
#define GetCurrentDir _getcwd
*/

//#define CWD
#define DEBUG_MODE


char cCurrentPath[FILENAME_MAX];

void tesselate(const char * fName, int detailLevel) {
	std::vector<tinyobj::shape_t> shapes;
	ExtractFromFile(fName, shapes);

	for (size_t i = 0; i < shapes.size(); i++) {
		printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
		printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
		printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
		assert((shapes[i].mesh.indices.size() % 3) == 0);
		for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
			printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2], shapes[i].mesh.material_ids[f]);
		}

		printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
		assert((shapes[i].mesh.positions.size() % 3) == 0);
		for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
			printf("  v[%ld] = (%f, %f, %f)\n", v,
				shapes[i].mesh.positions[3 * v + 0],
				shapes[i].mesh.positions[3 * v + 1],
				shapes[i].mesh.positions[3 * v + 2]);
		}
	}

	int x = 0; //Allows addition of breakpoint after Extract function


}


#ifdef DEBUG_MODE
int main() {
	std::cout << "Hello World!\n";
	glm::vec4 pineapples = glm::vec4();
	char * fName = "Objects/Box.obj";

#ifdef CWD
	/*Gets CWD*/
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
	printf("The current working directory is %s", cCurrentPath);
	/*End of CWD code*/
#endif

	/*std::ifstream ifs(fName);
	assert(ifs.good());*/

	tesselate(fName, 0);

	return 0;
}
#endif



