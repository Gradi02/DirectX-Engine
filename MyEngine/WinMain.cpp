/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  There is a main Script: 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Window.h"
#include "exceptionsHandler.h"
#include <sstream>




int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    try 
    {
        Window wnd(800, 300, "test");

        MSG msg;
        BOOL getResult;
        int i = 0;

        while ((getResult = GetMessage(&msg, nullptr, 0, 0)) > 0)       //sprawdzam czy jaki� event z win32 zosta� pobrany, dwa zera na koncu zwracaj� 
        {                                                               //wszystkie wiadomo�ci z systemu, funkcja zwroci 0 gdy app.quit i -1 gdy error
            TranslateMessage(&msg);
            DispatchMessageA(&msg);

            //Test Code
            if (!wnd.ms.isEmpty())
            {
                const auto e = wnd.ms.Read();
                switch (e.GetType())
                {
                case Mouse::Event::Type::W_Down:
                    {
                        std::ostringstream oss;
                        oss << "Scroll: " << (--i);
                        wnd.SetTitle(oss.str());
                    }
                    break;
                case Mouse::Event::Type::W_Up:   
                    {
                        std::ostringstream oss;
                        oss << "Scroll: " << (++i);
                        wnd.SetTitle(oss.str());
                    }
                    break;
                }
            }
        }

        if (getResult == -1)                                            //Dodatkowo warunek wy�ej orzypisuje do zmiennej i sprawdzam ten output
        {                                                               //je�li -1 to error inaczej zwr�� kod zakonczenia programu
            return -1;
        }

        return msg.wParam;
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