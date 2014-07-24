// Gdi.h: interface for the CGdi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDI_H__7F316BC5_4FC2_47FE_AE36_2452E39746C3__INCLUDED_)
#define AFX_GDI_H__7F316BC5_4FC2_47FE_AE36_2452E39746C3__INCLUDED_
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<Tlhelp32.h>
#include "NtQuery.h"
#include "psapi.h"
#include <queue>
#include <vector>
#include <string>

using namespace std;


class Gdi  
{
///////////////////////////////////////////////////////////////
//���캯��
public:
	Gdi();
	virtual ~Gdi();

////////////////////////////////////////////////////////////////
//��������  ��������ÿ�����Updataһ��   ����Updata���ø��� ���º��� ����������)
public:
	void Updata(DWORD ProcessID,HANDLE Process, BOOL OpenProcess); //��������
private:
	void UpdataGdi(HANDLE process);  //����GDI
	void UpdataCPU(DWORD ProcessID,HANDLE Process, BOOL OpenProcess); //����CPU 
	void UpdataGdiType(DWORD ProcessID,HANDLE Handle); //����GDI���
	void UpdataThread(DWORD ProcessID); //�����̶߳���
///////////////////////////////////////////////////////////////
//��ͼ 
public:
	void SetDraw(CDC *pdc, int cursel,  bool bDraw = true); // trueΪ��ͼ falseΪ�ı�curselֵ
private:
	void SetBitmap(); //�˺������� ����ͼ��С λ�õ�
	Draw(int x, int y, int weight, int height, bool choose=0); //�˺���������ͼ������������ж� 
	void DrawGdiTypeRect(int j,int x,int y, double xArgument, double yArgument, CDC *pDC, int num);
	void DrawGdiType(CDC *MemDC,int weight,int height);
	void DrawGDI(CDC *MemDC,int weight,int height);
	void DrawThreadNum(CDC *MemDC,int weight,int height);
	void DrawCpu2(CDC *pDC,int weight,int height);
	void DrawCpu(CDC *pDC,int weight,int height);
	void DrawMemory(CDC *pDC, int weight, int height);

////////////////////////////////////////////////////////////////
// Get Set����

public:
	DWORD GetProcessMem();
	bool GetFindProcess();
	CString GetSP(TCHAR  sp[128]);
	vector<THREADINFO> GetThreadInfo();
	DWORD GetGdiNum();
	DWORD GetCursel();
	vector<GDITYPEINFO> GetGDITypeInfo();
	vector<GDIINFO> GetGDIInfo();
	CString GetChineseGdiType(DWORD i);
	CString GetEnglishGdiType(DWORD i);
	int GetMedian(int i);
	queue<DWORD> GetProcessQueueWokingSize();
	DWORD GetProcessWokingSize();
	void GetGdiTypeNum(int (&type)[15]);
	DWORD GetWin32GDIType(BYTE InternalType);
	queue<int> GetQueueGdi();
	DWORD GetPageFileSize();
	DWORD GetPagePath();
	DWORD GetAvailVirtual();
	queue<int> GetQueueThreadNum(); 
	DWORD GetVirtualMem();
	CString GetVersion();
	DWORD GetAvalMem();
	DWORD GetPhyMem();
	int GetCpuUsedAge();
	queue<int> GetQueueCpuUsedAge();
	int GetCpuNumber();

public:
	void SetCursel(int cursel);
	void SetFirstTime(bool ft);
	double GetArgument(DWORD max);
	void SetFindProcess(BOOL i);
	void SetQueueCpuUsedAge(int age); //����CPUʹ���ʶ���
	BOOL IsProcessWorking(); //�жϽ����Ƿ�رա���δд��


protected:
	//��ȡAPI
	typedef   LONG   (WINAPI   *PROCNTQSI)(UINT,PVOID,ULONG,PULONG); 
	typedef   DWORD  (WINAPI  *GETGUIRESOURCES) (HANDLE,DWORD);
	typedef unsigned (CALLBACK * Proc0) (void);          //GDI
	
