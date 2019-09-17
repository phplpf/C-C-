// CaptureScreen.cpp: implementation of the CaptureScreen.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CaptureScreen.h"

//////////////////////////////////////////////////////////////////////
LPSTR lpBmpData=NULL;
DWORD dwBmpSize=0;
DWORD dwBmpInfoSize=0;
int   CaptureThreadCount=0;//ץ���߳�����Ŀǰû��ʹ��
CRITICAL_SECTION csCaptureScreen;
int	  iBmpCX;
int   iBmpCY;
////////////////////////////////////////
//����ɨβ����,�ͷ��ڴ棬�ڷ����̺߳���ServerThread��ʹ��
void CleanScreenInfo(void)
{
	if(lpBmpData)
	{
		GlobalUnlock(lpBmpData);
		lpBmpData=(char*)GlobalFree(lpBmpData);
	}
	dwBmpSize=0;
	dwBmpInfoSize=0;
}

//��׽��Ļ����
bool GetScreenData(int nBits)
{
	//λͼλ������Ϊ����2^24��ֵ,��Ҫ���ǵ���������
	if (nBits>24)
		return false;
	HDC		hScrDC, hMemDC;			// ��Ļ���ڴ��豸������
	HBITMAP		hBitmap, hOldBitmap;		// λͼ���
	int		xScrn, yScrn;			// ��Ļ�ֱ��� 

	HDC		hDC;				//�豸������
	WORD		wBitCount;			//λͼ��ÿ��������ռ�ֽ���

	//�����ɫ���С�� λͼ�������ֽڴ�С ��λͼ�ļ���С �� д���ļ��ֽ���
	DWORD		dwPaletteSize=0, dwBmBitsSize=0;//,dwBmpInfoSize=0;
	BITMAP		Bitmap;			//λͼ���Խṹ
	BITMAPINFOHEADER	bi;		//λͼ��Ϣͷ�ṹ 
	LPBITMAPINFOHEADER	lpbi;		//ָ��λͼ��Ϣͷ�ṹ

	//�����ļ��������ڴ�������ɫ����  
	HANDLE			hDib;
	HPALETTE		hPal,hOldPal=NULL;

	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap (hScrDC,xScrn,yScrn);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP) SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC, 0, 0, xScrn, yScrn, 
			hScrDC, 0, 0, SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hBitmap = (HBITMAP) SelectObject(hMemDC, hOldBitmap);


	//����λͼÿ��������ռ�ֽ���
	if (nBits <= 1)
		wBitCount = 1;
	else if (nBits <= 4)
		wBitCount = 4;
	else if (nBits <= 8)
		wBitCount = 8;
	else if (nBits <= 16)
		wBitCount = 16;
	else if (nBits <= 24)
		wBitCount = 24;
	//�����ɫ���С
	if (wBitCount <24)
		dwPaletteSize = (1 << wBitCount) * sizeof(RGBQUAD);

	//����λͼ��Ϣͷ�ṹ
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount+31)& ~31)/8 *Bitmap.bmHeight;
	dwBmpInfoSize = dwPaletteSize + sizeof(BITMAPINFOHEADER);
	//��ʱλͼ���ݴ�С����
	DWORD dwNewBmpSize;
	dwNewBmpSize = dwBmBitsSize + dwBmpInfoSize;
	iBmpCX=Bitmap.bmWidth;
	iBmpCY=Bitmap.bmHeight;
	//Ϊλͼ���ݷ����ڴ�
	if(dwNewBmpSize!=dwBmpSize)//λͼ�����Ϣû�б仯
	{
		if(!lpBmpData)
		{
			hDib  = GlobalAlloc(GHND,dwNewBmpSize);
			if(!hDib)
			{
				DeleteObject(hBitmap);
				DeleteDC(hScrDC);
				DeleteDC(hMemDC);
				dwBmpSize=0;
				dwBmpInfoSize=0;
				return false;
			}
		}
		else
		{
			GlobalUnlock(lpBmpData);
			lpBmpData=(char*)GlobalFree(lpBmpData);
			hDib  = GlobalAlloc(GHND,dwNewBmpSize);
			if(!hDib)
			{
				DeleteObject(hBitmap);
				DeleteDC(hScrDC);
				DeleteDC(hMemDC);
				dwBmpSize=0;
				dwBmpInfoSize=0;
				return false;
			}
		}
		lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
		*lpbi = bi;
	}
	else//λͼ�����Ϣû�б仯
	{
		lpbi = (LPBITMAPINFOHEADER)lpBmpData;
		*lpbi = bi;
	}

	// �����ɫ��   
	hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = GetDC (NULL);
		hOldPal = SelectPalette(hDC, hPal, FALSE);
		RealizePalette(hDC);
	}
	// ��ȡ�õ�ɫ�����µ�����ֵ
	GetDIBits(
			hDC,
			hBitmap,
			0, 
			(UINT) Bitmap.bmHeight,
			(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize,
			(BITMAPINFO *)lpbi,
			DIB_RGB_COLORS
		  );
	//�ָ���ɫ��
	if (hOldPal)
	{
		SelectPalette(hScrDC, hOldPal, TRUE);
		RealizePalette(hScrDC);
		ReleaseDC(NULL, hDC);
	}

	lpBmpData = (char *)lpbi;
	dwBmpSize = dwNewBmpSize;
	//���
	DeleteObject (hBitmap);
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	return TRUE;

/*	BITMAPINFOHEADER	bi;		//λͼ��Ϣͷ�ṹ
	HBITMAP hBitmap;
	
	LPBITMAPINFOHEADER	lpbi = NULL;		//ָ��λͼ��Ϣͷ�ṹ 
	HDC		hScrDC, hMemDC;			// ��Ļ���ڴ��豸������
	HBITMAP		 hOldBitmap;		// λͼ���
	int		xScrn, yScrn;			// ��Ļ�ֱ��� 
	BITMAP		Bitmap;			//λͼ���Խṹ
	
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	
	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = ::CreateCompatibleBitmap (hScrDC,xScrn,yScrn);

	
	
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP) SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC, 0, 0, xScrn, yScrn, hScrDC, 0, 0, SRCCOPY);
	
	//�õ���Ļλͼ�ľ��
	hBitmap = (HBITMAP) SelectObject(hMemDC, hOldBitmap);
	
	//����λͼ��Ϣͷ�ṹ
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;//Ŀ���豸�ļ������Ϊ1?????????????????????????
	bi.biBitCount = 24;//ÿ�������ɫֵ�ö���λ����
	bi.biCompression = BI_RGB; //ѹ����ʽ 0��ѹ�� 1-RLE8ѹ�� 2-RLE4ѹ�� 3-ÿ�����ص��ֵ���������
	bi.biSizeImage = Bitmap.bmWidth*Bitmap.bmHeight*24;//((Bitmap.bmWidth * 24+31)& ~31)/8 *Bitmap.bmHeight;
	bi.biXPelsPerMeter = 0; //ˮƽ�ֱ���
	bi.biYPelsPerMeter = 0; //��ֱ�ֱ���
	bi.biClrUsed = 0;//λͼʵ��ʹ�õ���ɫ���е���ɫ��
	bi.biClrImportant = 0;//������ɫ����Ҫ

	//��ʱλͼ���ݴ�С����
	DWORD dwNewBmpSize;
	dwNewBmpSize = bi.biSizeImage/8 + 40;

	iBmpCX=Bitmap.bmWidth;
	iBmpCY=Bitmap.bmHeight;

	lpbi = (LPBITMAPINFOHEADER)malloc( bi.biSizeImage/8+40 );
	memset( lpbi, 0, bi.biSizeImage/8+40 );
	
	*lpbi = bi;
	
	
	GetDIBits(hMemDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi+sizeof(BITMAPINFOHEADER),
		(BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	   
	lpBmpData =(char*)lpbi;
	dwBmpSize = dwNewBmpSize;
	//���
	DeleteObject (hBitmap);
	DeleteDC(hMemDC);

	return TRUE;*/
}