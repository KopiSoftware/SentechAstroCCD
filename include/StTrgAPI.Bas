'Created Date:2013/08/09 17:05
Attribute VB_Name = "mdlStTrgAPI"
Option Explicit

'------------------------------------------------------------------------------
'Initialize
'------------------------------------------------------------------------------
Public Declare Function StTrg_Open Lib "StTrgAPI.dll" () As Long
Public Declare Sub StTrg_Close Lib "StTrgAPI.dll" (ByVal hCamera As Long)

'------------------------------------------------------------------------------
'Camera Information
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetDllVersion Lib "StTrgAPI.dll" (ByRef pdwFileVersionMS As Long, ByRef pdwFileVersionLS As Long, ByRef pdwProductVersionMS As Long, ByRef pdwProductVersionLS As Long) As Long
Public Declare Function StTrg_GetCameraVersion Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwUSBVendorID As Integer, ByRef pwUSBProductID As Integer, ByRef pwFPGAVersion As Integer, ByRef pwFirmVersion As Integer) As Long
Public Declare Function StTrg_GetProductNameA Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal pszProductName As String, ByVal dwBufferSize As Long) As Long
Public Declare Function StTrg_GetColorArray Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwColorArray As Integer) As Long
Public Declare Function StTrg_HasFunction Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwCameraFunctionID As Long, ByRef pbHasFunction As Long) As Long
Public Declare Function StTrg_ReadUserMemory Lib "StTrgAPI.dll" (ByVal hCamera As Long,  pbyteData As Byte, ByVal wOffset As Integer, ByVal wLength As Integer) As Long
Public Declare Function StTrg_WriteUserMemory Lib "StTrgAPI.dll" (ByVal hCamera As Long,  pbyteData As Byte, ByVal wOffset As Integer, ByVal wLength As Integer) As Long
Public Declare Function StTrg_ReadCameraUserIDA Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwCameraID As Long, ByVal pszCameraName As String, ByVal dwBufferSize As Long) As Long
Public Declare Function StTrg_WriteCameraUserIDA Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwCameraID As Long, ByVal pszCameraName As String, ByVal dwBufferSize As Long) As Long
Public Declare Function StTrg_ResetCounter Lib "StTrgAPI.dll" (ByVal hCamera As Long) As Long

'------------------------------------------------------------------------------
'Setting
'------------------------------------------------------------------------------
Public Declare Function StTrg_WriteSettingFileA Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal pszFileName As String) As Long
Public Declare Function StTrg_ReadSettingFileA Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal pszFileName As String) As Long
Public Declare Function StTrg_CameraSetting Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wMode As Integer) As Long

'------------------------------------------------------------------------------
'Image Information
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetEnableScanMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwEnableScanMode As Integer) As Long
Public Declare Function StTrg_GetMaximumImageSize Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwMaximumImageWidth As Long, ByRef pdwMaximumImageHeight As Long) As Long
Public Declare Function StTrg_GetScanMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwScanMode As Integer, ByRef pdwOffsetX As Long, ByRef pdwOffsetY As Long, ByRef pdwWidth As Long, ByRef pdwHeight As Long) As Long
Public Declare Function StTrg_SetScanMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wScanMode As Integer, ByVal dwOffsetX As Long, ByVal dwOffsetY As Long, ByVal dwWidth As Long, ByVal dwHeight As Long) As Long
Public Declare Function StTrg_GetEnableTransferBitsPerPixel Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwEnableTransferBitsPerPixel As Long) As Long
Public Declare Function StTrg_GetTransferBitsPerPixel Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwTransferBitsPerPixel As Long) As Long
Public Declare Function StTrg_SetTransferBitsPerPixel Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwTransferBitsPerPixel As Long) As Long
Public Declare Function StTrg_GetSkippingAndBinning Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pbyteHSkipping As Byte, ByRef pbyteVSkipping As Byte, ByRef pbyteHBinning As Byte, ByRef pbyteVBinning As Byte) As Long
Public Declare Function StTrg_SetSkippingAndBinning Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteHSkipping As Byte, ByVal byteVSkipping As Byte, ByVal byteHBinning As Byte, ByVal byteVBinning As Byte) As Long
Public Declare Function StTrg_GetBinningSumMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwValue As Integer) As Long
Public Declare Function StTrg_SetBinningSumMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wValue As Integer) As Long
Public Declare Function StTrg_ConvTo8BitsImage Lib "StTrgAPI.dll" (ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwTransferBitsPerPixel As Long,  pwRaw As Integer,  pbyteRaw As Byte) As Long
Public Declare Function StTrg_ConvYUVOrBGRToBGRImage Lib "StTrgAPI.dll" (ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwTransferBitsPerPixel As Long,  pbyteYUVOrBGR As Byte, ByVal dwPixelFormat As Long,  pbyteBGR As Byte) As Long

'------------------------------------------------------------------------------
'Clock
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetOutputFPS Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pfFPS As Single) As Long
Public Declare Function StTrg_GetClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwClockMode As Long, ByRef pdwClock As Long) As Long
Public Declare Function StTrg_SetClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwClockMode As Long, ByVal dwClock As Long) As Long
Public Declare Function StTrg_GetEnableClockMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwClockMode As Long) As Long
Public Declare Function StTrg_GetVBlankForFPS Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwVLines As Long) As Long
Public Declare Function StTrg_SetVBlankForFPS Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwVLines As Long) As Long
Public Declare Function StTrg_GetMaxVBlankForFPS Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwVLines As Long) As Long
Public Declare Function StTrg_GetFrameClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwTotalLine As Integer, ByRef pwTotalHClock As Integer) As Long

