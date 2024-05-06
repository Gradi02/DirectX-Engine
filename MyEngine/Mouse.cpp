/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  Mouse class code file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Mouse.h"
#include <Windows.h>

std::pair<int, int> Mouse::GetPos() const noexcept
{
	return { x,y };
}

int Mouse::GetPosX() const noexcept
{
	return x;
}

int Mouse::GetPosY() const noexcept
{
	return y;
}

bool Mouse::IsInWindow() const noexcept
{
	return isInWindow;
}

bool Mouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool Mouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

Mouse::Event Mouse::Read() noexcept
{
	if (mousebuffer.size() > 0u)	//jeœli kolejka wiêksza od 0 to zwróæ pierwszy event w kolejce i go z niej usuñ
	{
		Mouse::Event e = mousebuffer.front();
		mousebuffer.pop();
		return e;
	}
	else					//Jeœli kolejka pusta to wywo³aj konstruktor bezarg który zwróci event invalid
	{
		return Mouse::Event();
	}
}

void Mouse::Flush() noexcept
{
	mousebuffer = std::queue<Mouse::Event>();
}

void Mouse::OnRightPressed(int xn, int yn) noexcept
{
	x = xn;
	y = yn;

	mousebuffer.push(Mouse::Event(Mouse::Event::Type::R_Pressed, *this));
	TrimBuffer();
}

void Mouse::OnLeftPressed(int xn, int yn) noexcept
{
	x = xn;
	y = yn;

	mousebuffer.push(Mouse::Event(Mouse::Event::Type::L_Pressed, *this));
	TrimBuffer();
}

void Mouse::OnRightReleased(int xn, int yn) noexcept
{
	x = xn;
	y = yn;

	mousebuffer.push(Mouse::Event(Mouse::Event::Type::R_Released, *this));
	TrimBuffer();
}

void Mouse::OnLeftReleased(int xn, int yn) noexcept
{
	x = xn;
	y = yn;

	mousebuffer.push(Mouse::Event(Mouse::Event::Type::L_Released, *this));
	TrimBuffer();
}

void Mouse::OnWheelUp(int xn, int yn) noexcept
{
	mousebuffer.push(Mouse::Event(Mouse::Event::Type::W_Up, *this));
	TrimBuffer();
}

void Mouse::OnWheelDown(int xn, int yn) noexcept
{
	mousebuffer.push(Mouse::Event(Mouse::Event::Type::W_Down, *this));
	TrimBuffer();
}

void Mouse::OnMouseMove(int xn, int yn) noexcept
{
	x = xn;
	y = yn;

	mousebuffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
	TrimBuffer();
}

void Mouse::OnMouseEnter() noexcept
{
	isInWindow = true;
	mousebuffer.push(Mouse::Event(Mouse::Event::Type::Enter, *this));
	TrimBuffer();
}

void Mouse::OnMouseLeave() noexcept
{
	isInWindow = false;
	mousebuffer.push(Mouse::Event(Mouse::Event::Type::Leave, *this));
	TrimBuffer();
}

void Mouse::TrimBuffer() noexcept
{
	while (mousebuffer.size() > mousebufferSize)
	{
		mousebuffer.pop();
	}
}

//Better wheel control (you can just check if <0 or >0)
void Mouse::OnWheelCarry(int xn, int yn, int delta) noexcept
{
	wheelCarry+=delta;
	while (wheelCarry >= WHEEL_DELTA)
	{
		wheelCarry -= WHEEL_DELTA;
		OnWheelUp(xn, yn);
	}
	while (wheelCarry <= -WHEEL_DELTA)
	{
		wheelCarry += WHEEL_DELTA;
		OnWheelDown(xn, yn);
	}
}