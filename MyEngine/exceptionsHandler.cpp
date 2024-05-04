/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  Exceptions Handler Code File: 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "exceptionsHandler.h"
#include <sstream>

//Konstruktor klasy exception
EngineExceptions::EngineExceptions(int lineN, const char* fileN) noexcept
	:line(lineN), file(fileN) {}

const char* EngineExceptions::what() const noexcept
{
	std::ostringstream oss;		//coœ jak string builder w javie
	oss << GetType() << std::endl << GetOriginString();			//zbiera info
	whatBuffer = oss.str();				//zapisuje info do buffera by go nie zgubiæ
	return whatBuffer.c_str();			//zwraca pointer na const char*
}

const char* EngineExceptions::GetType() const noexcept
{
	return "EngineException";
}

int EngineExceptions::GetLine() const noexcept
{
	return line;
}

const std::string& EngineExceptions::GetFile() const noexcept
{
	return file;
}

std::string EngineExceptions::GetOriginString() const noexcept
{
	std::ostringstream oss;		//coœ jak string builder w javie
	oss << "[FILE] " << file << std::endl
		<< "[LINE] " << line << std::endl;
	return oss.str();
}