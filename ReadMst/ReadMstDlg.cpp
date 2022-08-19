
// ReadMstDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ReadMst.h"
#include "ReadMstDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadMstDlg ��ȭ ����



CReadMstDlg::CReadMstDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READMST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadMstDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReadMstDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CReadMstDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CReadMstDlg �޽��� ó����

BOOL CReadMstDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CReadMstDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CReadMstDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CReadMstDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CReadMstDlg::FileBrowse(CString& sPath)
{
	sPath = _T("");

	/* Load from file */
	CString FilePath;
	CFileFind finder;
	CString SrchPath, strTitleMsg, strErrMsg;

	CWaitCursor mCursor;

	CString DirPath[10];
	CString strWorkDir;
	BOOL bResult;

	CString strMcNum;
	int nAoiMachineNum = 0;

	// File Open Filter 
	static TCHAR BASED_CODE szFilter[] = _T("Mst Files (*.mst)|*.mst|All Files (*.*)|*.*||");

	// CFileDialog 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	// Win2k Style FileDialog Box
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12; // +12�� Win2k Style�� ���̾�α� �ڽ��� Open��.

	// Open Directory
	TCHAR strPrevDir[MAX_PATH];
	DWORD dwLength = GetCurrentDirectory(MAX_PATH, strPrevDir);
	strWorkDir = strPrevDir;
	dlg.m_ofn.lpstrInitialDir = strWorkDir;

	bResult = 0;

	// Dialog Open
	if (dlg.DoModal() == IDOK)
	{
		sPath = FilePath = dlg.GetPathName();
		return TRUE;
	}

	return FALSE;
}

