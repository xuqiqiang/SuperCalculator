#pragma once


// CSettingDlg �Ի���

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingDlg();

// �Ի�������
	enum { IDD = IDD_SETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	HICON m_hIcon;

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void setPoint(int point);
//	int new_point;
private:
	int new_point;
public:
	afx_msg void OnBnClickedOk();
	void writeSetting();
};
