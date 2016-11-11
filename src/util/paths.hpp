#pragma once

#include <string>

#define OUTPUTPATH(filename) std::string(OUTPUT_FOLDER) + std::string(filename)
#define SHADERPATH(filename) std::string(SHADERS_FOLDER) + std::string(filename)
#define KERNELPATH(filename) std::string(KERNELS_FOLDER) + std::string(filename)
#define RESOURCEPATH(filename) std::string(RESOURCES_FOLDER) + std::string(filename)