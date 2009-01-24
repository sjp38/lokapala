#include "stdafx.h"
#include "SampleManagerFacade.h"

void SampleManagerFacade::CallSampleManager()
{
	AfxMessageBox(_T("sample manager called"));
	SampleManager2SD::Instance()->CallSampleManager2();
}