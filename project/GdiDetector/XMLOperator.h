#ifndef _XMLOPERATOR_H
#define _XMLOPERATOR_H


//#include "Markup.h"
#include "Struct_Define.h"
//#include "StdAfx.h"

class CMarkup;

// using namespace std;
// 
// typedef struct _CALL_STACK{
// 	std::vector<std::string> callStack;
// }CALL_STACK, *PCALL_STACK;
// 
// // �Ĵ�����Ϣ
// typedef struct _REGISTERS_INFORMATION{
// 	unsigned long Edi;
// 	unsigned long Esi;
// 	unsigned long Eax;
// 	unsigned long Ebx;
// 	unsigned long Ecx;
// 	unsigned long Edx;
// 	unsigned long Eip;
// 	unsigned long Ebp;
// 	unsigned long SegCs;
// 	unsigned long EFlags;
// 	unsigned long Esp;
// 	unsigned long SegSs;
// }REGISTERS_INFORMATION, PREGISTERS_INFORMATION;
// 
// 
// 
// // ģ����Ϣ
// typedef struct _MODULE_INFORMATION{
// 	unsigned long		BaseOfImage;			// ӳ���ַ
// 	unsigned long		ImageSize;				// ӳ���С
// 	unsigned long		TimeDateStamp;			// ʱ���
// 	unsigned long		CheckSum;				// ����ֵ
// 	char				ModuleName[32];			// ģ����
// 	char				ImageName[256];			// ӳ��·��
// 	char				LoadedImageName[256];	// װ�ص�ӳ����
// 	char				LoadedPdbName[256];		// װ�ص�PDB��
// 	unsigned __int64	FileVersion;			// �ļ��汾ֵ
// }MODULE_INFORMATION, *PMODULE_INFORMATION;
// 
// 
// // �������
// typedef enum _HANDLE_TYPE{
// 	_BITMAP = 1,
// 		_BRUSH = 2,
// 		_COLORSPACE = 3,
// 		_DC = 4,
// 		_ENHMETADC = 5,
// 		_ENHMETAFILE = 6,
// 		_EXTPEN = 7,
// 		_FONT = 8,
// 		_MEMDC = 9,
// 		_METAFILE = 10,
// 		_METADC = 11,
// 		_PAL = 12,
// 		_PEN = 13,
// 		_REGION = 14,
// 		_UNKNOWN = 15
// }HANDLE_TYPE;
// 
// // ��Ӧ����������Ϣ
// typedef struct _HANDLE_INFORAMTION{
// 	unsigned long handle;						// ���ֵ
// 	unsigned uType;								// �������
// 	char szParaInfo[256];						// ������Ϣ
// 	CALL_STACK callStack;						// ��������ջ��Ϣ
// 	REGISTERS_INFORMATION registers;			// �Ĵ�����Ϣ
// 	std::vector<MODULE_INFORMATION> moduleInfo;	// ģ����Ϣ
// }HANDLE_INFORAMTION, *PHANDLE_INFORMATION;
// 



class xmloperator
{
public:
	xmloperator();
	void AddHandleType(PHANDLE_INFORMATION p);
	void AddHandleValue(PHANDLE_INFORMATION p);
	void AddParameterinfo(PHANDLE_INFORMATION p);
	void AddRegisters(unsigned long p,char *name);
	void AddCallStacks(PHANDLE_INFORMATION p);
	void AddModules(PHANDLE_INFORMATION p);
	void Add(PHANDLE_INFORMATION p);
	void Createxml();
	void SetFileName(string filename);
	void Start(string name);
	void End(string name);
	void Read(PHANDLE_INFORMATION p);
	void Find_All_Data( string &Tag, string &Value);
	vector<string> Split(const string& s,const string& match,bool removeEmpty, bool fullMatch);
	void ShowHandle(string Handle,string &test);
	void Find_Data( string &Tag, string &Value);
	string Show_Data(PHANDLE_INFORMATION p);
	string test;
	std::vector<std::string> Stack;
protected:
	CMarkup  *xml;
	string filename;
	
private:
	
};






#endif