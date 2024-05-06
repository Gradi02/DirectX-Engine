/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  Timer Header File
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <chrono>

class EngineTimer
{
public:
	EngineTimer();
	float Mark();
	float Peak() const;
private:
	std::chrono::steady_clock::time_point last;
};