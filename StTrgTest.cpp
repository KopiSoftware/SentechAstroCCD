#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "include/StTrgApi.h"
#include "SetCameraFunction.h"

#ifdef _WIN64
#pragma comment(lib, "lib/x64/StTrgApi.lib")
#else //_WIN64
#pragma comment(lib, "lib/x86/StTrgApi.lib")
#endif //_WIN64

#include <direct.h>

#define DISPLAY_CALLBACK_INFO
/*
#define DISPLAY_TIME_WHITE_BALANCE
#define DISPLAY_TIME_MIRROE_ROTATION
#define DISPLAY_TIME_COLOR_INTERPOLATION
#define DISPLAY_TIME_HUE_SATURATION_COLOR_MATRIX
#define DISPLAY_TIME_SHARPNESS
*/
#ifdef DISPLAY_CALLBACK_INFO
LARGE_INTEGER g_timeSoftTriggerOrTransferEnd = {0};
LARGE_INTEGER g_timeExposureEnd = {0};
LARGE_INTEGER g_timeTransferEnd = {0};
LARGE_INTEGER g_timeFirstFrame = {0};
#endif //DISPLAY_CALLBACK_INFO

BOOL	g_bExitMenu = FALSE;
BOOL	g_bContinuousSoftTriggerFg = FALSE;
BOOL	g_bSaveFileFg = FALSE;
TCHAR	g_szBitmapFilePath[MAX_PATH];

BYTE	g_byteMirrorMode = STCAM_MIRROR_HORIZONTAL;
	//STCAM_MIRROR_OFF, STCAM_MIRROR_HORIZONTAL, STCAM_MIRROR_VERTICAL, STCAM_MIRROR_HORIZONTAL_VERTICAL
BYTE	g_byteRotationMode = STCAM_ROTATION_CLOCKWISE_90;
	//STCAM_ROTATION_OFF, STCAM_ROTATION_CLOCKWISE_90, STCAM_ROTATION_COUNTERCLOCKWISE_90
