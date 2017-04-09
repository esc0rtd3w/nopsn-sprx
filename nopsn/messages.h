#pragma once

#include "core.h"
#include "dialog.h"

using namespace Dialog;


void PrintToXMB(char* text)
{
	msgdialog_mode = MODE_STRING_OK;
	Show(text);
}



