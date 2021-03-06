#include <stdio.h>
#include <windows.h>

static struct _SYSTEMTIME systemtime;

void initDate(unsigned short *date) {
    GetLocalTime(&systemtime);
    date[0] = systemtime.wYear;
    date[1] = systemtime.wMonth;
    date[2] = systemtime.wDay;
}

void printHEX(unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02X", data[i]);
    }
}

int main() {
    HMODULE hMod = LoadLibrary("nslicense.dll");
    typedef int (*PFN1)(void *, int);
    PFN1 pfn1 = (PFN1)GetProcAddress(hMod, "NSLICENSE_DateToMagicCode");

    unsigned short date[3] = {0};
    unsigned char code1[22] = {0};
    unsigned char code2[22] = {0};

    initDate(date);

    /* 第一种 */
    pfn1(date, (int)code1);
    printHEX(code1, 22);
    printf("\n");
    printHEX(code1, 16);
    printHEX((unsigned char *)&systemtime, 4);
    printHEX((unsigned char *)&systemtime + 6, 2);
    printf("\n");

    /* 第二种 */
    pfn1(&systemtime, (int)code2);
    printHEX(code2, 22);
    printf("\n");

    FreeLibrary(hMod);

    if (!getenv("PROMPT")) system("pause");

    return 0;
}