int long_exposure_time = 0;
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
double mdblGetIntervalTime(LARGE_INTEGER *pliBase, LARGE_INTEGER *pliCur)
{
	static	BOOL sbFirstTimeFg = TRUE;
	static	LARGE_INTEGER liFreq;
	double	dblIntervalTime = 0.0;

	if(sbFirstTimeFg)
	{
		QueryPerformanceFrequency(&liFreq);
		sbFirstTimeFg = FALSE;
	}

	if(pliBase->QuadPart < pliCur->QuadPart)
	{
		dblIntervalTime = ((double)(pliCur->QuadPart - pliBase->QuadPart) * 1000.0) / (double)liFreq.QuadPart;
	}
	return(dblIntervalTime);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
DWORD mdwGetAveragePixelValue(DWORD dwWidth, DWORD dwHeight, PBYTE pbyteRaw)
{
	DWORD	dwPixelCount = dwWidth * dwHeight;
	DWORD	dwRestCycle = dwPixelCount;
	DWORD	dwSum  = 0;

	while(dwRestCycle--)
	{
		dwSum += pbyteRaw[dwRestCycle];
	}
	dwSum /= dwPixelCount;

	return(dwSum);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void __stdcall ExposureEndCallback(HANDLE hCamera, DWORD dwFrameNo, PVOID pvContext)
{
#ifdef DISPLAY_CALLBACK_INFO
	QueryPerformanceCounter(&g_timeExposureEnd);
	_tprintf(TEXT("EE %u - %0.1fms\n"),
		dwFrameNo,
		mdblGetIntervalTime(&g_timeSoftTriggerOrTransferEnd, &g_timeExposureEnd));
#endif //DISPLAY_CALLBACK_INFO
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void __stdcall TransferEndCallback(HANDLE hCamera, DWORD dwFrameNo, DWORD dwWidth, DWORD dwHeight, WORD wColorArray, PBYTE pbyteRaw, PVOID pvContext)
{
	static DWORD sdwDropCount = 0;
	static DWORD sdwExpectFrameNo = 0;
	static BOOL sbFirstTimeFg = TRUE;
	
#ifdef DISPLAY_CALLBACK_INFO
	QueryPerformanceCounter(&g_timeTransferEnd);
#endif //DISPLAY_CALLBACK_INFO

	if(sbFirstTimeFg)
	{
#ifdef DISPLAY_CALLBACK_INFO
		g_timeFirstFrame = g_timeTransferEnd;
#endif //DISPLAY_CALLBACK_INFO
		sbFirstTimeFg = FALSE;
	}
	else if(sdwExpectFrameNo != dwFrameNo)
	{
		sdwDropCount += dwFrameNo - sdwExpectFrameNo;
		_tprintf(TEXT("Drop:%u\n"), sdwDropCount);
	}
	sdwExpectFrameNo = dwFrameNo + 1;

#ifdef DISPLAY_CALLBACK_INFO
	_tprintf(TEXT("TE %u - %0.1fms - Drop:%u - Ave.:%u - %0.1fms\n"),
		dwFrameNo,
		mdblGetIntervalTime(&g_timeExposureEnd, &g_timeTransferEnd),
		sdwDropCount,
		mdwGetAveragePixelValue(dwWidth, dwHeight, pbyteRaw),
		mdblGetIntervalTime(&g_timeFirstFrame, &g_timeTransferEnd));
#endif //DISPLAY_CALLBACK_INFO

	if(STCAM_COLOR_ARRAY_MONO == wColorArray)
	{
		//---------------------------------------------------------------------
		//Mirror Rotation
		//---------------------------------------------------------------------
#ifdef DISPLAY_TIME_MIRROE_ROTATION
		LARGE_INTEGER	pMirrorRotationTime[] = {{0}, {0}};
		QueryPerformanceCounter(&pMirrorRotationTime[0]);
#endif //DISPLAY_TIME_MIRROE_ROTATION
		StTrg_MirrorRotation(g_byteMirrorMode, g_byteRotationMode, &dwWidth, &dwHeight, &wColorArray, pbyteRaw);
#ifdef DISPLAY_TIME_MIRROE_ROTATION
		QueryPerformanceCounter(&pMirrorRotationTime[1]);
		_tprintf(TEXT("\tMirror Rotation Time : %0.3fms\n"),mdblGetIntervalTime(&pMirrorRotationTime[0], &pMirrorRotationTime[1]));
#endif //DISPLAY_TIME_MIRROE_ROTATION

		//---------------------------------------------------------------------
		//Sharpness
		//---------------------------------------------------------------------
#ifdef DISPLAY_TIME_SHARPNESS
		LARGE_INTEGER	pSharpnessTime[] = {{0}, {0}};
		QueryPerformanceCounter(&pSharpnessTime[0]);
#endif //DISPLAY_TIME_SHARPNESS
		StTrg_Sharpness(hCamera, dwWidth, dwHeight, STCAM_PIXEL_FORMAT_08_MONO_OR_RAW, pbyteRaw);
#ifdef DISPLAY_TIME_SHARPNESS
		QueryPerformanceCounter(&pSharpnessTime[1]);
		_tprintf(TEXT("\tSharpness Time : %0.3fms\n"),mdblGetIntervalTime(&pSharpnessTime[0], &pSharpnessTime[1]));
#endif //DISPLAY_TIME_SHARPNESS

		if(g_bSaveFileFg)
		{
			TCHAR szFileName[MAX_PATH];
			_stprintf(szFileName, TEXT("%s\\%u.bmp"), g_szBitmapFilePath, dwFrameNo);
			g_bSaveFileFg = FALSE;
			StTrg_SaveImage(dwWidth, dwHeight, STCAM_PIXEL_FORMAT_08_MONO_OR_RAW, pbyteRaw, szFileName, 0);
		}
	}
	else
	{
		//---------------------------------------------------------------------
		//White Balance
		//---------------------------------------------------------------------
#ifdef DISPLAY_TIME_WHITE_BALANCE
		LARGE_INTEGER	pWhiteBalanceTime[] = {{0}, {0}};
		QueryPerformanceCounter(&pWhiteBalanceTime[0]);
#endif //DISPLAY_TIME_WHITE_BALANCE
		StTrg_WhiteBalance(hCamera, pbyteRaw);
#ifdef DISPLAY_TIME_WHITE_BALANCE
		QueryPerformanceCounter(&pWhiteBalanceTime[1]);
		_tprintf(TEXT("\tWhite Balance Time : %0.3fms\n"),mdblGetIntervalTime(&pWhiteBalanceTime[0], &pWhiteBalanceTime[1]));
#endif //DISPLAY_TIME_WHITE_BALANCE

		//---------------------------------------------------------------------
		//Mirror Rotation
		//---------------------------------------------------------------------
#ifdef DISPLAY_TIME_MIRROE_ROTATION
		LARGE_INTEGER	pMirrorRotationTime[] = {{0}, {0}};
		QueryPerformanceCounter(&pMirrorRotationTime[0]);
#endif //DISPLAY_TIME_MIRROE_ROTATION
		StTrg_MirrorRotation(g_byteMirrorMode, g_byteRotationMode, &dwWidth, &dwHeight, &wColorArray, pbyteRaw);
#ifdef DISPLAY_TIME_MIRROE_ROTATION
		QueryPerformanceCounter(&pMirrorRotationTime[1]);
		_tprintf(TEXT("\tMirror Rotation Time : %0.3fms\n"),mdblGetIntervalTime(&pMirrorRotationTime[0], &pMirrorRotationTime[1]));
#endif //DISPLAY_TIME_MIRROE_ROTATION


		//---------------------------------------------------------------------
		//Color Interpolation
		//---------------------------------------------------------------------
		PBYTE pbyteBGR = new BYTE[dwWidth * dwHeight * 4];
#ifdef DISPLAY_TIME_COLOR_INTERPOLATION
		LARGE_INTEGER	pColorInterpolationTime[] = {{0}, {0}};
		QueryPerformanceCounter(&pColorInterpolationTime[0]);
#endif //DISPLAY_TIME_COLOR_INTERPOLATION
		BYTE	byteColorInterpolationMethod = STCAM_COLOR_INTERPOLATION_BILINEAR;
				//STCAM_COLOR_INTERPOLATION_NONE_MONO
				//STCAM_COLOR_INTERPOLATION_NONE_COLOR
				//STCAM_COLOR_INTERPOLATION_NEAREST_NEIGHBOR
				//STCAM_COLOR_INTERPOLATION_BILINEAR
				//STCAM_COLOR_INTERPOLATION_BICUBIC
		DWORD  dwPixelFormat = STCAM_PIXEL_FORMAT_24_BGR;
			//STCAM_PIXEL_FORMAT_24_BGR
			//STCAM_PIXEL_FORMAT_32_BGR
		StTrg_ColorInterpolation(dwWidth, dwHeight, wColorArray,
								pbyteRaw, pbyteBGR, byteColorInterpolationMethod, dwPixelFormat);
#ifdef DISPLAY_TIME_COLOR_INTERPOLATION
		QueryPerformanceCounter(&pColorInterpolationTime[1]);
		_tprintf(TEXT("\tColor Interpolation Time : %0.3fms\n"),mdblGetIntervalTime(&pColorInterpolationTime[0], &pColorInterpolationTime[1]));
#endif //DISPLAY_TIME_COLOR_INTERPOLATION

		//---------------------------------------------------------------------
		//Hue Saturation Color Matrix
		//---------------------------------------------------------------------
#ifdef DISPLAY_TIME_HUE_SATURATION_COLOR_MATRIX
		LARGE_INTEGER	pHueSaturationColorMatrixTime[] = {{0}, {0}};
		QueryPerformanceCounter(&pHueSaturationColorMatrixTime[0]);
#endif //DISPLAY_TIME_HUE_SATURATION_COLOR_MATRIX
		StTrg_HueSaturationColorMatrix(hCamera, dwWidth, dwHeight, dwPixelFormat, pbyteBGR);
#ifdef DISPLAY_TIME_HUE_SATURATION_COLOR_MATRIX
		QueryPerformanceCounter(&pHueSaturationColorMatrixTime[1]);
		_tprintf(TEXT("\tHue Saturation Color Matrix Time : %0.3fms\n"),mdblGetIntervalTime(&pHueSaturationColorMatrixTime[0], &pHueSaturationColorMatrixTime[1]));
#endif //DISPLAY_TIME_HUE_SATURATION_COLOR_MATRIX

		//---------------------------------------------------------------------
		//Sharpness
		//---------------------------------------------------------------------
#ifdef DISPLAY_TIME_SHARPNESS
		LARGE_INTEGER	pSharpnessTime[] = {{0}, {0}};
		QueryPerformanceCounter(&pSharpnessTime[0]);
#endif //DISPLAY_TIME_SHARPNESS
		StTrg_Sharpness(hCamera, dwWidth, dwHeight, dwPixelFormat, pbyteBGR);
#ifdef DISPLAY_TIME_SHARPNESS
		QueryPerformanceCounter(&pSharpnessTime[1]);
		_tprintf(TEXT("\tSharpness Time : %0.3fms\n"),mdblGetIntervalTime(&pSharpnessTime[0], &pSharpnessTime[1]));
#endif //DISPLAY_TIME_SHARPNESS


		//---------------------------------------------------------------------
		//Save Bitmap File
		//---------------------------------------------------------------------
		if(g_bSaveFileFg)
		{
			TCHAR szFileName[MAX_PATH];
			_stprintf(szFileName, TEXT("%s\\%u.bmp"), g_szBitmapFilePath, dwFrameNo);
			g_bSaveFileFg = FALSE;
			StTrg_SaveImage(dwWidth, dwHeight, dwPixelFormat, pbyteBGR, szFileName, 0);
		}

		delete[] pbyteBGR;
	}


#ifdef DISPLAY_CALLBACK_INFO
	QueryPerformanceCounter(&g_timeSoftTriggerOrTransferEnd);
#endif //DISPLAY_CALLBACK_INFO
	if(g_bContinuousSoftTriggerFg)
	{
		if(!StTrg_SoftTrigger(hCamera))
		{
			_tprintf(TEXT("Soft Trigger Failed.\n"));
		}
	}
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void __stdcall RcvErrorCallback(HANDLE hCamera, DWORD dwErrorCode, PVOID pvContext)
{
	static DWORD spdwErrorCount[] = {0, 0, 0, 0, 0, 0};
	
	switch(dwErrorCode)
	{
	case(ERR_EXPOSURE_END_DROPPED):
		spdwErrorCount[0]++;
		_tprintf(TEXT("Error While Waitting Exposure End:"));
		break;
	case(ERR_IMAGE_DATA_DROPPED):
		spdwErrorCount[1]++;
		_tprintf(TEXT("Error While Waitting Transfer End:"));
		break;
	case(ERR_TIMEOUT_ST2EE):
		spdwErrorCount[2]++;
		_tprintf(TEXT("Error TimeOut(ST2EE):"));
		break;
	case(ERR_TIMEOUT_TE2EE):
		spdwErrorCount[3]++;
		_tprintf(TEXT("Error TimeOut(TE2EE):"));
		break;
	case(ERR_TIMEOUT_EE2TE):
		spdwErrorCount[4]++;
		_tprintf(TEXT("Error TimeOut(EE2TE):"));
		break;
	case(ERR_TIMEOUT_RO2TE):
		spdwErrorCount[5]++;
		_tprintf(TEXT("Error TimeOut(RO2TE):"));
		break;
	case(ERROR_ACCESS_DENIED):
		_tprintf(TEXT("Error Access Denied:"));
		g_bExitMenu = TRUE;
		break;
	}
	_tprintf(TEXT("(%u, %u, %u, %u, %u, %u,)\n"), 
		spdwErrorCount[0], spdwErrorCount[1], spdwErrorCount[2], 
		spdwErrorCount[3], spdwErrorCount[4], spdwErrorCount[5]);

#ifdef DISPLAY_CALLBACK_INFO
	QueryPerformanceCounter(&g_timeSoftTriggerOrTransferEnd);
#endif //DISPLAY_CALLBACK_INFO
	if(ERROR_ACCESS_DENIED != dwErrorCode)
	{
		if(g_bContinuousSoftTriggerFg)
		{
			if(!StTrg_SoftTrigger(hCamera))
			{
				_tprintf(TEXT("Soft Trigger Failed.\n"));
			}
		}
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	HANDLE hCamera = INVALID_HANDLE_VALUE;


	//Set Process Priority
	//SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

	//-------------------------------------------------------------------------
	//Bitmap File Path
	//-------------------------------------------------------------------------
	_tcscpy(g_szBitmapFilePath, argv[0]);
	TCHAR *szTmp = _tcsrchr(g_szBitmapFilePath, TEXT('\\'));
	szTmp[1] = NULL;

	//-------------------------------------------------------------------------
	//Open
	//-------------------------------------------------------------------------
	hCamera = StTrg_Open();
	if(INVALID_HANDLE_VALUE == hCamera)
	{
		_tprintf(TEXT("Couldn't Open.\n"));
		return(-1);
	}

	//-------------------------------------------------------------------------
	//Camera Version
	//-------------------------------------------------------------------------
	if(!GetCameraVersion(hCamera))	return(-1);

	//-------------------------------------------------------------------------
	//Color Array
	//-------------------------------------------------------------------------
	if(!GetColorArray(hCamera))	return(-1);

	//-------------------------------------------------------------------------
	//Camera User ID
	//-------------------------------------------------------------------------
	if(!SetCameraID(hCamera)) return(-1);
	
	//-------------------------------------------------------------------------
	//Scan Mode
	//-------------------------------------------------------------------------
	if(!SetScanMode(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//Exposure Time
	//-------------------------------------------------------------------------
	if(!SetExposureTime(hCamera)) return(-1);
	
	//-------------------------------------------------------------------------
	//Gain
	//-------------------------------------------------------------------------
	if(!SetGain(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//Trigger Mode
	//-------------------------------------------------------------------------
	if(!SetTriggerMode(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//IO
	//-------------------------------------------------------------------------
	if(!SetIO(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//LED
	//-------------------------------------------------------------------------
	if(!SetLED(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//Trigger Timing
	//-------------------------------------------------------------------------
	if(!SetTriggerTimming(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//Reset Counter
	//-------------------------------------------------------------------------
	if(!ResetFrameCounter(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//White Balance
	//-------------------------------------------------------------------------
	if(!SetWhiteBalance(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//Mirror Rotation
	//-------------------------------------------------------------------------
	LPCTSTR		szMirrorMode = NULL;
	LPCTSTR		szRotationMode = NULL;
	switch(g_byteMirrorMode)
	{
	case(STCAM_MIRROR_OFF):						szMirrorMode = TEXT("OFF");	break;
	case(STCAM_MIRROR_HORIZONTAL):				szMirrorMode = TEXT("HORIZONTAL");	break;
	case(STCAM_MIRROR_VERTICAL):				szMirrorMode = TEXT("VERTICAL");	break;
	case(STCAM_MIRROR_HORIZONTAL_VERTICAL):		szMirrorMode = TEXT("HORIZONTAL_VERTICAL");	break;
	}
	switch(g_byteRotationMode)
	{
	case(STCAM_ROTATION_OFF):					szRotationMode = TEXT("OFF");	break;
	case(STCAM_ROTATION_CLOCKWISE_90):			szRotationMode = TEXT("CLOCKWISE_90");	break;
	case(STCAM_ROTATION_COUNTERCLOCKWISE_90):	szRotationMode = TEXT("COUNTERCLOCKWISE_90");	break;
	}
	_tprintf(TEXT("===== Mirror/Rotation ======\n"));
	_tprintf(TEXT("Mirror Mode : %u - %s\n"), g_byteMirrorMode, szMirrorMode);
	_tprintf(TEXT("Rotation Mode : %u - %s\n"), g_byteRotationMode, szRotationMode);

	//-------------------------------------------------------------------------
	//Hue Saturation Color Matrix
	//-------------------------------------------------------------------------
	if(!SetHueSaturationColorMatrix(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//Sharpness
	//-------------------------------------------------------------------------
	if(!SetSharpness(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//Time Out
	//-------------------------------------------------------------------------
	if(!SetTimeOut(hCamera)) return(-1);

	//-------------------------------------------------------------------------
	//Callback Functions
	//-------------------------------------------------------------------------
	if(!StTrg_SetExposureEndCallback(hCamera, ExposureEndCallback, NULL))
	{
		_tprintf(TEXT("Set Exposure End Callback Failed\n"));
		return(-1);
	}
	
	if(!StTrg_SetTransferEndCallback(hCamera, TransferEndCallback, NULL))
	{
		_tprintf(TEXT("Set Transfer End Callback Failed\n"));
		return(-1);
	}

	if(!StTrg_SetRcvErrorCallback(hCamera, RcvErrorCallback, NULL))
	{
		_tprintf(TEXT("Set Rcv Error Callback Failed\n"));
		return(-1);
	}

	//-------------------------------------------------------------------------
	//Transfer Start
	//-------------------------------------------------------------------------
	if(!StTrg_StartTransfer(hCamera))
	{
		_tprintf(TEXT("Couldn't Start.\n"));
		return(-1);
	}

	//-------------------------------------------------------------------------
	//
	//-------------------------------------------------------------------------
	_tprintf(TEXT("H[Enter] - Display Help\n"));
	TCHAR	szInput[2] = {0, 0};
	int i;
	WORD pwWBGain[4];
	LPCTSTR pWBGainName[] = {TEXT("GainR"), TEXT("GainGr"), TEXT("GainGb"), TEXT("GainB")};
	while(!g_bExitMenu)
	{
		szInput[0] = _gettchar();
		_tcsupr(szInput);
		switch(szInput[0])
		{
		case(TEXT('B')):
			g_bSaveFileFg = TRUE;
			break;
		case(TEXT('E')):
			g_bExitMenu = TRUE;
			break;
		case(TEXT('F')):
			g_bContinuousSoftTriggerFg = FALSE;
			break;
		case(TEXT('H')):
			_tprintf(TEXT("B[Enter] : Save Next Frame To Bitmap File\n"));
			_tprintf(TEXT("E[Enter] : Exit\n"));
			_tprintf(TEXT("F[Enter] : Stop Continuous Soft Trigger\n"));
			_tprintf(TEXT("H[Enter] : Display Help\n"));
			_tprintf(TEXT("S[Enter] : Start Continuous Soft Trigger\n"));
			_tprintf(TEXT("O[Enter] : Single Soft Trigger\n"));
			_tprintf(TEXT("2[Enter] : Soft Sub Trigger\n"));
			_tprintf(TEXT("R[Enter] : Read Out\n"));
			_tprintf(TEXT("W[Enter] : Set White Balance Mode -> ONESHOT\n"));
			_tprintf(TEXT("X[Enter] : Get White Balance Gain\n"));
			break;
		case(TEXT('S')):
			//-----------------------------------------------------------------
			//Soft Trigger
			//-----------------------------------------------------------------
			g_bContinuousSoftTriggerFg = TRUE;

#ifdef DISPLAY_CALLBACK_INFO
			QueryPerformanceCounter(&g_timeSoftTriggerOrTransferEnd);
#endif //DISPLAY_CALLBACK_INFO
			if(!StTrg_SoftTrigger(hCamera))
			{
				_tprintf(TEXT("Continuous Soft Trigger Failed.\n"));
				return(-1);
			}
			break;
		case(TEXT('O')):
			//-----------------------------------------------------------------
			//Soft Trigger
			//-----------------------------------------------------------------
			g_bContinuousSoftTriggerFg = FALSE;
#ifdef DISPLAY_CALLBACK_INFO
			QueryPerformanceCounter(&g_timeSoftTriggerOrTransferEnd);
#endif //DISPLAY_CALLBACK_INFO
			if(!StTrg_SoftTrigger(hCamera))
			{
				_tprintf(TEXT("Single Soft Trigger Failed.\n"));
				return(-1);
			}
			break;
		case(TEXT('2')):
			if(!StTrg_SoftSubTrigger(hCamera))
			{
				_tprintf(TEXT("Soft Sub Trigger Failed.\n"));
				return(-1);
			}
			break;
		case(TEXT('R')):
			//-----------------------------------------------------------------
			//Read Out
			//-----------------------------------------------------------------
			if(!StTrg_TriggerReadOut(hCamera))
			{
				_tprintf(TEXT("Read Out Failed.\n"));
				return(-1);
			}
			break;
		case(TEXT('W')):
			if(!StTrg_SetWhiteBalanceMode(hCamera, STCAM_WB_ONESHOT))
			{
				_tprintf(TEXT("Set White Balance Mode Failed.\n"));
				return(-1);
			}
			_tprintf(TEXT("White Balance Mode:ONESHOT(0x%02X)\n"), STCAM_WB_ONESHOT);
			break;
		case(TEXT('X')):
			if(!StTrg_GetWhiteBalanceGain(hCamera, &pwWBGain[0], &pwWBGain[1], &pwWBGain[2], &pwWBGain[3]))
			{
				_tprintf(TEXT("Get White Balance Gain Failed.\n"));
				return(-1);
			}
			for(i = 0; i < 4; i++)
			{
				_tprintf(TEXT("WB %s : %u - x %0.2f\n"), pWBGainName[i], pwWBGain[i], pwWBGain[i] / 128.0);
			}
			break;

		case(TEXT('P')):
				if(long_exposure_time == 0)//input your exposure
				{
					printf("Input exposure time in miliseconds: ");
					scanf("%d", &long_exposure_time);
					printf("\n");
				}

					g_bSaveFileFg = TRUE;//capture the next frame
	
					g_bContinuousSoftTriggerFg = FALSE;
					#ifdef DISPLAY_CALLBACK_INFO
						QueryPerformanceCounter(&g_timeSoftTriggerOrTransferEnd);
					#endif
					if(!StTrg_SoftTrigger(hCamera))
					{
						_tprintf(TEXT("Single Soft Trigger Failed.\n"));
						return(-1);
					}
						
					_sleep(long_exposure_time);//delay that long time to exposure
	
					if(!StTrg_SoftSubTrigger(hCamera))
					{
						_tprintf(TEXT("Soft Sub Trigger Failed.\n"));
						return(-1);
					}
				break;

		}
	}	//while(!g_bExitMenu)

	
	//-------------------------------------------------------------------------
	//Stop Transfer
	//-------------------------------------------------------------------------
	if(!StTrg_StopTransfer(hCamera))
	{
		_tprintf(TEXT("Can't Stop.\n"));
		return(-1);
	}


	//-------------------------------------------------------------------------
	//Close
	//-------------------------------------------------------------------------
	StTrg_Close(hCamera);
	
	_tprintf(TEXT("End(Press Enter)\n"));
	getchar();
	getchar();

	return 0;
}