'------------------------------------------------------------------------------
'Shutter Gain Control
'------------------------------------------------------------------------------
Public Declare Function StTrg_SetGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wGain As Integer) As Long
Public Declare Function StTrg_GetGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwGain As Integer) As Long
Public Declare Function StTrg_GetMaxGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwMaxGain As Integer) As Long
Public Declare Function StTrg_GetGainDBFromSettingValue Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wGain As Integer, ByRef pfGaindB As Single) As Long
Public Declare Function StTrg_GetExposureClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwExposureValue As Long) As Long
Public Declare Function StTrg_SetExposureClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwExposureValue As Long) As Long
Public Declare Function StTrg_GetMaxShortExposureClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwMaximumExposureClock As Long) As Long
Public Declare Function StTrg_GetMaxLongExposureClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwMaximumExposureClock As Long) As Long
Public Declare Function StTrg_GetExposureClockFromTime Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal fExpTime As Single, ByRef pdwExposureClock As Long) As Long
Public Declare Function StTrg_GetExposureTimeFromClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwExposureClock As Long, ByRef pfExpTime As Single) As Long
Public Declare Function StTrg_SetDigitalGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wDigitalGain As Integer) As Long
Public Declare Function StTrg_GetDigitalGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwDigitalGain As Integer) As Long
Public Declare Function StTrg_ALC Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wCurrentBrightness As Integer, ByRef pdwALCStatus As Long) As Long
Public Declare Function StTrg_GetAveragePixelValue Lib "StTrgAPI.dll" (ByVal dwImageWidth As Long, ByVal dwImageHeight As Long, ByVal wColorArray As Integer, ByVal dwTransferBitsPerPixel As Long,  pbyteRaw As Byte, ByVal dwAOIOffsetX As Long, ByVal dwAOIOffsetY As Long, ByVal dwAOIWidth As Long, ByVal dwAOIHeight As Long,  pfAverage As Single) As Long
Public Declare Function StTrg_SetALCMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteALCMode As Byte) As Long
Public Declare Function StTrg_GetALCMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pbyteALCMode As Byte) As Long
Public Declare Function StTrg_SetALCTargetLevel Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wLevel As Integer) As Long
Public Declare Function StTrg_GetALCTargetLevel Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwLevel As Integer) As Long
Public Declare Function StTrg_GetAGCMinGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwMinGain As Integer) As Long
Public Declare Function StTrg_SetAGCMinGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wMinGain As Integer) As Long
Public Declare Function StTrg_GetAGCMaxGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwMaxGain As Integer) As Long
Public Declare Function StTrg_SetAGCMaxGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wMaxGain As Integer) As Long
Public Declare Function StTrg_GetAEMinExposureClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwMinExposureClock As Long) As Long
Public Declare Function StTrg_SetAEMinExposureClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwMinExposureClock As Long) As Long
Public Declare Function StTrg_GetAEMaxExposureClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwMaxExposureClock As Long) As Long
Public Declare Function StTrg_SetAEMaxExposureClock Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwMaxExposureClock As Long) As Long

'------------------------------------------------------------------------------
'Trigger
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetTriggerMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwTriggerMode As Long) As Long
Public Declare Function StTrg_SetTriggerMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwTriggerMode As Long) As Long
Public Declare Function StTrg_GetTriggerTiming Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwTriggerTimingType As Long, ByRef pdwValue As Long) As Long
Public Declare Function StTrg_SetTriggerTiming Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwTriggerTimingType As Long, ByVal dwValue As Long) As Long
Public Declare Function StTrg_SoftTrigger Lib "StTrgAPI.dll" (ByVal hCamera As Long) As Long
Public Declare Function StTrg_SoftSubTrigger Lib "StTrgAPI.dll" (ByVal hCamera As Long) As Long
Public Declare Function StTrg_TriggerReadOut Lib "StTrgAPI.dll" (ByVal hCamera As Long) As Long

'------------------------------------------------------------------------------
'IOPin
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetIOPinDirection Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwDirection As Long) As Long
Public Declare Function StTrg_SetIOPinDirection Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwDirection As Long) As Long
Public Declare Function StTrg_GetIOPinPolarity Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwPolarity As Long) As Long
Public Declare Function StTrg_SetIOPinPolarity Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwPolarity As Long) As Long
Public Declare Function StTrg_GetIOPinMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal bytePinNo As Byte, ByRef pdwMode As Long) As Long
Public Declare Function StTrg_SetIOPinMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal bytePinNo As Byte, ByVal dwMode As Long) As Long
Public Declare Function StTrg_GetIOPinStatus Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwStatus As Long) As Long
Public Declare Function StTrg_SetIOPinStatus Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwStatus As Long) As Long
Public Declare Function StTrg_GetSwStatus Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwSwStatus As Long) As Long
Public Declare Function StTrg_GetLEDStatus Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pdwLEDStatus As Long) As Long
Public Declare Function StTrg_SetLEDStatus Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwLEDStatus As Long) As Long

'------------------------------------------------------------------------------
'Timeout
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetTimeOut Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwTimeOutType As Long, ByRef pdwTimeOutMS As Long) As Long
Public Declare Function StTrg_SetTimeOut Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwTimeOutType As Long, ByVal dwTimeOutMS As Long) As Long

