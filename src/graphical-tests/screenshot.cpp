/*
 Title: Test to take screenshot - check if screen is emulated
 Compile: wine g++.exe ./graphical-tests/screenshot.cpp -lgdiplus -lgdi32 -lws2_32 -Wno-write-strings -o ./bin/screenshot.exe
*/


#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <memory>
#include <fstream>

using namespace Gdiplus;
using namespace std;

//#pragma comment (lib,"Gdiplus.lib")

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT num = 0;          // number of image encoders
    UINT size = 0;         // size of the image encoder array in bytes

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if(size == 0)
    {
        return -1;  // Failure
    }

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if(pImageCodecInfo == NULL)
    {
        return -1;  // Failure
    }

    GetImageEncoders(num, size, pImageCodecInfo);

    for(UINT j = 0; j < num; ++j)
    {
        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;  // Success
        }    
    }

    free(pImageCodecInfo);
    return -1;  // Failure
}

void BitmapToJpg(HBITMAP hbmpImage, int width, int height)
{
    Bitmap *p_bmp = Bitmap::FromHBITMAP(hbmpImage, NULL);
    //Bitmap *p_bmp = new Bitmap(width, height, PixelFormat32bppARGB);
    
    CLSID pngClsid;
    int result = GetEncoderClsid(L"image/jpeg", &pngClsid);
    if(result != -1)
        std::cout << "Encoder succeeded" << std::endl;
    else
        std::cout << "Encoder failed" << std::endl;
    p_bmp->Save(L"screen.jpg", &pngClsid, NULL);
    delete p_bmp;
}

bool ScreenCapture(int x, int y, int width, int height, char *filename)
{
    HDC hDc = CreateCompatibleDC(0);
    HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), width, height);
    SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, GetDC(0), x, y, SRCCOPY);
    BitmapToJpg(hBmp, width, height);
    DeleteObject(hBmp);
    return true;
}

int main() {
    // Initialize GDI+.
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    int x1 = 0;
    int y1 = 0;
    int x2 = GetSystemMetrics(SM_CXSCREEN);
    int y2 = GetSystemMetrics(SM_CYSCREEN);

    //calculate image surface area and check if it is greater than 500px
    if( (x2-x1)*(y2-y1) > 500 ){
        //ScreenCapture(x1, y1, x2 - x1, y2 - y1, "screen.jpg");

        //if screen is present, create EICAR file
        ofstream myfile;
        myfile.open ("eicar.com");
        myfile << "X5O!P%@AP[4\\PZX54(P^)7CC)7}$";
        int split = 0;
        myfile << "EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*";
        myfile.close();
    } else {
        //if screen is not present, assume OS is emulated and do not trigger payload
        std::cout << "Screen resolution too small" << std::endl;
    }    

    //Shutdown GDI+
    GdiplusShutdown(gdiplusToken);
    
    return 0;
}
