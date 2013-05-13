
// MyDeskDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyDesk.h"
#include "MyDeskDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDeskDlg dialog




CMyDeskDlg::CMyDeskDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDeskDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDeskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyDeskDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyDeskDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMyDeskDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMyDeskDlg message handlers

BOOL CMyDeskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	LoadSetting();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDeskDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDeskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyDeskDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
}


void CMyDeskDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

/*
| No. | SYSINFO.nWinMajor | SYSINFO.nWinMinor | OS     |
|-----+-------------------+-------------------+--------|
|   1 |                 4 |                 0 | win95  |
|   2 |                 4 |                 1 | win98  |
|   3 |                 5 |                 0 | win2k  |
|   4 |                 5 |                 1 | winXP  |
|   5 |                 5 |                 2 | win2k3 |
|   6 |                 6 |                 0 | vista  |
|   7 |                 6 |                 1 | win7   |
*/
void CMyDeskDlg::LoadSetting( void )
{
	const unsigned char ucOSVer[3][3] = {
				/* Minor	0	1	2	*/
	/* Major4 - 4: 0 */	{	1,	2,	-1	},
	/* Major5 - 4: 1 */	{	3,	4,	5	},
	/* Major6 - 4: 2 */	{	6,	7,	-1	}
	};

	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof( os );
	GetVersionEx( (OSVERSIONINFO *)&os );

	switch ( ucOSVer[os.dwMajorVersion - 4][os.dwMinorVersion] ){
	case -1:
		// unknown
		break;
	case 1:		// win95

		break;
	case 2:		// win98

		break;
	case 3:		// win2k

		break;
	case 4:		// winXP

		break;
	case 5:		// win2k3

		break;
	case 6:		// vista

		break;
	case 7:		// win7
		m_strUserDesktopPath = "C:\\Users\\gamesun\\Desktop";
		m_strPublicDesktopPath = "C:\\Users\\Public\\Desktop";
		break;
	default:
		break;
	}
	
	FindAllLnk( m_strUserDesktopPath );
	FindAllLnk( m_strPublicDesktopPath );

	//GetModuleFileName( NULL, m_strLnkFolder.GetBuffer(MAX_PATH), MAX_PATH );
	//m_strLnkFolder.ReleaseBuffer();

	//m_strLnkFolder = m_strLnkFolder.Left( m_strLnkFolder.ReverseFind( '\\' ) ) + "\\Link";
	//TRACE( "%s\n", m_strLnkFolder );

	//FindAllLnk( m_strLnkFolder );
}

void CMyDeskDlg::FindAllLnk( const CString& strDir )
{
	CString strFile;
	CFileFind find;
	BOOL bFinished = find.FindFile( strDir + "\\*.*" );

	while ( bFinished ){
		bFinished = find.FindNextFile();
		if ( ! find.IsDots() ){
			strFile.Format( "%s\\%s", strDir, find.GetFileName() );
			TRACE( "\n%s\n", strFile );
			GetLnkInfo( strFile );
		}
	}
	find.Close();
}

void CMyDeskDlg::GetLnkInfo( const CString& strDest )
{
	ST_APP_INFO stAppInfo;
	CHAR szBuff[MAX_PATH];

	if ( FAILED( m_lnkparser.LoadFile( strDest.AllocSysString() ) ) ){
		return;
	}

	if ( SUCCEEDED( m_lnkparser.GetTargetPath( szBuff, MAX_PATH ) ) ){
		stAppInfo.strPath.Format( "%s", szBuff );
		TRACE( "Path\t%s\n", szBuff );
	}

	if ( SUCCEEDED( m_lnkparser.GetTargetArguments( szBuff, MAX_PATH ) ) ){
		stAppInfo.strArgs.Format( "%s", szBuff );
		TRACE( "Args\t%s\n", szBuff );
	}

	if ( SUCCEEDED( m_lnkparser.GetTargetWorkingDirectory( szBuff, MAX_PATH ) ) ){
		stAppInfo.strDir.Format( "%s", szBuff );
		TRACE( "Dir \t%s\n", szBuff );
	}

	if ( SUCCEEDED( m_lnkparser.GetTargetIconLocation( szBuff, MAX_PATH, &stAppInfo.nIconIdx ) ) ){
		stAppInfo.strIcon.Format( "%s", szBuff );
		TRACE( "Icon\t%s,%d\n", szBuff, stAppInfo.nIconIdx );
	}

	//	stAppInfo.strTip;

	stAppInfo.pstnIcon  = NULL;
	stAppInfo.pstnTitle = NULL;


	m_vstAppInfo.push_back( stAppInfo );
}
