/**@file	OSDecisionSD.cpp
 * @brief	OSM의 DecisionSD의 멤버함수 구현
 * @author	siva
 */

#include "stdafx.h"
#include "OSDecisionSD.h"

#include "Resource.h"

/**@brief	실행된 프로세스를 알린다.\n
 *			테스트에서는 단순히 리스트박스에 그 이름만 표시한다.
 * @param	a_executedProcess	실행된 프로세스의 이름
 */
void COSDecisionSD::NotifyExecutedProcess(CString a_executedProcess)
{
	CListBox *pListBox = (CListBox *)( (CCBFMediator::Instance()->GetMainDlg())->GetDlgItem(IDC_LISTTEST) );
	pListBox->AddString(a_executedProcess);
	CCBFMediator::Instance()->ReportExecutedProcess(&a_executedProcess);
}