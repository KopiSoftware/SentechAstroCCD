#ifndef _SET_CAMERA_FUNCTION_H
#define _SET_CAMERA_FUNCTION_H

BOOL	GetCameraVersion(HANDLE hCamera);
BOOL	GetColorArray(HANDLE hCamera);
BOOL	SetCameraID(HANDLE hCamera);
BOOL	SetScanMode(HANDLE hCamera);
BOOL	SetClockMode(HANDLE hCamera);
BOOL	SetExposureTime(HANDLE hCamera);
BOOL	SetGain(HANDLE hCamera);
BOOL	SetTriggerMode(HANDLE hCamera);
BOOL	SetIO(HANDLE hCamera);
BOOL	SetLED(HANDLE hCamera);
BOOL	SetTriggerTimming(HANDLE hCamera);
BOOL	ResetFrameCounter(HANDLE hCamera);
BOOL	SetWhiteBalance(HANDLE hCamera);
BOOL	SetHueSaturationColorMatrix(HANDLE hCamera);
BOOL	SetSharpness(HANDLE hCamera);
BOOL	SetTimeOut(HANDLE hCamera);

#endif //_SET_CAMERA_FUNCTION_H


