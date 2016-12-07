#pragma once
#include "afxwin.h"
#include "CyImage.h"
#include <vector>
using namespace std;

// CDlgQRDecode �Ի���

class CDlgQRDecode : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgQRDecode)

public:
	CDlgQRDecode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgQRDecode();

	CyImage*			m_pImage;			// ��ǰͼ��
	RoiRect				m_roi;				// ����Ȥ����
	CString				m_strPublicString;	// ������Ϣ
	CString				m_strPrivateString; // ������Ϣ
	int					m_ncLength;			// ���ݳ���
	float				m_fModuleSize;		// ģ��ߴ�
	int					m_nLevel;			// ������
	int					m_nVersion;			// ����汾
	int					m_nMaskingNo;		// ����汾
	float2				m_fPos[4];			// λ����Ϣ
	CToolTipCtrl		m_ToolTip;			// ������ʾ

	// ������ɫ
	COLORREF			m_BackgroundColor;		//����ɫ
	COLORREF			m_ForegroundColor;		//ǰ��ɫ
	COLORREF			m_QREncodeColor1;		//��Ԫһ
	COLORREF			m_QREncodeColor2;		//��Ԫ��
	vector<CPixelPoint>	m_ForegroundElemsIndex;	//ǰ��ɫ������

	void SetImage();						// ���õ�ǰͼ��
	BOOL Decode();							// ����ͼ��
	void UpdateDecodeInfo();				// ���½�����Ϣ
	void UpdateecLevelTipText(int nEcLevel);// ������Ϣ��ʾ
	void Reset();							// �������пؼ�

// �Ի�������
	enum { IDD = IDD_QRDECODE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDecode();
	BOOL m_bUseHybrid;
	BOOL m_bTryHarder;
	CButton m_checkUseHybrid;
	CButton m_checkTryHarder;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonSaveImage();
	afx_msg void OnBnClickedBnForeground();
	afx_msg void OnBnClickedBnBackground();
	afx_msg void OnBnClickedBnEncodeColor1();
	afx_msg void OnBnClickedBnEncodeColor2();
	afx_msg void OnBnClickedButtonClear();
};