#pragma once

#include <conio.h>
#include "Struct.h"
#include "UIBase.h"
#include "Singleton.h"

class OptionsArrow : public Singleton<OptionsArrow>
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

