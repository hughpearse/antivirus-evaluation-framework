/*
 Title: Test to create registry key 
 Compile: wine gcc.exe filesystem-tests/create-registry.c -o bin/create-registry.exe
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <winbase.h>

void xor_encrypt_decrypt(char *key, char *string, char *buf)
{
	int i, string_length = strlen(string);
	for(i=0; i<string_length; i++)
	{
		buf[i]=string[i]^key[i];
	}
}
unsigned char ciphertext[]="\x28\x54\x3C\x52\x27\x4A\x32\x25\x20\x3A\x47\x2F\x27\x35\x2A\x51\x44\x49\x23\x2D\x5E\x58\x31\x27\x59\x56\x0E\x57\x32\x26\x31\x25\x22\x4C\x20\x27\x36\x21\x36\x25\x22\x25\x5E\x32\x39\x3B\x3B\x32\x39\x33\x26\x20\x5A\x3B\x37\x37\x24\x4C\x35\x3A\x3B\x2A\x53\x40\x38\x4A\x3B\x59";

char key[]="passwordpasswordpasswordpasswordpasswordpasswordpasswordpasswordpassw";

char plaintext[72] = {0}; //zero the memory first

int main(void)
{
    HKEY hkey;
    DWORD dwDisposition;
    xor_encrypt_decrypt(key, ciphertext, plaintext);
    if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, 
      TEXT("SOFTWARE\\EICAR"), 
      0, NULL, 0, 
      KEY_WRITE, NULL, 
      &hkey, &dwDisposition) == ERROR_SUCCESS) 
    {
        long setRes = RegSetValueEx (hkey, "EICAR-Key", 0, REG_SZ, (LPBYTE)plaintext, strlen(plaintext)+1);
         if (setRes == ERROR_SUCCESS) {
                printf("Success writing to Registry.\n");
            } else {
                printf("Error writing to Registry.\n");
            }
        RegCloseKey(hkey);
    }
    else
        MessageBox(NULL,"error","",0);

return 0;  
}

