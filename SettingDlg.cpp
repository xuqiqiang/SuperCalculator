// SettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperCalculator.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include "SuperCalculatorDlg.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettingDlg::IDD, pParent)
	, new_point(0)
{
	/*CString str_point;
	str_point.Format(_T("%d"), new_point);

	SetDlgItemText(IDC_EDIT1, str_point);*/

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CString str_point;
	str_point.Format(_T("%d"), new_point);

	SetDlgItemText(IDC_EDIT1, str_point);
	//m_edit1.ModifyStyle(WS_HSCROLL|ES_AUTOHSCROLL|ES_MULTILINE | ES_WANTRETURN, 0);
	//m_edit1.ModifyStyle(WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | ES_WANTRETURN, 0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// CSettingDlg 消息处理程序


void CSettingDlg::setPoint(int point)
{
	new_point = point;
}


void CSettingDlg::OnBnClickedOk()
{

	CString str_point;
	GetDlgItemText(IDC_EDIT1, str_point);
	new_point = _ttoi(str_point);

	writeSetting();

	CSuperCalculatorDlg *pParent;
	pParent = (CSuperCalculatorDlg *)GetParent();
	pParent->point = new_point;
	CDialogEx::OnOK();
}


void CSettingDlg::writeSetting()
{
	LPCTSTR pszFileName = _T("C://MySetting.txt");

	CStdioFile myFile;
	CFileException fileException;

	if (!myFile.Open(pszFileName, CFile::modeCreate | CFile::typeText | CFile::modeWrite, 0))
	{
		return;
	}

	CString str_data;
	str_data.Format(_T("%d"), new_point);

	myFile.WriteString(str_data);

	myFile.Close();
}
