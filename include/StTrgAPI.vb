'Created Date:2013/08/09 17:05
Imports System.Runtime.InteropServices
Public Class StTrg
	Public Delegate Sub funcExposureEndCallback(ByVal hCamera As IntPtr, ByVal dwFrameNo as System.UInt32, ByVal lpContext As IntPtr)
	Public Delegate Sub funcTransferEndCallback(ByVal hCamera As IntPtr, ByVal dwFrameNo as System.UInt32, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal wColorArray As System.UInt16, ByVal pvRaw as IntPtr, ByVal lpContext As IntPtr)
	Public Delegate Sub funcRcvErrorCallback(ByVal hCamera As IntPtr, ByVal dwErrorCode as System.UInt32, ByVal lpContext As IntPtr)
	
	'------------------------------------------------------------------------------
	'Initialize
	'------------------------------------------------------------------------------
	Public Declare Function Open Lib "StTrgAPI.dll" Alias "StTrg_Open" () As IntPtr
	Public Declare Sub Close Lib "StTrgAPI.dll" Alias "StTrg_Close" (ByVal hCamera As IntPtr)
	
	'------------------------------------------------------------------------------
	'Camera Information
	'------------------------------------------------------------------------------
	Public Declare Function GetDllVersion Lib "StTrgAPI.dll" Alias "StTrg_GetDllVersion" (ByRef pdwFileVersionMS As System.UInt32, ByRef pdwFileVersionLS As System.UInt32, ByRef pdwProductVersionMS As System.UInt32, ByRef pdwProductVersionLS As System.UInt32) As integer
	Public Declare Function GetCameraVersion Lib "StTrgAPI.dll" Alias "StTrg_GetCameraVersion" (ByVal hCamera As IntPtr, ByRef pwUSBVendorID As System.UInt16, ByRef pwUSBProductID As System.UInt16, ByRef pwFPGAVersion As System.UInt16, ByRef pwFirmVersion As System.UInt16) As integer
	Public Declare Function GetProductNameA Lib "StTrgAPI.dll" Alias "StTrg_GetProductNameA" (ByVal hCamera As IntPtr, ByVal pszProductName As System.Text.StringBuilder, ByVal dwBufferSize As System.UInt32) As integer
	Public Declare Function GetProductNameW Lib "StTrgAPI.dll" Alias "StTrg_GetProductNameW" (ByVal hCamera As IntPtr, ByVal pszProductName As System.Text.StringBuilder, ByVal dwBufferSize As System.UInt32) As integer
	Public Declare Auto Function GetProductName Lib "StTrgAPI.dll" Alias "StTrg_GetProductName" (ByVal hCamera As IntPtr, ByVal pszProductName As System.Text.StringBuilder, ByVal dwBufferSize As System.UInt32) As integer
	Public Declare Function GetColorArray Lib "StTrgAPI.dll" Alias "StTrg_GetColorArray" (ByVal hCamera As IntPtr, ByRef pwColorArray As System.UInt16) As integer
	Public Declare Function HasFunction Lib "StTrgAPI.dll" Alias "StTrg_HasFunction" (ByVal hCamera As IntPtr, ByVal dwCameraFunctionID As System.UInt32, ByRef pbHasFunction As integer) As integer
	Public Declare Function ReadUserMemory Lib "StTrgAPI.dll" Alias "StTrg_ReadUserMemory" (ByVal hCamera As IntPtr,  pbyteData As IntPtr, ByVal wOffset As System.UInt16, ByVal wLength As System.UInt16) As integer
	Public Declare Function WriteUserMemory Lib "StTrgAPI.dll" Alias "StTrg_WriteUserMemory" (ByVal hCamera As IntPtr,  pbyteData As IntPtr, ByVal wOffset As System.UInt16, ByVal wLength As System.UInt16) As integer
	Public Declare Function ReadCameraUserIDA Lib "StTrgAPI.dll" Alias "StTrg_ReadCameraUserIDA" (ByVal hCamera As IntPtr, ByRef pdwCameraID As System.UInt32, ByVal pszCameraName As System.Text.StringBuilder, ByVal dwBufferSize As System.UInt32) As integer
	Public Declare Function ReadCameraUserIDW Lib "StTrgAPI.dll" Alias "StTrg_ReadCameraUserIDW" (ByVal hCamera As IntPtr, ByRef pdwCameraID As System.UInt32, ByVal pszCameraName As System.Text.StringBuilder, ByVal dwBufferSize As System.UInt32) As integer
	Public Declare Auto Function ReadCameraUserID Lib "StTrgAPI.dll" Alias "StTrg_ReadCameraUserID" (ByVal hCamera As IntPtr, ByRef pdwCameraID As System.UInt32, ByVal pszCameraName As System.Text.StringBuilder, ByVal dwBufferSize As System.UInt32) As integer
	Public Declare Function WriteCameraUserIDA Lib "StTrgAPI.dll" Alias "StTrg_WriteCameraUserIDA" (ByVal hCamera As IntPtr, ByVal dwCameraID As System.UInt32, ByVal pszCameraName As String, ByVal dwBufferSize As System.UInt32) As integer
	Public Declare Function WriteCameraUserIDW Lib "StTrgAPI.dll" Alias "StTrg_WriteCameraUserIDW" (ByVal hCamera As IntPtr, ByVal dwCameraID As System.UInt32, ByVal pszCameraName As String, ByVal dwBufferSize As System.UInt32) As integer
	Public Declare Auto Function WriteCameraUserID Lib "StTrgAPI.dll" Alias "StTrg_WriteCameraUserID" (ByVal hCamera As IntPtr, ByVal dwCameraID As System.UInt32, ByVal pszCameraName As String, ByVal dwBufferSize As System.UInt32) As integer
	Public Declare Function ResetCounter Lib "StTrgAPI.dll" Alias "StTrg_ResetCounter" (ByVal hCamera As IntPtr) As integer
	
	'------------------------------------------------------------------------------
	'Setting
	'------------------------------------------------------------------------------
	Public Declare Function WriteSettingFileW Lib "StTrgAPI.dll" Alias "StTrg_WriteSettingFileW" (ByVal hCamera As IntPtr, ByVal pszFileName As String) As integer
	Public Declare Auto Function WriteSettingFile Lib "StTrgAPI.dll" Alias "StTrg_WriteSettingFile" (ByVal hCamera As IntPtr, ByVal pszFileName As String) As integer
	Public Declare Function WriteSettingFileA Lib "StTrgAPI.dll" Alias "StTrg_WriteSettingFileA" (ByVal hCamera As IntPtr, ByVal pszFileName As String) As integer
	Public Declare Function ReadSettingFileW Lib "StTrgAPI.dll" Alias "StTrg_ReadSettingFileW" (ByVal hCamera As IntPtr, ByVal pszFileName As String) As integer
	Public Declare Auto Function ReadSettingFile Lib "StTrgAPI.dll" Alias "StTrg_ReadSettingFile" (ByVal hCamera As IntPtr, ByVal pszFileName As String) As integer
	Public Declare Function ReadSettingFileA Lib "StTrgAPI.dll" Alias "StTrg_ReadSettingFileA" (ByVal hCamera As IntPtr, ByVal pszFileName As String) As integer
	Public Declare Function CameraSetting Lib "StTrgAPI.dll" Alias "StTrg_CameraSetting" (ByVal hCamera As IntPtr, ByVal wMode As System.UInt16) As integer
	
	'------------------------------------------------------------------------------
	'Image Information
	'------------------------------------------------------------------------------
	Public Declare Function GetEnableScanMode Lib "StTrgAPI.dll" Alias "StTrg_GetEnableScanMode" (ByVal hCamera As IntPtr, ByRef pwEnableScanMode As System.UInt16) As integer
	Public Declare Function GetMaximumImageSize Lib "StTrgAPI.dll" Alias "StTrg_GetMaximumImageSize" (ByVal hCamera As IntPtr, ByRef pdwMaximumImageWidth As System.UInt32, ByRef pdwMaximumImageHeight As System.UInt32) As integer
	Public Declare Function GetScanMode Lib "StTrgAPI.dll" Alias "StTrg_GetScanMode" (ByVal hCamera As IntPtr, ByRef pwScanMode As System.UInt16, ByRef pdwOffsetX As System.UInt32, ByRef pdwOffsetY As System.UInt32, ByRef pdwWidth As System.UInt32, ByRef pdwHeight As System.UInt32) As integer
	Public Declare Function SetScanMode Lib "StTrgAPI.dll" Alias "StTrg_SetScanMode" (ByVal hCamera As IntPtr, ByVal wScanMode As System.UInt16, ByVal dwOffsetX As System.UInt32, ByVal dwOffsetY As System.UInt32, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32) As integer
	Public Declare Function GetEnableTransferBitsPerPixel Lib "StTrgAPI.dll" Alias "StTrg_GetEnableTransferBitsPerPixel" (ByVal hCamera As IntPtr, ByRef pdwEnableTransferBitsPerPixel As System.UInt32) As integer
	Public Declare Function GetTransferBitsPerPixel Lib "StTrgAPI.dll" Alias "StTrg_GetTransferBitsPerPixel" (ByVal hCamera As IntPtr, ByRef pdwTransferBitsPerPixel As System.UInt32) As integer
	Public Declare Function SetTransferBitsPerPixel Lib "StTrgAPI.dll" Alias "StTrg_SetTransferBitsPerPixel" (ByVal hCamera As IntPtr, ByVal dwTransferBitsPerPixel As System.UInt32) As integer
	Public Declare Function GetSkippingAndBinning Lib "StTrgAPI.dll" Alias "StTrg_GetSkippingAndBinning" (ByVal hCamera As IntPtr, ByRef pbyteHSkipping As Byte, ByRef pbyteVSkipping As Byte, ByRef pbyteHBinning As Byte, ByRef pbyteVBinning As Byte) As integer
	Public Declare Function SetSkippingAndBinning Lib "StTrgAPI.dll" Alias "StTrg_SetSkippingAndBinning" (ByVal hCamera As IntPtr, ByVal byteHSkipping As Byte, ByVal byteVSkipping As Byte, ByVal byteHBinning As Byte, ByVal byteVBinning As Byte) As integer
	Public Declare Function GetBinningSumMode Lib "StTrgAPI.dll" Alias "StTrg_GetBinningSumMode" (ByVal hCamera As IntPtr, ByRef pwValue As System.UInt16) As integer
	Public Declare Function SetBinningSumMode Lib "StTrgAPI.dll" Alias "StTrg_SetBinningSumMode" (ByVal hCamera As IntPtr, ByVal wValue As System.UInt16) As integer
	Public Declare Function ConvTo8BitsImage Lib "StTrgAPI.dll" Alias "StTrg_ConvTo8BitsImage" (ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwTransferBitsPerPixel As System.UInt32,  pwRaw As IntPtr,  pbyteRaw As IntPtr) As integer
	Public Declare Function ConvYUVOrBGRToBGRImage Lib "StTrgAPI.dll" Alias "StTrg_ConvYUVOrBGRToBGRImage" (ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwTransferBitsPerPixel As System.UInt32,  pbyteYUVOrBGR As IntPtr, ByVal dwPixelFormat As System.UInt32,  pbyteBGR As IntPtr) As integer
	
	'------------------------------------------------------------------------------
	'Clock
	'------------------------------------------------------------------------------
	Public Declare Function GetOutputFPS Lib "StTrgAPI.dll" Alias "StTrg_GetOutputFPS" (ByVal hCamera As IntPtr, ByRef pfFPS As Single) As integer
	Public Declare Function GetClock Lib "StTrgAPI.dll" Alias "StTrg_GetClock" (ByVal hCamera As IntPtr, ByRef pdwClockMode As System.UInt32, ByRef pdwClock As System.UInt32) As integer
	Public Declare Function SetClock Lib "StTrgAPI.dll" Alias "StTrg_SetClock" (ByVal hCamera As IntPtr, ByVal dwClockMode As System.UInt32, ByVal dwClock As System.UInt32) As integer
	Public Declare Function GetEnableClockMode Lib "StTrgAPI.dll" Alias "StTrg_GetEnableClockMode" (ByVal hCamera As IntPtr, ByRef pdwClockMode As System.UInt32) As integer
	Public Declare Function GetVBlankForFPS Lib "StTrgAPI.dll" Alias "StTrg_GetVBlankForFPS" (ByVal hCamera As IntPtr, ByRef pdwVLines As System.UInt32) As integer
	Public Declare Function SetVBlankForFPS Lib "StTrgAPI.dll" Alias "StTrg_SetVBlankForFPS" (ByVal hCamera As IntPtr, ByVal dwVLines As System.UInt32) As integer
	Public Declare Function GetMaxVBlankForFPS Lib "StTrgAPI.dll" Alias "StTrg_GetMaxVBlankForFPS" (ByVal hCamera As IntPtr, ByRef pdwVLines As System.UInt32) As integer
	Public Declare Function GetFrameClock Lib "StTrgAPI.dll" Alias "StTrg_GetFrameClock" (ByVal hCamera As IntPtr, ByRef pwTotalLine As System.UInt16, ByRef pwTotalHClock As System.UInt16) As integer
	
	'------------------------------------------------------------------------------
	'Shutter Gain Control
	'------------------------------------------------------------------------------
	Public Declare Function SetGain Lib "StTrgAPI.dll" Alias "StTrg_SetGain" (ByVal hCamera As IntPtr, ByVal wGain As System.UInt16) As integer
	Public Declare Function GetGain Lib "StTrgAPI.dll" Alias "StTrg_GetGain" (ByVal hCamera As IntPtr, ByRef pwGain As System.UInt16) As integer
	Public Declare Function GetMaxGain Lib "StTrgAPI.dll" Alias "StTrg_GetMaxGain" (ByVal hCamera As IntPtr, ByRef pwMaxGain As System.UInt16) As integer
	Public Declare Function GetGainDBFromSettingValue Lib "StTrgAPI.dll" Alias "StTrg_GetGainDBFromSettingValue" (ByVal hCamera As IntPtr, ByVal wGain As System.UInt16, ByRef pfGaindB As Single) As integer
	Public Declare Function GetExposureClock Lib "StTrgAPI.dll" Alias "StTrg_GetExposureClock" (ByVal hCamera As IntPtr, ByRef pdwExposureValue As System.UInt32) As integer
	Public Declare Function SetExposureClock Lib "StTrgAPI.dll" Alias "StTrg_SetExposureClock" (ByVal hCamera As IntPtr, ByVal dwExposureValue As System.UInt32) As integer
	Public Declare Function GetMaxShortExposureClock Lib "StTrgAPI.dll" Alias "StTrg_GetMaxShortExposureClock" (ByVal hCamera As IntPtr, ByRef pdwMaximumExposureClock As System.UInt32) As integer
	Public Declare Function GetMaxLongExposureClock Lib "StTrgAPI.dll" Alias "StTrg_GetMaxLongExposureClock" (ByVal hCamera As IntPtr, ByRef pdwMaximumExposureClock As System.UInt32) As integer
	Public Declare Function GetExposureClockFromTime Lib "StTrgAPI.dll" Alias "StTrg_GetExposureClockFromTime" (ByVal hCamera As IntPtr, ByVal fExpTime As Single, ByRef pdwExposureClock As System.UInt32) As integer
	Public Declare Function GetExposureTimeFromClock Lib "StTrgAPI.dll" Alias "StTrg_GetExposureTimeFromClock" (ByVal hCamera As IntPtr, ByVal dwExposureClock As System.UInt32, ByRef pfExpTime As Single) As integer
	Public Declare Function SetDigitalGain Lib "StTrgAPI.dll" Alias "StTrg_SetDigitalGain" (ByVal hCamera As IntPtr, ByVal wDigitalGain As System.UInt16) As integer
	Public Declare Function GetDigitalGain Lib "StTrgAPI.dll" Alias "StTrg_GetDigitalGain" (ByVal hCamera As IntPtr, ByRef pwDigitalGain As System.UInt16) As integer
	Public Declare Function ALC Lib "StTrgAPI.dll" Alias "StTrg_ALC" (ByVal hCamera As IntPtr, ByVal wCurrentBrightness As System.UInt16, ByRef pdwALCStatus As System.UInt32) As integer
	Public Declare Function GetAveragePixelValue Lib "StTrgAPI.dll" Alias "StTrg_GetAveragePixelValue" (ByVal dwImageWidth As System.UInt32, ByVal dwImageHeight As System.UInt32, ByVal wColorArray As System.UInt16, ByVal dwTransferBitsPerPixel As System.UInt32,  pbyteRaw As IntPtr, ByVal dwAOIOffsetX As System.UInt32, ByVal dwAOIOffsetY As System.UInt32, ByVal dwAOIWidth As System.UInt32, ByVal dwAOIHeight As System.UInt32,  pfAverage As IntPtr) As integer
	Public Declare Function SetALCMode Lib "StTrgAPI.dll" Alias "StTrg_SetALCMode" (ByVal hCamera As IntPtr, ByVal byteALCMode As Byte) As integer
	Public Declare Function GetALCMode Lib "StTrgAPI.dll" Alias "StTrg_GetALCMode" (ByVal hCamera As IntPtr, ByRef pbyteALCMode As Byte) As integer
	Public Declare Function SetALCTargetLevel Lib "StTrgAPI.dll" Alias "StTrg_SetALCTargetLevel" (ByVal hCamera As IntPtr, ByVal wLevel As System.UInt16) As integer
	Public Declare Function GetALCTargetLevel Lib "StTrgAPI.dll" Alias "StTrg_GetALCTargetLevel" (ByVal hCamera As IntPtr, ByRef pwLevel As System.UInt16) As integer
	Public Declare Function GetAGCMinGain Lib "StTrgAPI.dll" Alias "StTrg_GetAGCMinGain" (ByVal hCamera As IntPtr, ByRef pwMinGain As System.UInt16) As integer
	Public Declare Function SetAGCMinGain Lib "StTrgAPI.dll" Alias "StTrg_SetAGCMinGain" (ByVal hCamera As IntPtr, ByVal wMinGain As System.UInt16) As integer
	Public Declare Function GetAGCMaxGain Lib "StTrgAPI.dll" Alias "StTrg_GetAGCMaxGain" (ByVal hCamera As IntPtr, ByRef pwMaxGain As System.UInt16) As integer
	Public Declare Function SetAGCMaxGain Lib "StTrgAPI.dll" Alias "StTrg_SetAGCMaxGain" (ByVal hCamera As IntPtr, ByVal wMaxGain As System.UInt16) As integer
	Public Declare Function GetAEMinExposureClock Lib "StTrgAPI.dll" Alias "StTrg_GetAEMinExposureClock" (ByVal hCamera As IntPtr, ByRef pdwMinExposureClock As System.UInt32) As integer
	Public Declare Function SetAEMinExposureClock Lib "StTrgAPI.dll" Alias "StTrg_SetAEMinExposureClock" (ByVal hCamera As IntPtr, ByVal dwMinExposureClock As System.UInt32) As integer
	Public Declare Function GetAEMaxExposureClock Lib "StTrgAPI.dll" Alias "StTrg_GetAEMaxExposureClock" (ByVal hCamera As IntPtr, ByRef pdwMaxExposureClock As System.UInt32) As integer
	Public Declare Function SetAEMaxExposureClock Lib "StTrgAPI.dll" Alias "StTrg_SetAEMaxExposureClock" (ByVal hCamera As IntPtr, ByVal dwMaxExposureClock As System.UInt32) As integer
	
	'------------------------------------------------------------------------------
	'Trigger
	'------------------------------------------------------------------------------
	Public Declare Function GetTriggerMode Lib "StTrgAPI.dll" Alias "StTrg_GetTriggerMode" (ByVal hCamera As IntPtr, ByRef pdwTriggerMode As System.UInt32) As integer
	Public Declare Function SetTriggerMode Lib "StTrgAPI.dll" Alias "StTrg_SetTriggerMode" (ByVal hCamera As IntPtr, ByVal dwTriggerMode As System.UInt32) As integer
	Public Declare Function GetTriggerTiming Lib "StTrgAPI.dll" Alias "StTrg_GetTriggerTiming" (ByVal hCamera As IntPtr, ByVal dwTriggerTimingType As System.UInt32, ByRef pdwValue As System.UInt32) As integer
	Public Declare Function SetTriggerTiming Lib "StTrgAPI.dll" Alias "StTrg_SetTriggerTiming" (ByVal hCamera As IntPtr, ByVal dwTriggerTimingType As System.UInt32, ByVal dwValue As System.UInt32) As integer
	Public Declare Function SoftTrigger Lib "StTrgAPI.dll" Alias "StTrg_SoftTrigger" (ByVal hCamera As IntPtr) As integer
	Public Declare Function ReadSDRAMTrigger Lib "StTrgAPI.dll" Alias "StTrg_ReadSDRAMTrigger" (ByVal hCamera As IntPtr) As integer
	Public Declare Function SoftSubTrigger Lib "StTrgAPI.dll" Alias "StTrg_SoftSubTrigger" (ByVal hCamera As IntPtr) As integer
	Public Declare Function TriggerReadOut Lib "StTrgAPI.dll" Alias "StTrg_TriggerReadOut" (ByVal hCamera As IntPtr) As integer
	
	'------------------------------------------------------------------------------
	'IOPin
	'------------------------------------------------------------------------------
	Public Declare Function GetIOPinDirection Lib "StTrgAPI.dll" Alias "StTrg_GetIOPinDirection" (ByVal hCamera As IntPtr, ByRef pdwDirection As System.UInt32) As integer
	Public Declare Function SetIOPinDirection Lib "StTrgAPI.dll" Alias "StTrg_SetIOPinDirection" (ByVal hCamera As IntPtr, ByVal dwDirection As System.UInt32) As integer
	Public Declare Function GetIOPinPolarity Lib "StTrgAPI.dll" Alias "StTrg_GetIOPinPolarity" (ByVal hCamera As IntPtr, ByRef pdwPolarity As System.UInt32) As integer
	Public Declare Function SetIOPinPolarity Lib "StTrgAPI.dll" Alias "StTrg_SetIOPinPolarity" (ByVal hCamera As IntPtr, ByVal dwPolarity As System.UInt32) As integer
	Public Declare Function GetIOPinMode Lib "StTrgAPI.dll" Alias "StTrg_GetIOPinMode" (ByVal hCamera As IntPtr, ByVal bytePinNo As Byte, ByRef pdwMode As System.UInt32) As integer
	Public Declare Function SetIOPinMode Lib "StTrgAPI.dll" Alias "StTrg_SetIOPinMode" (ByVal hCamera As IntPtr, ByVal bytePinNo As Byte, ByVal dwMode As System.UInt32) As integer
	Public Declare Function GetIOPinStatus Lib "StTrgAPI.dll" Alias "StTrg_GetIOPinStatus" (ByVal hCamera As IntPtr, ByRef pdwStatus As System.UInt32) As integer
	Public Declare Function SetIOPinStatus Lib "StTrgAPI.dll" Alias "StTrg_SetIOPinStatus" (ByVal hCamera As IntPtr, ByVal dwStatus As System.UInt32) As integer
	Public Declare Function GetSwStatus Lib "StTrgAPI.dll" Alias "StTrg_GetSwStatus" (ByVal hCamera As IntPtr, ByRef pdwSwStatus As System.UInt32) As integer
	Public Declare Function GetLEDStatus Lib "StTrgAPI.dll" Alias "StTrg_GetLEDStatus" (ByVal hCamera As IntPtr, ByRef pdwLEDStatus As System.UInt32) As integer
	Public Declare Function SetLEDStatus Lib "StTrgAPI.dll" Alias "StTrg_SetLEDStatus" (ByVal hCamera As IntPtr, ByVal dwLEDStatus As System.UInt32) As integer
	
	'------------------------------------------------------------------------------
	'Timeout
	'------------------------------------------------------------------------------
	Public Declare Function GetTimeOut Lib "StTrgAPI.dll" Alias "StTrg_GetTimeOut" (ByVal hCamera As IntPtr, ByVal dwTimeOutType As System.UInt32, ByRef pdwTimeOutMS As System.UInt32) As integer
	Public Declare Function SetTimeOut Lib "StTrgAPI.dll" Alias "StTrg_SetTimeOut" (ByVal hCamera As IntPtr, ByVal dwTimeOutType As System.UInt32, ByVal dwTimeOutMS As System.UInt32) As integer
	
	'------------------------------------------------------------------------------
	'Callback Function
	'------------------------------------------------------------------------------
	Public Declare Function SetExposureEndCallback Lib "StTrgAPI.dll" Alias "StTrg_SetExposureEndCallback" (ByVal hCamera As IntPtr, ByVal func As funcExposureEndCallback, ByVal pvContext As IntPtr) As integer
	Public Declare Function SetTransferEndCallback Lib "StTrgAPI.dll" Alias "StTrg_SetTransferEndCallback" (ByVal hCamera As IntPtr, ByVal func As funcTransferEndCallback, ByVal pvContext As IntPtr) As integer
	Public Declare Function SetRcvErrorCallback Lib "StTrgAPI.dll" Alias "StTrg_SetRcvErrorCallback" (ByVal hCamera As IntPtr, ByVal func As funcRcvErrorCallback, ByVal pvContext As IntPtr) As integer
	
	'------------------------------------------------------------------------------
	'Image Acquisition
	'------------------------------------------------------------------------------
	Public Declare Function SetRcvMsgWnd Lib "StTrgAPI.dll" Alias "StTrg_SetRcvMsgWnd" (ByVal hCamera As IntPtr, ByVal hWnd As IntPtr) As integer
	Public Declare Function SetRawSnapShotBufferCount Lib "StTrgAPI.dll" Alias "StTrg_SetRawSnapShotBufferCount" (ByVal hCamera As IntPtr, ByVal dwBufferCount As System.UInt32) As integer
	Public Declare Function TakeRawSnapShot Lib "StTrgAPI.dll" Alias "StTrg_TakeRawSnapShot" (ByVal hCamera As IntPtr,  pbyteRaw As IntPtr, ByVal dwBufferSize As System.UInt32, ByRef pdwNumberOfByteTrans As System.UInt32, ByRef pdwFrameNo As System.UInt32, ByVal dwMilliseconds As System.UInt32) As integer
	
	'------------------------------------------------------------------------------
	'Transfer Control
	'------------------------------------------------------------------------------
	Public Declare Function StartTransfer Lib "StTrgAPI.dll" Alias "StTrg_StartTransfer" (ByVal hCamera As IntPtr) As integer
	Public Declare Function StopTransfer Lib "StTrgAPI.dll" Alias "StTrg_StopTransfer" (ByVal hCamera As IntPtr) As integer
	
	'------------------------------------------------------------------------------
	'Noise Reduction
	'------------------------------------------------------------------------------
	Public Declare Function NoiseReduction2 Lib "StTrgAPI.dll" Alias "StTrg_NoiseReduction2" (ByVal hCamera As IntPtr, ByVal dwNoiseReductionMode As System.UInt32, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal wColorArray As System.UInt16,  pbyteRaw As IntPtr, ByVal wRawBitsPerPixel As System.UInt16) As integer
	Public Declare Function NoiseReduction Lib "StTrgAPI.dll" Alias "StTrg_NoiseReduction" (ByVal hCamera As IntPtr, ByVal dwNoiseReductionMode As System.UInt32, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal wColorArray As System.UInt16,  pbyteRaw As IntPtr) As integer
	
	'------------------------------------------------------------------------------
	'White Balance Control
	'------------------------------------------------------------------------------
	Public Declare Function GetWhiteBalanceMode Lib "StTrgAPI.dll" Alias "StTrg_GetWhiteBalanceMode" (ByVal hCamera As IntPtr, ByRef pbyteWBMode As Byte) As integer
	Public Declare Function SetWhiteBalanceMode Lib "StTrgAPI.dll" Alias "StTrg_SetWhiteBalanceMode" (ByVal hCamera As IntPtr, ByVal byteWBMode As Byte) As integer
	Public Declare Function GetWhiteBalanceGain Lib "StTrgAPI.dll" Alias "StTrg_GetWhiteBalanceGain" (ByVal hCamera As IntPtr, ByRef pwWBGainR As System.UInt16, ByRef pwWBGainGr As System.UInt16, ByRef pwWBGainGb As System.UInt16, ByRef pwWBGainB As System.UInt16) As integer
	Public Declare Function SetWhiteBalanceGain Lib "StTrgAPI.dll" Alias "StTrg_SetWhiteBalanceGain" (ByVal hCamera As IntPtr, ByVal wWBGainR As System.UInt16, ByVal wWBGainGr As System.UInt16, ByVal wWBGainGb As System.UInt16, ByVal wWBGainB As System.UInt16) As integer
	Public Declare Function WhiteBalance Lib "StTrgAPI.dll" Alias "StTrg_WhiteBalance" (ByVal hCamera As IntPtr,  pbyteRaw As IntPtr) As integer
	Public Declare Function WhiteBalance2 Lib "StTrgAPI.dll" Alias "StTrg_WhiteBalance2" (ByVal hCamera As IntPtr,  pwRaw As IntPtr, ByVal wRawBitsPerPixel As System.UInt16) As integer
	
	'------------------------------------------------------------------------------
	'Gamma
	'------------------------------------------------------------------------------
	Public Declare Function GetGammaModeEx Lib "StTrgAPI.dll" Alias "StTrg_GetGammaModeEx" (ByVal hCamera As IntPtr, ByVal byteGammaTarget As Byte, ByRef pbyteGammaMode As Byte, ByRef pwGamma As System.UInt16, ByRef pshtBrightness As Short, ByRef pbyteContrast As Byte,  pbyteGammaTable As IntPtr) As integer
	Public Declare Function SetGammaModeEx Lib "StTrgAPI.dll" Alias "StTrg_SetGammaModeEx" (ByVal hCamera As IntPtr, ByVal byteGammaTarget As Byte, ByVal byteGammaMode As Byte, ByVal wGamma As System.UInt16, ByVal shtBrightness As Short, ByVal byteContrast As Byte,  pbyteGammaTable As IntPtr) As integer
	Public Declare Function RawColorGamma Lib "StTrgAPI.dll" Alias "StTrg_RawColorGamma" (ByVal hCamera As IntPtr, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal wColorArray As System.UInt16,  pbyteRaw As IntPtr) As integer
	Public Declare Function BGRGamma Lib "StTrgAPI.dll" Alias "StTrg_BGRGamma" (ByVal hCamera As IntPtr, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwPixelFormat As System.UInt32,  pbyteBGR As IntPtr) As integer
	Public Declare Function GetGammaModeEx2 Lib "StTrgAPI.dll" Alias "StTrg_GetGammaModeEx2" (ByVal hCamera As IntPtr, ByVal byteGammaTarget As Byte, ByRef pbyteGammaMode As Byte, ByRef pwGamma As System.UInt16, ByRef pshtBrightness As Short, ByRef pwContrast As System.UInt16,  pwGammaTable As IntPtr, ByRef pwBitsPerEachColor As System.UInt16) As integer
	Public Declare Function SetGammaModeEx2 Lib "StTrgAPI.dll" Alias "StTrg_SetGammaModeEx2" (ByVal hCamera As IntPtr, ByVal byteGammaTarget As Byte, ByVal byteGammaMode As Byte, ByVal wGamma As System.UInt16, ByVal shtBrightness As Short, ByVal wContrast As System.UInt16,  pwGammaTable As IntPtr, ByVal wBitsPerEachColor As System.UInt16) As integer
	Public Declare Function RawColorGamma2 Lib "StTrgAPI.dll" Alias "StTrg_RawColorGamma2" (ByVal hCamera As IntPtr, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal wColorArray As System.UInt16,  pbyteRaw As IntPtr, ByVal wRawBitsPerPixel As System.UInt16) As integer
	Public Declare Function BGRGamma2 Lib "StTrgAPI.dll" Alias "StTrg_BGRGamma2" (ByVal hCamera As IntPtr, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwPixelFormat As System.UInt32,  pbyteBGR As IntPtr, ByVal wBitsPerEachColor As System.UInt16) As integer
	Public Declare Function GetCameraGammaValue Lib "StTrgAPI.dll" Alias "StTrg_GetCameraGammaValue" (ByVal hCamera As IntPtr, ByRef pwValue As System.UInt16) As integer
	Public Declare Function SetCameraGammaValue Lib "StTrgAPI.dll" Alias "StTrg_SetCameraGammaValue" (ByVal hCamera As IntPtr, ByVal wValue As System.UInt16) As integer
	
	'------------------------------------------------------------------------------
	'Mirror Rotation
	'------------------------------------------------------------------------------
	Public Declare Function MirrorRotation Lib "StTrgAPI.dll" Alias "StTrg_MirrorRotation" (ByVal byteMirrorMode As Byte, ByVal byteRotationMode As Byte, ByRef pdwWidth As System.UInt32, ByRef pdwHeight As System.UInt32, ByRef pwColorArray As System.UInt16,  pbyteRaw As IntPtr) As integer
	Public Declare Function GetMirrorMode Lib "StTrgAPI.dll" Alias "StTrg_GetMirrorMode" (ByVal hCamera As IntPtr, ByRef pbyteMirrorMode As Byte) As integer
	Public Declare Function SetMirrorMode Lib "StTrgAPI.dll" Alias "StTrg_SetMirrorMode" (ByVal hCamera As IntPtr, ByVal byteMirrorMode As Byte) As integer
	
	'------------------------------------------------------------------------------
	'Color Interpolation
	'------------------------------------------------------------------------------
	Public Declare Function ColorInterpolation2 Lib "StTrgAPI.dll" Alias "StTrg_ColorInterpolation2" (ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal wColorArray As System.UInt16,  pwRaw As IntPtr,  pwBGR As IntPtr, ByVal byteColorInterpolationMethod As Byte, ByVal dwPixelFormat As System.UInt32, ByVal wRawBitsPerPixel As System.UInt16) As integer
	Public Declare Function ColorInterpolation Lib "StTrgAPI.dll" Alias "StTrg_ColorInterpolation" (ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal wColorArray As System.UInt16,  pbyteRaw As IntPtr,  pbyteBGR As IntPtr, ByVal byteColorInterpolationMethod As Byte, ByVal dwPixelFormat As System.UInt32) As integer
	
	'------------------------------------------------------------------------------
	'Hue Saturation/Color Matrix
	'------------------------------------------------------------------------------
	Public Declare Function GetHueSaturationMode Lib "StTrgAPI.dll" Alias "StTrg_GetHueSaturationMode" (ByVal hCamera As IntPtr, ByRef pbyteHueSaturationMode As Byte, ByRef pshtHue As Short, ByRef pwSaturation As System.UInt16) As integer
	Public Declare Function SetHueSaturationMode Lib "StTrgAPI.dll" Alias "StTrg_SetHueSaturationMode" (ByVal hCamera As IntPtr, ByVal byteHueSaturationMode As Byte, ByVal shtHue As Short, ByVal wSaturation As System.UInt16) As integer
	Public Declare Function GetColorMatrix Lib "StTrgAPI.dll" Alias "StTrg_GetColorMatrix" (ByVal hCamera As IntPtr, ByRef pbyteColorMatrixMode As Byte, ByVal pshtColorMatrix As IntPtr) As integer
	Public Declare Function SetColorMatrix Lib "StTrgAPI.dll" Alias "StTrg_SetColorMatrix" (ByVal hCamera As IntPtr, ByVal byteColorMatrixMode As Byte, ByVal pshtColorMatrix As IntPtr) As integer
	Public Declare Function HueSaturationColorMatrix2 Lib "StTrgAPI.dll" Alias "StTrg_HueSaturationColorMatrix2" (ByVal hCamera As IntPtr, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwPixelFormat As System.UInt32,  pbyteBGR As IntPtr, ByVal wBitsPerEachColor As System.UInt16) As integer
	Public Declare Function HueSaturationColorMatrix Lib "StTrgAPI.dll" Alias "StTrg_HueSaturationColorMatrix" (ByVal hCamera As IntPtr, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwPixelFormat As System.UInt32,  pbyteBGR As IntPtr) As integer
	
	'------------------------------------------------------------------------------
	'Sharpness
	'------------------------------------------------------------------------------
	Public Declare Function GetSharpnessMode Lib "StTrgAPI.dll" Alias "StTrg_GetSharpnessMode" (ByVal hCamera As IntPtr, ByRef pbyteSharpnessMode As Byte, ByRef pwSharpnessGain As System.UInt16, ByRef pbyteSharpnessCoring As Byte) As integer
	Public Declare Function SetSharpnessMode Lib "StTrgAPI.dll" Alias "StTrg_SetSharpnessMode" (ByVal hCamera As IntPtr, ByVal byteSharpnessMode As Byte, ByVal wSharpnessGain As System.UInt16, ByVal byteSharpnessCoring As Byte) As integer
	Public Declare Function Sharpness Lib "StTrgAPI.dll" Alias "StTrg_Sharpness" (ByVal hCamera As IntPtr, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwPixelFormat As System.UInt32,  pbyteGrayOrBGR As IntPtr) As integer
	Public Declare Function Sharpness2 Lib "StTrgAPI.dll" Alias "StTrg_Sharpness2" (ByVal hCamera As IntPtr, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwPixelFormat As System.UInt32,  pbyteGrayOrBGR As IntPtr, ByVal wBitsPerEachColor As System.UInt16) As integer
	
	'------------------------------------------------------------------------------
	'Save Image
	'------------------------------------------------------------------------------
	Public Declare Function SaveImageW Lib "StTrgAPI.dll" Alias "StTrg_SaveImageW" (ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwPixelFormat As System.UInt32,  pbyteGrayOrBGR As IntPtr, ByVal pszFileName As String, ByVal dwParam As System.UInt32) As integer
	Public Declare Auto Function SaveImage Lib "StTrgAPI.dll" Alias "StTrg_SaveImage" (ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwPixelFormat As System.UInt32,  pbyteGrayOrBGR As IntPtr, ByVal pszFileName As String, ByVal dwParam As System.UInt32) As integer
	Public Declare Function SaveImageA Lib "StTrgAPI.dll" Alias "StTrg_SaveImageA" (ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32, ByVal dwPixelFormat As System.UInt32,  pbyteGrayOrBGR As IntPtr, ByVal pszFileName As String, ByVal dwParam As System.UInt32) As integer
	
	'------------------------------------------------------------------------------
	'Defect Pixel Correction
	'------------------------------------------------------------------------------
	Public Declare Function GetEnableDefectPixelCorrectionCount Lib "StTrgAPI.dll" Alias "StTrg_GetEnableDefectPixelCorrectionCount" (ByVal hCamera As IntPtr, ByRef pwCount As System.UInt16) As integer
	Public Declare Function GetDefectPixelCorrectionMode Lib "StTrgAPI.dll" Alias "StTrg_GetDefectPixelCorrectionMode" (ByVal hCamera As IntPtr, ByRef pwMode As System.UInt16) As integer
	Public Declare Function SetDefectPixelCorrectionMode Lib "StTrgAPI.dll" Alias "StTrg_SetDefectPixelCorrectionMode" (ByVal hCamera As IntPtr, ByVal wMode As System.UInt16) As integer
	Public Declare Function GetDefectPixelCorrectionPosition Lib "StTrgAPI.dll" Alias "StTrg_GetDefectPixelCorrectionPosition" (ByVal hCamera As IntPtr, ByVal wIndex As System.UInt16, ByRef pdwX As System.UInt32, ByRef pdwY As System.UInt32) As integer
	Public Declare Function SetDefectPixelCorrectionPosition Lib "StTrgAPI.dll" Alias "StTrg_SetDefectPixelCorrectionPosition" (ByVal hCamera As IntPtr, ByVal wIndex As System.UInt16, ByVal dwX As System.UInt32, ByVal dwY As System.UInt32) As integer
	Public Declare Function DetectDefectPixel Lib "StTrgAPI.dll" Alias "StTrg_DetectDefectPixel" (ByVal hCamera As IntPtr, ByVal dwWidth As System.UInt32, ByVal dwHeight As System.UInt32,  pbyteRaw As IntPtr, ByVal wThreashold As System.UInt16) As integer
	
	'------------------------------------------------------------------------------
	'Preview
	'------------------------------------------------------------------------------
	Public Declare Function Draw Lib "StTrgAPI.dll" Alias "StTrg_Draw" (ByVal hCamera As IntPtr, ByVal hDC As IntPtr, ByVal DestOffsetX As integer, ByVal DestOffsetY As integer, ByVal dwDestWidth As System.UInt32, ByVal dwDestHeight As System.UInt32, ByVal SrcOffsetX As integer, ByVal SrcOffsetY As integer, ByVal dwSrcWidth As System.UInt32, ByVal dwSrcHeight As System.UInt32, ByVal dwOrgWidth As System.UInt32, ByVal dwOrgHeight As System.UInt32,  pbyteGrayOrBGR As IntPtr, ByVal dwPixelFormat As System.UInt32) As integer
	
	'------------------------------------------------------------------------------
	'For Specific Camera
	'------------------------------------------------------------------------------
	Public Declare Function GetIOARegister Lib "StTrgAPI.dll" Alias "StTrg_GetIOARegister" (ByVal hCamera As IntPtr, ByVal dwStartAdd As System.UInt32, ByVal dwEndAdd As System.UInt32,  pwValue As IntPtr) As integer
	Public Declare Function SetIOARegister Lib "StTrgAPI.dll" Alias "StTrg_SetIOARegister" (ByVal hCamera As IntPtr, ByVal dwStartAdd As System.UInt32, ByVal dwEndAdd As System.UInt32,  pwValue As IntPtr) As integer
	Public Declare Function GetITARegister Lib "StTrgAPI.dll" Alias "StTrg_GetITARegister" (ByVal hCamera As IntPtr, ByVal dwStartAdd As System.UInt32, ByVal dwEndAdd As System.UInt32,  pwValue As IntPtr) As integer
	Public Declare Function SetITARegister Lib "StTrgAPI.dll" Alias "StTrg_SetITARegister" (ByVal hCamera As IntPtr, ByVal dwStartAdd As System.UInt32, ByVal dwEndAdd As System.UInt32,  pwValue As IntPtr) As integer
	Public Declare Function GetJBARegister Lib "StTrgAPI.dll" Alias "StTrg_GetJBARegister" (ByVal hCamera As IntPtr, ByVal dwStartAdd As System.UInt32, ByVal dwEndAdd As System.UInt32,  pwValue As IntPtr) As integer
	Public Declare Function SetJBARegister Lib "StTrgAPI.dll" Alias "StTrg_SetJBARegister" (ByVal hCamera As IntPtr, ByVal dwStartAdd As System.UInt32, ByVal dwEndAdd As System.UInt32,  pwValue As IntPtr) As integer
	
	'------------------------------------------------------------------------------
	'Other
	'------------------------------------------------------------------------------
	Public Declare Function SetProcessorIdleState Lib "StTrgAPI.dll" Alias "StTrg_SetProcessorIdleState" (ByVal dwAC As System.UInt32, ByVal dwDC As System.UInt32) As integer
	Public Declare Function ResetRootHub Lib "StTrgAPI.dll" Alias "StTrg_ResetRootHub" () As integer
	Public Declare Function GetProcessorIdleState Lib "StTrgAPI.dll" Alias "StTrg_GetProcessorIdleState" (ByRef pdwAC As System.UInt32, ByRef pdwDC As System.UInt32) As integer
	Public Declare Function SetDigitalClamp Lib "StTrgAPI.dll" Alias "StTrg_SetDigitalClamp" (ByVal hCamera As IntPtr, ByVal wValue As System.UInt16) As integer
	Public Declare Function GetDigitalClamp Lib "StTrgAPI.dll" Alias "StTrg_GetDigitalClamp" (ByVal hCamera As IntPtr, ByRef pwValue As System.UInt16) As integer
	Public Declare Function ClearBuffer Lib "StTrgAPI.dll" Alias "StTrg_ClearBuffer" (ByVal hCamera As IntPtr) As integer
	'------------------------------------------------------------------------------
	'BINNING_SUM_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_BINNING_SUM_MODE_OFF As System.UInt16 = &H0000
	'------------------------------------------------------------------------------
	'DEFECT_PIXEL_CORRECTION_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_DEFECT_PIXEL_CORRECTION_OFF As System.UInt16 = &H0000
	'------------------------------------------------------------------------------
	'ALC_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_ALCMODE_OFF As Byte = 0
	Public Const STCAM_ALCMODE_CAMERA_AE_ON As Byte = &H10
	Public Const STCAM_ALCMODE_CAMERA_AGC_ON As Byte = &H20
	Public Const STCAM_ALCMODE_CAMERA_AE_AGC_ON As Byte = &H30
	Public Const STCAM_ALCMODE_PC_AE_AGC_ON As Byte = &H01
	'------------------------------------------------------------------------------
	'BINNING_SUM_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_BINNING_SUM_MODE_H As System.UInt16 = &H0001
	'------------------------------------------------------------------------------
	'DEFECT_PIXEL_CORRECTION_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_DEFECT_PIXEL_CORRECTION_ON As System.UInt16 = &H0001
	'------------------------------------------------------------------------------
	'BINNING_SUM_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_BINNING_SUM_MODE_V As System.UInt16 = &H0100
	'------------------------------------------------------------------------------
	'ALC_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_ALCMODE_PC_AE_ON As Byte = &H02
	Public Const STCAM_ALCMODE_PC_AGC_ON As Byte = &H03
	Public Const STCAM_ALCMODE_PC_AE_AGC_ONESHOT As Byte = &H04
	Public Const STCAM_ALCMODE_PC_AE_ONESHOT As Byte = &H05
	Public Const STCAM_ALCMODE_PC_AGC_ONESHOT As Byte = &H06
	'------------------------------------------------------------------------------
	'ERROR_STCAM
	'------------------------------------------------------------------------------
	Public Const ERR_EXPOSURE_END_DROPPED As System.UInt32 = &HE0000001UI
	Public Const ERR_IMAGE_DATA_DROPPED As System.UInt32 = &HE0000002UI
	Public Const ERR_TIMEOUT_ST2EE As System.UInt32 = &HE0000003UI
	Public Const ERR_TIMEOUT_TE2EE As System.UInt32 = &HE0000004UI
	Public Const ERR_TIMEOUT_EE2TE As System.UInt32 = &HE0000005UI
	Public Const ERR_TIMEOUT_RO2TE As System.UInt32 = &HE0000006UI
	Public Const ERR_INVALID_FUNCTION_WHILE_TRANSFERRING As System.UInt32 = &HE0000100UI
	'------------------------------------------------------------------------------
	'WM_STCAM
	'------------------------------------------------------------------------------
	Public Const WM_STCAM_TRANSFER_END As integer = &HB101
	Public Const WM_STCAM_EXPOSURE_END As integer = &HB102
	Public Const WM_STCAM_RCV_ERROR As integer = &HB103
	'------------------------------------------------------------------------------
	'COLOR_ARRAY
	'------------------------------------------------------------------------------
	Public Const STCAM_COLOR_ARRAY_MONO As System.UInt16 = &H0001
	Public Const STCAM_COLOR_ARRAY_RGGB As System.UInt16 = &H0002
	Public Const STCAM_COLOR_ARRAY_GRBG As System.UInt16 = &H0003
	Public Const STCAM_COLOR_ARRAY_GBRG As System.UInt16 = &H0004
	Public Const STCAM_COLOR_ARRAY_BGGR As System.UInt16 = &H0005
	'------------------------------------------------------------------------------
	'SCAN_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_SCAN_MODE_NORMAL As System.UInt16 = &H0000
	Public Const STCAM_SCAN_MODE_PARTIAL_2 As System.UInt16 = &H0001
	Public Const STCAM_SCAN_MODE_PARTIAL_4 As System.UInt16 = &H0002
	Public Const STCAM_SCAN_MODE_PARTIAL_1 As System.UInt16 = &H0004
	Public Const STCAM_SCAN_MODE_VARIABLE_PARTIAL As System.UInt16 = &H0008
	Public Const STCAM_SCAN_MODE_BINNING As System.UInt16 = &H0010
	Public Const STCAM_SCAN_MODE_BINNING_PARTIAL_1 As System.UInt16 = &H0020
	Public Const STCAM_SCAN_MODE_BINNING_PARTIAL_2 As System.UInt16 = &H0040
	Public Const STCAM_SCAN_MODE_BINNING_PARTIAL_4 As System.UInt16 = &H0080
	Public Const STCAM_SCAN_MODE_BINNING_VARIABLE_PARTIAL As System.UInt16 = &H0100
	Public Const STCAM_SCAN_MODE_AOI As System.UInt16 = &H8000
	'------------------------------------------------------------------------------
	'PIXEL_FORMAT
	'------------------------------------------------------------------------------
	Public Const STCAM_PIXEL_FORMAT_08_MONO_OR_RAW As System.UInt32 = &H00000001UI
	Public Const STCAM_PIXEL_FORMAT_24_BGR As System.UInt32 = &H00000004UI
	Public Const STCAM_PIXEL_FORMAT_32_BGR As System.UInt32 = &H00000008UI
	'------------------------------------------------------------------------------
	'PIXEL_FORMAT_FOR_SAVE
	'------------------------------------------------------------------------------
	Public Const STCAM_PIXEL_FORMAT_10_MONO_OR_RAW As System.UInt32 = &H00000010UI
	'------------------------------------------------------------------------------
	'PIXEL_FORMAT
	'------------------------------------------------------------------------------
	Public Const STCAM_PIXEL_FORMAT_48_BGR As System.UInt32 = &H00000100UI
	'------------------------------------------------------------------------------
	'PIXEL_FORMAT_FOR_SAVE
	'------------------------------------------------------------------------------
	Public Const STCAM_PIXEL_FORMAT_12_MONO_OR_RAW As System.UInt32 = &H00000020UI
	'------------------------------------------------------------------------------
	'PIXEL_FORMAT
	'------------------------------------------------------------------------------
	Public Const STCAM_PIXEL_FORMAT_64_BGR As System.UInt32 = &H00000200UI
	'------------------------------------------------------------------------------
	'PIXEL_FORMAT_FOR_SAVE
	'------------------------------------------------------------------------------
	Public Const STCAM_PIXEL_FORMAT_16_MONO_OR_RAW As System.UInt32 = &H00000002UI
	'------------------------------------------------------------------------------
	'COLOR_INTERPOLATION
	'------------------------------------------------------------------------------
	Public Const STCAM_COLOR_INTERPOLATION_NONE_MONO As Byte = 0
	Public Const STCAM_COLOR_INTERPOLATION_NONE_COLOR As Byte = 1
	Public Const STCAM_COLOR_INTERPOLATION_NEAREST_NEIGHBOR As Byte = 2
	Public Const STCAM_COLOR_INTERPOLATION_BILINEAR As Byte = 3
	Public Const STCAM_COLOR_INTERPOLATION_BILINEAR_FALSE_COLOR_REDUCTION As Byte = 5
	Public Const STCAM_COLOR_INTERPOLATION_BICUBIC As Byte = 4
	'------------------------------------------------------------------------------
	'WB
	'------------------------------------------------------------------------------
	Public Const STCAM_WB_OFF As Byte = 0
	Public Const STCAM_WB_MANUAL As Byte = 1
	Public Const STCAM_WB_FULLAUTO As Byte = 2
	Public Const STCAM_WB_ONESHOT As Byte = 3
	'------------------------------------------------------------------------------
	'GAMMA_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_GAMMA_OFF As Byte = 0
	Public Const STCAM_GAMMA_ON As Byte = 1
	Public Const STCAM_GAMMA_REVERSE As Byte = 2
	Public Const STCAM_GAMMA_TABLE As Byte = 255
	'------------------------------------------------------------------------------
	'GAMMA_TARGET
	'------------------------------------------------------------------------------
	Public Const STCAM_GAMMA_TARGET_Y As Byte = 0
	Public Const STCAM_GAMMA_TARGET_R As Byte = 1
	Public Const STCAM_GAMMA_TARGET_GR As Byte = 2
	Public Const STCAM_GAMMA_TARGET_GB As Byte = 3
	Public Const STCAM_GAMMA_TARGET_B As Byte = 4
	'------------------------------------------------------------------------------
	'SHARPNESS
	'------------------------------------------------------------------------------
	Public Const STCAM_SHARPNESS_OFF As Byte = 0
	Public Const STCAM_SHARPNESS_ON As Byte = 1
	'------------------------------------------------------------------------------
	'HUE_SATURATION
	'------------------------------------------------------------------------------
	Public Const STCAM_HUE_SATURATION_OFF As Byte = 0
	Public Const STCAM_HUE_SATURATION_ON As Byte = 1
	'------------------------------------------------------------------------------
	'COLOR_MATRIX
	'------------------------------------------------------------------------------
	Public Const STCAM_COLOR_MATRIX_OFF As Byte = &H00
	Public Const STCAM_COLOR_MATRIX_CUSTOM As Byte = &HFF
	'------------------------------------------------------------------------------
	'MIRROR
	'------------------------------------------------------------------------------
	Public Const STCAM_MIRROR_OFF As Byte = 0
	Public Const STCAM_MIRROR_HORIZONTAL As Byte = 1
	Public Const STCAM_MIRROR_VERTICAL As Byte = 2
	Public Const STCAM_MIRROR_HORIZONTAL_VERTICAL As Byte = 3
	'------------------------------------------------------------------------------
	'MIRROR_CAMERA
	'------------------------------------------------------------------------------
	Public Const STCAM_MIRROR_HORIZONTAL_CAMERA As Byte = 16
	Public Const STCAM_MIRROR_VERTICAL_CAMERA As Byte = 32
	'------------------------------------------------------------------------------
	'ROTATION
	'------------------------------------------------------------------------------
	Public Const STCAM_ROTATION_OFF As Byte = 0
	Public Const STCAM_ROTATION_CLOCKWISE_90 As Byte = 1
	Public Const STCAM_ROTATION_COUNTERCLOCKWISE_90 As Byte = 2
	'------------------------------------------------------------------------------
	'CLOCK_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_CLOCK_MODE_NORMAL As System.UInt32 = &H00000000UI
	Public Const STCAM_CLOCK_MODE_DIV_2 As System.UInt32 = &H00000001UI
	Public Const STCAM_CLOCK_MODE_DIV_4 As System.UInt32 = &H00000002UI
	Public Const STCAM_CLOCK_MODE_VGA_90FPS As System.UInt32 = &H00000100UI
	'------------------------------------------------------------------------------
	'USBPID
	'------------------------------------------------------------------------------
	Public Const STCAM_USBPID_STC_B33USB As System.UInt16 = &H0705
	Public Const STCAM_USBPID_STC_C33USB As System.UInt16 = &H0305
	Public Const STCAM_USBPID_STC_B83USB As System.UInt16 = &H0805
	Public Const STCAM_USBPID_STC_C83USB As System.UInt16 = &H0605
	Public Const STCAM_USBPID_STC_TB33USB As System.UInt16 = &H0906
	Public Const STCAM_USBPID_STC_TC33USB As System.UInt16 = &H1006
	Public Const STCAM_USBPID_STC_TB83USB As System.UInt16 = &H1106
	Public Const STCAM_USBPID_STC_TC83USB As System.UInt16 = &H1206
	Public Const STCAM_USBPID_STC_TB133USB As System.UInt16 = &H0109
	Public Const STCAM_USBPID_STC_TC133USB As System.UInt16 = &H0209
	Public Const STCAM_USBPID_STC_TB152USB As System.UInt16 = &H1306
	Public Const STCAM_USBPID_STC_TC152USB As System.UInt16 = &H1406
	Public Const STCAM_USBPID_STC_TB202USB As System.UInt16 = &H1506
	Public Const STCAM_USBPID_STC_TC202USB As System.UInt16 = &H1606
	Public Const STCAM_USBPID_STC_MB33USB As System.UInt16 = &H0110
	Public Const STCAM_USBPID_STC_MC33USB As System.UInt16 = &H0210
	Public Const STCAM_USBPID_STC_MB83USB As System.UInt16 = &H0310
	Public Const STCAM_USBPID_STC_MC83USB As System.UInt16 = &H0410
	Public Const STCAM_USBPID_STC_MB133USB As System.UInt16 = &H0510
	Public Const STCAM_USBPID_STC_MC133USB As System.UInt16 = &H0610
	Public Const STCAM_USBPID_STC_MB152USB As System.UInt16 = &H0710
	Public Const STCAM_USBPID_STC_MC152USB As System.UInt16 = &H0810
	Public Const STCAM_USBPID_STC_MB202USB As System.UInt16 = &H0910
	Public Const STCAM_USBPID_STC_MC202USB As System.UInt16 = &H1010
	Public Const STCAM_USBPID_APBWVUSB_LED As System.UInt16 = &H0509
	Public Const STCAM_USBPID_APCWVUSB_LED As System.UInt16 = &H0609
	Public Const STCAM_USBPID_STC_MBA5MUSB3 As System.UInt16 = &H0111
	Public Const STCAM_USBPID_STC_MCA5MUSB3 As System.UInt16 = &H0211
	Public Const STCAM_USBPID_STC_MBE132U3V As System.UInt16 = &H0112
	Public Const STCAM_USBPID_STC_MCE132U3V As System.UInt16 = &H0212
	'------------------------------------------------------------------------------
	'TRIGGER_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_TRIGGER_MODE_TYPE_MASK As System.UInt32 = &H00000003UI
	Public Const STCAM_TRIGGER_MODE_CAMERA_MEMORY_MASK As System.UInt32 = &H00000030UI
	Public Const STCAM_TRIGGER_MODE_READOUT_SOURCE_MASK As System.UInt32 = &H00000040UI
	Public Const STCAM_TRIGGER_MODE_EXPEND_MASK As System.UInt32 = &H00000100UI
	Public Const STCAM_TRIGGER_MODE_SOURCE_MASK As System.UInt32 = &H00000C00UI
	Public Const STCAM_TRIGGER_MODE_EXPTIME_MASK As System.UInt32 = &H00003000UI
	Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_MASK As System.UInt32 = &H00004000UI
	Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_MASK As System.UInt32 = &H00008000UI
	Public Const STCAM_TRIGGER_MODE_TRIGGER_MASK_MASK As System.UInt32 = &H00010000UI
	Public Const STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_MASK As System.UInt32 = &H00060000UI
	Public Const STCAM_TRIGGER_MODE_TYPE_FREE_RUN As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_TYPE_TRIGGER As System.UInt32 = &H00000001UI
	Public Const STCAM_TRIGGER_MODE_TYPE_TRIGGER_RO As System.UInt32 = &H00000002UI
	Public Const STCAM_TRIGGER_MODE_EXPTIME_EDGE_PRESET As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_EXPTIME_PULSE_WIDTH As System.UInt32 = &H00001000UI
	Public Const STCAM_TRIGGER_MODE_EXPTIME_START_STOP As System.UInt32 = &H00002000UI
	Public Const STCAM_TRIGGER_MODE_SOURCE_NONE As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_SOURCE_SOFTWARE As System.UInt32 = &H00000400UI
	Public Const STCAM_TRIGGER_MODE_SOURCE_HARDWARE As System.UInt32 = &H00000800UI
	Public Const STCAM_TRIGGER_MODE_READOUT_SOFTWARE As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_READOUT_HARDWARE As System.UInt32 = &H00000040UI
	Public Const STCAM_TRIGGER_MODE_EXPEND_DISABLE As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_EXPEND_ENABLE As System.UInt32 = &H00000100UI
	Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_OFF As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_ON As System.UInt32 = &H00004000UI
	Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_OFF As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_ON As System.UInt32 = &H00008000UI
	Public Const STCAM_TRIGGER_MODE_CAMERA_MEMORY_TYPE_B As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_CAMERA_MEMORY_TYPE_A As System.UInt32 = &H00000010UI
	Public Const STCAM_TRIGGER_MODE_CAMERA_MEMORY_OFF As System.UInt32 = &H00000020UI
	Public Const STCAM_TRIGGER_MODE_TRIGGER_MASK_OFF As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_TRIGGER_MASK_ON As System.UInt32 = &H00010000UI
	Public Const STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_ERS As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_GRR As System.UInt32 = &H00020000UI
	Public Const STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_GS As System.UInt32 = &H00040000UI
	'------------------------------------------------------------------------------
	'TRIGGER_TIMING
	'------------------------------------------------------------------------------
	Public Const STCAM_TRIGGER_TIMING_EXPOSURE_DELAY As System.UInt32 = &H00000000UI
	Public Const STCAM_TRIGGER_TIMING_STROBE_START_DELAY As System.UInt32 = &H00000001UI
	Public Const STCAM_TRIGGER_TIMING_STROBE_END_DELAY As System.UInt32 = &H00000002UI
	Public Const STCAM_TRIGGER_TIMING_TRIGGER_PULSE_DELAY As System.UInt32 = &H00000003UI
	Public Const STCAM_TRIGGER_TIMING_OUTPUT_PULSE_DELAY As System.UInt32 = &H00000003UI
	Public Const STCAM_TRIGGER_TIMING_OUTPUT_PULSE_DURATION As System.UInt32 = &H00000004UI
	Public Const STCAM_TRIGGER_TIMING_TRIGGER_PULSE_DURATION As System.UInt32 = &H00000004UI
	Public Const STCAM_TRIGGER_TIMING_READOUT_DELAY As System.UInt32 = &H00000005UI
	'------------------------------------------------------------------------------
	'IO_PIN_MODE
	'------------------------------------------------------------------------------
	Public Const STCAM_OUT_PIN_MODE_DISABLE As System.UInt32 = &H0000
	Public Const STCAM_OUT_PIN_MODE_GENERAL_OUTPUT As System.UInt32 = &H0001
	Public Const STCAM_OUT_PIN_MODE_TRIGGER_OUTPUT_PROGRAMMABLE As System.UInt32 = &H0010
	Public Const STCAM_OUT_PIN_MODE_TRIGGER_OUTPUT_LOOP_THROUGH As System.UInt32 = &H0011
	Public Const STCAM_OUT_PIN_MODE_EXPOSURE_END As System.UInt32 = &H0012
	Public Const STCAM_OUT_PIN_MODE_CCD_READ_END_OUTPUT As System.UInt32 = &H0013
	Public Const STCAM_OUT_PIN_MODE_STROBE_OUTPUT_PROGRAMMABLE As System.UInt32 = &H0020
	Public Const STCAM_OUT_PIN_MODE_STROBE_OUTPUT_EXPOSURE As System.UInt32 = &H0021
	Public Const STCAM_OUT_PIN_MODE_TRIGGER_VALID_OUT As System.UInt32 = &H0014
	Public Const STCAM_IN_PIN_MODE_DISABLE As System.UInt32 = &H0000
	Public Const STCAM_IN_PIN_MODE_GENERAL_INPUT As System.UInt32 = &H0001
	Public Const STCAM_IN_PIN_MODE_TRIGGER_INPUT As System.UInt32 = &H0010
	Public Const STCAM_IN_PIN_MODE_READOUT_INPUT As System.UInt32 = &H0030
	Public Const STCAM_IN_PIN_MODE_SUB_TRIGGER_INPUT As System.UInt32 = &H0040
	'------------------------------------------------------------------------------
	'TIMEOUT
	'------------------------------------------------------------------------------
	Public Const STCAM_TIMEOUT_ST2EE As System.UInt32 = &H00000000UI
	Public Const STCAM_TIMEOUT_TE2EE As System.UInt32 = &H00000001UI
	Public Const STCAM_TIMEOUT_EE2TE As System.UInt32 = &H00000002UI
	Public Const STCAM_TIMEOUT_RO2TE As System.UInt32 = &H00000003UI
	'------------------------------------------------------------------------------
	'CAMERA_FUNCTION
	'------------------------------------------------------------------------------
	Public Const STCAM_CAMERA_FUNCTION_VGA90FPS As System.UInt32 = 0
	Public Const STCAM_CAMERA_FUNCTION_STARTSTOP As System.UInt32 = 1
	Public Const STCAM_CAMERA_FUNCTION_MEMORY As System.UInt32 = 2
	Public Const STCAM_CAMERA_FUNCTION_IO_CHANGE_DIRECTION As System.UInt32 = 4
	Public Const STCAM_CAMERA_FUNCTION_LED As System.UInt32 = 5
	Public Const STCAM_CAMERA_FUNCTION_DISABLE_DIP_SW As System.UInt32 = 7
	Public Const STCAM_CAMERA_FUNCTION_10BIT As System.UInt32 = 8
	Public Const STCAM_CAMERA_FUNCTION_12BIT As System.UInt32 = 15
	Public Const STCAM_CAMERA_FUNCTION_CDS_GAIN_TYPE As System.UInt32 = 16
	Public Const STCAM_CAMERA_FUNCTION_PHOTOCOUPLER As System.UInt32 = 17
	Public Const STCAM_CAMERA_FUNCTION_TRIGGER_MASK As System.UInt32 = 18
	Public Const STCAM_CAMERA_FUNCTION_V_BLANK_FOR_FPS As System.UInt32 = 21
	Public Const STCAM_CAMERA_FUNCTION_MIRROR_HORIZONTAL As System.UInt32 = 22
	Public Const STCAM_CAMERA_FUNCTION_MIRROR_VERTICAL As System.UInt32 = 23
	Public Const STCAM_CAMERA_FUNCTION_AWB As System.UInt32 = 24
	Public Const STCAM_CAMERA_FUNCTION_AGC As System.UInt32 = 25
	Public Const STCAM_CAMERA_FUNCTION_AE As System.UInt32 = 26
	Public Const STCAM_CAMERA_FUNCTION_IO_UNIT_US As System.UInt32 = 27
	Public Const STCAM_CAMERA_FUNCTION_CMOS_RESET_TYPE_0 As System.UInt32 = 28
	Public Const STCAM_CAMERA_FUNCTION_CMOS_RESET_TYPE_ERS_GRR As System.UInt32 = 28
	Public Const STCAM_CAMERA_FUNCTION_DISABLED_READOUT As System.UInt32 = 29
	Public Const STCAM_CAMERA_FUNCTION_DIGITAL_CLAMP As System.UInt32 = 55
	Public Const STCAM_CAMERA_FUNCTION_TRIGGER_VALID_OUT As System.UInt32 = 56
	Public Const STCAM_CAMERA_FUNCTION_CAMERA_GAMMA As System.UInt32 = 57
	Public Const STCAM_CAMERA_FUNCTION_STORE_CAMERA_SETTING As System.UInt32 = 58
	Public Const STCAM_CAMERA_FUNCTION_DEFECT_PIXEL_CORRECTION As System.UInt32 = 59
	Public Const STCAM_CAMERA_FUNCTION_DISABLE_MEMORY_TYPE_SELECTION As System.UInt32 = 60
	Public Const STCAM_CAMERA_FUNCTION_BINNING_COLUMN_SUM As System.UInt32 = 61
	Public Const STCAM_CAMERA_FUNCTION_H_BINNING_SUM As System.UInt32 = 61
	Public Const STCAM_CAMERA_FUNCTION_DISABLE_EXPOSURE_START_WAIT_HD As System.UInt32 = 62
	Public Const STCAM_CAMERA_FUNCTION_DISABLE_EXPOSURE_START_WAIT_READ_OUT As System.UInt32 = 63
	Public Const STCAM_CAMERA_FUNCTION_DISABLE_PULSE_WIDTH_EXPOSURE As System.UInt32 = 69
	Public Const STCAM_CAMERA_FUNCTION_CMOS_RESET_TYPE_1 As System.UInt32 = 72
	Public Const STCAM_CAMERA_FUNCTION_V_BINNING_SUM As System.UInt32 = 131
	Public Const STCAM_CAMERA_FUNCTION_TRIGGER As System.UInt32 = 256
	Public Const STCAM_CAMERA_FUNCTION_DIGITAL_GAIN As System.UInt32 = 257
	Public Const STCAM_CAMERA_FUNCTION_VARIABLE_PARTIAL As System.UInt32 = 258
	Public Const STCAM_CAMERA_FUNCTION_BINNING_PARTIAL As System.UInt32 = 259
	Public Const STCAM_CAMERA_FUNCTION_IO As System.UInt32 = 260
	Public Const STCAM_CAMERA_FUNCTION_RESET_FRAME_COUNTER As System.UInt32 = 261
	'------------------------------------------------------------------------------
	'NOISE_REDUCTION
	'------------------------------------------------------------------------------
	Public Const STCAM_NR_OFF As System.UInt32 = &H00000000UI
	Public Const STCAM_NR_EASY As System.UInt32 = &H00000001UI
	Public Const STCAM_NR_COMPREX As System.UInt32 = &H00000002UI
	Public Const STCAM_NR_DARK_CL As System.UInt32 = &H80000000UI
	'------------------------------------------------------------------------------
	'LED_STATUS
	'------------------------------------------------------------------------------
	Public Const STCAM_LED_GREEN_ON As System.UInt32 = &H00000001UI
	Public Const STCAM_LED_RED_ON As System.UInt32 = &H00000002UI
	'------------------------------------------------------------------------------
	'TRANSFER_BITS_PER_PIXEL
	'------------------------------------------------------------------------------
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_08 As System.UInt32 = &H00000001UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_10 As System.UInt32 = &H00000002UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_12 As System.UInt32 = &H00000004UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_08 As System.UInt32 = &H00000001UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_10 As System.UInt32 = &H00000002UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_12 As System.UInt32 = &H00000004UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_14 As System.UInt32 = &H00000008UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_16 As System.UInt32 = &H00000010UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_08 As System.UInt32 = &H00000020UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_10 As System.UInt32 = &H00000040UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_12 As System.UInt32 = &H00000080UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_14 As System.UInt32 = &H00000100UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_16 As System.UInt32 = &H00000200UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_BGR_08 As System.UInt32 = &H00000400UI
	Public Const STCAM_TRANSFER_BITS_PER_PIXEL_BGR_10 As System.UInt32 = &H00000800UI
	'------------------------------------------------------------------------------
	'JBA_REG_ADDRESS
	'------------------------------------------------------------------------------
	Public Const JBA_REG_ADD_HDR_MODE As System.UInt32 = &H03
	Public Const JBA_REG_ADD_T2_RATIO As System.UInt32 = &H04
	Public Const JBA_REG_ADD_T3_RATIO As System.UInt32 = &H05
	Public Const JBA_REG_ADD_V1_STEP As System.UInt32 = &H06
	Public Const JBA_REG_ADD_V2_STEP As System.UInt32 = &H07
	Public Const JBA_REG_ADD_V3_STEP As System.UInt32 = &H08
	Public Const JBA_REG_ADD_ADC_MODE As System.UInt32 = &H1F
	Public Const JBA_REG_ADD_LED1 As System.UInt32 = &H20
	Public Const JBA_REG_ADD_LED2 As System.UInt32 = &H21
	'------------------------------------------------------------------------------
	'CAMERA_SETTING
	'------------------------------------------------------------------------------
	Public Const STCAM_CAMERA_SETTING_INITIALIZE As System.UInt16 = &H8000
	Public Const STCAM_CAMERA_SETTING_WRITE As System.UInt16 = &H2000
	Public Const STCAM_CAMERA_SETTING_READ As System.UInt16 = &H1000
	Public Const STCAM_CAMERA_SETTING_STANDARD As System.UInt16 = &H0800
	Public Const STCAM_CAMERA_SETTING_DEFECT_PIXEL_POSITION As System.UInt16 = &H0400
End Class

