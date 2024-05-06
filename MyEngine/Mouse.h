/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  Mouse class header file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <queue>

class Mouse
{
	friend class Window;	//This class is an extension of window class

public:
	class Event
	{
	public:
		enum class Type
		{
			L_Pressed,
			R_Pressed,
			L_Released,
			R_Released,
			W_Up,
			W_Down,
			Move,
			Enter,
			Leave,
			Invalid
		};
	private:
		Type type;
		bool leftIsPressed;
		bool rightIsPressed;
		int x;
		int y;
	public:
		Event() noexcept : type(Type::Invalid), leftIsPressed(false), rightIsPressed(false), x(0), y(0) {}
		Event(Type ty, const Mouse& prt) noexcept : 
			type(ty), 
			leftIsPressed(prt.leftIsPressed), 
			rightIsPressed(prt.rightIsPressed),
			x(prt.x), 
			y(prt.y) {}
		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
		std::pair<int, int> GetPos() const noexcept
		{
			return { x,y };
		}
		int GetPosX() const noexcept
		{
			return x;
		}
		int GetPosY() const noexcept
		{
			return y;
		}
		bool LeftIsPressed() const noexcept
		{
			return leftIsPressed;
		}
		bool RightIsPressed() const noexcept
		{
			return rightIsPressed;
		}
		Type GetType() const noexcept
		{
			return type;
		}
	};
public:
	Mouse() = default;	//deklaracja konstrukora domyœlnego - w zasadzie zbêdna ale warto zaznaczyæ
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	//Getters
	std::pair<int, int> GetPos() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool IsInWindow() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	//Operators
	bool isEmpty() const noexcept
	{
		return mousebuffer.empty();
	}
	Mouse::Event Read() noexcept;
	void Flush() noexcept;
private:
	void OnRightPressed(int xn, int yn) noexcept;
	void OnLeftPressed(int xn, int yn) noexcept;
	void OnRightReleased(int xn, int yn) noexcept;
	void OnLeftReleased(int xn, int yn) noexcept;
	void OnWheelUp(int xn, int yn) noexcept;
	void OnWheelDown(int xn, int yn) noexcept;
	void OnMouseMove(int xn, int yn) noexcept;
	void OnWheelCarry(int xn, int yn, int delta) noexcept;
	void OnMouseEnter() noexcept;
	void OnMouseLeave() noexcept;
	void TrimBuffer() noexcept;
private:
	static constexpr unsigned int mousebufferSize = 16u;
	int x;
	int y;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	bool isInWindow = false;
	int wheelCarry = 0;
	std::queue<Event> mousebuffer;
};