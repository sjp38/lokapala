// MessengerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Operator.h"
#include "MessengerDlg.h"

#include "ConnectedHostsDTO.h"
#include "MessageDTO.h"

// CMessengerDlg dialog

IMPLEMENT_DYNAMIC(CMessengerDlg, CDialog)

CMessengerDlg::CMessengerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessengerDlg::IDD, pParent)
{

}

CMessengerDlg::~CMessengerDlg()
{
}

void CMessengerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONVERSATION_LIST, m_conversationBox);
	DDX_Control(pDX, IDC_CONNECTED_LIST, m_connectedList);
	DDX_Control(pDX, IDC_INPUT, m_input);
}


BEGIN_MESSAGE_MAP(CMessengerDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SEND, &CMessengerDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CMessengerDlg message handlers
/**@brief	���̾�α� ������ ������� ����
 */
HBRUSH CMessengerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch( nCtlColor ) 
	{
	case CTLCOLOR_DLG :
		return (HBRUSH)CreateSolidBrush( RGB(255,255,255) ); // ���ϴ� �����ڵ带 �Է��Ѵ�.
		break;
	case CTLCOLOR_STATIC :
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(255,255,255));
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

/**@brief	Ÿ��Ʋ�� ���� ������ �� �ֵ��� �Ѵ�.
 */
void CMessengerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialog::OnLButtonDown(nFlags, point);
}

/**@brief	�޼��� ���� ��ư Ŭ��.
 */
void CMessengerDlg::OnBnClickedSend()
{
	// TODO: Add your control notification handler code here
	CMessageDTO message;
	m_input.GetWindowTextW(message.m_message);

	int nCount = m_connectedList.GetSelCount();
	CArray<int,int> selected;
	selected.SetSize(nCount);
	m_connectedList.GetSelItems(nCount, selected.GetData());

	for(int i=0; i<selected.GetCount(); i++)
	{		
		m_connectedList.GetText(selected[i], message.m_hostAddress);		
		CCBFMediator::Instance()->PostTextMessgeTo(&message);
	}	
}

/**@brief	���� ���̾�α� ���� ��, ���� ����� ȣ��Ʈ �ּҸ� ���� ��Ͽ� �����Ѵ�.
 */
BOOL CMessengerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CConnectedHostsDTO *connectedHostsData = (CConnectedHostsDTO *)CCBFMediator::Instance()->GetConnectedHosts();

	for(int i=0; i<connectedHostsData->m_connected.GetCount(); i++)
	{
		m_connectedList.AddString(connectedHostsData->m_connected[i].m_hostAddress);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/**@brief	��ȭ ������ ǥ���Ѵ�.
 */
void CMessengerDlg::DisplayConversation(CString a_message)
{	
	int length = m_conversationBox.GetWindowTextLengthW();
	m_conversationBox.SetSel(length, length);
	m_conversationBox.ReplaceSel(a_message+_T("\r\n"));
}