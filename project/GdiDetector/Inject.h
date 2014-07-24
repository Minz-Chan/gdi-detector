#include <windows.h>
#include <tchar.h>

#ifndef _INJECT_H
#define _INJECT_H


// ����API�ҽ���ṹ
// typedef struct _HOOK_ITEM {
// 	DWORD	dwAddr ;			// IAT�����ڵ�ַ
// 	DWORD	dwOldValue ;		// IAT���ԭʼ������ַ
// 	DWORD	dwNewValue ;		// IAT����º�����ַ
// } HOOK_ITEM, *PHOOK_ITEM ;

#ifndef _STRUCT_HOOK_ITEM
#define _STRUCT_HOOK_ITEM

typedef struct _HOOK_ITEM{
	DWORD dwIATAddr;			// IAT�����ڵ�ַ
	DWORD dwOldImportAddr;		// IAT���ԭʼ������ַ
	DWORD dwEATAddr;			// Ŀ��ģ���EAT�����ڵ�ַ
	DWORD dwOldExportAddr;		// Ŀ��ģ���EAT���ԭʼ������ַ
	DWORD dwNewFuncAddr;		// ָ����º�����ַ
}HOOK_ITEM, *PHOOK_ITEM;

#endif //_STRUCT_HOOK_ITEM

// �����ض���API��ʵ�ֺ���
// BOOL WINAPI SetImportAddress(PCHAR pDllName, PCHAR pFunName, DWORD dwNewProc, PHOOK_ITEM pItem);
// BOOL WINAPI SetExportAddress(PCHAR pDllName, PCHAR pFunName, DWORD dwNewProc, PHOOK_ITEM pItem);
// BOOL WINAPI RedirectApi(PCHAR pDllName, PCHAR pFunName, DWORD dwNewProc, PHOOK_ITEM pItem);

// �������������ڵ�
// ����pDllName:Ŀ��API���ڵ�DLL����
// ����pFunName:Ŀ��API����
// ����dwNewProc:�Զ���ĺ�����ַ
// ����pItem:���ڱ���EAT����Ϣ
BOOL WINAPI SetExportAddress(PCHAR pDllName, PCHAR pFunName, DWORD dwNewProc, PHOOK_ITEM pItem){

	// �������Ƿ�Ϸ�
	if (pDllName == NULL || pFunName == NULL || !dwNewProc || !pItem)
		return FALSE;
	
	// ���Ŀ��ģ���Ƿ����
	char szTempDllName[256] = {0};
	DWORD dwBaseImage = (DWORD)GetModuleHandle(pDllName);	// �Ѽ��ص�DLL��ַ
	if (dwBaseImage == 0)
		return FALSE;
	
	// ȡ��PE�ļ�ͷ��Ϣָ��
	PIMAGE_DOS_HEADER			pDosHeader = (PIMAGE_DOS_HEADER)dwBaseImage;
	PIMAGE_NT_HEADERS			pNtHeader = (PIMAGE_NT_HEADERS)(dwBaseImage + (pDosHeader->e_lfanew));
	PIMAGE_OPTIONAL_HEADER32	pOptionalHeader = &(pNtHeader->OptionalHeader);
	PIMAGE_SECTION_HEADER		pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeader + 0x18 \
		+ pNtHeader->FileHeader.SizeOfOptionalHeader);
	
	// ���������
	//PIMAGE_THUNK_DATA pThunk, pEAT;
	PIMAGE_EXPORT_DIRECTORY pIED = (PIMAGE_EXPORT_DIRECTORY)(dwBaseImage + \
		pOptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	unsigned ord = 0;
	if ((unsigned) pFunName < 0xFFFF) // ordinal ?
		ord = (unsigned) pFunName;
	else{

		const DWORD * pNames = (const DWORD *)(dwBaseImage + pIED->AddressOfNames);
		const WORD * pOrds = (const WORD *)(dwBaseImage + pIED->AddressOfNameOrdinals);
		

		// ȡ���ں�����ַ�������е��±����ord
		for(unsigned i=0; i < pIED->AddressOfNames; i++){
			
			if(strcmp(pFunName, (const char *)(dwBaseImage + pNames[i])) == 0){
				ord = pIED->Base + pOrds[i];
				break;
			}
		}
	}
	if(ord<pIED->Base || ord>pIED->NumberOfNames)
		return FALSE;
	
	// ָ�������ĺ�����ַ��
	// ע: ������еĺ�����ַ���еĵ�ֵַ��RVA��ַ
	// �����ģ���ַ��ֵ���ܵõ������ĺ�����ֵַ
	DWORD * pFuncAddr = (DWORD *)(dwBaseImage + pIED->AddressOfFunctions);

	
	// ����ض�����Ϣ
	pItem->dwEATAddr = (DWORD)pIED;
	pItem->dwOldExportAddr = dwBaseImage + pFuncAddr[ord - pIED->Base] ;
	pItem->dwNewFuncAddr = dwNewProc;

	
	DWORD dwNewFuncRVA = dwNewProc - dwBaseImage;
	DWORD dwOldProtect = 0;

	// �޸�EAT��
	VirtualProtect((DWORD *)&pFuncAddr[ord - pIED->Base], 4, PAGE_READWRITE, &dwOldProtect);
	pFuncAddr[ord - pIED->Base]=dwNewFuncRVA;
	VirtualProtect((DWORD *)&pFuncAddr[ord - pIED->Base], 4, PAGE_READWRITE, &dwOldProtect);

	return TRUE;
}



