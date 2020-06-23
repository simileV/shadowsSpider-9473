#include "pch.h"
#include "FileSystem.h"

void testFS()
{
	string pathTestFS0 = "C:/Users/aleks/source/repos/testFS/";
	string pathTestFS1 = "C:/Users/aleks/source/repos/testFS/firstEntry/";

	if (fs::exists(pathTestFS0))
	{
		cout << "pathTestFS0 exists already...deleting first" << endl;
		fs::remove_all(pathTestFS0);

		//remove all children
	}

	else
	{
		cout << "pathTestFS0 does not exist" << endl;
		fs::create_directory(pathTestFS0);
		fs::create_directory(pathTestFS1);
	}

	//create new file and give R / W / RW
	string pathTestFile = "C:/Users/aleks/source/repos/testFS/testFile.xml";
	ofstream(pathTestFile.c_str());

	//cout << "created test xml file" << endl;

	fs::remove("C:/Users/aleks/source/repos/testFS/testFile.xml");

	//for (auto &i : fs::directory_iterator(pathTestFfyhS0))
	//	cout << i << endl;

	//cout << "00000000" << endl;

	//for (auto &i : fs::directory_iterator(pathTestFS0))
	//	cout << i << endl;

	//cout << "00000000" << endl;

	fs::remove_all(pathTestFS0); //

	//fs::space_info cDriveSpace = fs::space("C:/");
	//cout << "cDriveSpace capacity / avaliable / free = " << cDriveSpace.capacity << " " << cDriveSpace.available << " " << cDriveSpace.free << endl;
}

bool testIfWinHandleExists(const char *name)
{
	HWND hwnd;
	//DWORD pid;
	//RECT rect;

	hwnd = FindWindowA(0, name);
	//hwnd = FindWindowA(0, (name));

	//GetWindowThreadProcessId(hwnd, &pid);

	//LPCTSTR WindowName = "Mozilla Firefox";
	//LPCTSTR WindowName = "Chrome";
	//HWND Find = FindWindow("Chrome", 0);

	//HWND Find = ::FindWindowEx(0, 0, "MozillaUIWindowClass", 0);
	//HWND Find = ::FindWindowEx(0, 0, "MozillaUIWindowClass", 0);

	if (hwnd)
	{
		getWindowPos(name);

		return 1;
	}

	//cout << "window not found for : " << name << endl;
	return 0;
}

void getWindowPos(const char *name)
{
	HWND hwnd;
	DWORD pid;
	RECT rect;

	hwnd = FindWindowA(0, name);
	GetWindowThreadProcessId(hwnd, &pid);

	//hwnd = GetBoundsRect();
	GetWindowRect(hwnd, &rect);
	int myRectW = rect.right - rect.left;
	int myRectH = rect.bottom - rect.top;

	//cout << name << " LRTB : " << rect.left << " " << rect.right << " " << rect.top << " " << rect.bottom << endl;
	cout << name << " LU : " << rect.left << " " << rect.top << endl;
	cout << name << " WH = " << myRectW << " " << myRectH << endl;

	//int winW
	//nicehash LRTB : 3559 4189 411 851
}