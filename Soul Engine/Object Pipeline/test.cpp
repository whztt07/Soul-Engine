#include <iostream>
#include <glm.hpp>
#include <gtx/rotate_vector.hpp>
#include "../Include Files/Metrics.h"
#include "extractor.h"
#include <stdio.h>

#include <cassert>
#include <fstream>

#include <stdio.h>  /* defines FILENAME_MAX */

#include <direct.h>
#define GetCurrentDir _getcwd


#define DEBUG_MODE


char cCurrentPath[FILENAME_MAX];

void tesselate(const char * fName, int detailLevel) {
	std::vector<tinyobj::shape_t> shapes;
	ExtractFromFile(fName, shapes);



}


#ifdef DEBUG_MODE
int main() {
	std::cout << "Hello World!\n";
	glm::vec4 pineapples = glm::vec4();
	char * fName = "Box.txt";

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
	printf("The current working directory is %s", cCurrentPath);

	std::ifstream ifs(fName);
	assert(ifs.good());

	tesselate(fName, 0);

	return 0;
}
#endif



