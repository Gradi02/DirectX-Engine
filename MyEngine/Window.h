/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  Windows Class Script: 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "WinCustomLib.h"
#include "exceptionsHandler.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphic.h"
#include <string>
#include <optional>
#include <memory>

//Declaration of window class
class Window
{
public:
	class Exceptions : public EngineExceptions
	{
		using EngineExceptions::EngineExceptions;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrExceptions : public Exceptions
	{
	public:
		HrExceptions(int line, const char* file, HRESULT hrN) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxExceptions : public Exceptions
	{
	public: 
		using Exceptions::Exceptions;
		const char* GetType() const noexcept override;
	};
private:
	//Singleton for Window Class
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;				//Get wndClass
		static HINSTANCE GetInstance() noexcept;			//Get hInst
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;					//Wy��czenie konstruktowa kopiuj�cego (klasa ma mie� tylko jedn� instancje)
		WindowClass& operator=(const WindowClass&) = delete;		//Wy��czenie operatora '=' dla tej klasy
		static constexpr const char* wndClassName = "My Engine";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const char* name) noexcept;
	~Window();
	Window(const Window&) = delete;						//Wy��czenie konstruktowa kopiuj�cego (klasa ma mie� tylko jedn� instancje)
	Window& operator=(const Window&) = delete;			//Wy��czenie operatora '=' dla tej klasy
	void SetTitle(const std::string ntitle);
	static std::optional<int> ProcessMessages();
	Graphic& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kmb;
	Mouse ms;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphic> pGfx;
};

//macro for bet exceptions
#define ENG_EXCEPT(hr) Window::HrExceptions(__LINE__,__FILE__,hr)
#define ENG_LAST_EXCEPT() Window::HrExceptions(__LINE__,__FILE__,GetLastError())
#define ENG_NOGFX_EXCEPT() Window::NoGfxExceptions(__LINE__,__FILE__)
