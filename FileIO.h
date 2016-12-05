#pragma once

/************************************************************************/
// 文件读写函数，可以跨平台
/************************************************************************/

// 将图像数据以二进制形式写入文件，nChannel表示一个像素占用几个字节
BOOL WriteTxt(const char* fileName, BYTE* pSrc, int nRowlen, int nHeight, int nChannel);

// 将图像数据以二进制形式读入文件，nChannel表示一个像素占用几个字节
BYTE* ReadTxt(const char* fileName, int &nWidth, int &nHeight, int &nRowlen, int &nChannel);