'------------------------------------------------------------------------------
'Image Acquisition
'------------------------------------------------------------------------------
Public Declare Function StTrg_SetRcvMsgWnd Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal hWnd As Long) As Long
Public Declare Function StTrg_SetRawSnapShotBufferCount Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwBufferCount As Long) As Long
Public Declare Function StTrg_TakeRawSnapShot Lib "StTrgAPI.dll" (ByVal hCamera As Long,  pbyteRaw As Byte, ByVal dwBufferSize As Long, ByRef pdwNumberOfByteTrans As Long, ByRef pdwFrameNo As Long, ByVal dwMilliseconds As Long) As Long

'------------------------------------------------------------------------------
'Transfer Control
'------------------------------------------------------------------------------
Public Declare Function StTrg_StartTransfer Lib "StTrgAPI.dll" (ByVal hCamera As Long) As Long
Public Declare Function StTrg_StopTransfer Lib "StTrgAPI.dll" (ByVal hCamera As Long) As Long

'------------------------------------------------------------------------------
'Noise Reduction
'------------------------------------------------------------------------------
Public Declare Function StTrg_NoiseReduction2 Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwNoiseReductionMode As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal wColorArray As Integer,  pbyteRaw As Byte, ByVal wRawBitsPerPixel As Integer) As Long
Public Declare Function StTrg_NoiseReduction Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwNoiseReductionMode As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal wColorArray As Integer,  pbyteRaw As Byte) As Long

'------------------------------------------------------------------------------
'White Balance Control
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetWhiteBalanceMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pbyteWBMode As Byte) As Long
Public Declare Function StTrg_SetWhiteBalanceMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteWBMode As Byte) As Long
Public Declare Function StTrg_GetWhiteBalanceGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwWBGainR As Integer, ByRef pwWBGainGr As Integer, ByRef pwWBGainGb As Integer, ByRef pwWBGainB As Integer) As Long
Public Declare Function StTrg_SetWhiteBalanceGain Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wWBGainR As Integer, ByVal wWBGainGr As Integer, ByVal wWBGainGb As Integer, ByVal wWBGainB As Integer) As Long
Public Declare Function StTrg_WhiteBalance2 Lib "StTrgAPI.dll" (ByVal hCamera As Long,  pwRaw As Integer, ByVal wRawBitsPerPixel As Integer) As Long
Public Declare Function StTrg_WhiteBalance Lib "StTrgAPI.dll" (ByVal hCamera As Long,  pbyteRaw As Byte) As Long

'------------------------------------------------------------------------------
'Gamma
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetGammaModeEx Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteGammaTarget As Byte, ByRef pbyteGammaMode As Byte, ByRef pwGamma As Integer, ByRef pshtBrightness As Integer, ByRef pbyteContrast As Byte,  pbyteGammaTable As Byte) As Long
Public Declare Function StTrg_SetGammaModeEx Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteGammaTarget As Byte, ByVal byteGammaMode As Byte, ByVal wGamma As Integer, ByVal shtBrightness As Integer, ByVal byteContrast As Byte,  pbyteGammaTable As Byte) As Long
Public Declare Function StTrg_RawColorGamma Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal wColorArray As Integer,  pbyteRaw As Byte) As Long
Public Declare Function StTrg_BGRGamma Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwPixelFormat As Long,  pbyteBGR As Byte) As Long
Public Declare Function StTrg_GetGammaModeEx2 Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteGammaTarget As Byte, ByRef pbyteGammaMode As Byte, ByRef pwGamma As Integer, ByRef pshtBrightness As Integer, ByRef pwContrast As Integer,  pwGammaTable As Integer, ByRef pwBitsPerEachColor As Integer) As Long
Public Declare Function StTrg_SetGammaModeEx2 Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteGammaTarget As Byte, ByVal byteGammaMode As Byte, ByVal wGamma As Integer, ByVal shtBrightness As Integer, ByVal wContrast As Integer,  pwGammaTable As Integer, ByVal wBitsPerEachColor As Integer) As Long
Public Declare Function StTrg_RawColorGamma2 Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal wColorArray As Integer,  pbyteRaw As Byte, ByVal wRawBitsPerPixel As Integer) As Long
Public Declare Function StTrg_BGRGamma2 Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwPixelFormat As Long,  pbyteBGR As Byte, ByVal wBitsPerEachColor As Integer) As Long
Public Declare Function StTrg_GetCameraGammaValue Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwValue As Integer) As Long
Public Declare Function StTrg_SetCameraGammaValue Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wValue As Integer) As Long

'------------------------------------------------------------------------------
'Mirror Rotation
'------------------------------------------------------------------------------
Public Declare Function StTrg_MirrorRotation Lib "StTrgAPI.dll" (ByVal byteMirrorMode As Byte, ByVal byteRotationMode As Byte, ByRef pdwWidth As Long, ByRef pdwHeight As Long, ByRef pwColorArray As Integer,  pbyteRaw As Byte) As Long
Public Declare Function StTrg_GetMirrorMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pbyteMirrorMode As Byte) As Long
Public Declare Function StTrg_SetMirrorMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteMirrorMode As Byte) As Long

'------------------------------------------------------------------------------
'Color Interpolation
'------------------------------------------------------------------------------
Public Declare Function StTrg_ColorInterpolation2 Lib "StTrgAPI.dll" (ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal wColorArray As Integer,  pwRaw As Integer,  pwBGR As Integer, ByVal byteColorInterpolationMethod As Byte, ByVal dwPixelFormat As Long, ByVal wRawBitsPerPixel As Integer) As Long
Public Declare Function StTrg_ColorInterpolation Lib "StTrgAPI.dll" (ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal wColorArray As Integer,  pbyteRaw As Byte,  pbyteBGR As Byte, ByVal byteColorInterpolationMethod As Byte, ByVal dwPixelFormat As Long) As Long

