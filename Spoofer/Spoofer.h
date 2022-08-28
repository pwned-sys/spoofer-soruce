#pragma once
#include <iostream>
#include "../xorstr.hpp"
#include "../mapper/kdmapper.hpp"
#include <Windows.h>
#include "../Util.h"
using namespace std;
bool SpuwufVolume(char drive)
{
	const int max_pbsi = 3;

	struct partial_boot_sector_info
	{
		LPCSTR Fs;
		DWORD FsOffs; 
		DWORD SerialOffs;
	};

	partial_boot_sector_info pbsi[max_pbsi] =
	{
	 {"FAT32", 0x52, 0x43},
	 {"FAT",   0x36, 0x27},
	 {"NTFS",  0x03, 0x48}
	};

	char buf[64];
	sprintf_s(buf, "\\\\.\\%c:", drive);

	HANDLE hFile = CreateFileA(buf, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	BYTE sector[0x200];
	DWORD dwBytesRead;
	bool result = false;
	if (ReadFile(hFile, sector, sizeof(sector), &dwBytesRead, nullptr)) {
		int i;
		for (i = 0; i < max_pbsi; i++)
		{
			if (strncmp(pbsi[i].Fs, (const char*)(sector + pbsi[i].FsOffs), strlen(pbsi[i].Fs)) == 0)
			{
				break;
			}
		}

		if (i < max_pbsi) {
			printf("drive: %c, Serial: %X\r\n", drive, *(PDWORD)(sector + pbsi[i].SerialOffs));
			printf("\n");
			DWORD aaaaa = Util::NewVolume();
			std::ostringstream aa;
			aa << aaaaa;
			std::cout << aa.str();
			*(PDWORD)(sector + pbsi[i].SerialOffs) = aaaaa;
			printf("drive: %c, Spoofed Serial: %X\r\n", drive, *(PDWORD)(sector + pbsi[i].SerialOffs));
			if (INVALID_SET_FILE_POINTER != SetFilePointer(hFile, NULL, NULL, FILE_BEGIN)) {
				DWORD dwBytesWritten;
				result = ::WriteFile(hFile, sector, sizeof(sector), &dwBytesWritten, nullptr) == TRUE;
			}
		}
		else
			printf("unknown fs\r\n");
	}

	::CloseHandle(hFile);
	return result;
}
void Spoof() {
    HANDLE hDevice = NULL;
    HANDLE fileFind = NULL;
        char drv = 'A';
        while (drv != '[')
        {
            Sleep(105);
            const char* charDrvCF;
            const char* charDrv;
            stringstream Str;
            string drvStr;
            Str << drv;
            Str >> drvStr;
            string drvSpc = drvStr + ":\\";
            string fCheck = "\\\\.\\";
            string fhCheck = fCheck + drvStr + ":";
            charDrvCF = fhCheck.c_str();
            charDrv = drvSpc.c_str();
            hDevice = CreateFile(charDrvCF,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                NULL,
                OPEN_EXISTING,
                0,
                NULL);
            if (hDevice != INVALID_HANDLE_VALUE)
            {
                switch (GetDriveType(charDrv))
                {
                case DRIVE_FIXED:
                {
					SpuwufVolume(drv);
                    break;
                }
                }
            }
            drv++;
        
    }

}