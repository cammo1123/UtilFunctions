#include <Windows.h>
#include <iostream>
#include <Mmdeviceapi.h>
#include <Endpointvolume.h>

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

int SetVolume(char *nVolume = NULL)
{

	CoInitialize(NULL);

	IMMDeviceEnumerator *deviceEnumerator = NULL;
	CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);

	IMMDevice *defaultDevice = NULL;
	deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();

	if (nVolume != NULL)
		endpointVolume->SetMasterVolumeLevelScalar(std::stof(nVolume) / 100, NULL);

	float Volume = 0.0;
	endpointVolume->GetMasterVolumeLevelScalar(&Volume);
	endpointVolume->Release();

	CoUninitialize();
	return Volume * 100.0;
}

void SendKey(BYTE virtualKey)
{
	keybd_event(virtualKey, 0, 0, 0);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
}

int main(int argc, char *argv[])
{
	if (strcmp(argv[1], (char *)"--media") == 0)
	{
		if (strcmp(argv[2], (char *)"playpause") == 0)
		{
			SendKey(VK_MEDIA_PLAY_PAUSE);
		}
		else if (strcmp(argv[2], (char *)"next") == 0)
		{
			SendKey(VK_MEDIA_NEXT_TRACK);
		}
		else if (strcmp(argv[2], (char *)"prev") == 0)
		{
			SendKey(VK_MEDIA_PREV_TRACK);
		}
		else if (strcmp(argv[2], (char *)"stop") == 0)
		{
			SendKey(VK_MEDIA_STOP);
		}
	}
	else if (strcmp(argv[1], (char *)"--volume") == 0)
	{
		std::cout << SetVolume(argv[2]);
	}

	return 0;
}