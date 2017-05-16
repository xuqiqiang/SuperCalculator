#pragma once


// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
	enum { IDD = IDD_SETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