    PROCNTQSI   NtQuerySystemInformation; //API
	PROCNTQSI   ZwQuerySystemInformation; //API
	GETGUIRESOURCES      GetGuiResources;//API
	Proc0                 GdiQueryTable;//API

private:
//////////////////////////////////////////////////////////////
//  ����

	vector<THREADINFO> vThreadInfo;
	int iGdiInfoNum;
	BOOL bStart;// �ж��Ƿ��һ��
	/////////////////////////////////////////
    //CPU
	SYSTEM_PERFORMANCE_INFORMATION   SysPerfInfo;  //ϵͳ������Ϣ
    SYSTEM_TIME_INFORMATION          SysTimeInfo;  //ϵͳʱ����Ϣ
    SYSTEM_BASIC_INFORMATION         SysBaseInfo;  //ϵͳ������Ϣ
	PSYSTEM_HANDLE_INFORMATION        pSysHandleInfo;//���
	vector <SYSTEM_HANDLE_INFORMATION>  vSysHandleInfo;//
	PSYSTEM_PROCESSES                pSp;//��5��
    double                           dbIdleTime;   //����ʱ��
    double                           dbSystemTime; //ϵͳʱ��
    LARGE_INTEGER                    liOldIdleTime;   //�ɿ���ʱ��
    LARGE_INTEGER                    liOldSystemTime; //��ϵͳʱ��
	queue<int> qiCpuUseAge;   //��ŵ�λʱ��CPUʹ�����
	//////////////////////////////////////////
	//�ڴ� 
	LPMEMORYSTATUS pmst;
	PPROCESS_MEMORY_COUNTERS ppmc;   //�����ڴ�
	queue<DWORD> qdWorkingSize;   //�����ڴ���� 
	DWORD dwWorkingSize;  //�˿̽���ʹ���ڴ�
	DWORD m_NowMemory;//�˿��ڴ�
	//////////////////////////////////////////
	//ϵͳ�汾
	OSVERSIONINFO osvi; 
	//////////////////////////////////////////
	//�߳�
	queue<int> qiThreadNum;
	DWORD m_NowThread;//�˿��߳�
	
	//////////////////////////////////////////
	//GDI
	queue<int> qiGdi;
	int GdiType[15]; // 1-14 ���̸���GDI���͵�GDI����
	GDITableCell * pGDITable;  
	vector<GDIINFO>  sss	; //�����Ϣ 
	vector<GDIINFO>  vGdiInfo; //�����Ϣ 
	vector<GDITYPEINFO> vGdiTypeInfo; //���������Ϣ
  
	DWORD m_NowGdi;   //�˿�GDI
	////////////////////////////////////////
	//��ͼ����
	int m_Cursel; //����ͼ
	bool FindProcess; //�Ƿ��ҵ�����
	bool FirstTime; //�Ƿ��1��
	CDC *pDC; //��ʱ��ĻDC
	DWORD m_rgb[15];//GDI�������ͱ� ������ɫ
	int LineNumGDI;    // �������õĲ���
	int LineNumCPU; //CPU����
	int LineNumThread; //�߳�����
	int LineNumMemory; //������߲���
	///////////////////////////////////////

};


/*
#define OBJ_PEN             1
#define OBJ_BRUSH           2
#define OBJ_DC              3
#define OBJ_METADC          4
#define OBJ_PAL             5
#define OBJ_FONT            6
#define OBJ_BITMAP          7
#define OBJ_REGION          8
#define OBJ_METAFILE        9
#define OBJ_MEMDC           10
#define OBJ_EXTPEN          11
#define OBJ_ENHMETADC       12
#define OBJ_ENHMETAFILE     13
*/
//pen brush dc metadc pal font bitmap region metafile memdc extpen enhmetadc enhmetafile other

#endif // !defined(AFX_GDI_H__7F316BC5_4FC2_47FE_AE36_2452E39746C3__INCLUDED_)