'------------------------------------------------------------------------------
'Hue Saturation/Color Matrix
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetHueSaturationMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pbyteHueSaturationMode As Byte, ByRef pshtHue As Integer, ByRef pwSaturation As Integer) As Long
Public Declare Function StTrg_SetHueSaturationMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteHueSaturationMode As Byte, ByVal shtHue As Integer, ByVal wSaturation As Integer) As Long
Public Declare Function StTrg_GetColorMatrix Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pbyteColorMatrixMode As Byte, ByVal pshtColorMatrix As Integer) As Long
Public Declare Function StTrg_SetColorMatrix Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteColorMatrixMode As Byte, ByVal pshtColorMatrix As Integer) As Long
Public Declare Function StTrg_HueSaturationColorMatrix Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwPixelFormat As Long,  pbyteBGR As Byte) As Long
Public Declare Function StTrg_HueSaturationColorMatrix2 Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwPixelFormat As Long,  pbyteBGR As Byte, ByVal wBitsPerEachColor As Integer) As Long

'------------------------------------------------------------------------------
'Sharpness
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetSharpnessMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pbyteSharpnessMode As Byte, ByRef pwSharpnessGain As Integer, ByRef pbyteSharpnessCoring As Byte) As Long
Public Declare Function StTrg_SetSharpnessMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal byteSharpnessMode As Byte, ByVal wSharpnessGain As Integer, ByVal byteSharpnessCoring As Byte) As Long
Public Declare Function StTrg_Sharpness2 Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwPixelFormat As Long,  pbyteGrayOrBGR As Byte, ByVal wBitsPerEachColor As Integer) As Long
Public Declare Function StTrg_Sharpness Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwPixelFormat As Long,  pbyteGrayOrBGR As Byte) As Long

'------------------------------------------------------------------------------
'Save Image
'------------------------------------------------------------------------------
Public Declare Function StTrg_SaveImageA Lib "StTrgAPI.dll" (ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwPixelFormat As Long,  pbyteGrayOrBGR As Byte, ByVal pszFileName As String, ByVal dwParam As Long) As Long

'------------------------------------------------------------------------------
'Defect Pixel Correction
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetEnableDefectPixelCorrectionCount Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwCount As Integer) As Long
Public Declare Function StTrg_GetDefectPixelCorrectionMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwMode As Integer) As Long
Public Declare Function StTrg_SetDefectPixelCorrectionMode Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wMode As Integer) As Long
Public Declare Function StTrg_GetDefectPixelCorrectionPosition Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wIndex As Integer, ByRef pdwX As Long, ByRef pdwY As Long) As Long
Public Declare Function StTrg_SetDefectPixelCorrectionPosition Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wIndex As Integer, ByVal dwX As Long, ByVal dwY As Long) As Long
Public Declare Function StTrg_DetectDefectPixel Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwWidth As Long, ByVal dwHeight As Long,  pbyteRaw As Byte, ByVal wThreashold As Integer) As Long

'------------------------------------------------------------------------------
'Preview
'------------------------------------------------------------------------------
Public Declare Function StTrg_Draw Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal hDC As Long, ByVal DestOffsetX As Long, ByVal DestOffsetY As Long, ByVal dwDestWidth As Long, ByVal dwDestHeight As Long, ByVal SrcOffsetX As Long, ByVal SrcOffsetY As Long, ByVal dwSrcWidth As Long, ByVal dwSrcHeight As Long, ByVal dwOrgWidth As Long, ByVal dwOrgHeight As Long,  pbyteGrayOrBGR As Byte, ByVal dwPixelFormat As Long) As Long

'------------------------------------------------------------------------------
'For Specific Camera
'------------------------------------------------------------------------------
Public Declare Function StTrg_GetIOARegister Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwStartAdd As Long, ByVal dwEndAdd As Long,  pwValue As Integer) As Long
Public Declare Function StTrg_SetIOARegister Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwStartAdd As Long, ByVal dwEndAdd As Long,  pwValue As Integer) As Long
Public Declare Function StTrg_GetITARegister Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwStartAdd As Long, ByVal dwEndAdd As Long,  pwValue As Integer) As Long
Public Declare Function StTrg_SetITARegister Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwStartAdd As Long, ByVal dwEndAdd As Long,  pwValue As Integer) As Long
Public Declare Function StTrg_GetJBARegister Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwStartAdd As Long, ByVal dwEndAdd As Long,  pwValue As Integer) As Long
Public Declare Function StTrg_SetJBARegister Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal dwStartAdd As Long, ByVal dwEndAdd As Long,  pwValue As Integer) As Long