// �������������ڵ�
// ����pDllName:Ŀ��API���ڵ�DLL����
// ����pFunName:Ŀ��API����
// ����dwNewProc:�Զ���ĺ�����ַ
// ����pItem:���ڱ���IAT����Ϣ
BOOL WINAPI SetImportAddress(PCHAR pDllName, PCHAR pFunName, DWORD dwNewProc, PHOOK_ITEM pItem){

	// �������Ƿ�Ϸ�
	if (pDllName == NULL || pFunName == NULL || !dwNewProc || !pItem)
		return FALSE;
	
	// ���Ŀ��ģ���Ƿ����
	char szTempDllName[256] = {0};
	DWORD dwBaseImage = (DWORD)GetModuleHandle(NULL);	// Ŀ����̵Ļ�ַ
	if (dwBaseImage == 0)
		return FALSE;
	
	// ȡ��PE�ļ�ͷ��Ϣָ��
	PIMAGE_DOS_HEADER			pDosHeader = (PIMAGE_DOS_HEADER)dwBaseImage;
	PIMAGE_NT_HEADERS			pNtHeader = (PIMAGE_NT_HEADERS)(dwBaseImage + (pDosHeader->e_lfanew));
	PIMAGE_OPTIONAL_HEADER32	pOptionalHeader = &(pNtHeader->OptionalHeader);
	PIMAGE_SECTION_HEADER		pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeader + 0x18 \
											+ pNtHeader->FileHeader.SizeOfOptionalHeader);
	
	// ���������
	PIMAGE_THUNK_DATA pThunk, pIAT;
	PIMAGE_IMPORT_DESCRIPTOR pIID = (PIMAGE_IMPORT_DESCRIPTOR)(dwBaseImage + \
		pOptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	while (pIID->FirstThunk )
	{
		// ����Ƿ�Ŀ��ģ��
		if (strcmp((PCHAR)(dwBaseImage+pIID->Name), pDllName))
		{
			pIID++;
			continue;
		}
		
		// ��ȡIAT��ĵ�ַ
		pIAT = (PIMAGE_THUNK_DATA)(dwBaseImage + pIID->FirstThunk);
		if (pIID->OriginalFirstThunk){
			pThunk = (PIMAGE_THUNK_DATA)(dwBaseImage + pIID->OriginalFirstThunk);
		}
		else
			pThunk = pIAT;
		
		// ����IAT
		DWORD	dwThunkValue = 0;
		while ((dwThunkValue = *((DWORD*)pThunk)) != 0)
		{
			// �� dwThunkValue ���λ(MSBλ)Ϊ0, ˵��������������������.
			// ��ʱ���� IMAGE_IMPORT_BY_NAME �ṹ, ��ͨ������ֵ��ΪRVAת�� 
			// IMAGE_IMPORT_BY_NAME ����, ���� Hint ���Ǻ�������.
			// ע: ͨ�� Depends ��֪ϵͳ�ļ�������ģ��Kernel32.dll, User32.dll,
			// Gdi32.dll�Ȳ�������������.
			if (( dwThunkValue & IMAGE_ORDINAL_FLAG32 ) == 0)
			{
				// ����Ƿ�Ŀ�꺯��
				if (strcmp ( (PCHAR)(dwBaseImage+dwThunkValue+2), pFunName ) == 0)
				{
					// ��亯���ض�����Ϣ
					pItem->dwIATAddr = (DWORD)pIAT;
					pItem->dwOldImportAddr = *((DWORD*)pIAT);
					pItem->dwNewFuncAddr = dwNewProc;
					
					// �޸�IAT��
					DWORD dwOldProtect = 0;
					VirtualProtect (pIAT, 4, PAGE_READWRITE, &dwOldProtect);
					*((DWORD*)pIAT) = dwNewProc;
					VirtualProtect (pIAT, 4, PAGE_READWRITE, &dwOldProtect);
					return TRUE;
				}
			}
			
			pThunk ++;
			pIAT ++;
		}
		
		pIID ++;
	}
	
	return FALSE;
}

// ����API������ڵ�
// ����pDllName:Ŀ��API���ڵ�DLL����
// ����pFunName:Ŀ��API����
// ����dwNewProc:�Զ���ĺ�����ַ
// ����pItem:���ڱ���HOOK_ITEM��Ϣ
BOOL WINAPI RedirectApi(PCHAR pDllName, PCHAR pFunName, DWORD dwNewProc, PHOOK_ITEM pItem){
	
	if(SetImportAddress(pDllName, pFunName, dwNewProc, pItem)
		&& SetExportAddress(pDllName, pFunName, dwNewProc, pItem))
		return TRUE;
	else
		return FALSE;
}

#endif