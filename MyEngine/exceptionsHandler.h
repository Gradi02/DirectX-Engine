/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  My First C++ DirectX game engine!                                                                                                         
//  Adrian Nowowiejski / 05.2024                                                                           
//  
//  Exceptions Handler Header File: 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <exception>
#include <string>
#pragma once

class EngineExceptions : public std::exception
{
public:
	EngineExceptions(int lineN, const char* fileN) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private: 
	int line;
	std::string file;
	int returnVal;
protected:
	mutable std::string whatBuffer;
};