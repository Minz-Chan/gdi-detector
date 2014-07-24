#ifndef NTQUERY_H
#define  NTQUERY_H

///////////////////////////////////////////
//        NTQuery  ͷ�ļ�
///////////////////////////////////////////

#include   <Tlhelp32.h> 

#define   SystemBasicInformation         0  //ϵͳ������Ϣ
#define   SystemPerformanceInformation   2  //ϵͳ������Ϣ
#define   SystemTimeInformation          3  //ϵͳʱ����Ϣ
#define SystemHandleInformation          16 //ϵͳ���       
#define SystemProcessesAndThreadsInformation 5// 5�Ź���

#define   Li2Double(x)   ((double)((x).HighPart)   *   4.294967296E9   +   (double)((x).LowPart))  //4.294967296E9 ԭ����2^32
//�о�����ܶ��࣬ Ϊʲô��ֱ��    s.QuadPart



typedef   struct 
{ 
        DWORD       dwUnknown1; 
        ULONG       uKeMaximumIncrement;  //һ��ʱ�ӵļ�����λ
        ULONG       uPageSize;            //һ���ڴ�ҳ�Ĵ�С
        ULONG       uMmNumberOfPhysicalPages;   //ϵͳ�����Ŷ��ٸ�ҳ
        ULONG       uMmLowestPhysicalPage;      //�Ͷ��ڴ�ҳ
        ULONG       uMmHighestPhysicalPage;     //�߶��ڴ�ҳ
        ULONG       uAllocationGranularity; 
        PVOID       pLowestUserAddress;         //�ض��û���ַ
        PVOID       pMmHighestUserAddress;      //�߶��û���ַ
        ULONG       uKeActiveProcessors;        //����Ĵ�����
        BYTE         bKeNumberProcessors;  //CPU����
        BYTE         bUnknown2; 
        WORD         wUnknown3; 
}SYSTEM_BASIC_INFORMATION; //ϵͳ������Ϣ

typedef   struct 
{ 
        LARGE_INTEGER       liIdleTime;       //CPU����ʱ��
        DWORD            dwSpare[76];  //
}   SYSTEM_PERFORMANCE_INFORMATION;  //ϵͳ������Ϣ


typedef   struct 
{ 
        LARGE_INTEGER   liKeBootTime;    //ϵͳ��������ʱ�� 
        LARGE_INTEGER   liKeSystemTime; 
        LARGE_INTEGER   liExpTimeZoneBias; 
        ULONG                   uCurrentTimeZoneId; 
        DWORD                   dwReserved;
}   SYSTEM_TIME_INFORMATION;      //ϵͳʱ����Ϣ


                                       //���� ָ�� ��С ʹ�ô�С



typedef struct _SYSTEM_HANDLE_INFORMATION
{ 
	ULONG ProcessID;		      //���̵ı�ʶID 
	UCHAR ObjectTypeNumber;      //�������� 
	UCHAR Flags;				//0x01 = PROTECT_FROM_CLOSE,0x02 = INHERIT 
	USHORT Handle;             //����������ֵ 
	PVOID  Object;            //��������ָ���ں˶����ַ 
	ACCESS_MASK GrantedAccess;      //�������ʱ��׼��Ķ���ķ���Ȩ 
}SYSTEM_HANDLE_INFORMATION, * PSYSTEM_HANDLE_INFORMATION; 

typedef struct _UNICODE_STRING {
  USHORT  Length;     //UNICODEռ�õ��ڴ��ֽ���������*2��
  USHORT  MaximumLength;
  PWSTR  Buffer;
} UNICODE_STRING ,*PUNICODE_STRING;

typedef LONG KPRIORITY;

