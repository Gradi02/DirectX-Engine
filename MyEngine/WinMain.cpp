/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  There is a main Script: 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "App.h"
#include "exceptionsHandler.h"
#include <sstream>



int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    try 
    {
        return App{}.Go();
    }
    catch (const EngineExceptions& e)
    {
        MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
    }
    catch (const std::exception& e)
    {
        MessageBox(nullptr, e.what(), "Standard Exception!", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        MessageBox(nullptr, "No details available!", "Unknown Exception!", MB_OK | MB_ICONEXCLAMATION);
    }
    return -1;
}