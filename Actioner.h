#include <Windows.h>
#pragma comment(lib,"user32.lib")

class Action {
private:
	INPUT * mouse_input=NULL;
	INPUT * key_input = NULL;
	unsigned int size;
public:
	POINT  mousepoint;
	Action(int size) {
		if (size <= 2)size = 3;
			this->size = size;
			mouse_input = new INPUT[size];
			key_input = new INPUT[size];
	}
	~Action() {
		mouse_input = NULL;
		key_input = NULL;
	}
	void clean() {
		delete[] mouse_input;
		delete[] key_input ;
	}
	Action move(long x,long y,bool absolut=false) {
		ZeroMemory(&mouse_input[0], sizeof(mouse_input[0]));
		mouse_input[0].type = INPUT_MOUSE;
		mouse_input[0].mi.dx = x;
		mouse_input[0].mi.dy = y;
		if (absolut)
			mouse_input[0].mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
		else
			mouse_input[0].mi.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &mouse_input[0], sizeof(mouse_input[0]));
		GetCursorPos(&mousepoint);   // »°µÿ÷∑
		return *this;
	}
	Action click() {
		ZeroMemory(&mouse_input[0], sizeof(mouse_input[0])*2);
		mouse_input[0].type = INPUT_MOUSE;
		mouse_input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &mouse_input[0], sizeof(mouse_input[0]) );
		mouse_input[1].type = INPUT_MOUSE;
		mouse_input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &mouse_input[1], sizeof(mouse_input[1]));
		return *this;
	}
	Action dbclick() {
		/*ZeroMemory(&mouse_input[0], sizeof(mouse_input[0]));
		mouse_input[0].type = INPUT_MOUSE;
		mouse_input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &mouse_input[0], sizeof(mouse_input[0]));
		mouse_input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &mouse_input[0], sizeof(mouse_input[0]));
		mouse_input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &mouse_input[0], sizeof(mouse_input[0]));
		mouse_input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &mouse_input[0], sizeof(mouse_input[0]));*/
		return click().click();
		//return *this;
	}
	Action rclick() {
		ZeroMemory(&mouse_input[0], sizeof(mouse_input[0])*2);
		mouse_input[0].type = INPUT_MOUSE;
		mouse_input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &mouse_input[0], sizeof(mouse_input[0]));
		mouse_input[1].type = INPUT_MOUSE;
		mouse_input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(1, &mouse_input[1], sizeof(mouse_input[1]));
		return *this;
	}
	Action input(wchar_t str[] ) {
		ZeroMemory(&key_input[0], sizeof(key_input[0]));
		key_input[0].type= INPUT_KEYBOARD;
		key_input[0].ki.dwFlags = KEYEVENTF_UNICODE;
		key_input[0].ki.time = GetTickCount();
		for(unsigned int i =0;i<wcslen(str);i++)
		{
			key_input[0].ki.wScan = str[i];
			SendInput(1,&key_input[0], sizeof(key_input[0]));
		}
		return *this;
	}
	Action press(WORD vk) {
		return keydown(vk).keyup(vk);
	}
	Action keydown(WORD vk) {
		ZeroMemory(&key_input[0], sizeof(key_input[0]));
		key_input[0].type = INPUT_KEYBOARD;
		key_input[0].ki.dwFlags = 0;
		key_input[0].ki.time = GetTickCount();
		key_input[0].ki.wVk = vk;
		SendInput(1, &key_input[0], sizeof(key_input[0]));
		return *this;
	}
	Action keyup(WORD vk) {
		ZeroMemory(&key_input[0], sizeof(key_input[0]));
		key_input[0].type = INPUT_KEYBOARD;
		key_input[0].ki.dwFlags = KEYEVENTF_KEYUP;
		key_input[0].ki.time = GetTickCount();
		key_input[0].ki.wVk = vk;
		SendInput(1, &key_input[0], sizeof(key_input[0]));
		return *this;
	}
	Action key_selectall() {
		return keydown(VK_LCONTROL).press('A').keyup(VK_LCONTROL);
	}
	Action key_past() {
		return keydown(VK_LCONTROL).press('V').keyup(VK_LCONTROL);
	}
	Action key_cut() {
		return keydown(VK_LCONTROL).press('X').keyup(VK_LCONTROL);
	}
	Action key_find() {
		return keydown(VK_LCONTROL).press('F').keyup(VK_LCONTROL);
	}
	Action key_undo() {
		return keydown(VK_LCONTROL).press('Z').keyup(VK_LCONTROL);
	}
	Action key_redo() {
		return keydown(VK_LCONTROL).press('Y').keyup(VK_LCONTROL);
	}
	Action key_res() {
		return keydown(VK_LCONTROL).keydown(VK_LSHIFT).keydown(VK_ESCAPE).keyup(VK_ESCAPE).keyup(VK_LSHIFT).keyup(VK_LCONTROL);
	}
	Action keycompare(WORD list[]) {
		int len=1+sizeof(list) / sizeof(WORD);
		INPUT *ckey=new INPUT [2 * len];
		ZeroMemory(ckey, sizeof(ckey[0])* 2 * len);
		for (int i = 0; i < len;i++) {
			ckey[i].type = INPUT_KEYBOARD;
			ckey[i].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
			ckey[i].ki.wVk = list[i];
		}
		//WORD tm= GetTickCount();
		for (int i = len; i < len*2; i++) {
			ckey[i].type = INPUT_KEYBOARD;
			ckey[i].ki.dwFlags = KEYEVENTF_KEYUP ;
			ckey[i].ki.wVk = list[i-len];
		}
		for (int i = 0; i < len * 2; i++) {
			SendInput(1, &ckey[i], sizeof(ckey[i]));
		}
		

		
		//delete[] ckey;
		return *this;
	}	
};