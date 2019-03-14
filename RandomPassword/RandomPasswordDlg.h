// RandomPasswordDlg.h: 头文件
//

#pragma once

// CRandomPassword 对话框
class CRandomPassword : public CDialogEx
{
// 构造
public:
	CRandomPassword(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RANDOMPASSWORD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnChangePasswordlength();
	afx_msg void OnClickedGeneratepassword();
	afx_msg void OnClickedCopytoclipboard();
};
