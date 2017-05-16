
// SuperCalculatorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CSuperCalculatorDlg �Ի���
class CSuperCalculatorDlg : public CDialogEx
{
// ����
public:
	CSuperCalculatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SUPERCALCULATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_cb;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	CEdit m_edit1;
	CEdit m_edit3;
	afx_msg void OnBnClickedButton2();
	int point;
	void readSetting();
	afx_msg void OnCbnEditchangeCombo1();
	static UINT CalcThreadProc(LPVOID pParam);
	bool CalcThreadProcStart;
	static UINT WaitThreadProc(LPVOID pParam);
};
