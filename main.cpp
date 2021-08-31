#include <Windows.h>
#include <iostream>

void SendKey(BYTE virtualKey)
{
	keybd_event(virtualKey, 0, 0, 0);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
}

int main(int argc, char *argv[])
{
	SendKey(VK_MEDIA_PLAY_PAUSE);
	return 0;
}