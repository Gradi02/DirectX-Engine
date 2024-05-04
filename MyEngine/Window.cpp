/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  Windows Class Script: 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Window.h"
#include <string>
#include <sstream>
#include "resource.h"


//Declarations
Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept: hInst(GetModuleHandle(nullptr))
{
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = HandleMsgSetup;    //Zdefiniowano procedure dzia³ania okna - jego zachowania (to samo gdy w to miejsce wstawie DefWindowProc)
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetInstance();       //Pobierz instancje
    wc.hIcon = static_cast<HICON>(LoadImage(hInst,MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 1));  //plik mussi byæ w formacie .ico
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = GetName();       //Pobierz nazwe
    wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 1));
    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
    return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
    return wndClass.hInst;
}

Window::Window(int width, int height, const char* name) noexcept
{
    //Calculate window size
    RECT wr;
    wr.left = 100;
    wr.right = width + wr.left;
    wr.top = 100;
    wr.bottom = height + wr.top;
    //AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

    //Check if creating window fails
    if (FAILED(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
    {
        throw ENG_LAST_EXCEPT();
    }

    //Create window
    hWnd = CreateWindow
    (
        WindowClass::GetName(),
        name,                                       //nazwa okna
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,   //tu mo¿esz eksperymentowaæ z ró¿nymi rodzajami i typami okien z docs
        CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
        nullptr, nullptr, WindowClass::GetInstance(), this
    );

    //Check for error after building window
    if (hWnd == nullptr)
    {
        throw ENG_LAST_EXCEPT();
    }

    //Show window
    ShowWindow(hWnd, SW_SHOWDEFAULT);                      //okna domyœlnie nie widaæ trzeba je pokazaæ funkcj¹, drugi argument te¿ mo¿na zmieniæ
}

Window::~Window()
{
    DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    //Use create parameter passed from CreateWindow() to store window class pointer
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
        
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
        
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case WM_CLOSE:                  //WindowMessage_Type
        PostQuitMessage(0);
        return 0; 

    case WM_KILLFOCUS:              //stay focused on main window
        kmb.ClearState();       
        break;

    /////////////// Keyboard ///////////////
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:     //sprawdzam te¿ syskey dla np alta (WM_MENU)
        if (!(lParam & 0x40000000) || kmb.IsAutorepeatEnabled())
        {
            kmb.OnKeyPressed(static_cast<unsigned char>(wParam));
        }
        break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        kmb.OnKeyReleased(static_cast<unsigned char>(wParam));
        break;
    case WM_CHAR:
        kmb.OnChar(static_cast<unsigned char>(wParam));
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}


//Engine Error Exceptions Stuffs
Window::Exceptions::Exceptions(int line, const char* file, HRESULT hrN) noexcept
    : EngineExceptions(line, file), hr(hrN) {}

const char* Window::Exceptions::what() const noexcept
{
    std::ostringstream oss;		//coœ jak string builder w javie
    oss << GetType() << std::endl
        << "[Error Code] " << GetErrorCode() << std::endl
        << "[Description] " << GetErrorString() << std::endl
        << GetOriginString();
    whatBuffer = oss.str();				//zapisuje info do buffera by go nie zgubiæ
    return whatBuffer.c_str();			//zwraca pointer na const char*
}

const char* Window::Exceptions::GetType() const noexcept
{
    return "Engine Window Exception";
}

std::string Window::Exceptions::TranslateErrorCode(HRESULT hr) noexcept
{
    char* msgBuff = nullptr;
    DWORD msgLen = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, hr, MAKELANGID(LANG_POLISH, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&msgBuff), 0, nullptr
    );

    if (msgLen == 0)
    {
        return "Undefined Error!";
    }

    std::string errorStr = msgBuff;
    LocalFree(msgBuff);
    return errorStr;
}

HRESULT Window::Exceptions::GetErrorCode() const noexcept
{
    return hr;
}

std::string Window::Exceptions::GetErrorString() const noexcept
{
    return TranslateErrorCode(hr);
}




