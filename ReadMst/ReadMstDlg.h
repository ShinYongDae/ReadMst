
// ReadMstDlg.h : 헤더 파일
//

#pragma once

#define RGN_STRIP_VARIABLE_NUM	23		// REGION_STRIP 구조체에서 배열을 제외한 변수의 갯수
#define MAX_NodeNumX			200
#define MAX_NodeNumY			200
#define MAX_NMSWATH				100

typedef struct {
	int nMode;											// 0 : Full Mode, 1 : Strip Mode
	int nMSwath;										// 모터가 움직일 회수.
	int NodeNumX, NodeNumY;								// 각 축당 셀 갯수
	int PanelPixelX, PanelPixelY;						// 전체 판넬 이미지의 크기
	int OvrXPix, OvrYPix;								// 각 축으로 오버랩되는 부분의 크기
	int ProcSizeX, ProcSizeY;							// 각 축당 셀의 크기
	int nCell;											// 전체 셀 갯수
	int nIPU;											// AOI의 IPU 갯수
	int CameraValidPixel;								// 실제 검사하기 위해 사용되는 이미지의 X축 크기
	int nScanMarginX, nScanMarginY;						// 실제 사용되는 이미지에 각 축방향으로 더해지는 여분 이미지의 크기 Ex) nScanMarginX = (8192 ? CameraValidPixel)/2
	int nRegionX, nRegionY;								// Reserved Data
	int nCellDivideX, nCellDivideY;						// 한 스트립당 각 축 방향 셀 갯수
	int nCADPinPosPixX, nCADPinPosPixY;					// Pin Position X, y
	int nProcMarginX, nProcMarginY;						// Reserved Data
	int StPosX[MAX_NodeNumX * MAX_NodeNumY];			// 각 셀의 왼쪽 윗부분의 X 위치
	int StPosY[MAX_NodeNumX * MAX_NodeNumY];			// 각 셀의 왼쪽 윗부분의 Y 위치
	int EdPosX[MAX_NodeNumX * MAX_NodeNumY];			// 각 셀의 오른쪽 아래부분의 X 위치
	int EdPosY[MAX_NodeNumX * MAX_NodeNumY];			// 각 셀의 오른쪽 아래부분의 Y 위치
	int XSwathPixPos[MAX_NMSWATH];						// 모터가 움직이기 시작하는 위치
} REGION_STRIP;		//Total 100476 Byte

// CReadMstDlg 대화 상자
class CReadMstDlg : public CDialogEx
{
	BOOL FileBrowse(CString& sPath);
	BOOL LoadStripRgnFromCam(CString sPath, CString& sData);

// 생성입니다.
public:
	CReadMstDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READMST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
