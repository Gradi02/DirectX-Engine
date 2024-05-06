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
    const float t = timer.Peak();
    static float lastT = 0;
    if (t - lastT >= 0.1f)
    {
        std::ostringstream oss;
        oss << "Run Time: " << t;
        wnd.SetTitle(oss.str());
        lastT = t;
    }
}



