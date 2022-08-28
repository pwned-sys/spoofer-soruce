#pragma once
#pragma once

// warnings
#define no_init_all deprecated
#pragma warning( disable : 4129 )

// sdk
#include <Windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <sstream>
#include <TlHelp32.h>
#include <Psapi.h>
#include <iostream>
#include <cassert>
#pragma warning(disable:4191 4099)
#pragma warning(disable:4996)

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LUGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

// lib
#pragma comment(lib, "ntdll.lib")

// vmprotect

// curl

// defines
#include <cstdio>

#pragma comment(lib, "Urlmon.lib")
#define stra(x) VMProtectDecryptStringA(x)
#include "api/KeyAuth.hpp"
#include "xorstr.hpp"
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <filesystem>
#include "util.h"
#include "mapper/kdmapper.hpp"
#include <sys/stat.h>
#include <conio.h>

// xor
#include "xorstr.hpp"
// self
#include "api/KeyAuth.hpp"
#include "process.h"

namespace Util {
	void SetColor(unsigned short color)
	{
		HANDLE con = 0;
		con = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(con, color);
	}

	void Clear()
	{
		COORD topLeft = { 0, 0 };
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;
		GetConsoleScreenBufferInfo(console, &screen);
		FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		SetConsoleCursorPosition(console, topLeft);
		return;
	}

	void Command(const char* Command) {
		system(Command);
	}
	void WriteLine(std::string text, int time = 1) {
		std::cout << std::setw(35);
		for (int i = 0; text[i] != '\0'; i++) {
				Sleep(time);
				std::cout << text[i];
				if (text[i] == ' ')
					Sleep(0);
			}
	}
	void WriteCentered(std::string text, int time = 1) {
		std::cout << std::setw(25);
		for (int i = 0; text[i] != '\0'; i++) {
			Sleep(time);
			std::cout << text[i];
			if (text[i] == ' ')
				Sleep(0);
		}
	}
	std::string GenRandomString(const int len) {
		VMStart();
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"*'?=`´_:;-><\\=)(/&%$§\"{[]}"
			"abcdefghijklmnopqrstuvwxyz";
		std::string tmp_s;
		tmp_s.reserve(len);

		for (int i = 0; i < len; ++i) {
			tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		VMEnd();
		return tmp_s;
	}
	DWORD NewVolume() {
		VMStart();

			auto randchar = []() -> char
			{
				const char charset[] =
					"0123456789"
					"ABCDEF";
				const size_t max_index = (sizeof(charset) - 1);
				return charset[rand() % max_index];
			};
			std::string str(8, 0);
			std::generate_n(str.begin(), 8, randchar);
		
		VMEnd();
		return std::strtoul(str.c_str(), NULL, 16);
	}
	enum State { Detected, Undetected, Unknown};
	void SetConsoleWindow(HANDLE conout, SHORT cols, SHORT rows)
	{
		VM_FISH_WHITE_START
		CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
		sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
		GetConsoleScreenBufferInfoEx(conout, &sbInfoEx);
		sbInfoEx.dwSize.X = cols;
		sbInfoEx.dwSize.Y = rows;
		sbInfoEx.srWindow = { 0, 0, cols, rows };
		sbInfoEx.dwMaximumWindowSize = { cols, rows };
		SetConsoleScreenBufferInfoEx(conout, &sbInfoEx);

		DWORD mode;
		GetConsoleMode(conout, &mode);
		mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
		SetConsoleMode(conout, mode);
		VM_FISH_WHITE_END
	}
	int s_width = 888;
	void PrintMainMenu() {
		Util::Clear();
		Util::WriteLine(XorStr("[1] Clean Tracking Files and Registry Values\n"));
		Util::WriteLine(XorStr("[2] Spoof Serials\n"));
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		Util::WriteLine("Please choose an selection: ");
	}
}