'------------------------------------------------------------------------------
'Other
'------------------------------------------------------------------------------
Public Declare Function StTrg_ResetRootHub Lib "StTrgAPI.dll" () As Long
Public Declare Function StTrg_SetProcessorIdleState Lib "StTrgAPI.dll" (ByVal dwAC As Long, ByVal dwDC As Long) As Long
Public Declare Function StTrg_GetProcessorIdleState Lib "StTrgAPI.dll" (ByRef pdwAC As Long, ByRef pdwDC As Long) As Long
Public Declare Function StTrg_SetDigitalClamp Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByVal wValue As Integer) As Long
Public Declare Function StTrg_GetDigitalClamp Lib "StTrgAPI.dll" (ByVal hCamera As Long, ByRef pwValue As Integer) As Long
Public Declare Function StTrg_ClearBuffer Lib "StTrgAPI.dll" (ByVal hCamera As Long) As Long
'------------------------------------------------------------------------------
'For 16bits raw image
'------------------------------------------------------------------------------
Public Declare Function StTrg_TakeRawSnapShot_W Lib "StTrgAPI.dll" Alias "StTrg_TakeRawSnapShot" (ByVal hCamera As Long, ByRef pbyteRaw As Integer, ByVal dwBufferSize As Long, ByRef pdwNumberOfByteTrans As Long, ByRef pdwFrameNo As Long, ByVal dwMilliseconds As Long) As Long
Public Declare Function StTrg_SaveImageA_W Lib "StTrgAPI.dll" Alias "StTrg_SaveImageA" (ByVal dwWidth As Long, ByVal dwHeight As Long, ByVal dwPixelFormat As Long, ByRef pbyteGrayOrBGR As Integer, ByVal pszFileName As String, ByVal dwParam As Long) As Long
'------------------------------------------------------------------------------
'BINNING_SUM_MODE
'------------------------------------------------------------------------------
Public Const STCAM_BINNING_SUM_MODE_OFF As Integer = &H0000
'------------------------------------------------------------------------------
'DEFECT_PIXEL_CORRECTION_MODE
'------------------------------------------------------------------------------
Public Const STCAM_DEFECT_PIXEL_CORRECTION_OFF As Integer = &H0000
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
Public Const STCAM_BINNING_SUM_MODE_H As Integer = &H0001
'------------------------------------------------------------------------------
'DEFECT_PIXEL_CORRECTION_MODE
'------------------------------------------------------------------------------
Public Const STCAM_DEFECT_PIXEL_CORRECTION_ON As Integer = &H0001
'------------------------------------------------------------------------------
'BINNING_SUM_MODE
'------------------------------------------------------------------------------
Public Const STCAM_BINNING_SUM_MODE_V As Integer = &H0100
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
Public Const ERR_EXPOSURE_END_DROPPED As Long = &HE0000001&
Public Const ERR_IMAGE_DATA_DROPPED As Long = &HE0000002&
Public Const ERR_TIMEOUT_ST2EE As Long = &HE0000003&
Public Const ERR_TIMEOUT_TE2EE As Long = &HE0000004&
Public Const ERR_TIMEOUT_EE2TE As Long = &HE0000005&
Public Const ERR_TIMEOUT_RO2TE As Long = &HE0000006&
Public Const ERR_INVALID_FUNCTION_WHILE_TRANSFERRING As Long = &HE0000100&
'------------------------------------------------------------------------------
'WM_STCAM
'------------------------------------------------------------------------------
Public Const WM_STCAM_TRANSFER_END As Long = &HB101&
Public Const WM_STCAM_EXPOSURE_END As Long = &HB102&
Public Const WM_STCAM_RCV_ERROR As Long = &HB103&
'------------------------------------------------------------------------------
'COLOR_ARRAY
'------------------------------------------------------------------------------
Public Const STCAM_COLOR_ARRAY_MONO As Integer = &H0001
Public Const STCAM_COLOR_ARRAY_RGGB As Integer = &H0002
Public Const STCAM_COLOR_ARRAY_GRBG As Integer = &H0003
Public Const STCAM_COLOR_ARRAY_GBRG As Integer = &H0004
Public Const STCAM_COLOR_ARRAY_BGGR As Integer = &H0005
'------------------------------------------------------------------------------
'SCAN_MODE
'------------------------------------------------------------------------------
Public Const STCAM_SCAN_MODE_NORMAL As Integer = &H0000
Public Const STCAM_SCAN_MODE_PARTIAL_2 As Integer = &H0001
Public Const STCAM_SCAN_MODE_PARTIAL_4 As Integer = &H0002
Public Const STCAM_SCAN_MODE_PARTIAL_1 As Integer = &H0004
Public Const STCAM_SCAN_MODE_VARIABLE_PARTIAL As Integer = &H0008
Public Const STCAM_SCAN_MODE_BINNING As Integer = &H0010
Public Const STCAM_SCAN_MODE_BINNING_PARTIAL_1 As Integer = &H0020
Public Const STCAM_SCAN_MODE_BINNING_PARTIAL_2 As Integer = &H0040
Public Const STCAM_SCAN_MODE_BINNING_PARTIAL_4 As Integer = &H0080
Public Const STCAM_SCAN_MODE_BINNING_VARIABLE_PARTIAL As Integer = &H0100
Public Const STCAM_SCAN_MODE_AOI As Integer = &H8000
'------------------------------------------------------------------------------
'PIXEL_FORMAT
'------------------------------------------------------------------------------
Public Const STCAM_PIXEL_FORMAT_08_MONO_OR_RAW As Long = &H00000001&
Public Const STCAM_PIXEL_FORMAT_24_BGR As Long = &H00000004&
Public Const STCAM_PIXEL_FORMAT_32_BGR As Long = &H00000008&
'------------------------------------------------------------------------------
'PIXEL_FORMAT_FOR_SAVE
'------------------------------------------------------------------------------
Public Const STCAM_PIXEL_FORMAT_10_MONO_OR_RAW As Long = &H00000010&
'------------------------------------------------------------------------------
'PIXEL_FORMAT
'------------------------------------------------------------------------------
Public Const STCAM_PIXEL_FORMAT_48_BGR As Long = &H00000100&
'------------------------------------------------------------------------------
'PIXEL_FORMAT_FOR_SAVE
'------------------------------------------------------------------------------
Public Const STCAM_PIXEL_FORMAT_12_MONO_OR_RAW As Long = &H00000020&
'------------------------------------------------------------------------------
'PIXEL_FORMAT
'------------------------------------------------------------------------------
Public Const STCAM_PIXEL_FORMAT_64_BGR As Long = &H00000200&
'------------------------------------------------------------------------------
'PIXEL_FORMAT_FOR_SAVE
'------------------------------------------------------------------------------
Public Const STCAM_PIXEL_FORMAT_16_MONO_OR_RAW As Long = &H00000002&
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
Public Const STCAM_CLOCK_MODE_NORMAL As Long = &H00000000&
Public Const STCAM_CLOCK_MODE_DIV_2 As Long = &H00000001&
Public Const STCAM_CLOCK_MODE_DIV_4 As Long = &H00000002&
Public Const STCAM_CLOCK_MODE_VGA_90FPS As Long = &H00000100&
'------------------------------------------------------------------------------
'USBPID
'------------------------------------------------------------------------------
Public Const STCAM_USBPID_STC_B33USB As Integer = &H0705
Public Const STCAM_USBPID_STC_C33USB As Integer = &H0305
Public Const STCAM_USBPID_STC_B83USB As Integer = &H0805
Public Const STCAM_USBPID_STC_C83USB As Integer = &H0605
Public Const STCAM_USBPID_STC_TB33USB As Integer = &H0906
Public Const STCAM_USBPID_STC_TC33USB As Integer = &H1006
Public Const STCAM_USBPID_STC_TB83USB As Integer = &H1106
Public Const STCAM_USBPID_STC_TC83USB As Integer = &H1206
Public Const STCAM_USBPID_STC_TB133USB As Integer = &H0109
Public Const STCAM_USBPID_STC_TC133USB As Integer = &H0209
Public Const STCAM_USBPID_STC_TB152USB As Integer = &H1306
Public Const STCAM_USBPID_STC_TC152USB As Integer = &H1406
Public Const STCAM_USBPID_STC_TB202USB As Integer = &H1506
Public Const STCAM_USBPID_STC_TC202USB As Integer = &H1606
Public Const STCAM_USBPID_STC_MB33USB As Integer = &H0110
Public Const STCAM_USBPID_STC_MC33USB As Integer = &H0210
Public Const STCAM_USBPID_STC_MB83USB As Integer = &H0310
Public Const STCAM_USBPID_STC_MC83USB As Integer = &H0410
Public Const STCAM_USBPID_STC_MB133USB As Integer = &H0510
Public Const STCAM_USBPID_STC_MC133USB As Integer = &H0610
Public Const STCAM_USBPID_STC_MB152USB As Integer = &H0710
Public Const STCAM_USBPID_STC_MC152USB As Integer = &H0810
Public Const STCAM_USBPID_STC_MB202USB As Integer = &H0910
Public Const STCAM_USBPID_STC_MC202USB As Integer = &H1010
Public Const STCAM_USBPID_APBWVUSB_LED As Integer = &H0509
Public Const STCAM_USBPID_APCWVUSB_LED As Integer = &H0609
Public Const STCAM_USBPID_STC_MBA5MUSB3 As Integer = &H0111
Public Const STCAM_USBPID_STC_MCA5MUSB3 As Integer = &H0211
Public Const STCAM_USBPID_STC_MBE132U3V As Integer = &H0112
Public Const STCAM_USBPID_STC_MCE132U3V As Integer = &H0212
'------------------------------------------------------------------------------
'TRIGGER_MODE
'------------------------------------------------------------------------------
Public Const STCAM_TRIGGER_MODE_TYPE_MASK As Long = &H00000003&
Public Const STCAM_TRIGGER_MODE_CAMERA_MEMORY_MASK As Long = &H00000030&
Public Const STCAM_TRIGGER_MODE_READOUT_SOURCE_MASK As Long = &H00000040&
Public Const STCAM_TRIGGER_MODE_EXPEND_MASK As Long = &H00000100&
Public Const STCAM_TRIGGER_MODE_SOURCE_MASK As Long = &H00000C00&
Public Const STCAM_TRIGGER_MODE_EXPTIME_MASK As Long = &H00003000&
Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_MASK As Long = &H00004000&
Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_MASK As Long = &H00008000&
Public Const STCAM_TRIGGER_MODE_TRIGGER_MASK_MASK As Long = &H00010000&
Public Const STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_MASK As Long = &H00060000&
Public Const STCAM_TRIGGER_MODE_TYPE_FREE_RUN As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_TYPE_TRIGGER As Long = &H00000001&
Public Const STCAM_TRIGGER_MODE_TYPE_TRIGGER_RO As Long = &H00000002&
Public Const STCAM_TRIGGER_MODE_EXPTIME_EDGE_PRESET As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_EXPTIME_PULSE_WIDTH As Long = &H00001000&
Public Const STCAM_TRIGGER_MODE_EXPTIME_START_STOP As Long = &H00002000&
Public Const STCAM_TRIGGER_MODE_SOURCE_NONE As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_SOURCE_SOFTWARE As Long = &H00000400&
Public Const STCAM_TRIGGER_MODE_SOURCE_HARDWARE As Long = &H00000800&
Public Const STCAM_TRIGGER_MODE_READOUT_SOFTWARE As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_READOUT_HARDWARE As Long = &H00000040&
Public Const STCAM_TRIGGER_MODE_EXPEND_DISABLE As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_EXPEND_ENABLE As Long = &H00000100&
Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_OFF As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_HD_ON As Long = &H00004000&
Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_OFF As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_EXPOSURE_WAIT_READOUT_ON As Long = &H00008000&
Public Const STCAM_TRIGGER_MODE_CAMERA_MEMORY_TYPE_B As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_CAMERA_MEMORY_TYPE_A As Long = &H00000010&
Public Const STCAM_TRIGGER_MODE_CAMERA_MEMORY_OFF As Long = &H00000020&
Public Const STCAM_TRIGGER_MODE_TRIGGER_MASK_OFF As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_TRIGGER_MASK_ON As Long = &H00010000&
Public Const STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_ERS As Long = &H00000000&
Public Const STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_GRR As Long = &H00020000&
Public Const STCAM_TRIGGER_MODE_CMOS_RESET_TYPE_GS As Long = &H00040000&
'------------------------------------------------------------------------------
'TRIGGER_TIMING
'------------------------------------------------------------------------------
Public Const STCAM_TRIGGER_TIMING_EXPOSURE_DELAY As Long = &H00000000&
Public Const STCAM_TRIGGER_TIMING_STROBE_START_DELAY As Long = &H00000001&
Public Const STCAM_TRIGGER_TIMING_STROBE_END_DELAY As Long = &H00000002&
Public Const STCAM_TRIGGER_TIMING_TRIGGER_PULSE_DELAY As Long = &H00000003&
Public Const STCAM_TRIGGER_TIMING_OUTPUT_PULSE_DELAY As Long = &H00000003&
Public Const STCAM_TRIGGER_TIMING_OUTPUT_PULSE_DURATION As Long = &H00000004&
Public Const STCAM_TRIGGER_TIMING_TRIGGER_PULSE_DURATION As Long = &H00000004&
Public Const STCAM_TRIGGER_TIMING_READOUT_DELAY As Long = &H00000005&
'------------------------------------------------------------------------------
'IO_PIN_MODE
'------------------------------------------------------------------------------
Public Const STCAM_OUT_PIN_MODE_DISABLE As Long = &H0000&
Public Const STCAM_OUT_PIN_MODE_GENERAL_OUTPUT As Long = &H0001&
Public Const STCAM_OUT_PIN_MODE_TRIGGER_OUTPUT_PROGRAMMABLE As Long = &H0010&
Public Const STCAM_OUT_PIN_MODE_TRIGGER_OUTPUT_LOOP_THROUGH As Long = &H0011&
Public Const STCAM_OUT_PIN_MODE_EXPOSURE_END As Long = &H0012&
Public Const STCAM_OUT_PIN_MODE_CCD_READ_END_OUTPUT As Long = &H0013&
Public Const STCAM_OUT_PIN_MODE_STROBE_OUTPUT_PROGRAMMABLE As Long = &H0020&
Public Const STCAM_OUT_PIN_MODE_STROBE_OUTPUT_EXPOSURE As Long = &H0021&
Public Const STCAM_OUT_PIN_MODE_TRIGGER_VALID_OUT As Long = &H0014&
Public Const STCAM_IN_PIN_MODE_DISABLE As Long = &H0000&
Public Const STCAM_IN_PIN_MODE_GENERAL_INPUT As Long = &H0001&
Public Const STCAM_IN_PIN_MODE_TRIGGER_INPUT As Long = &H0010&
Public Const STCAM_IN_PIN_MODE_READOUT_INPUT As Long = &H0030&
Public Const STCAM_IN_PIN_MODE_SUB_TRIGGER_INPUT As Long = &H0040&
'------------------------------------------------------------------------------
'TIMEOUT
'------------------------------------------------------------------------------
Public Const STCAM_TIMEOUT_ST2EE As Long = &H00000000&
Public Const STCAM_TIMEOUT_TE2EE As Long = &H00000001&
Public Const STCAM_TIMEOUT_EE2TE As Long = &H00000002&
Public Const STCAM_TIMEOUT_RO2TE As Long = &H00000003&
'------------------------------------------------------------------------------
'CAMERA_FUNCTION
'------------------------------------------------------------------------------
Public Const STCAM_CAMERA_FUNCTION_VGA90FPS As Long = 0
Public Const STCAM_CAMERA_FUNCTION_STARTSTOP As Long = 1
Public Const STCAM_CAMERA_FUNCTION_MEMORY As Long = 2
Public Const STCAM_CAMERA_FUNCTION_IO_CHANGE_DIRECTION As Long = 4
Public Const STCAM_CAMERA_FUNCTION_LED As Long = 5
Public Const STCAM_CAMERA_FUNCTION_DISABLE_DIP_SW As Long = 7
Public Const STCAM_CAMERA_FUNCTION_10BIT As Long = 8
Public Const STCAM_CAMERA_FUNCTION_12BIT As Long = 15
Public Const STCAM_CAMERA_FUNCTION_CDS_GAIN_TYPE As Long = 16
Public Const STCAM_CAMERA_FUNCTION_PHOTOCOUPLER As Long = 17
Public Const STCAM_CAMERA_FUNCTION_TRIGGER_MASK As Long = 18
Public Const STCAM_CAMERA_FUNCTION_V_BLANK_FOR_FPS As Long = 21
Public Const STCAM_CAMERA_FUNCTION_MIRROR_HORIZONTAL As Long = 22
Public Const STCAM_CAMERA_FUNCTION_MIRROR_VERTICAL As Long = 23
Public Const STCAM_CAMERA_FUNCTION_AWB As Long = 24
Public Const STCAM_CAMERA_FUNCTION_AGC As Long = 25
Public Const STCAM_CAMERA_FUNCTION_AE As Long = 26
Public Const STCAM_CAMERA_FUNCTION_IO_UNIT_US As Long = 27
Public Const STCAM_CAMERA_FUNCTION_CMOS_RESET_TYPE_0 As Long = 28
Public Const STCAM_CAMERA_FUNCTION_CMOS_RESET_TYPE_ERS_GRR As Long = 28
Public Const STCAM_CAMERA_FUNCTION_DISABLED_READOUT As Long = 29
Public Const STCAM_CAMERA_FUNCTION_DIGITAL_CLAMP As Long = 55
Public Const STCAM_CAMERA_FUNCTION_TRIGGER_VALID_OUT As Long = 56
Public Const STCAM_CAMERA_FUNCTION_CAMERA_GAMMA As Long = 57
Public Const STCAM_CAMERA_FUNCTION_STORE_CAMERA_SETTING As Long = 58
Public Const STCAM_CAMERA_FUNCTION_DEFECT_PIXEL_CORRECTION As Long = 59
Public Const STCAM_CAMERA_FUNCTION_DISABLE_MEMORY_TYPE_SELECTION As Long = 60
Public Const STCAM_CAMERA_FUNCTION_BINNING_COLUMN_SUM As Long = 61
Public Const STCAM_CAMERA_FUNCTION_H_BINNING_SUM As Long = 61
Public Const STCAM_CAMERA_FUNCTION_DISABLE_EXPOSURE_START_WAIT_HD As Long = 62
Public Const STCAM_CAMERA_FUNCTION_DISABLE_EXPOSURE_START_WAIT_READ_OUT As Long = 63
Public Const STCAM_CAMERA_FUNCTION_DISABLE_PULSE_WIDTH_EXPOSURE As Long = 69
Public Const STCAM_CAMERA_FUNCTION_CMOS_RESET_TYPE_1 As Long = 72
Public Const STCAM_CAMERA_FUNCTION_V_BINNING_SUM As Long = 131
Public Const STCAM_CAMERA_FUNCTION_TRIGGER As Long = 256
Public Const STCAM_CAMERA_FUNCTION_DIGITAL_GAIN As Long = 257
Public Const STCAM_CAMERA_FUNCTION_VARIABLE_PARTIAL As Long = 258
Public Const STCAM_CAMERA_FUNCTION_BINNING_PARTIAL As Long = 259
Public Const STCAM_CAMERA_FUNCTION_IO As Long = 260
Public Const STCAM_CAMERA_FUNCTION_RESET_FRAME_COUNTER As Long = 261
'------------------------------------------------------------------------------
'NOISE_REDUCTION
'------------------------------------------------------------------------------
Public Const STCAM_NR_OFF As Long = &H00000000&
Public Const STCAM_NR_EASY As Long = &H00000001&
Public Const STCAM_NR_COMPREX As Long = &H00000002&
Public Const STCAM_NR_DARK_CL As Long = &H80000000&
'------------------------------------------------------------------------------
'LED_STATUS
'------------------------------------------------------------------------------
Public Const STCAM_LED_GREEN_ON As Long = &H00000001&
Public Const STCAM_LED_RED_ON As Long = &H00000002&
'------------------------------------------------------------------------------
'TRANSFER_BITS_PER_PIXEL
'------------------------------------------------------------------------------
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_08 As Long = &H00000001&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_10 As Long = &H00000002&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_12 As Long = &H00000004&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_08 As Long = &H00000001&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_10 As Long = &H00000002&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_12 As Long = &H00000004&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_14 As Long = &H00000008&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_RAW_16 As Long = &H00000010&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_08 As Long = &H00000020&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_10 As Long = &H00000040&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_12 As Long = &H00000080&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_14 As Long = &H00000100&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_MONO_16 As Long = &H00000200&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_BGR_08 As Long = &H00000400&
Public Const STCAM_TRANSFER_BITS_PER_PIXEL_BGR_10 As Long = &H00000800&
'------------------------------------------------------------------------------
'JBA_REG_ADDRESS
'------------------------------------------------------------------------------
Public Const JBA_REG_ADD_HDR_MODE As Long = &H03&
Public Const JBA_REG_ADD_T2_RATIO As Long = &H04&
Public Const JBA_REG_ADD_T3_RATIO As Long = &H05&
Public Const JBA_REG_ADD_V1_STEP As Long = &H06&
Public Const JBA_REG_ADD_V2_STEP As Long = &H07&
Public Const JBA_REG_ADD_V3_STEP As Long = &H08&
Public Const JBA_REG_ADD_ADC_MODE As Long = &H1F&
Public Const JBA_REG_ADD_LED1 As Long = &H20&
Public Const JBA_REG_ADD_LED2 As Long = &H21&
'------------------------------------------------------------------------------
'CAMERA_SETTING
'------------------------------------------------------------------------------
Public Const STCAM_CAMERA_SETTING_INITIALIZE As Integer = &H8000
Public Const STCAM_CAMERA_SETTING_WRITE As Integer = &H2000
Public Const STCAM_CAMERA_SETTING_READ As Integer = &H1000
Public Const STCAM_CAMERA_SETTING_STANDARD As Integer = &H0800
Public Const STCAM_CAMERA_SETTING_DEFECT_PIXEL_POSITION As Integer = &H0400

