/*
  �� ���̺귯���� DirectShow ����� ����Ͽ� CAM ��� ����ó���� �Ҷ� ����մϴ�.
  DirectShow API�� Ŭ������ �����ڵ��� ���� ���ϰ� ���α׷��� ������ �� �ֵ��� 
  �籸���� ���̺귯�� �Դϴ�.
  �� ���̺귯���� ���� �������� �߰��ϰų� �������� �ʿ��ϴٸ� �Ʒ��� �� ���Ϸ�
  �ǰ� �����ֽðų� ��α׿� ��۷� �����ּ���.

  �̸��� : tipsware@naver.com
  ��α� : http://blog.naver.com/tipsware

  ���̺귯�� ���� : 2018�� 6�� 5�� ( �輺�� )
  ���̺귯�� ���� ������Ʈ : 2019�� 5�� 5�� ( �輺�� )

  �׸��� �� ���̺귯���� ����ϴ� ������� ���ϰ� ����� �� �ֵ���
  �ʿ��� ���̺귯���� �߰��ϴ� ��ó���� �ڵ带 ����ϴ�.

  #include "tw_direct_show.h"


  #pragma comment(lib, "strmiids.lib")

  #ifdef _DEBUG
	  #pragma comment(lib, "dsh_tw_direct_show.lib")
  #else
	  #pragma comment(lib, "rst_tw_direct_show.lib")
  #endif
*/

#ifndef _TW_DIRECT_SHOW_H_
#define _TW_DIRECT_SHOW_H_

#include <dshow.h>

interface ISampleGrabberCB : public IUnknown
{
	virtual STDMETHODIMP SampleCB(double SampleTime, IMediaSample *pSample) = 0;
	virtual STDMETHODIMP BufferCB(double SampleTime, BYTE *pBuffer, long BufferLen) = 0;
};

interface ISampleGrabber : public IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE SetOneShot(BOOL OneShot) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetMediaType(const AM_MEDIA_TYPE *pType) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType(AM_MEDIA_TYPE *pType) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetBufferSamples(BOOL BufferThem) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCurrentBuffer(long *pBufferSize, long *pBuffer) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCurrentSample(IMediaSample **ppSample) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetCallback(ISampleGrabberCB *pCallback, long WhichMethodToCallback) = 0;
};

static const IID IID_ISampleGrabber = { 0x6B652FFF,0x11FE,0x4fce,{ 0x92,0xAD,0x02,0x66,0xB5,0xD7,0xC7,0x8F } };
static const IID IID_ISampleGrabberCB = { 0x0579154A,0x2B53,0x4994,{ 0xB0,0xD0,0xE7,0x73,0x14,0x8E,0xFF,0x85 } };

static const CLSID CLSID_SampleGrabber = { 0xC1F400A0,0x3F08,0x11d3,{ 0x9F,0x0B,0x00,0x60,0x08,0x03,0x9E,0x37 } };
static const CLSID CLSID_NullRenderer = { 0xC1F400A4,0x3F08,0x11d3,{ 0x9F,0x0B,0x00,0x60,0x08,0x03,0x9E,0x37 } };
static const CLSID CLSID_VideoEffects1Category = { 0xcc7bfb42,0xf175,0x11d1,{ 0xa3,0x92,0x0,0xe0,0x29,0x1f,0x39,0x59 } };
static const CLSID CLSID_VideoEffects2Category = { 0xcc7bfb43,0xf175,0x11d1,{ 0xa3,0x92,0x0,0xe0,0x29,0x1f,0x39,0x59 } };
static const CLSID CLSID_AudioEffects1Category = { 0xcc7bfb44,0xf175,0x11d1,{ 0xa3,0x92,0x0,0xe0,0x29,0x1f,0x39,0x59 } };
static const CLSID CLSID_AudioEffects2Category = { 0xcc7bfb45,0xf175,0x11d1,{ 0xa3,0x92,0x0,0xe0,0x29,0x1f,0x39,0x59 } };


class TW_PreviewGraphBuilder
{
private:
	ICaptureGraphBuilder2 *mp_graph_builder;
	IBaseFilter *mp_video_capture;
	IGraphBuilder *mp_filter_graph;
	IAMVideoCompression *mp_video_comp;
	IAMStreamConfig *mp_stream_config;
	IVideoWindow *mp_video_window;
	IBasicVideo *mp_basic_video;
	IMediaEventEx *mp_media_event;

