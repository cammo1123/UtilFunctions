#include <Windows.h>

int strcmp(char *s1, char *s2)
{
	for (; *s1 && *s2; s1++, s2++)
	{
		int res = *s1 - *s2;
		if (res)
			return res;
	}
	return *s1 - *s2;
}

void SendKey(BYTE virtualKey)
{
	keybd_event(virtualKey, 0, 0, 0);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
	return;
}

int main(int argc, char *argv[])
{

	if (strcmp(argv[1], (char *)"playpause") == 0)
	{
		SendKey(VK_MEDIA_PLAY_PAUSE);
	}
	else if (strcmp(argv[1], (char *)"next") == 0)
	{
		SendKey(VK_MEDIA_NEXT_TRACK);
	}
	else if (strcmp(argv[1], (char *)"prev") == 0)
	{
		SendKey(VK_MEDIA_PREV_TRACK);
	}
	else if (strcmp(argv[1], (char *)"stop") == 0)
	{
		SendKey(VK_MEDIA_STOP);
	}
	return 0;
}