typedef struct _VM_COUNTERS
{
	ULONG PeakVirtualSize;//����洢��ֵ��С;
	ULONG VirtualSize;//����洢��С;
	ULONG PageFaultCount;//ҳ������Ŀ;
	ULONG PeakWorkingSetSize;//��������ֵ��С;
	ULONG WorkingSetSize;//��������С;
	ULONG QuotaPeakPagedPoolUsage;//��ҳ��ʹ������ֵ;
	ULONG QuotaPagedPoolUsage; //��ҳ��ʹ�����;
	ULONG QuotaPeakNonPagedPoolUsage;//�Ƿ�ҳ��ʹ������ֵ;
	ULONG QuotaNonPagedPoolUsage;//�Ƿ�ҳ��ʹ�����;
	ULONG PagefileUsage;//ҳ�ļ�ʹ�����;
	ULONG PeakPagefileUsage;//ҳ�ļ�ʹ�÷�ֵ;
}VM_COUNTERS,*PVM_COUNTERS;

typedef struct _IO_COUNTERS
{
	LARGE_INTEGER ReadOperationCount;//I/O��������Ŀ;
	LARGE_INTEGER WriteOperationCount;//I/Oд������Ŀ;
	LARGE_INTEGER OtherOperationCount;//I/O����������Ŀ;
	LARGE_INTEGER ReadTransferCount;//I/O��������Ŀ;
	LARGE_INTEGER WriteTransferCount;//I/Oд������Ŀ;
	LARGE_INTEGER OtherTransferCount;//I/O��������������Ŀ;
}IO_COUNTERS,*PIO_COUNTERS;

typedef struct _CLIENT_ID 
{ 
HANDLE UniqueProcess; 
HANDLE UniqueThread; 
}CLIENT_ID; 
typedef enum _THREAD_STATE 
{ 
StateInitialized, 
StateReady, 
StateRunning, 
StateStandby, 
StateTerminated, 
StateWait, 
StateTransition, 
StateUnknown 
}THREAD_STATE; 

typedef enum _KWAIT_REASON 
{ 
Executive, 
FreePage, 
PageIn, 
PoolAllocation, 
DelayExecution, 
Suspended, 
UserRequest, 
WrExecutive, 
WrFreePage, 
WrPageIn, 
WrPoolAllocation, 
WrDelayExecution, 
WrSuspended, 
WrUserRequest, 
WrEventPair, 
WrQueue, 
WrLpcReceive, 
WrLpcReply, 
WrVertualMemory, 
WrPageOut, 
WrRendezvous, 
Spare2, 
Spare3, 
Spare4, 
Spare5, 
Spare6, 
WrKernel 
}KWAIT_REASON; 

typedef struct _SYSTEM_THREADS
{
LARGE_INTEGER KernelTime;//CPU�ں�ģʽʹ��ʱ�䣻
LARGE_INTEGER UserTime;//CPU�û�ģʽʹ��ʱ�䣻
LARGE_INTEGER CreateTime;//�̴߳���ʱ�䣻
ULONG WaitTime;//�ȴ�ʱ�䣻
PVOID StartAddress;//�߳̿�ʼ�������ַ��
CLIENT_ID ClientId;//�̱߳�ʶ����
KPRIORITY Priority;//�߳����ȼ���
KPRIORITY BasePriority;//�������ȼ���
ULONG ContextSwitchCount;//�����л���Ŀ��
THREAD_STATE State;//��ǰ״̬��
KWAIT_REASON WaitReason;//�ȴ�ԭ��
}SYSTEM_THREADS,*PSYSTEM_THREADS;


