// RandomPasswordDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "RandomPassword.h"
#include "RandomPasswordDlg.h"
#include "afxdialogex.h"
#include "Password.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRandomPassword 对话框
CRandomPassword::CRandomPassword(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RANDOMPASSWORD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRandomPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRandomPassword, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(PasswordLength, &CRandomPassword::OnChangePasswordlength)
	ON_BN_CLICKED(GeneratePassword, &CRandomPassword::OnClickedGeneratepassword)
	ON_BN_CLICKED(CopyToClipboard, &CRandomPassword::OnClickedCopytoclipboard)
END_MESSAGE_MAP()

// CRandomPassword 消息处理程序
BOOL CRandomPassword::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	((CButton*)GetDlgItem(LowerCaseLetters))->SetCheck(1);
	GetDlgItem(PasswordLength)->SetWindowTextW(_T("10"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CRandomPassword::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRandomPassword::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CRandomPassword::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE://ESC键
			return true;
		case VK_RETURN://Enter键
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CRandomPassword::OnChangePasswordlength()
{
	UpdateData(true);
	CString length;
	GetDlgItem(PasswordLength)->GetWindowTextW(length);
	length.ReleaseBuffer();
	if (_ttoi(length) < 1)
	{
		GetDlgItem(PasswordLength)->SetWindowTextW(_T("1"));
	}
	else if (_ttoi(length) > 100)
	{
		GetDlgItem(PasswordLength)->SetWindowTextW(_T("100"));
	}
}

void CRandomPassword::OnClickedGeneratepassword()
{
	int number = ((CButton*)GetDlgItem(Numbers))->GetCheck();
	int upperCaseLetter = ((CButton*)GetDlgItem(UpperCaseLetters))->GetCheck();
	int lowerCaseLetter = ((CButton*)GetDlgItem(LowerCaseLetters))->GetCheck();
	CString length;
	GetDlgItem(PasswordLength)->GetWindowTextW(length);

	Password pass;
	CString password = CString(pass.getPassword(number, upperCaseLetter, lowerCaseLetter, _ttoi(length)).c_str());
	GetDlgItem(Passwords)->SetWindowTextW(password);
}

void CRandomPassword::OnClickedCopytoclipboard()
{
	if (OpenClipboard())
	{
		EmptyClipboard();
		CString pass;
		GetDlgItem(Passwords)->GetWindowTextW(pass);

		HANDLE hClip = GlobalAlloc(GMEM_MOVEABLE, pass.GetLength() * 2 + 1);
		LPWSTR lpstrcpy = (LPWSTR)GlobalLock(hClip);
		memcpy(lpstrcpy, pass, pass.GetLength() * 2 + 1);
		GlobalUnlock(hClip);
		SetClipboardData(CF_UNICODETEXT, lpstrcpy);

		CloseClipboard();
	}
}
