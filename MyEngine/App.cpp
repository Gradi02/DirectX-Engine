/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  App file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "App.h"
#include <sstream>

App::App() : 
    wnd(800, 300, "test") 
{}

int App::Go()   //wykonuje siê na starcie programu
{
    while (true)
    {
        if (const auto ecode = Window::ProcessMessages())
        {
            return *ecode;
        }
        Frame();
    }
}

void App::Frame()
{
    const float c = sin(timer.Peak()) / 2.0f + 0.5f;
    wnd.Gfx().ClearBuffer(c, c, c);
    wnd.Gfx().DrawTestTriangle();
    wnd.Gfx().EndFrame();
}



