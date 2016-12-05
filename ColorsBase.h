/************************************************************************
* @file 
* @brief 彩色二维码彩色编码解码基类
* @date 2016/10/15
************************************************************************/

#pragma once

#include "DataTypes.h"
#include <vector>
using namespace std;

#ifndef MAX_MODULESIZE
#define MAX_MODULESIZE 177
#endif

/************************************************************************
* 彩色编码模块：1 - 在白色模块编码；0 - 在黑色模块编码
************************************************************************/
enum EncodeModule
{
	BlackModule = 0,		// 在前景色编码（黑色）
	WhiteModule = 1,		// 在背景色编码（白色）
};

/************************************************************************
* @class ColorsBase 彩色二维码编码解码基类
************************************************************************/
class ColorsBase
{
protected:
	BYTE*				m_pBitMatrix[MAX_MODULESIZE];	// 原二维码
	int					m_nSymbolSize;					// 二维码尺寸
	vector<CPixelPoint> m_HeaderIndex;					// 数据头索引
	CLogoRect			m_LogoRect;						// 二维码LOGO

private:
	EncodeModule		m_EncodeModule;					// 彩色编码模块（1，默认为白色）

public:
	/** 创建一个彩色编码解码基类对象
	* @param[in] bMatrix[MAX_MODULESIZE][MAX_MODULESIZE]	二维码数据
	* @param[in] nSymbolSize								二维码尺寸
	*/
	ColorsBase(BYTE bMatrix[MAX_MODULESIZE][MAX_MODULESIZE], int nSymbolSize)
	{
		for (int i = 0; i < nSymbolSize; ++i)
		{
			m_pBitMatrix[i] = bMatrix[i];
		}
		// 默认无LOGO
		m_LogoRect = 0;
		// 默认在白色模块编码色彩
		m_EncodeModule = WhiteModule;
		m_nSymbolSize = nSymbolSize;
	}

	// 默认的析构函数
	~ColorsBase() { }

	// 设置编码模块
	void SetEncodeModule(EncodeModule Module)
	{
		m_EncodeModule = Module;
	}

	// 获取编码模块
	EncodeModule GetEncodeModule()
	{
		return m_EncodeModule;
	}

	// 设置二维码LOGO
	void SetLogoRect(CMyRect logo)
	{
		m_LogoRect = logo;
	}

	// 获取二维码LOGO
	CMyRect GetLogoRect()
	{
		return m_LogoRect;
	}

	// 获取模块总数
	int GetModulesCount()
	{
		return m_nSymbolSize * m_nSymbolSize - m_LogoRect.Width() * m_LogoRect.Height();
	}

	// 获取编码模块总数
	int GetColorsMoudlesCount(BOOL bFore = TRUE);

	// 获取编码模块的索引
	vector<CPixelPoint> GetColorsModuleIndex(BOOL bFore = TRUE);

	// (row, col)非数据头索引
	BOOL NotHeaderIndex(int row, int col);

	// 获取彩色数据头的索引
	virtual void GetDataHeaderIndex() = 0;
};