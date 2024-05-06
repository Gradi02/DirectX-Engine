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
#include <string>
#include <optional>

//Declaration of window class
class Window
{
public:
	class Exceptions : public EngineExceptions
	{
	public:
		Exceptions(int line, const char* file, HRESULT hrN) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
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
		WindowClass(const WindowClass&) = delete;					//Wy³¹czenie konstruktowa kopiuj¹cego (klasa ma mieæ tylko jedn¹ instancje)
		WindowClass& operator=(const WindowClass&) = delete;		//Wy³¹czenie operatora '=' dla tej klasy
		static constexpr const char* wndClassName = "My Engine";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const char* name) noexcept;
	~Window();
	Window(const Window&) = delete;						//Wy³¹czenie konstruktowa kopiuj¹cego (klasa ma mieæ tylko jedn¹ instancje)
	Window& operator=(const Window&) = delete;			//Wy³¹czenie operatora '=' dla tej klasy
	void SetTitle(const std::string ntitle);
	static std::optional<int> ProcessMessages();
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
};

//macro for bet exceptions
#define ENG_EXCEPT(hr) Window::Exceptions(__LINE__,__FILE__,hr)
#define ENG_LAST_EXCEPT() Window::Exceptions(__LINE__,__FILE__,GetLastError())
