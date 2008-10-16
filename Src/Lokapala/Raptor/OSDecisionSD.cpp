/**@file	OSDecisionSD.cpp
 * @brief	OSM�� DecisionSD�� ����Լ� ����
 * @author	siva
 */

#include "stdafx.h"
#include "OSDecisionSD.h"

#include "Resource.h"

/**@brief	����� ���μ����� �˸���.\n
 *			�׽�Ʈ������ �ܼ��� ����Ʈ�ڽ��� �� �̸��� ǥ���Ѵ�.
 * @param	a_executedProcess	����� ���μ����� �̸�
 */
void COSDecisionSD::NotifyExecutedProcess(CString a_executedProcess)
{
	CListBox *pListBox = (CListBox *)( (CCBFMediator::Instance()->GetMainDlg())->GetDlgItem(IDC_LISTTEST) );
	pListBox->AddString(a_executedProcess);
	CCBFMediator::Instance()->ReportExecutedProcess(&a_executedProcess);
}