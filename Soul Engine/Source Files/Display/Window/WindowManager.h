#pragma once

#include "Utility\Includes\GLFWIncludes.h"
#include "Metrics.h"


namespace WindowManager {

	namespace detail {
		extern int monitorCount;
		extern GLFWmonitor** monitors;
	}

	//GLFW needs to be initialized
	void Init();

	//cleanup all windows
	void Terminate();

	bool ShouldClose();

	void SignelClose();

	void SoulCreateWindow(int monitor, uint x, uint y, uint width, uint height);

	void Draw();
}