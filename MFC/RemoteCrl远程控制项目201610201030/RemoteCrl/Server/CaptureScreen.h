#pragma once

///////////ץ����ȫ�ֱ���//////////////
extern LPSTR lpBmpData;	//λͼ����ָ��
extern int   CaptureThreadCount ;//ץ���߳���
extern DWORD dwBmpSize;	//λͼ���ݴ�С
extern DWORD dwBmpInfoSize;	//λͼ��Ϣ
extern CRITICAL_SECTION csCaptureScreen;//�û�������Ļ���ݵ��ٽ�������
extern int	 iBmpCX;//λͼ���
extern int   iBmpCY;//λͼ�߶�
///////////////////////////////////////
void CleanScreenInfo(void);
bool GetScreenData(int nBits);