BOOL CReadMstDlg::LoadStripRgnFromCam(CString sPath, CString& sData)
{
	CString sName[MAX_PATH] = 
	{
		_T("nMode"),									// 0 : Full Mode, 1 : Strip Mode
		_T("nMSwath"), 									// ���Ͱ� ������ ȸ��.
		_T("NodeNumX"), _T("NodeNumY"),					// �� ��� �� ����
		_T("PanelPixelX"), _T("PanelPixelY"), 			// ��ü �ǳ� �̹����� ũ��		
		_T("OvrXPix"), _T("OvrYPix"),					// �� ������ �������Ǵ� �κ��� ũ��		 
		_T("ProcSizeX"), _T("ProcSizeY"),				// �� ��� ���� ũ��	 
		_T("nCell"),									// ��ü �� ����
		_T("nIPU"),										// AOI�� IPU ����
		_T("CameraValidPixel"), 						// ���� �˻��ϱ� ���� ���Ǵ� �̹����� X�� ũ��
		_T("nScanMarginX"), _T("nScanMarginY"), 		// ���� ���Ǵ� �̹����� �� ��������� �������� ���� �̹����� ũ�� Ex) nScanMarginX = (8192 ? CameraValidPixel)/2
		_T("nRegionX"), _T("nRegionY"), 				// Reserved Data
		_T("nCellDivideX"), _T("nCellDivideY"), 		// �� ��Ʈ���� �� �� ���� �� ����
		_T("nCADPinPosPixX"), _T("nCADPinPosPixY"), 	// Pin Position x, y
		_T("nProcMarginX"), _T("nProcMarginY"),			// Reserved Data
		_T("StPosX"),									// �� ���� ���� ���κ��� X ��ġ
		_T("StPosY"),									// �� ���� ���� ���κ��� Y ��ġ
		_T("EdPosX"),									// �� ���� ������ �Ʒ��κ��� X ��ġ
		_T("EdPosY"), 									// �� ���� ������ �Ʒ��κ��� Y ��ġ
		_T("XSwathPixPos")								// ���Ͱ� �����̱� �����ϴ� ��ġ
	};

	CFile file;
	int Rsize, RsizeStPosX, RsizeStPosY, RsizeEdPosX, RsizeEdPosY, RsizeXSwathPixPos;
	int SizeI, SizeIXSwathPixPos, i, nData, nN;
	//char FileNCam[200];
	TCHAR FileNCam[200];

	nN = 0;
	sData = _T("");
	CString str;

	//strcpy(FileNCam, sPath);
	wsprintf(FileNCam, TEXT("%s"), sPath);

	if (!file.Open(FileNCam, CFile::modeRead))
	{
		if (!file.Open(FileNCam, CFile::modeRead))
		{
			return(FALSE);
		}
	}

	REGION_STRIP* pCellRgn = new REGION_STRIP;

	SizeI = sizeof(int) * RGN_STRIP_VARIABLE_NUM;
	Rsize = file.Read((void *)pCellRgn, SizeI);

	if (Rsize != SizeI)
	{
		AfxMessageBox(_T("MST File is incorrected."), MB_ICONSTOP | MB_OK);
		return(FALSE);
	}

	for (i = 0; i < RGN_STRIP_VARIABLE_NUM; i++)
	{
		//SizeI = sizeof(int);
		//Rsize = file.Read((void *)pCellRgn, SizeI);
		nData = *((&pCellRgn->nMode) + i);
		//str.Format(_T("%d"), nData);
		str.Format(_T("%s: %d"), sName[nN], nData); nN++;
		sData += str;
		sData += _T("\r\n");
	}
	sData += _T("\r\n");

	int nCell = pCellRgn->NodeNumX * pCellRgn->NodeNumY;
	SizeI = sizeof(int) * nCell;
	RsizeStPosX = file.Read((void *)&pCellRgn->StPosX, SizeI);
	RsizeStPosY = file.Read((void *)&pCellRgn->StPosY, SizeI);
	RsizeEdPosX = file.Read((void *)&pCellRgn->EdPosX, SizeI);
	RsizeEdPosY = file.Read((void *)&pCellRgn->EdPosY, SizeI);

	for (i = 0; i < nCell; i++)
	{
		nData = *((pCellRgn->StPosX) + i);
		//str.Format(_T("%d"), nData);
		str.Format(_T("%s: %d"), sName[nN], nData);
		sData += str;
		sData += _T("\r\n");
	}
	sData += _T("\r\n"); nN++;

	for (i = 0; i < nCell; i++)
	{
		nData = *((pCellRgn->StPosY) + i);
		//str.Format(_T("%d"), nData);
		str.Format(_T("%s: %d"), sName[nN], nData);
		sData += str;
		sData += _T("\r\n");
	}
	sData += _T("\r\n"); nN++;

	for (i = 0; i < nCell; i++)
	{
		nData = *((pCellRgn->EdPosX) + i);
		//str.Format(_T("%d"), nData);
		str.Format(_T("%s: %d"), sName[nN], nData);
		sData += str;
		sData += _T("\r\n");
	}
	sData += _T("\r\n"); nN++;

	for (i = 0; i < nCell; i++)
	{
		nData = *((pCellRgn->EdPosY) + i);
		//str.Format(_T("%d"), nData);
		str.Format(_T("%s: %d"), sName[nN], nData);
		sData += str;
		sData += _T("\r\n");
	}
	sData += _T("\r\n"); nN++;


	SizeIXSwathPixPos = sizeof(int) * pCellRgn->nMSwath;
	RsizeXSwathPixPos = file.Read((void *)&pCellRgn->XSwathPixPos, SizeIXSwathPixPos);

	if (RsizeStPosX != SizeI && RsizeStPosY != SizeI && RsizeEdPosX != SizeI && RsizeEdPosY != SizeI && RsizeXSwathPixPos != SizeIXSwathPixPos)
	{
		AfxMessageBox(_T("MST File is incorrected."),MB_ICONSTOP|MB_OK);
		return(FALSE);
	}
	for (i = 0; i < pCellRgn->nMSwath; i++)
	{
		nData = *((pCellRgn->XSwathPixPos) + i);
		//str.Format(_T("%d"), nData);
		str.Format(_T("%s: %d"), sName[nN], nData);
		sData += str;
		sData += _T("\r\n");
	}
	sData += _T("\r\n");


	if (pCellRgn)
		delete pCellRgn;

	return(TRUE);
}

void CReadMstDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString sPath;

	if (!FileBrowse(sPath))
		return;
	GetDlgItem(IDC_STATIC_PATH)->SetWindowText(sPath);

	CString sData;
	if(!LoadStripRgnFromCam(sPath, sData))
		AfxMessageBox(_T("LoadStripRgnFromCam failed!"));
	GetDlgItem(IDC_EDIT1)->SetWindowText(sData);
}
