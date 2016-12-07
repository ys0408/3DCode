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
#define MAX_CODEUTF8NUM		1000	// ������utf8��������
#endif

/* - �������� -
CString strEncodeData	��������
CQR_Encode* pQR_Encode	������
int nLevel				������
int nVersion			�汾��
BOOL bAutoExtent		�Զ���չ
int nMaskingNo			�����
��ע�����ݾ�ת��Ϊutf8��ʽ���б���
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


/* - ת��ͼ�� -
CyImage* pImage					��ά��ͼ��
int nPixelSize					���ش�С
COLORREF ForegroundColor		ǰ��ɫ
COLORREF BackgroundColor		����ɫ
CLogoRect LogoRect				LOGO��
CQR_Encode* pQR_Encode			QR��
BOOL bForegroundColorReturned	����ǰ��ɫ����
��ע������ά��ת��Ϊͼ�������ʾ��Ĭ�Ϸ���ǰ��ɫ������
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
	// ��ά��λ��̽����Ϣ
	CLogoRect right(nSymbleSize - 8, 0, nSymbleSize, 8);	// �Ҳ�λ��ʶ����
	CLogoRect top(0, nSymbleSize - 8, 8, nSymbleSize);		// ����λ��ʶ����
	CLogoRect origin(0, 0, 8, 8);							// ��ά��ԭ��
	for (int i = 0; i < nSymbleSize; ++i)
	{
		for (int j = 0; j < nSymbleSize; ++j)
		{
			if (pQR_Encode->m_byModuleData[i][j] == bForegroundColorReturned)
			{
				// ���ñ���ɫ
				SetPixel(pHead, nPixelSize, i * nPixelSize, j * nPixelSize, nRowlen, 3, BackgroundColor);
			}
			else if (IndexNotInRect(i, j, LogoRect) && // ȥ��Logo����
				IndexNotInRect(j, i, right) && IndexNotInRect(j, i, origin) && IndexNotInRect(j, i, top))
			{
				// ����ǰ��ɫ
				SetPixel(pHead, nPixelSize, i * nPixelSize, j * nPixelSize, nRowlen, 3, ForegroundColor);
				ForegroundColorIndex.push_back(CPixelPoint(i, j));//i��j��
			}
		}
	}
	// �޸ĸ�������
	pImage->MemcpyByteToFloat();
	return ForegroundColorIndex;
}