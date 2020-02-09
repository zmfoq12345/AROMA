
// AROMADlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "AROMA.h"
#include "AROMADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "strmiids.lib")

#ifdef _DEBUG
#pragma comment(lib, "dsh_tw_direct_show.lib")
#else
#pragma comment(lib, "rst_tw_direct_show.lib")
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CAROMADlg 대화 상자



CAROMADlg::CAROMADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AROMA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAROMADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAROMADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON2, &CAROMADlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CAROMADlg::OnClickedButton1)
END_MESSAGE_MAP()


// CAROMADlg 메시지 처리기

BOOL CAROMADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// Circle Window
	CRgn rgn;
	rgn.CreateEllipticRgn(400, 0, 0, 400);
	SetWindowRgn(rgn, TRUE);

	SetBackgroundColor(RGB(0, 200, 255));

	// CamData 가져오기
	mLiveCam.MakeDeviceList();

	mpPreview = mLiveCam.MakePreviewGraphBuilder(0);
	//mcPreview = mLiveCam.MakeCaptureGraphBuilder(0, m_hWnd);
	if (mpPreview != NULL) {
		mpPreview->SetPreviewMode(m_hWnd, -100, 50);
		mpPreview->StartPreview();
	}
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAROMADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAROMADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAROMADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAROMADlg::ConnectDB(){
	
}

void CAROMADlg::saveImg() {
	// 화면 전체를 캡쳐하기 위해서 Window DC 를 사용합니다. ::GetDC(NULL) 이라고 해도 결과는 동일합니다.
	HDC h_dc = ::GetWindowDC(NULL);

	// 캡쳐에 사용할 CImage 객체를 선언한다.
	CImage tips_image;


	CRect r;
	GetWindowRect(r);

	// mcPreview->GetWidth();
	// mcPreview->GetHeight();
	// mcPreview->GetWidth(), mcPreview->GetHeight(),

	// 수평 해상도를 얻는다.
	int cx = ::GetSystemMetrics(SM_CXSCREEN);

	// 수직 해상도를 얻는다.
	int cy = ::GetSystemMetrics(SM_CYSCREEN);

	// 화면의 색상 수를 얻는다.
	int color_depth = ::GetDeviceCaps(h_dc, BITSPIXEL);

	// 캡쳐에 사용할 이미지를 생성한다.
	tips_image.Create(r.Width() - 68, r.Width() - 68, color_depth, 0);

	// 화면 전체 이미지를 m_tips_image 객체에 복사한다. 
	::BitBlt(tips_image.GetDC(), 0, 0, cx, cy, h_dc, r.Width()+260, r.Height()-150, SRCCOPY);

	// 캡쳐한 이미지를 "test.png" 라는 이름으로 저장한다.
	tips_image.Save(L"test.png", Gdiplus::ImageFormatPNG);

	// 화면 캡쳐에 사용했던 DC를 해제한다.
	::ReleaseDC(NULL, h_dc);

	tips_image.ReleaseDC();
}

void CAROMADlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_is_clicked) {
		m_is_clicked = TRUE;
		m_prev_pos = point;
		GetCursorPos(&m_prev_pos);
		SetCapture(); // window를 빠져나가도 마우스 이벤트를 계속 받아옴
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CAROMADlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_is_clicked) {
		m_is_clicked = FALSE;
		ReleaseCapture(); // SetCapture 해제
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CAROMADlg::OnMouseMove(UINT nFlags, CPoint point)
{

	if (m_is_clicked) {
		CRect r;
		GetWindowRect(r);

		CPoint pos;
		GetCursorPos(&pos);

		SetWindowPos(NULL, r.left + pos.x - m_prev_pos.x, r.top + pos.y - m_prev_pos.y, 0, 0, SWP_NOSIZE);

		m_prev_pos = pos;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CAROMADlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (mpPreview != NULL) {
		mpPreview->StopPreview();
		delete mpPreview;
	}

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CAROMADlg::OnClickedButton1()
{
	saveImg();



	// HDC hdc = ::GetDC(m_hWnd);
	// mpPreview->ScreenShot(hdc, 100,100,100,100);
}


void CAROMADlg::OnClickedButton2()
{
	OnOK();
}
