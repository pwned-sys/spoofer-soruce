#include <iostream>
#include "api/KeyAuth.hpp"
#include "xorstr.hpp"
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include "mapper/kdmapper.hpp"
#include <fileapi.h>
#include <iomanip> 
#include "Spoofer/Spoofer.h"
#include "Util.h"
//#define DISABLE_OUTPUT
using namespace std;
using namespace KeyAuth;
void safe();
void notSafe();
void me();

std::string name = ""; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = ""; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = ""; // app secret, the blurred text on licenses tab and other tabs
std::string version = ""; // leave alone unless you've changed version on website

api KeyAuthApp(name, ownerid, secret, version);

void SpoofMenu() {
	VM_FISH_BLACK_START
		int option;
	std::vector<std::uint8_t> bytes;
	HANDLE iqvw64e_device_handle;
spoofselection:
	Util::Clear();
	Util::WriteLine(XorStr("[1] Randomize Serials\n"));
	Util::WriteLine(XorStr("[2] Null Serials\n"));
	Util::WriteLine("Please choose an selection: ");
	std::cin >> option;
	std::string YN;
	if (option == 1) {
		Util::WriteLine(XorStr("Old Disk Serial(s):"));
		std::cout << std::endl;
		system(XorStr("wmic diskdrive get serialnumber\n").c_str());
		notSafe();
		bytes = KeyAuthApp.download(XorStr("ID")); // driver 1 / randomize
		safe();
		iqvw64e_device_handle = intel_driver::Load();

		if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE) {
			std::cout << XorStr("\n IQ00001. Contact Staff For More Info.");
			Sleep(3500);
			exit(0);
		}
		if (!kdmapper::MapDriver(iqvw64e_device_handle, bytes.data())) {
			std::cout << XorStr("\n IQ00001. Contact Staff For More Info.");
			intel_driver::Unload(iqvw64e_device_handle);
			Sleep(3500);
			exit(0);
		}
		intel_driver::Unload(iqvw64e_device_handle);
		system(XorStr("powershell -command \"Reset-PhysicalDisk *\" --quiet --no-verbose >$null 2>&1").c_str());
		system(XorStr("net stop winmgmt /Y >nul").c_str());
		Util::WriteLine(XorStr("New Disk Serial Number(s):"));
		std::cout << std::endl;
		system(XorStr("wmic diskdrive get serialnumber\n").c_str());
		std::cout << std::endl;
		std::cout << std::endl << std::endl;
		std::cout << std::endl;
		Util::WriteLine(XorStr("Press any key to go back to the menu"));
		system(XorStr("Pause >nul").c_str());
	}
	else if (option == 2) {
		Util::WriteLine(XorStr("Old Disk Serial(s):"));
		std::cout << std::endl;
		system(XorStr("wmic diskdrive get serialnumber\n").c_str());
		notSafe();
		bytes = KeyAuthApp.download(XorStr("ID")); // driver 2 / null
		safe();
		iqvw64e_device_handle = intel_driver::Load();

		if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE) {
			std::cout << XorStr("\n IQ00001. Contact Staff For More Info.");
			Sleep(3500);
			exit(0);
		}
		if (!kdmapper::MapDriver(iqvw64e_device_handle, bytes.data())) {
			std::cout << XorStr("\n IQ00001. Contact Staff For More Info.");
			intel_driver::Unload(iqvw64e_device_handle);
			Sleep(3500);
			exit(0);
		}
		intel_driver::Unload(iqvw64e_device_handle);
		system(XorStr("powershell -command \"Reset-PhysicalDisk *\" --quiet --no-verbose >$null 2>&1").c_str());
		system(XorStr("net stop winmgmt /Y >nul").c_str());
		Util::WriteLine(XorStr("New Disk Serial Number(s):"));
		std::cout << std::endl;
		system(XorStr("wmic diskdrive get serialnumber\n").c_str());
		std::cout << std::endl;
		std::cout << std::endl << std::endl;
		std::cout << std::endl;
		Util::WriteLine(XorStr("Press any key to go back to the menu"));
		system(XorStr("Pause >nul").c_str());
	}
	else {
		goto spoofselection;
	}
	VM_FISH_BLACK_END

}
int main(int argc, char** argv)
{
//	VM_DOLPHIN_BLACK_START
		char ownPth[MAX_PATH];

	// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
/*	HMODULE hModule = GetModuleHandle(NULL);

		GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));


	//std::cout << fs::basepath(full_path) << std::endl;

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;
	COORD newSize;
	newSize.X = scrBufferWidth;
	newSize.Y = winHeight;

	// set the new screen buffer dimensions
	int Status = SetConsoleScreenBufferSize(hOut, newSize);*/
#pragma region Variables
	std::string license;
#pragma endregion

	safe();
	SetConsoleTitleA(Util::GenRandomString(6969).c_str());
	Sleep(500);
#ifdef LOGS
	system("pause");
#endif // LOGS
	Util::WriteLine(XorStr("\n\nConnecting.."), 25);
	notSafe();
	KeyAuthApp.init();

	if (KeyAuthApp.checkblack())
	{
		exit(0);
	}
	
	safe();
	LOGINLABEL: 
	Util::Clear();
	if (std::filesystem::exists(XorStr("C:\\ProgramData\\pwned.example\\Config.cfg").c_str())) {
		std::ifstream password_file(XorStr("C:\\ProgramData\\pwned.example\\Config.cfg"), std::ios::in);
		std::getline(password_file, license);
		notSafe();
		if (KeyAuthApp.license(encryption::decode(license))) {
			safe();
			goto encryptinglicense;
		}
		else {
			DeleteFileA(XorStr("C:\\ProgramData\\pwned.example\\Config.cfg").c_str());
		}
		Sleep(4000);
		goto LOGINLABEL;
	}
	else {
		std::filesystem::create_directories(XorStr("C:\\ProgramData\\pwned.example").c_str());
		Util::WriteLine("License: ");
		std::cin >> license;
		notSafe();
		if(KeyAuthApp.license(license)) {
			std::ofstream password_file2(XorStr("C:\\ProgramData\\pwned.example\\Config.cfg").c_str());
			safe();
			password_file2 << encryption::encode(license);
			goto encryptinglicense;
		}
		else {
			DeleteFileA(XorStr("C:\\ProgramData\\pwned\\Config.cfg").c_str());
		}
		Sleep(4000);
		goto LOGINLABEL;
	}
encryptinglicense:
	int option;
	Util::Clear();
	Util::WriteLine("Current Users Online: " + KeyAuthApp.user_data.numUsersOnline);
	Sleep(2000);
starting:
	Util::PrintMainMenu();
	std::cin >> option;
	switch (option) {
	case 2:
		SpoofMenu();
		goto encryptinglicense;
	default:
		goto starting;
	}
}

void* pe_header[4096];
void safe()
{
	MutateStart();
	DWORD old = 0;
	void* module = GetModuleHandleW(0);

	VirtualProtect(module, 4096, PAGE_READWRITE, &old);
	memcpy(pe_header, module, 4096);
	ZeroMemory(module, 4096);
	VirtualProtect(module, 4096, old, &old);
	MutateEnd();
}
void notSafe()
{
	MutateStart();
	DWORD old = 0;
	void* module = GetModuleHandleW(0);

	VirtualProtect(module, 4096, PAGE_READWRITE, &old);
	memcpy(module, pe_header, 4096);
	VirtualProtect(module, 4096, old, &old);
	MutateEnd();
}