typedef struct _SYSTEM_PROCESSES
{
ULONG NextEntryDelta; //���ɽṹ���е�ƫ����;
ULONG ThreadCount; //�߳���Ŀ;
ULONG Reserved1[6];
LARGE_INTEGER CreateTime; //����ʱ��;
LARGE_INTEGER UserTime;//�û�ģʽ(Ring 3)��CPUʱ��;
LARGE_INTEGER KernelTime; //�ں�ģʽ(Ring 0)��CPUʱ��;
UNICODE_STRING ProcessName; //��������;
KPRIORITY BasePriority;//��������Ȩ;
ULONG ProcessId; //���̱�ʶ��;
ULONG InheritedFromProcessId; //�����̵ı�ʶ��;
ULONG HandleCount; //�����Ŀ;
ULONG Reserved2[2];
VM_COUNTERS  VmCounters; //����洢���Ľṹ������;
IO_COUNTERS IoCounters; //IO�����ṹ������;
SYSTEM_THREADS Threads[1]; //��������̵߳Ľṹ���飬����;
}SYSTEM_PROCESSES,*PSYSTEM_PROCESSES;


typedef struct
{
	DWORD  pKernel;//ָ���ں˵�ַ�ռ�
	WORD   nProcess; // NT/2000��ָ�����ID
	WORD   nCount;
	WORD   nUpper;
	WORD   nType;
	DWORD  pUser;//ָ���û���ַ�ռ�
} GDITableCell;

/*
typedefstruct  _MEMORYSTATUSEX
{
	DWORD dwLength; //����
	DWORD dwMemoryLoad; //��æ�ȼ�
	unsigned int dwTotalPhys; //�����ڴ�����
	unsigned int dwAvailPhys; //�ɷ�����ڴ�����
	unsigned int dwTotalPageFile; //Ӳ��ҳ�����ļ�
	unsigned int dwAvailPageFile;//��δ�����ҳ�����ļ�
	unsigned int dwTotalVirtual; //��ַ�ռ䱻������˽�е�
	unsigned int dwAvailVirtual; //���Ƶ�ַ�ռ�
}MEMORYSTATUS, *LPMEMORYSTATUS;
*/

// �߳�
typedef   enum   _THREADINFOCLASS   
{ 
        ThreadBasicInformation, 
        ThreadTimes, 
        ThreadPriority, 
        ThreadBasePriority, 
        ThreadAffinityMask, 
        ThreadImpersonationToken, 
        ThreadDescriptorTableEntry, 
        ThreadEnableAlignmentFaultFixup, 
        ThreadEventPair_Reusable, 
        ThreadQuerySetWin32StartAddress, 
        ThreadZeroTlsCell, 
        ThreadPerformanceCount, 
        ThreadAmILastThread, 
        ThreadIdealProcessor, 
        ThreadPriorityBoost, 
        ThreadSetTlsArrayAddress, 
        ThreadIsIoPending, 
        ThreadHideFromDebugger, 
        ThreadBreakOnTermination, 
        MaxThreadInfoClass 
}  THREADINFOCLASS; 

//typedef  struct   _CLIENT_ID  
//{ 
//        HANDLE   UniqueProcess; 
 //       HANDLE   UniqueThread; 
//}   CLIENT_ID; 
typedef   CLIENT_ID   *PCLIENT_ID; 

typedef   struct   _THREAD_BASIC_INFORMATION   {   //   Information   Class   0 
        LONG           ExitStatus; 
        PVOID         TebBaseAddress; 
        CLIENT_ID   ClientId; 
        LONG   AffinityMask; 
        LONG   Priority; 
        LONG   BasePriority; 
}   THREAD_BASIC_INFORMATION,   *PTHREAD_BASIC_INFORMATION; 

typedef struct
{
	DWORD id; // �߳�ID
	DWORD  pri;  //�߳�����ֵ

} THREADINFO, *PTHREADINFO;

//ÿ��GDI��Ϣ
typedef struct 
{
	DWORD handle;//���
	CString type; //����
	DWORD pKernel;// �ں˵�ַ�ռ�
} GDIINFO, *PGDIINFO;

//ÿ��GDI������Ϣ
typedef struct
{
	CString type;//�������� Ӣ��
	DWORD num; //��������
	CString Expand; //��չ��Ϣ
	
} GDITYPEINFO, *PGDITYPEINFO; 



#endif
