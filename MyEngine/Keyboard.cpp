/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  Keyboard class file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Keyboard.h"


bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];	//odczytuje po indeksie keycode z bittablicy
}

Keyboard::Event Keyboard::ReadKey() noexcept
{
	if (keybuffer.size() > 0u)	//je�li kolejka wi�ksza od 0 to zwr�� pierwszy event w kolejce i go z niej usu�
	{
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	else					//Je�li kolejka pusta to wywo�aj konstruktor bezarg kt�ry zwr�ci event invalid
	{
		return Keyboard::Event();
	}
}

bool Keyboard::KeyQueueIsEmpty() const noexcept
{
	return keybuffer.empty();
}

char Keyboard::ReadChar() noexcept
{
	if (charbuffer.size() > 0u)	//je�li kolejka wi�ksza od 0 to zwr�� pierwszy event w kolejce i go z niej usu�
	{
		unsigned char e = charbuffer.front();
		charbuffer.pop();
		return e;
	}
	else					//Je�li kolejka pusta to wywo�aj konstruktor bezarg kt�ry zwr�ci event invalid
	{
		return 0;
	}
}

bool Keyboard::CharQueueIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void Keyboard::FlushKeyQueue() noexcept
{
	keybuffer = std::queue<Event>();
}

void Keyboard::FlushCharQueue() noexcept
{
	charbuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
	FlushKeyQueue();
	FlushCharQueue();
}

void Keyboard::EnableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool Keyboard::IsAutorepeatEnabled() const noexcept
{
	return autorepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Pressed, keycode));
	TrimBuffer(keybuffer);
}

void Keyboard::OnKeyReleased(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Released, keycode));
	TrimBuffer(keybuffer);
}

void Keyboard::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void Keyboard::ClearState() noexcept
{
	keystates.reset();
}

template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept	//funkcja jest templatem aby mog�a dzia�a� dla charbuffera i keybuffera
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}
