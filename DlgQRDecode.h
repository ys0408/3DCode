#pragma once
#include "afxwin.h"
#include "CyImage.h"
#include <vector>
using namespace std;

// CDlgQRDecode 对话框

class CDlgQRDecode : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgQRDecode)

public:
	CDlgQRDecode(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgQRDecode();

	CyImage*			m_pImage;			// 当前图像
	RoiRect				m_roi;				// 感兴趣区域
	CString				m_strPublicString;	// 解码信息
	CString				m_strPrivateString; // 加密信息
	int					m_ncLength;			// 数据长度
	float				m_fModuleSize;		// 模块尺寸
	int					m_nLevel;			// 纠错率
	int					m_nVersion;			// 编码版本
	int					m_nMaskingNo;		// 掩码版本
	float2				m_fPos[4];			// 位置信息
	CToolTipCtrl		m_ToolTip;			// 工具提示

	// 编码颜色
	COLORREF			m_BackgroundColor;		//背景色
	COLORREF			m_ForegroundColor;		//前景色
	COLORREF			m_QREncodeColor1;		//码元一
	COLORREF			m_QREncodeColor2;		//码元二
	vector<CPixelPoint>	m_ForegroundElemsIndex;	//前景色的索引

	void SetImage();						// 设置当前图像
	BOOL Decode();							// 解码图像
	void UpdateDecodeInfo();				// 更新解码信息
	void UpdateecLevelTipText(int nEcLevel);// 更新信息提示
	void Reset();							// 重置所有控件

// 对话框数据
	enum { IDD = IDD_QRDECODE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
