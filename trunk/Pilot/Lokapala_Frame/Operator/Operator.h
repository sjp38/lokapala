// Operator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// COperatorApp:
// See Operator.cpp for the implementation of this class
//

class COperatorApp : public CWinApp
{
public:
	COperatorApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern COperatorApp theApp;