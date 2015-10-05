#pragma once

#include <Windows.h>
#include <IOstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "cuda_runtime.h"
#include <cuda.h>
#include <cudaGL.h>
#include <curand.h>

#define GLM_FORCE_CUDA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue> 
#include <map>
#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include <math.h>
#include <cmath>
#include <ctime>
#include <thread>
#include <future>
#include <fstream>
#include <sstream>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include "Metrics.h"

#include "device_launch_parameters.h"
#include "Utility\OpenGL\GLError.h"