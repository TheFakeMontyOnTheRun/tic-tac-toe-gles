//
// Created by monty on 21/02/16.
//
#include <glm/glm.hpp>

#include "Trig.h"
namespace odb {
	Trig::Trig() {
		cachedVertexData = nullptr;
		cachedUVData = nullptr;
		cachedNormalData = nullptr;
	}


	Trig::~Trig() {
		delete cachedUVData;
		delete cachedVertexData;
		delete cachedNormalData;
	}
}