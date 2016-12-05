#include "stdafx.h"
#include "QrEncodeFuncs.h"
#include "CodeTransform.h"
#include "PixelsOperation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef MAX_CODEUTF8NUM
#define MAX_CODEUTF8NUM		1000	// 最多编码utf8文字字数
#endif

/* - 编码数据 -
CString strEncodeData	编码数据
CQR_Encode* pQR_Encode	编码类
int nLevel				纠错率
int nVersion			版本号
BOOL bAutoExtent		自动扩展
int nMaskingNo			掩码号
备注：数据均转化为utf8格式进行编码
*/
BOOL EncodeData(CString strEncodeData, CQR_Encode* pQR_Encode, int nLevel, int nVersion, BOOL bAutoExtent, int nMaskingNo)
{
#ifdef UNICODE
	int ncLength = 0;
	char *utf8 = UnicodeConvert2UTF8(strEncodeData, ncLength);
	if (ncLength >= MAX_CODEUTF8NUM)
	{
		SAFE_DELETE(utf8);
		return FALSE;
	}
	BOOL m_bDataEncoded = pQR_Encode->EncodeDataUtf8(nLevel, nVersion, bAutoExtent, nMaskingNo, utf8, ncLength);
	SAFE_DELETE(utf8);
#else
	BOOL m_bDataEncoded = pQR_Encode->EncodeData(nLevel, nVersion, bAutoExtent, nMaskingNo, strEncodeData);
#endif
	return m_bDataEncoded;
}


/* - 转化图像 -
CyImage* pImage					二维码图像
int nPixelSize					像素大小
COLORREF ForegroundColor		前景色
COLORREF BackgroundColor		背景色
CLogoRect LogoRect				LOGO区
CQR_Encode* pQR_Encode			QR码
BOOL bForegroundColorReturned	返回前景色索引
备注：将二维码转换为图像进行显示，默认返回前景色索引。
*/
vector<CPixelPoint> Convert2Image(CyImage* pImage, int nPixelSize, COLORREF ForegroundColor, COLORREF BackgroundColor, CLogoRect LogoRect, CQR_Encode* pQR_Encode, BOOL bForegroundColorReturned)
{
	int nSymbleSize = pQR_Encode->m_nSymbleSize;
	int nWidth = nPixelSize * nSymbleSize + QR_MARGIN * 2;
	int nHeight = nPixelSize * nSymbleSize + QR_MARGIN * 2;

	pImage->Create(nWidth, nHeight, 24, 0UL);
	vector<CPixelPoint> ForegroundColorIndex;
	BYTE* pHead = pImage->GetHeadAddress();
	int nRowlen = pImage->GetRowlen();
	memset(pHead, 255, nHeight * nRowlen * sizeof(BYTE));
	// 二维码位置探测信息
	CLogoRect right(nSymbleSize - 8, 0, nSymbleSize, 8);	// 右侧位置识别区
	CLogoRect top(0, nSymbleSize - 8, 8, nSymbleSize);		// 顶端位置识别区
	CLogoRect origin(0, 0, 8, 8);							// 二维码原点
	for (int i = 0; i < nSymbleSize; ++i)
	{
		for (int j = 0; j < nSymbleSize; ++j)
		{
			if (pQR_Encode->m_byModuleData[i][j] == bForegroundColorReturned)
			{
				// 设置背景色
				SetPixel(pHead, nPixelSize, i * nPixelSize, j * nPixelSize, nRowlen, 3, BackgroundColor);
			}
			else if (IndexNotInRect(i, j, LogoRect) && // 去掉Logo区域
				IndexNotInRect(j, i, right) && IndexNotInRect(j, i, origin) && IndexNotInRect(j, i, top))
			{
				// 设置前景色
				SetPixel(pHead, nPixelSize, i * nPixelSize, j * nPixelSize, nRowlen, 3, ForegroundColor);
				ForegroundColorIndex.push_back(CPixelPoint(i, j));//i行j列
			}
		}
	}
	// 修改浮点数据
	pImage->MemcpyByteToFloat();
	return ForegroundColorIndex;
}