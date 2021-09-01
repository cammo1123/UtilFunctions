#include <Windows.h>
#include <iostream>
#include <Mmdeviceapi.h>
#include <Endpointvolume.h>

int main(int argc, char *argv[])
{
	float nVolume = std::stof(argv[1]);
	
	CoInitialize(NULL);

	IMMDeviceEnumerator *deviceEnumerator = NULL;
	IAudioEndpointVolume *endpointVolume = NULL;
	IMMDevice *defaultDevice = NULL;
	
	CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, 1, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);

	deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	defaultDevice->Activate(__uuidof(IAudioEndpointVolume), 1, NULL, (LPVOID *)&endpointVolume);

	endpointVolume->SetMasterVolumeLevelScalar(nVolume, NULL);

	deviceEnumerator->Release();
	defaultDevice->Release();
	endpointVolume->Release();
	
	CoUninitialize();

	return 0;
}