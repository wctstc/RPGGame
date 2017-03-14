#pragma once

#include <conio.h>
#include "Struct.h"
#include "UIBase.h"

class OptionsArrow
{
public:
	OptionsArrow(void);
	~OptionsArrow(void);
public:
	bool Init( OptionsPosition &optionsPosition);
	int SelectOption();
	
private:
	OptionsPosition m_optionsPosition;
};

