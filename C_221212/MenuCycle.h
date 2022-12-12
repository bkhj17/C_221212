#pragma once
#include <string>

class MenuCycle {
public:
	virtual bool IsClose() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual bool Render(std::string& renderTarget) = 0;
	virtual void BeforeClose() = 0;
};