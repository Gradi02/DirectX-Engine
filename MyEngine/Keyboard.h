/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  Keyboard class header file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;	//This class is an extension of window class

public:
	class Event
	{
	public:
		enum class Type
		{
			Pressed,
			Released,
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event() noexcept: type(Type::Invalid), code(0u) {}
		Event(Type ty, unsigned char cd) noexcept: type(ty), code(cd) {}
		bool IsPressed() const noexcept 
		{
			return type == Type::Pressed;
		}
		bool IsReleased() const noexcept
		{
			return type == Type::Released;
		}
		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
		unsigned char GetCode() const noexcept
		{
			return code;
		}
	};
public:
	Keyboard() = default;	//deklaracja konstrukora domyœlnego - w zasadzie zbêdna ale warto zaznaczyæ
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	//Keys events
	bool KeyIsPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyQueueIsEmpty() const noexcept;
	void FlushKeyQueue() noexcept;
	//Char events
	char ReadChar() noexcept;
	bool CharQueueIsEmpty() const noexcept;
	void FlushCharQueue() noexcept;
	void Flush() noexcept;
	//Autorepet control
	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool IsAutorepeatEnabled() const noexcept;
private:
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;	//256 bo tyle max wirtualnych kodów klawiszy mo¿na mieæ
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keystates;	//bitset klawiszy
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;
};