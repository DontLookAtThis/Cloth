#pragma once
#ifndef UTILITY_H
#define UTILITY_H

// OpenGL Include ------------------------------------------------------------------------------
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <fmod.hpp>
#include <Box2D.h>
#include <glm/common.hpp>

// Library Include -----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include <chrono>
#include <strstream>
#include <Windows.h>
#include <cassert>
#include <thread>
#include <sstream>

//#include <vld.h> // Memory Leak Detector


//----------------------------------------------------------------------------------------------

namespace util
{
	// Define the screen size
	static int SCR_WIDTH = 1600;
	static int SCR_HEIGHT = 900;
	static int PIXELUNIT = 40;
}

// Define Struct -------------------------------------------------------------------------------

struct DebugTimer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	DebugTimer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	
	~DebugTimer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		

		float ms = duration.count();
		std::cout << "Debug Timer took " << ms << " ms \n";
	}

};

struct Transform
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
};

enum InputState 
{
	INPUT_FIRST_RELEASE,	// First frame of Up state 
	INPUT_RELEASED,			// Default State (Up) 
	INPUT_FIRST_PRESS,		// First frame of Down state 
	INPUT_HOLD,				// Key is held Down 
};

enum ItemState
{
	ITEM_NONE,
	ITEM_RAILGUN,
	ITEM_GRAVITYWELL,
	ITEM_GRAPPLINGHOOK,
	ITEM_DROPBOX,
	ITEM_END,
};

enum InputMouse 
{ 
	MOUSE_LEFT, 
	MOUSE_MIDDLE, 
	MOUSE_RIGHT 
};

enum Shape
{
	CIRCLE,
	BOX,
	GRAVITY,
};

struct Vertex {

	glm::vec3 Position; // Position	
	glm::vec3 Normal; // Normal	
	glm::vec2 TexCoords; // TexCoords
};
//----------------------------------------------------------------------------------------------

enum ECAMERATYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE,
};


template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

#endif // !_UTILITY_H
