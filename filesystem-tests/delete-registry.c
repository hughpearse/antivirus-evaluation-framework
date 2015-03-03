/*
 Title: Test to delete registry key 
 Compile: wine gcc.exe filesystem-tests/delete-registry.c -o bin/delete-registry.exe
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <winbase.h>

#define PATH 256


int main(void)
{
LONG lnResult;
HKEY hKey;
CHAR bfWindows[PATH];

  /* Open the Registry key */
  if ( ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\",
        0, KEY_ALL_ACCESS,
        &hKey) ) {
    printf("Error opening key, use RegEdit\n");
    return 0;
  }
 /* Delete The Registry Entry...*/

   lnResult = RegDeleteKey(hKey,"ExampleKeyName\\");
  if ( ERROR_SUCCESS != lnResult ) {
    // Some error, so notify user...
    if ( lnResult == ERROR_FILE_NOT_FOUND ) {
      // Key does not exist
      RegCloseKey(hKey);
      return 0;
    } // end if
    // Some other error...
    printf("Error deleting key, use RegEdit\n");
    RegCloseKey(hKey);
    return 0;
  } // end if
return 0;  
}