	AM_MEDIA_TYPE *mp_media_type;
	char m_preview_flag;
	HWND mh_owner_wnd, mh_preview_wnd;
	SIZE m_preview_size;
	int m_preview_x, m_preview_y, m_notify_id;

public:
	TW_PreviewGraphBuilder(IMoniker *ap_video_dev, const wchar_t *ap_video_dev_name);
	~TW_PreviewGraphBuilder();

	AM_MEDIA_TYPE *GetMediaType();
	// Media type�� NULL �̸� -1, Format ������ ��ġ���� ������ 0, ���������� �����ϸ� 1
	int GetMediaSize(SIZE *ap_size);

	inline int IsStart() { return m_preview_flag == 2; }
	inline SIZE *GetPreviewSize() { return &m_preview_size; }
	inline HWND GetPreviewWnd() { return mh_preview_wnd; }

	int SetPreviewMode(HWND ah_wnd, int a_x, int a_y, unsigned int a_message_id = 25001);
	int StartPreview();
	void StopPreview();

	void ScreenShot(HDC ah_dest_dc, int a_x, int a_y, int a_cx, int a_cy);
	void ShowCaptureFilterOption();
	void ShowCapturePinOption();
	void RemoveDownstream(IBaseFilter *ap_filter);

	IAMStreamConfig *GetStreamCofing() { return mp_stream_config; }
	AM_MEDIA_TYPE *SetMediaTypeByIndex(int a_index);
	AM_MEDIA_TYPE *SetMediaTypeBySize(int a_width, int a_height);
};

class TW_CaptureGraphBuilder
{
private:
	ICaptureGraphBuilder2 *mp_graph_builder;
	IGraphBuilder *mp_filter_graph;
	IVideoWindow *mp_video_window;
	IMediaEventEx *mp_media_event;
	IMediaControl *mp_media_control;
	IBaseFilter *mp_capture_filter;
	IBaseFilter *mp_grabber_filter;
	ISampleGrabber *mp_sample_grabber;

	HWND mh_owner_wnd;
	int m_color_depth, m_image_width, m_image_height;
	double m_zoom_level;
	int m_preview_x, m_preview_y;

public:
	TW_CaptureGraphBuilder(IMoniker *ap_video_dev, const wchar_t *ap_video_dev_name, HWND ah_owner_wnd, int a_x = 1, int a_y = 1, double a_zoom_level = 1.0);
	~TW_CaptureGraphBuilder();

	long ScreenShotWidthCheckSize(long *ap_dest_data, long a_limit_size);
	long ScreenShot(long *ap_dest_data, long a_limit_size);
	long GetGrabberSize();

	void PreviewZoomLevel(double a_zoom_level = 1.0);
	void PreviewStartPos(int a_x, int a_y);

	void StartCapture()
	{
		mp_media_control->Run();
	}

	void StopCapture()
	{
		mp_media_control->Stop();
	}

	int GetWidth() { return m_image_width; }
	int GetHeight() { return m_image_height; }
};

class TW_LiveCam
{
private:
	IMoniker *mp_video_dev[10];
	wchar_t *mp_video_name_list[10];
	int m_video_dev_count;

public:
	TW_LiveCam();
	~TW_LiveCam();

	void MakeDeviceList();
	int GetDeviceCount() { return m_video_dev_count; }
	const wchar_t *GetDeviceName(int a_index) { return mp_video_name_list[a_index]; }

	TW_PreviewGraphBuilder *MakePreviewGraphBuilder(int a_device_index);
	TW_CaptureGraphBuilder *MakeCaptureGraphBuilder(int a_device_index, HWND ah_wnd);
	TW_CaptureGraphBuilder *MakeCaptureGraphBuilder(int a_device_index, HWND ah_wnd, int a_x, int a_y, double a_zoom_level);
};

void TWAPI_DeleteMediaType(AM_MEDIA_TYPE *ap_media_type, char a_self_delete = 1);

#endif  // _TW_DIRECT_SHOW_H_