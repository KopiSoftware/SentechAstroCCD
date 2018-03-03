#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "include/StTrgApi.h"
#include "SetCameraFunction.h"


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	GetCameraVersion(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== GetCameraVersion ======\n"));

	WORD	wUSBVendorID = 0;
	WORD	wUSBProductID = 0;
	WORD	wFPGAVersion = 0;
	WORD	wFirmVersion = 0;
	
	do{
		bReval = StTrg_GetCameraVersion(hCamera, &wUSBVendorID, &wUSBProductID, &wFPGAVersion, &wFirmVersion);
		if(!bReval) break;

		TCHAR szProductName[MAX_PATH];
		bReval = StTrg_GetProductName(hCamera, szProductName, sizeof(szProductName));
		if(!bReval) break;

		_tprintf(TEXT("USB Vendor ID : 0x%04X - Sensor Technology\n"), wUSBVendorID);
		_tprintf(TEXT("USB Product ID : 0x%04X - %s\n"), wUSBProductID, szProductName);
		_tprintf(TEXT("FPGA Version : 0x%04X\n"), wFPGAVersion);
		_tprintf(TEXT("Firmware Version : 0x%04X\n"), wFirmVersion);
	}while(FALSE);
	if(!bReval)
	{
		_tprintf(TEXT("Get Camera Version Failed.\n"));
	}
	return(bReval);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	GetColorArray(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== GetColorArray ======\n"));

	WORD	wColorArray = 0;
	bReval = StTrg_GetColorArray(hCamera, &wColorArray);

	if(bReval)
	{
		LPCTSTR	szColorArray = NULL;
		switch(wColorArray)
		{
		case(STCAM_COLOR_ARRAY_MONO):	szColorArray = TEXT("MONO"); break;
		case(STCAM_COLOR_ARRAY_RGGB):	szColorArray = TEXT("RGGB"); break;
		case(STCAM_COLOR_ARRAY_GRBG):	szColorArray = TEXT("GRBG"); break;
		case(STCAM_COLOR_ARRAY_GBRG):	szColorArray = TEXT("GBRG"); break;
		case(STCAM_COLOR_ARRAY_BGGR):	szColorArray = TEXT("BGGR"); break;
		default:						szColorArray = TEXT("UNKNOWN"); break;
		}
		_tprintf(TEXT("Color Array : 0x%04X - %s\n"), wColorArray, szColorArray);

	}
	else
	{
		_tprintf(TEXT("Get Color Array Failed.\n"));
	}
	return(bReval);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	SetCameraID(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetCameraID ======\n"));

	DWORD	dwCameraNo = 0;
	TCHAR	szCameraID[250];

	do{
		/*
		_tcscpy(szCameraID, TEXT("NewName"));
		bReval = StTrg_WriteCameraUserID(hCamera, dwCameraNo, szCameraID, 250);
		if(!bReval)
		{
			_tprintf(TEXT("Write Camera User ID Failed.\n"));
			break;
		}
		*/
		
		bReval = StTrg_ReadCameraUserID(hCamera, &dwCameraNo, szCameraID, 250);
		if(!bReval)
		{
			_tprintf(TEXT("Read Camera User ID Failed.\n"));
			break;
		}
		_tprintf(TEXT("Camera ID(No) : %u\n"), dwCameraNo);
		_tprintf(TEXT("Camera ID(String) : %s\n"), szCameraID);
	}while(0);
	return(bReval);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	SetScanMode(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetScanMode ======\n"));

	WORD	wScanMode = STCAM_SCAN_MODE_NORMAL;
		//STCAM_SCAN_MODE_NORMAL,  STCAM_SCAN_MODE_PARTIAL_1, 
		//STCAM_SCAN_MODE_PARTIAL_2, STCAM_SCAN_MODE_PARTIAL_4,STCAM_SCAN_MODE_VARIABLE_PARTIAL
		//STCAM_SCAN_MODE_BINNING, STCAM_SCAN_MODE_BINNING_PARTIAL_1, 
		//STCAM_SCAN_MODE_BINNING_PARTIAL_2, STCAM_SCAN_MODE_BINNING_PARTIAL_4, STCAM_SCAN_MODE_BINNING_VARIABLE_PARTIAL
		//STCAM_SCAN_MODE_AOI
	DWORD dwOffsetX = 0;
	DWORD dwOffsetY = 0;
	DWORD dwWidth = 0;
	DWORD dwHeight = 0;
	
	do{
		bReval = StTrg_SetScanMode(hCamera, wScanMode, dwOffsetX, dwOffsetY, dwWidth, dwHeight);
		if(!bReval)
		{
			_tprintf(TEXT("Set Scan Mode Failed.\n"));
			break;
		}

		bReval = StTrg_GetScanMode(hCamera, &wScanMode, &dwOffsetX, &dwOffsetY, &dwWidth, &dwHeight);
		if(!bReval)
		{
			_tprintf(TEXT("Get Scan Mode Failed.\n"));
			break;
		}
		LPCTSTR	szScanMode = NULL;
		switch(wScanMode)
		{
			case(STCAM_SCAN_MODE_NORMAL):					szScanMode = TEXT("NORMAL"); break;
			case(STCAM_SCAN_MODE_PARTIAL_1):				szScanMode = TEXT("PARTIAL_1"); break;
			case(STCAM_SCAN_MODE_PARTIAL_2):				szScanMode = TEXT("PARTIAL_2"); break;
			case(STCAM_SCAN_MODE_PARTIAL_4):				szScanMode = TEXT("PARTIAL_4"); break;
			case(STCAM_SCAN_MODE_VARIABLE_PARTIAL):			szScanMode = TEXT("VARIABLE_PARTIAL"); break;
			case(STCAM_SCAN_MODE_BINNING):					szScanMode = TEXT("BINNING"); break;
			case(STCAM_SCAN_MODE_BINNING_PARTIAL_1):		szScanMode = TEXT("BINNING_PARTIAL_1"); break;
			case(STCAM_SCAN_MODE_BINNING_PARTIAL_2):		szScanMode = TEXT("BINNING_PARTIAL_2"); break;
			case(STCAM_SCAN_MODE_BINNING_PARTIAL_4):		szScanMode = TEXT("BINNING_PARTIAL_4"); break;
			case(STCAM_SCAN_MODE_BINNING_VARIABLE_PARTIAL):	szScanMode = TEXT("BINNING_VARIABLE_PARTIAL"); break;
			case(STCAM_SCAN_MODE_AOI):						szScanMode = TEXT("AOI"); break;
			default:										szScanMode = TEXT("UNKNOWN"); break;
		}
		_tprintf(TEXT("Scan Mode : 0x%04X - %s\n"), wScanMode, szScanMode);
		_tprintf(TEXT("OffsetX : %u / OffsetY : %u\n"), dwOffsetX, dwOffsetY);
		_tprintf(TEXT("Width : %u / Height : %u\n"), dwWidth, dwHeight);
	}while(0);
	return(bReval);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	SetClockMode(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetClockMode ======\n"));

	DWORD	dwClockMode = STCAM_CLOCK_MODE_NORMAL;	//STCAM_CLOCK_MODE_NORMAL,STCAM_CLOCK_MODE_DIV_2,STCAM_CLOCK_MODE_DIV_4
	DWORD	dwCameraClock = 0;

	do{
		bReval = StTrg_SetClock(hCamera, dwClockMode, dwCameraClock);
		if(!bReval)
		{
			_tprintf(TEXT("Set Clock Failed.\n"));
			break;
		}
		
		bReval = StTrg_GetClock(hCamera, &dwClockMode, &dwCameraClock);
		if(!bReval)
		{
			_tprintf(TEXT("Get Clock Failed.\n"));
			break;
		}

		LPCTSTR	szClockMode = NULL;
		switch(dwClockMode)
		{
			case(STCAM_CLOCK_MODE_NORMAL):	szClockMode = TEXT("NORMAL"); break;
			case(STCAM_CLOCK_MODE_DIV_2):	szClockMode = TEXT("DIV_2"); break;
			case(STCAM_CLOCK_MODE_DIV_4):	szClockMode = TEXT("DIV_4"); break;
			default:						szClockMode = TEXT("UNKNOWN"); break;
		}
		_tprintf(TEXT("Clock Mode : 0x%04X - %s\n"), dwClockMode, szClockMode);
		_tprintf(TEXT("Camera Clock : %u Hz\n"), dwCameraClock);
	}while(0);
	return(bReval);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	SetExposureTime(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetExposureTime ======\n"));

	do{
		DWORD	pdwExposureClock[] = {0, 0, 0};

		bReval = StTrg_SetExposureClock(hCamera, pdwExposureClock[0]);
		if(!bReval)
		{
			_tprintf(TEXT("Set Exposure Clock Failed.\n"));
			break;
		}
		bReval = StTrg_GetExposureClock(hCamera, &pdwExposureClock[0]);
		if(!bReval)
		{
			_tprintf(TEXT("Get Exposure Clock Failed.\n"));
			break;
		}

		bReval = StTrg_GetMaxShortExposureClock(hCamera, &pdwExposureClock[1]);
		if(!bReval)
		{
			_tprintf(TEXT("Get Max Short Exposure Clock Failed.\n"));
			break;
		}

		bReval = StTrg_GetMaxLongExposureClock(hCamera, &pdwExposureClock[2]);
		if(!bReval)
		{
			_tprintf(TEXT("Get Max Long Exposure Clock Failed.\n"));
			break;
		}

		LPCTSTR pszTitle[] = {TEXT("Exposure Time"), TEXT("Max Exposure Time(Normal)"), TEXT("Max Exposure Time(Long Time Exposure)")};
		for(int i = 0; i < 3; i++)
		{
			float fExpTime = 0;

			bReval = StTrg_GetExposureTimeFromClock(hCamera, pdwExposureClock[i], &fExpTime);
			if(!bReval)
			{
				_tprintf(TEXT("Get Exposure Time From Clock Failed.\n"));
				break;
			}
			_tprintf(TEXT("%s : %u clocks - %0.3f ms\n"), pszTitle[i], pdwExposureClock[i], 1000.0 * fExpTime);
		}
	}while(0);
	return(bReval);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	SetGain(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetGain ======\n"));

	WORD	wGain = 85;
	WORD	wDigitalGain = 128;
	do{
		BOOL bHasDigitalGainFunction = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_DIGITAL_GAIN, &bHasDigitalGainFunction);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		/*
		bReval = StTrg_SetGain(hCamera, wGain);
		if(!bReval)
		{
			_tprintf(TEXT("Set Gain Failed.\n"));
			break;
		}
		if(bHasDigitalGainFunction)
		{
			bReval = StTrg_SetDigitalGain(hCamera, wDigitalGain);
			if(!bReval)
			{
				_tprintf(TEXT("Set Digital Gain Failed.\n"));
				break;
			}
		}
		*/
		bReval = StTrg_GetGain(hCamera, &wGain);
		if(!bReval)
		{
			_tprintf(TEXT("Get Gain Failed.\n"));
			break;
		}
		_tprintf(TEXT("CDS Gain : %u \n"), wGain);

		if(bHasDigitalGainFunction)
		{
			bReval = StTrg_GetDigitalGain(hCamera, &wDigitalGain);
			if(!bReval)
			{
				_tprintf(TEXT("Get Digital Gain Failed.\n"));
				break;
			}
			_tprintf(TEXT("Digital Gain : %u \n"), wDigitalGain);
		}
		else
		{
			_tprintf(TEXT("Digital Gain : Disable \n"));
		}
	}while(0);
	return(bReval);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	SetTriggerMode(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetTriggerMode ======\n"));

	BOOL bHasTriggerFunction = FALSE;
	bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_TRIGGER, &bHasTriggerFunction);
	if(!bReval)
	{
		_tprintf(TEXT("Has Function Failed.\n"));
		return(FALSE);
	}
	if(!bHasTriggerFunction)
	{
		_tprintf(TEXT("Trigger Function : Disable\n"));
		return(TRUE);
	}


	TCHAR	szInput[2] = {0, 0};

	DWORD dwTriggerMode = 0;
		//STCAM_TRIGGER_MODE_TYPE_FREE_RUN, STCAM_TRIGGER_MODE_TYPE_TRIGGER, STCAM_TRIGGER_MODE_TYPE_TRIGGER_RO
		//STCAM_TRIGGER_MODE_EXPTIME_EDGE_PRESET, STCAM_TRIGGER_MODE_EXPTIME_PULSE_WIDTH, STCAM_TRIGGER_MODE_EXPTIME_START_STOP
		//STCAM_TRIGGER_MODE_SOURCE_NONE, STCAM_TRIGGER_MODE_SOURCE_SOFTWARE, STCAM_TRIGGER_MODE_SOURCE_HARDWARE		
		//STCAM_TRIGGER_MODE_READOUT_SOFTWARE, STCAM_TRIGGER_MODE_READOUT_HARDWARE		
		//STCAM_TRIGGER_MODE_EXPEND_DISABLE, STCAM_TRIGGER_MODE_EXPEND_ENABLE
		//STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_OFF, STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_ON
		//STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_OFF, STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_ON
		//STCAM_TRIGGER_MODE_CAMERA_MEMORY_TYPE_B, STCAM_TRIGGER_MODE_CAMERA_MEMORY_TYPE_A, STCAM_TRIGGER_MODE_CAMERA_MEMORY_OFF
		//STCAM_TRIGGER_MODE_TRIGGER_MASK_OFF, STCAM_TRIGGER_MODE_TRIGGER_MASK_ON
		//STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_ERS, STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_GRR
	do{
		_tprintf(TEXT("Input Trigger Mode(F:Free Run, S:Soft Trigger(Edge Preset), 2:Soft Trigger(Start/Stop), H:Hard Trigger) : "));
		szInput[0] = _gettchar();
		_tcsupr(szInput);
		switch(szInput[0])
		{
			case(TEXT('f')):
			case(TEXT('F')):
				dwTriggerMode = STCAM_TRIGGER_MODE_TYPE_FREE_RUN | STCAM_TRIGGER_MODE_EXPEND_ENABLE;
				break;
			case(TEXT('s')):
			case(TEXT('S')):
				dwTriggerMode = STCAM_TRIGGER_MODE_TYPE_TRIGGER | STCAM_TRIGGER_MODE_SOURCE_SOFTWARE | STCAM_TRIGGER_MODE_EXPEND_ENABLE;
				break;
			case(TEXT('2')):
				dwTriggerMode = STCAM_TRIGGER_MODE_TYPE_TRIGGER | STCAM_TRIGGER_MODE_SOURCE_SOFTWARE | STCAM_TRIGGER_MODE_EXPEND_ENABLE | STCAM_TRIGGER_MODE_EXPTIME_START_STOP;
				break;
			case(TEXT('h')):
			case(TEXT('H')):
				dwTriggerMode = STCAM_TRIGGER_MODE_TYPE_TRIGGER | STCAM_TRIGGER_MODE_SOURCE_HARDWARE | STCAM_TRIGGER_MODE_EXPEND_ENABLE;
				break;
			default:
				szInput[0] = 0;
				break;
		}

		if(szInput[0])
			break;
	}while(1);

	do{
		bReval = StTrg_SetTriggerMode(hCamera,dwTriggerMode);
		if(!bReval)
		{
			_tprintf(TEXT("Set Trigger Mode Failed.\n"));
			break;
		}
		bReval = StTrg_GetTriggerMode(hCamera,&dwTriggerMode);
		if(!bReval)
		{
			_tprintf(TEXT("Get Trigger Mode Failed.\n"));
			break;
		}
		
		BOOL	bHasMemoryFunction = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_MEMORY, &bHasMemoryFunction);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		else if(bHasMemoryFunction)
		{
			BOOL	bDisableMemoryTypeSelection = FALSE;
			bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_DISABLE_MEMORY_TYPE_SELECTION, &bDisableMemoryTypeSelection);
			if(bDisableMemoryTypeSelection)
			{
				bHasMemoryFunction = FALSE;
			}
		}

		BOOL	bDisabledReadOut = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_DISABLED_READOUT, &bDisabledReadOut);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		BOOL	bDisabledWaitHD = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_DISABLE_EXPOSURE_START_WAIT_HD, &bDisabledWaitHD);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		BOOL	bDisabledWaitReadOut = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_DISABLE_EXPOSURE_START_WAIT_READ_OUT, &bDisabledWaitReadOut);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		BOOL	bHasTrigerMask = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_TRIGGER_MASK, &bHasTrigerMask);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}

		BOOL	bHasCMOSResetType = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_CMOS_RESET_TYPE_ERS_GRR, &bHasCMOSResetType);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}

		LPCTSTR	szTriggerMode = NULL;
		switch(STCAM_TRIGGER_MODE_TYPE_MASK & dwTriggerMode)
		{
		case(STCAM_TRIGGER_MODE_TYPE_FREE_RUN):		szTriggerMode = TEXT("FREE_RUN");	break;
		case(STCAM_TRIGGER_MODE_TYPE_TRIGGER):		szTriggerMode = TEXT("TRIGGER");	break;
		case(STCAM_TRIGGER_MODE_TYPE_TRIGGER_RO):	szTriggerMode = TEXT("TRIGGER_RO");	break;
		default:									szTriggerMode = TEXT("UNKNOWN");	break;
		}
		_tprintf(TEXT("Trigger Mode Type : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_TYPE_MASK & dwTriggerMode, szTriggerMode);

		switch(STCAM_TRIGGER_MODE_EXPTIME_MASK & dwTriggerMode)
		{
		case(STCAM_TRIGGER_MODE_EXPTIME_EDGE_PRESET):	szTriggerMode = TEXT("EDGE_PRESET");	break;
		case(STCAM_TRIGGER_MODE_EXPTIME_PULSE_WIDTH):	szTriggerMode = TEXT("PULSE_WIDTH");	break;
		case(STCAM_TRIGGER_MODE_EXPTIME_START_STOP):	szTriggerMode = TEXT("START_STOP");		break;
		default:										szTriggerMode = TEXT("UNKNOWN");	break;
		}
		_tprintf(TEXT("Exposure Time : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_EXPTIME_MASK & dwTriggerMode, szTriggerMode);

		switch(STCAM_TRIGGER_MODE_SOURCE_MASK & dwTriggerMode)
		{
		case(STCAM_TRIGGER_MODE_SOURCE_NONE):		szTriggerMode = TEXT("NONE");	break;
		case(STCAM_TRIGGER_MODE_SOURCE_SOFTWARE):	szTriggerMode = TEXT("SOFTWARE");	break;
		case(STCAM_TRIGGER_MODE_SOURCE_HARDWARE):	szTriggerMode = TEXT("HARDWARE");	break;
		default:									szTriggerMode = TEXT("UNKNOWN");	break;
		}
		_tprintf(TEXT("Trigger Source : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_SOURCE_MASK & dwTriggerMode, szTriggerMode);

		if(!bDisabledReadOut)
		{
			switch(STCAM_TRIGGER_MODE_READOUT_SOURCE_MASK & dwTriggerMode)
			{
			case(STCAM_TRIGGER_MODE_READOUT_SOFTWARE):	szTriggerMode = TEXT("SOFTWARE");	break;
			case(STCAM_TRIGGER_MODE_READOUT_HARDWARE):	szTriggerMode = TEXT("HARDWARE");	break;
			default:									szTriggerMode = TEXT("UNKNOWN");	break;
			}
			_tprintf(TEXT("Readout Source : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_READOUT_SOURCE_MASK & dwTriggerMode, szTriggerMode);
		}
		switch(STCAM_TRIGGER_MODE_EXPEND_MASK & dwTriggerMode)
		{
		case(STCAM_TRIGGER_MODE_EXPEND_DISABLE):	szTriggerMode = TEXT("DISABLE");	break;
		case(STCAM_TRIGGER_MODE_EXPEND_ENABLE):		szTriggerMode = TEXT("ENABLE");	break;
		default:									szTriggerMode = TEXT("UNKNOWN");	break;
		}
		_tprintf(TEXT("Exposure End : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_EXPEND_MASK & dwTriggerMode, szTriggerMode);

		if(!bDisabledWaitHD)
		{
			switch(STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_MASK & dwTriggerMode)
			{
			case(STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_OFF):	szTriggerMode = TEXT("IMMEDIATE");	break;
			case(STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_ON):	szTriggerMode = TEXT("Wait");	break;
			default:										szTriggerMode = TEXT("UNKNOWN");	break;
			}
			_tprintf(TEXT("Exposure Wait HD : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_MASK & dwTriggerMode, szTriggerMode);
		}

		if(!bDisabledWaitReadOut)
		{
			switch(STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_MASK & dwTriggerMode)
			{
			case(STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_OFF):	szTriggerMode = TEXT("IMMEDIATE");	break;
			case(STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_ON):	szTriggerMode = TEXT("Wait");	break;
			default:											szTriggerMode = TEXT("UNKNOWN");	break;
			}
			_tprintf(TEXT("Exposure Wait Readout : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_MASK & dwTriggerMode, szTriggerMode);
		}
		if(bHasMemoryFunction)
		{
			switch(STCAM_TRIGGER_MODE_CAMERA_MEMORY_MASK & dwTriggerMode)
			{
			case(STCAM_TRIGGER_MODE_CAMERA_MEMORY_TYPE_B):	szTriggerMode = TEXT("Type_B");	break;
			case(STCAM_TRIGGER_MODE_CAMERA_MEMORY_TYPE_A):	szTriggerMode = TEXT("Type_A");	break;
			case(STCAM_TRIGGER_MODE_CAMERA_MEMORY_OFF):		szTriggerMode = TEXT("OFF");	break;
			default:										szTriggerMode = TEXT("UNKNOWN");	break;
			}
			_tprintf(TEXT("Camera Memory : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_CAMERA_MEMORY_MASK & dwTriggerMode, szTriggerMode);
		}

		if(bHasTrigerMask)
		{
			switch(STCAM_TRIGGER_MODE_TRIGGER_MASK_MASK & dwTriggerMode)
			{
			case(STCAM_TRIGGER_MODE_TRIGGER_MASK_OFF):	szTriggerMode = TEXT("OFF");	break;
			case(STCAM_TRIGGER_MODE_TRIGGER_MASK_ON):	szTriggerMode = TEXT("ON");	break;
			default:										szTriggerMode = TEXT("UNKNOWN");	break;
			}
			_tprintf(TEXT("Trigger Mask : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_TRIGGER_MASK_MASK & dwTriggerMode, szTriggerMode);
		}


		if(bHasCMOSResetType)
		{
			switch(STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_MASK & dwTriggerMode)
			{
			case(STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_ERS):	szTriggerMode = TEXT("Electronic Rolling Shutter");	break;
			case(STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_GRR):	szTriggerMode = TEXT("Global Reset Release");	break;
			default:										szTriggerMode = TEXT("UNKNOWN");	break;
			}
			_tprintf(TEXT("CMOS Reset Type : 0x%08X - %s\n"), STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_MASK & dwTriggerMode, szTriggerMode);
		}

	}while(0);
	return(bReval);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	SetIO(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetIO ======\n"));

	DWORD	dwIODirection = 0;
	DWORD	dwIOStatus = 0;
	DWORD	dwPolarity = 0;
	DWORD	dwIOMode[4] = {0};
	DWORD	dwDipSWStatus = 0;
	int	i;
	do{
		BOOL bHasIOFunction = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_IO, &bHasIOFunction);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		if(!bHasIOFunction)
		{
			_tprintf(TEXT("IO Function : Disable\n"));
			break;
		}


		/*
		BOOL bHasSetIODirectionFunction = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_IO_CHANGE_DIRECTION, &bHasSetIODirectionFunction);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}

		if(bHasSetIODirectionFunction)
		{
			bReval = StTrg_SetIOPinDirection(hCamera, dwIODirection);
			if(!bReval)
			{
				_tprintf(TEXT("Set IO Pin Direction Failed.\n"));
				break;
			}
		}

		for(i=0;i<4;i++)
		{
			bReval = StTrg_SetIOPinMode(hCamera, i, dwIOMode[i]);
			if(!bReval)
			{
				_tprintf(TEXT("Set IP Pin Mode Failed.\n"));
				break;
			}
		}
		if(!bReval)	break;

		bReval = StTrg_SetIOPinPolarity(hCamera, dwPolarity);
		if(!bReval)
		{
			_tprintf(TEXT("Set IO Pin Polarity Failed.\n"));
			break;
		}

		bReval = StTrg_SetIOPinStatus(hCamera, dwIOStatus);
		if(!bReval)
		{
			_tprintf(TEXT("Set IO Pin Status Failed.\n"));
			break;
		}
		*/
		bReval = StTrg_GetIOPinDirection(hCamera, &dwIODirection);
		if(!bReval)
		{
			_tprintf(TEXT("Get IO Pin Direction Failed.\n"));
			break;
		}
		bReval = StTrg_GetIOPinPolarity(hCamera, &dwPolarity);
		if(!bReval)
		{
			_tprintf(TEXT("Get IO Pin Polarity Failed.\n"));
			break;
		}
		for(i=0;i<4;i++)
		{
			bReval = StTrg_GetIOPinMode(hCamera, i, &dwIOMode[i]);
			if(!bReval)
			{
				_tprintf(TEXT("Get IP Pin Mode Failed.\n"));
				break;
			}
		}
		if(!bReval)	break;

		bReval = StTrg_GetIOPinStatus(hCamera, &dwIOStatus);
		if(!bReval)
		{
			_tprintf(TEXT("Get IO Pin Status Failed.\n"));
			break;
		}

		
		BOOL bDisableDipSWFunction = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_DISABLE_DIP_SW, &bDisableDipSWFunction);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		if(!bDisableDipSWFunction)
		{
			bReval = StTrg_GetSwStatus(hCamera, &dwDipSWStatus);
			if(!bReval)
			{
				_tprintf(TEXT("Get Sw Status Failed.\n"));
				break;
			}
		}



		for(i=0;i<4;i++)
		{
			DWORD	ioDir = (dwIODirection >> i) & 0x0001;
			DWORD	ioPolarity = (dwPolarity >> i) & 0x0001;
			DWORD	ioStatus = (dwIOStatus >> i) & 0x0001;
			_tprintf(TEXT("IO%d Direction : %u - %s, Mode : 0x%04X, Polarity : %u - %s, Status : %u - %s\n"), 
				i,
				ioDir, 
				ioDir ? TEXT("OUTPUT") : TEXT("INPUT"),
				dwIOMode[i],
				ioPolarity, 
				(ioPolarity) ? TEXT("Positive") : TEXT("Negative"),
				ioStatus,
				(ioStatus) ? TEXT("HIGH") : TEXT("LOW")
				);
		}
		if(!bDisableDipSWFunction)
		{
			for(i=0;i<4;i++)
			{
				DWORD	swStatus = (dwDipSWStatus >> i) & 0x0001;
				_tprintf(TEXT("DIP SW%u : %u - %s\n"),
					i + 1,
					swStatus,
					(swStatus) ? TEXT("ON") : TEXT("OFF")
					);
			}
		}
	}while(0);
	return(bReval);

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	SetLED(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetLED ======\n"));

	DWORD	dwLEDStatus = STCAM_LED_GREEN_ON | STCAM_LED_RED_ON;
	do{
		BOOL bHasLEDFunction = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_LED, &bHasLEDFunction);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		if(!bHasLEDFunction)
		{
			_tprintf(TEXT("LED Function : Disable\n"));
			break;
		}

		bReval = StTrg_SetLEDStatus(hCamera, dwLEDStatus);
		if(!bReval)
		{
			_tprintf(TEXT("Set LED Function Failed.\n"));
			break;
		}
		bReval = StTrg_GetLEDStatus(hCamera, &dwLEDStatus);
		if(!bReval)
		{
			_tprintf(TEXT("Get LED Function Failed.\n"));
			break;
		}
		_tprintf(TEXT("RED LED : 0x%08X - %s\n"), 
			dwLEDStatus & STCAM_LED_RED_ON,
			(dwLEDStatus & STCAM_LED_RED_ON) ? TEXT("ON"):TEXT("OFF"));
		
		_tprintf(TEXT("GREEN LED : 0x%08X - %s\n"), 
			dwLEDStatus & STCAM_LED_GREEN_ON,
			(dwLEDStatus & STCAM_LED_GREEN_ON) ? TEXT("ON"):TEXT("OFF"));
	}while(0);
	return(bReval);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL	SetTriggerTimming(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetTriggerTimming ======\n"));

	DWORD	pdwTriggerTimingType[] = {
				STCAM_TRIGGER_TIMING_EXPOSURE_DELAY,
				STCAM_TRIGGER_TIMING_STROBE_START_DELAY,
				STCAM_TRIGGER_TIMING_STROBE_END_DELAY,
				STCAM_TRIGGER_TIMING_OUTPUT_PULSE_DELAY,
				STCAM_TRIGGER_TIMING_OUTPUT_PULSE_DURATION,
				STCAM_TRIGGER_TIMING_READOUT_DELAY};
	DWORD	pdwTriggerTimingValue[] = {0, 0, 0, 0, 0, 0};
	LPCTSTR	pszTimingTypeName[] = {
				TEXT("Exposure Delay"),
				TEXT("Strobe Start Delay"),
				TEXT("Strobe End Delay"),
				TEXT("Trigger Pulse Delay"),
				TEXT("Trigger Pulse Duration"),
				TEXT("Readout Delay")};
	int nCount = 6;
	do{
		BOOL	bDisabledReadOut = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_DISABLED_READOUT, &bDisabledReadOut);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		if(bDisabledReadOut)	nCount = 5;

		BOOL	bIsIOUnitUS = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_IO_UNIT_US, &bIsIOUnitUS);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}

		BOOL bHasTriggerFunction = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_TRIGGER, &bHasTriggerFunction);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		if(!bHasTriggerFunction)
		{
			_tprintf(TEXT("Trigger Function : Disable\n"));
			break;
		}

		DWORD	dwClockMode = 0;
		DWORD	dwCameraClock = 0;
		bReval = StTrg_GetClock(hCamera, &dwClockMode, &dwCameraClock);
		if(!bReval)
		{
			_tprintf(TEXT("Get Clock Failed.\n"));
		BOOL bHasTriggerFunction = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_TRIGGER, &bHasTriggerFunction);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		if(!bHasTriggerFunction)
		{
			_tprintf(TEXT("Trigger Function : Disable\n"));
			break;
		}
			break;
		}

		WORD	wTotalLine = 0;;
		WORD	wClockPerLine = 0;;
		bReval = StTrg_GetFrameClock(hCamera, &wTotalLine, &wClockPerLine);
		if(!bReval)
		{
			_tprintf(TEXT("Get Frame Clock Failed.\n"));
			break;
		}

		for(int i = 0; i < nCount; i++)
		{
			/*
			bReval = StTrg_SetTriggerTiming(hCamera, pdwTriggerTimingType[i], pdwTriggerTimingValue[i]);
			if(!bReval)
			{
				_tprintf(TEXT("Set Trigger Timing Failed.\n"));
				break;
			}
			*/
			bReval = StTrg_GetTriggerTiming(hCamera, pdwTriggerTimingType[i], &pdwTriggerTimingValue[i]);
			if(!bReval)
			{
				_tprintf(TEXT("Get Trigger Timing Failed.\n"));
				break;
			}

			if(pdwTriggerTimingType[i] != STCAM_TRIGGER_TIMING_READOUT_DELAY)
			{
				if(bIsIOUnitUS = FALSE)
				{
					_tprintf(TEXT("Trigger Timing[%s] : %u us\n"), 
									pszTimingTypeName[i], 
									pdwTriggerTimingValue[i]);
				}
				else
				{
					_tprintf(TEXT("Trigger Timing[%s] : %u Clocks - %0.3f us\n"), 
									pszTimingTypeName[i], 
									pdwTriggerTimingValue[i], 
									pdwTriggerTimingValue[i] * 1000000.0 /(double)dwCameraClock);
				}
			}
			else
			{
				_tprintf(TEXT("Trigger Timing[%s] : %u Lines - %0.3f ms\n"), 
									pszTimingTypeName[i], 
									pdwTriggerTimingValue[i], 
									pdwTriggerTimingValue[i] * wClockPerLine/(double)dwCameraClock * 1000.0 );
			}
		}
	}while(0);
	return(bReval);
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
BOOL	ResetFrameCounter(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== ResetFrameCounter ======\n"));

	do{
		BOOL bHasResetFrameCounterFunction = FALSE;
		bReval = StTrg_HasFunction(hCamera, STCAM_CAMERA_FUNCTION_RESET_FRAME_COUNTER, &bHasResetFrameCounterFunction);
		if(!bReval)
		{
			_tprintf(TEXT("Has Function Failed.\n"));
			break;
		}
		if(!bHasResetFrameCounterFunction)
		{
			_tprintf(TEXT("Reset Frame Counter Function : Disable\n"));
			break;
		}
		bReval =StTrg_ResetCounter(hCamera) ;
		if(!bReval)
		{
			_tprintf(TEXT("Reset Counter Failed.\n"));
		}
	}while(0);
	return(bReval);
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
BOOL	SetWhiteBalance(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetWhiteBalance ======\n"));

	WORD	pwWBGain[] = {128, 128, 128, 128};
	BYTE	byteWBMode = STCAM_WB_MANUAL;
		//STCAM_WB_OFF, STCAM_WB_MANUAL, STCAM_WB_FULLAUTO, STCAM_WB_ONESHOT
	do{
		WORD	wColorArray = STCAM_COLOR_ARRAY_MONO;
		bReval = StTrg_GetColorArray(hCamera, &wColorArray);
		if(!bReval)
		{
			_tprintf(TEXT("Get Color Array Failed.\n"));
			break;
		}
		if(STCAM_COLOR_ARRAY_MONO == wColorArray)
		{
			_tprintf(TEXT("Black And White Camera\n"));
			break;
		}
		/*
		bReval = StTrg_SetWhiteBalanceMode(hCamera, byteWBMode);
		if(!bReval)
		{
			_tprintf(TEXT("Set White Balance Mode Failed.\n"));
			break;
		}
		bReval = StTrg_SetWhiteBalanceGain(hCamera, pwWBGain[0], pwWBGain[1], pwWBGain[2], pwWBGain[3]);
		if(!bReval)
		{
			_tprintf(TEXT("Set White Balance Gain Failed.\n"));
			break;
		}
		*/
		bReval = StTrg_GetWhiteBalanceMode(hCamera, &byteWBMode);
		if(!bReval)
		{
			_tprintf(TEXT("Get White Balance Mode Failed.\n"));
			break;
		}
		bReval = StTrg_GetWhiteBalanceGain(hCamera, &pwWBGain[0], &pwWBGain[1], &pwWBGain[2], &pwWBGain[3]);
		if(!bReval)
		{
			_tprintf(TEXT("Get White Balance Gain Failed.\n"));
			break;
		}
		LPCTSTR szWBMode = NULL;
		switch(byteWBMode)
		{
		case(STCAM_WB_OFF):			szWBMode = TEXT("OFF");	break;
		case(STCAM_WB_MANUAL):		szWBMode = TEXT("MANUAL");	break;
		case(STCAM_WB_FULLAUTO):	szWBMode = TEXT("FULLAUTO");	break;
		case(STCAM_WB_ONESHOT):		szWBMode = TEXT("ONESHOT");	break;
		default:					szWBMode = TEXT("UNKNOWN");	break;
		}
		_tprintf(TEXT("White Balance Mode : 0x%02X - %s\n"), byteWBMode, szWBMode);
		LPCTSTR pWBGainName[] = {TEXT("GainR"), TEXT("GainGr"), TEXT("GainGb"), TEXT("GainB")};
		for(int i = 0; i < 4; i++)
		{
			_tprintf(TEXT("WB %s : %u - x %0.2f\n"), pWBGainName[i], pwWBGain[i], pwWBGain[i] / 128.0);
		}
	}while(0);
	return(bReval);
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
BOOL	SetHueSaturationColorMatrix(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetHueSaturationColorMatrix ======\n"));
	
	BYTE	byteHueSaturationMode = STCAM_HUE_SATURATION_ON;
		//STCAM_HUE_SATURATION_OFF, STCAM_HUE_SATURATION_ON
	SHORT	shtHue = 0;
	WORD	wSaturation = 100;
	BYTE	byteColorMatrixMode = STCAM_COLOR_MATRIX_CUSTOM;
		//STCAM_COLOR_MATRIX_OFF, STCAM_COLOR_MATRIX_CUSTOM
	SHORT	pshtColorMatrix[12] = 
		{
			30,	59,	11,	0,
			30,	59,	11,	0,
			30,	59,	11,	0,
		};

	do{
		WORD	wColorArray = STCAM_COLOR_ARRAY_MONO;
		bReval = StTrg_GetColorArray(hCamera, &wColorArray);
		if(!bReval)
		{
			_tprintf(TEXT("Get Color Array Failed.\n"));
			break;
		}
		if(STCAM_COLOR_ARRAY_MONO == wColorArray)
		{
			_tprintf(TEXT("Black And White Camera\n"));
			break;
		}
/*
		bReval = StTrg_SetHueSaturationMode(hCamera, byteHueSaturationMode, shtHue, wSaturation);
		if(!bReval)
		{
			_tprintf(TEXT("Set Hue Saturation Mode Failed.\n"));
			break;
		}
		bReval = StTrg_SetColorMatrix(hCamera, byteColorMatrixMode, pshtColorMatrix);
		if(!bReval)
		{
			_tprintf(TEXT("Set Color Matrix Failed.\n"));
			break;
		}
*/
		bReval = StTrg_GetHueSaturationMode(hCamera, &byteHueSaturationMode, &shtHue, &wSaturation);
		if(!bReval)
		{
			_tprintf(TEXT("Get Hue Saturation Mode Failed.\n"));
			break;
		}
		bReval = StTrg_GetColorMatrix(hCamera, &byteColorMatrixMode, pshtColorMatrix);
		if(!bReval)
		{
			_tprintf(TEXT("Get Color Matrix Failed.\n"));
			break;
		}
		_tprintf(TEXT("Hue Saturation Mode : %u - %s\n"), 
			byteHueSaturationMode, 
			(STCAM_HUE_SATURATION_OFF == byteHueSaturationMode) ? TEXT("OFF") : TEXT("ON"));
		if(STCAM_HUE_SATURATION_OFF != byteHueSaturationMode)
		{
			_tprintf(TEXT("Hue : %d\n"), shtHue);
			_tprintf(TEXT("Saturation : %u\n"), wSaturation);
		}

		_tprintf(TEXT("Color Matrix Mode : %u - %s\n"), 
			byteColorMatrixMode, 
			(STCAM_COLOR_MATRIX_OFF == byteColorMatrixMode) ? TEXT("OFF") : TEXT("CUSTOM"));
		if(STCAM_COLOR_MATRIX_OFF != byteColorMatrixMode)
		{
			_tprintf(
				TEXT("R <= ( %d x R + %d x G + %d x B + %d) / 100\n")
				TEXT("G <= ( %d x R + %d x G + %d x B + %d) / 100\n")
				TEXT("G <= ( %d x R + %d x G + %d x B + %d) / 100\n"), 
				pshtColorMatrix[0], pshtColorMatrix[1], pshtColorMatrix[2], pshtColorMatrix[3], 
				pshtColorMatrix[4], pshtColorMatrix[5], pshtColorMatrix[6], pshtColorMatrix[7],
				pshtColorMatrix[8], pshtColorMatrix[9], pshtColorMatrix[10], pshtColorMatrix[11]);
			
		}
	}while(0);
	return(bReval);
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
BOOL	SetSharpness(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetSharpness ======\n"));
	BYTE	byteSharpnessMode = STCAM_SHARPNESS_ON;
		//STCAM_SHARPNESS_OFF, STCAM_SHARPNESS_ON
	WORD	wSharpnessGain = 200;
	BYTE	byteSharpnessCoring = 0;
	do{
		/*
		bReval = StTrg_SetSharpnessMode(hCamera, byteSharpnessMode, wSharpnessGain, byteSharpnessCoring);
		if(!bReval)
		{
			_tprintf(TEXT("Set Sharpness Mode Failed.\n"));
			break;
		}
		*/
		bReval = StTrg_GetSharpnessMode(hCamera, &byteSharpnessMode, &wSharpnessGain, &byteSharpnessCoring);
		if(!bReval)
		{
			_tprintf(TEXT("Get Sharpness Mode Failed.\n"));
			break;
		}
		_tprintf(TEXT("Sharpness Mode : %u - %s\n"), 
			byteSharpnessMode, 
			(STCAM_SHARPNESS_OFF == byteSharpnessMode) ? TEXT("OFF") : TEXT("ON"));
		if(STCAM_SHARPNESS_OFF != byteSharpnessMode)
		{
			_tprintf(TEXT("Sharpness Gain : %u\n"), wSharpnessGain);
			_tprintf(TEXT("Sharpness Coring : %u\n"), byteSharpnessCoring);
		}

	}while(0);
	return(bReval);
}
//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
BOOL	SetTimeOut(HANDLE hCamera)
{
	BOOL	bReval = TRUE;
	_tprintf(TEXT("===== SetTimeOut ======\n"));

	DWORD	pdwTimeOutType[] = {
				STCAM_TIMEOUT_ST2EE,
				STCAM_TIMEOUT_TE2EE,
				STCAM_TIMEOUT_EE2TE,
				STCAM_TIMEOUT_RO2TE};
	DWORD	pdwTimeOutMS[] = {1000, 10000, 500, 500};
	TCHAR	*pszTimeOutTypeName[] = {
				TEXT("Soft Trigger To Exposure End"),
				TEXT("Transfer End To Exposure End"),
				TEXT("Exposure End To Transfer End"),
				TEXT("Read Out To Transfer End")};

	for(int i = 0; i < 4 ; i++)
	{
		/*
		bReval = StTrg_SetTimeOut(hCamera, pdwTimeOutType[i], pdwTimeOutMS[i]);
		if(!bReval)
		{
			_tprintf(TEXT("Set Time Out Failed.\n"));
			break;
		}
		*/
		bReval = StTrg_GetTimeOut(hCamera, pdwTimeOutType[i], &pdwTimeOutMS[i]);
		if(!bReval)
		{
			_tprintf(TEXT("Get Time Out Failed.\n"));
			break;
		}

		_tprintf(TEXT("Time Out[%s] : %u ms\n"), 
							pszTimeOutTypeName[i], 
							pdwTimeOutMS[i]);
	}
	return(bReval);
}






