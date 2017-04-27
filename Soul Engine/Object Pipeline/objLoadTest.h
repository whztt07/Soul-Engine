#include "../Source Files/Engine Core/Object/ObjLoader.cpp"
#include <iostream>
#include<vector>
#include<string>
#include "../Include Files/Metrics.h"

//Function for loading an .obj file. Output is stored in vars shapes and mat
void processFile(std::vector<tinyobj::shape_t>& shapes, std::vector<tinyobj::material_t>& mat, char* file);

//Function for tesselating an object. Input is given by vector shapes and a metric to
//Govern the size of the subtriangles
void tesselate(const std::vector<tinyobj::shape_t>& shapes, float metric);