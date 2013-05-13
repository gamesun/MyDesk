
// MyDeskDlg.h : header file
//

#pragma once
#include <vector>
#include "LnkParser.h"

typedef struct _app_info {
	CStatic *pstnIcon;
	CStatic *pstnTitle;

	CString strPath;
	CString strArgs;
	CString strDir;
	CString strIcon;
	CString strTip;
	int nIconIdx;
} ST_APP_INFO, *PST_APP_INFO;

// CMyDeskDlg dialog
class CMyDeskDlg : public CDialogEx
{
// Construction
public:
	CMyDeskDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYDESK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;


	CString m_strLnkFolder;
	CString m_strUserDesktopPath;
	CString m_strPublicDesktopPath;
	CLnkParser m_lnkparser;
	std::vector<ST_APP_INFO> m_vstAppInfo;


	void LoadSetting( void );
	void FindAllLnk( const CString& );
	void GetLnkInfo( const CString& );


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
