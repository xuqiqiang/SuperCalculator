
// SuperCalculatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SuperCalculator.h"
#include "SuperCalculatorDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "Calculator.h"
#include "MfcCall.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CSuperCalculatorDlg �Ի���



CSuperCalculatorDlg::CSuperCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSuperCalculatorDlg::IDD, pParent)
	, point(5)
	, CalcThreadProcStart(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuperCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cb);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
}

BEGIN_MESSAGE_MAP(CSuperCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSuperCalculatorDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CSuperCalculatorDlg::OnEnChangeEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSuperCalculatorDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDCANCEL, &CSuperCalculatorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CSuperCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSuperCalculatorDlg::OnBnClickedButton2)
	ON_CBN_EDITCHANGE(IDC_COMBO1, &CSuperCalculatorDlg::OnCbnEditchangeCombo1)
END_MESSAGE_MAP()


// CSuperCalculatorDlg ��Ϣ�������

BOOL CSuperCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//m_edit3.SetReadOnly(1);
	//m_edit3.EnableWindow(TRUE);

	m_cb.AddString(_T("+"));
	m_cb.AddString(_T("-"));
	m_cb.AddString(_T("*"));
	m_cb.AddString(_T("/"));
	m_cb.AddString(_T("exp"));
	m_cb.AddString(_T("%"));
	m_cb.AddString(_T("����"));


	m_cb.SetCurSel(0);

	SetDlgItemText(IDC_STATIC5, _T(""));

	readSetting();
	//m_edit1.ModifyStyle(WS_HSCROLL|ES_AUTOHSCROLL|ES_MULTILINE | ES_WANTRETURN, 0);
	//m_edit1.ModifyStyle(WS_HSCROLL | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_MULTILINE | ES_WANTRETURN, 0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSuperCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == IDD_SETTING_DIALOG)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С��������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSuperCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSuperCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSuperCalculatorDlg::OnBnClickedOk()
{
	//CTime::GetSecond
	//SetDlgItemText(IDC_EDIT3, _T("������..."));
	/*
	CString data1,data2;
	//Operator op = m_cb.GetCurSel();
	GetDlgItemText(IDC_EDIT1, data1);
	GetDlgItemText(IDC_EDIT2, data2);

	Operator op;
	GetDlgItemText(IDC_COMBO1, op);
	CString result;
	calculate(data1, op, data2, result, point);
	SetDlgItemText(IDC_EDIT3, result);*/

	if (!CalcThreadProcStart){
		CalcThreadProcStart = true;

		AfxBeginThread(WaitThreadProc, this, THREAD_PRIORITY_LOWEST, 0, 0, NULL);
		AfxBeginThread(CalcThreadProc, this, THREAD_PRIORITY_TIME_CRITICAL, 0, 0, NULL);

	}
	else{
		MessageBox(_T("���ڼ�����"), NULL, MB_OK);
	}

	//long t1 = GetTickCount();//����ν�����ȡ��ϵͳ����ʱ��(ms)

	//int i;
	////unsigned __int64 a = 5;// 999999999;
	////unsigned __int64 b = 5;// 999999999;
	////unsigned __int64 c;
	////for (i = 0; i < 100000000; i++){
	////	c = a*b;
	////}

	//int a1 = 5;// 9999;
	//int b1 = 5;// 9999;
	//int c1;

	//for (i = 0; i < 100000000; i++){
	//	c1 = a1*b1;
	//	c1 = a1*b1;
	//	c1 = a1*b1;
	//	c1 = a1*b1;
	//	c1 += c1;
	//	c1 += c1;
	//	c1 += c1;

	//}

	//long t2 = GetTickCount();//����ν�����ȡ��ϵͳ����ʱ��(ms)
	//CString str;
	//str.Format(_T("��ʱ%d"), t2-t1);

	//MessageBox(str, NULL, MB_OK);
	//AfxEndThread(WaitThreadProc);
}


void CSuperCalculatorDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSuperCalculatorDlg::OnCbnSelchangeCombo1()
{
	if (m_cb.GetCurSel()==6){
		m_edit1.SetReadOnly(1);
	}
	else{
		m_edit1.SetReadOnly(0);
	}
}

void CSuperCalculatorDlg::OnCbnEditchangeCombo1()
{
	Operator op;
	GetDlgItemText(IDC_COMBO1, op);
	if (op.Compare(_T("����")) == 0){
		m_edit1.SetReadOnly(1);
	}
	else{
		m_edit1.SetReadOnly(0);
	}
}


void CSuperCalculatorDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	//OnSysCommand(IDM_ABOUTBOX,NULL);
}


void CSuperCalculatorDlg::OnBnClickedButton1()
{
	OnSysCommand(IDM_ABOUTBOX, NULL);
}


void CSuperCalculatorDlg::OnBnClickedButton2()
{
	CSettingDlg dlgSetting = new CSettingDlg(this);
	dlgSetting.setPoint(point);
	dlgSetting.DoModal();
}


void CSuperCalculatorDlg::readSetting()
{
	//char * pszFileName = "C://myfile.txt";
	LPCTSTR pszFileName = _T("C://MySetting.txt");
	//SetDlgItemText(IDC_EDIT3, pszFileName);

	CStdioFile myFile;
	//myFile.Open()
	CFileException fileException;

	if (!myFile.Open(pszFileName, CFile::typeText | CFile::modeRead, 0))
	{
		return;
	}

	CString str;
	myFile.ReadString(str);
	int res = _ttoi(str);
	if (res > 0)
		point = res;
	else if (res == 0){
		if (str.Compare(_T("0"))==0)
			point = res;
	}
		
	//SetDlgItemText(IDC_EDIT3, str);

	myFile.Close();

}





UINT CSuperCalculatorDlg::CalcThreadProc(LPVOID pParam)
{

	long t1 = GetTickCount();//����ο�ʼǰȡ��ϵͳ����ʱ��(ms) ��

	
	CSuperCalculatorDlg * pDlg = (CSuperCalculatorDlg *)pParam;

	CString data1, data2;
	//Operator op = m_cb.GetCurSel();
	pDlg->GetDlgItemText(IDC_EDIT1, data1);
	pDlg->GetDlgItemText(IDC_EDIT2, data2);

	Operator op;
	pDlg->GetDlgItemText(IDC_COMBO1, op);
	CString result;
	calculate(data1, op, data2, result, pDlg->point);

	pDlg->CalcThreadProcStart = false;

	pDlg->SetDlgItemText(IDC_EDIT3, result);


	//pDlg->SetDlgItemText(IDC_STATIC5, _T("I LOVE YOU"));
	//pDlg->GetDlgItem(IDC_STATIC5)->SetWindowText(_T("I LOVE YOU"));
	
	

	long t2 = GetTickCount();//����ν�����ȡ��ϵͳ����ʱ��(ms)
	CString str;
	str.Format(_T("��ʱ:%dms"), t2 - t1);//ǰ��֮� ��������ʱ��
	//AfxMessageBox(str);//��ȡϵͳ����ʱ�� ��
	pDlg->SetDlgItemText(IDC_STATIC5, str);


	/*CString str;
	str.Format(_T("��ʱ%d"), ct.GetSecond() - time);

	pDlg->MessageBox(str, NULL, MB_OK); */


	return 0;
}


UINT CSuperCalculatorDlg::WaitThreadProc(LPVOID pParam)
{
	CSuperCalculatorDlg * pDlg = (CSuperCalculatorDlg *)pParam;

	int frame = 0;
	CString ani[4] = { _T("."), _T(".."), _T("..."), _T("...."), };
	while (pDlg->CalcThreadProcStart){
		pDlg->SetDlgItemText(IDC_EDIT3, _T("������") + ani[frame]);
		frame = (frame + 1) % 4;
		Sleep(500);
	}
	return 0;
}
