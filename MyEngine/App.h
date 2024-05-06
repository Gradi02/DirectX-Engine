/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  App header file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Window.h"
#include "EngineTimer.h"

class App
{
public:
	App();
	int Go();
private:
	void Frame();
private:
	Window wnd;
	EngineTimer timer;
};
