
// ReadMstDlg.h : ��� ����
//

#pragma once

#define RGN_STRIP_VARIABLE_NUM	23		// REGION_STRIP ����ü���� �迭�� ������ ������ ����
#define MAX_NodeNumX			200
#define MAX_NodeNumY			200
#define MAX_NMSWATH				100

typedef struct {
	int nMode;											// 0 : Full Mode, 1 : Strip Mode
	int nMSwath;										// ���Ͱ� ������ ȸ��.
	int NodeNumX, NodeNumY;								// �� ��� �� ����
	int PanelPixelX, PanelPixelY;						// ��ü �ǳ� �̹����� ũ��
	int OvrXPix, OvrYPix;								// �� ������ �������Ǵ� �κ��� ũ��
	int ProcSizeX, ProcSizeY;							// �� ��� ���� ũ��
	int nCell;											// ��ü �� ����
	int nIPU;											// AOI�� IPU ����
	int CameraValidPixel;								// ���� �˻��ϱ� ���� ���Ǵ� �̹����� X�� ũ��
	int nScanMarginX, nScanMarginY;						// ���� ���Ǵ� �̹����� �� ��������� �������� ���� �̹����� ũ�� Ex) nScanMarginX = (8192 ? CameraValidPixel)/2
	int nRegionX, nRegionY;								// Reserved Data
	int nCellDivideX, nCellDivideY;						// �� ��Ʈ���� �� �� ���� �� ����
	int nCADPinPosPixX, nCADPinPosPixY;					// Pin Position X, y
	int nProcMarginX, nProcMarginY;						// Reserved Data
	int StPosX[MAX_NodeNumX * MAX_NodeNumY];			// �� ���� ���� ���κ��� X ��ġ
	int StPosY[MAX_NodeNumX * MAX_NodeNumY];			// �� ���� ���� ���κ��� Y ��ġ
	int EdPosX[MAX_NodeNumX * MAX_NodeNumY];			// �� ���� ������ �Ʒ��κ��� X ��ġ
	int EdPosY[MAX_NodeNumX * MAX_NodeNumY];			// �� ���� ������ �Ʒ��κ��� Y ��ġ
	int XSwathPixPos[MAX_NMSWATH];						// ���Ͱ� �����̱� �����ϴ� ��ġ
} REGION_STRIP;		//Total 100476 Byte

// CReadMstDlg ��ȭ ����
class CReadMstDlg : public CDialogEx
{
	BOOL FileBrowse(CString& sPath);
	BOOL LoadStripRgnFromCam(CString sPath, CString& sData);

// �����Դϴ�.
public:
	CReadMstDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READMST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
