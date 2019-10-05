// WinComPort.h
//
// Functions for serial ports on Windows, C version
// by Lin, Jingyu, linjy02@hotmail.com, 2016.3
//
// ����ͨ������������ʣ�#include "WinComPort.h"����Ҳ����ͨ��WinComPort������ʣ�#include "WinComPort.hpp"����
// �������ʹ�÷�����
// 1. ��ComPortListName()��ѯ�������ƺͱ�š�
// 2. ��ComOpen()�򿪴��ڡ���ComClose()�رմ��ڡ�
// 3. ���ô��ڣ���ComDlgConfig()�����öԻ��򣻻���ComSetState()/ComGetState()��ȡ�����ô��ڡ�
// 4. �շ����ݣ���ComWrite()ͨ�����ڷ������ݣ���ComRead()��ȡ���ڽ��յ������ݡ�
//

#ifndef WINCOMPORT_H
#define WINCOMPORT_H

#define WinComPortExport extern "C" __declspec(dllexport)

/************************ ���ڲ�ѯ�Ϳ��� ************************/

// ���ܣ���ѯ�豸�������д��ڵ����ƺͱ�š�
// ���룺ComName[lenComName]�Ǳ��洮�������ַ����Ļ�������PortNo[nPortN0]�Ǳ��洮�ڱ�ŵ����顣
// ������������ư�˳�򱣴���ComName[lenComName]��������ڵ������ַ���֮����0�����
//       ���ڱ�ţ���COMx�е�x����˳�򱣴�������PortNo[nPortNo]�У���Ч���ڵı��Ϊ-1��
// ����ֵ��ϵͳ�д��ڵ�������
// ˵�������ComName[lenComName]��PortNo[nPortNo]�ռ䲻�����õ���Ӧ��Ϣ��������������Ȼ������ȷ�Ĵ���������
WinComPortExport int __stdcall ComPortListName(char* PortName, int lenPortName, int* PortNo, int nPortNo);

// ���ܣ���ѯע����д����ַ�����COMx�����ַ���֮����0�����
// ���룺PortName[lenPortName]�Ǳ���COMx�ַ����Ļ�������
// �����COMx�ַ���������PortName[lenPortName]��������ڵ��ַ���֮����0�����
// ����ֵ��ϵͳ�д��ڵ�������
// ˵�������PortName[lenPortName]�ռ䲻�����õ���Ӧ��Ϣ��������������Ȼ������ȷ�Ĵ���������
WinComPortExport int __stdcall ComPortQueryNumber(char* PortName, int lenPortName);

// ���ܣ��򿪴��ڡ�
// ���룺nPort�Ǵ��ںţ�szInBuf��szOutBuf�����������������С��
// ������ޡ�
// ����ֵ�����ھ����
// ˵������Ҫ���洮���Թ��������á�
WinComPortExport HANDLE __stdcall ComOpen(int nPort, int szInBuf = 4096, int szOutBuf = 4096);

// ���ܣ��رմ��ڡ�
// ���룺hCom����ComOpen��õĴ��ھ����
// ������ޡ�
WinComPortExport void __stdcall ComClose(HANDLE hCom);


/************************ �������� ************************/

// ���ܣ��ô������öԻ������ô��ڲ�����
// ���룺hCom����ComOpen��õĴ��ھ����pTitle�����������õĴ������ƣ�COMx����
// ��������ڲ������޸ġ�
WinComPortExport void __stdcall ComDlgConfig(HANDLE hCom, char* pTitle);

// ���ܣ�ֱ�����ô��ڲ�����
// ���룺hCom����ComOpen��õĴ��ھ��������Ϊ����ֵ��-1��ʾ��Ĭ��ֵ����BaudRate�ǲ����ʣ�ByteSize��ÿ���ֽ�bit����
//       Parity����żУ��λ: 0(��)��1(��)��2(ż)��StopBits��ֹͣλ: 0(1 bit), 1(1.5 bits), 2(2 bits)��
// ������ޡ�
WinComPortExport void __stdcall ComSetState(HANDLE hCom, int BaudRate = -1, int ByteSize = -1, int Parity = -1, int StopBits = -1);

// ���ܣ���ȡ���ڲ�����
// ���룺hCom����ComOpen��õĴ��ھ����
// �����BaudRate�ǲ����ʣ�ByteSize��ÿ���ֽ�bit����Parity����żУ��λ: 0(��)��1(��)��2(ż)��
//       StopBits��ֹͣλ: 0(1 bit), 1(1.5 bits), 2(2 bits)��
WinComPortExport void __stdcall ComGetState(HANDLE hCom, int& BaudRate, int& ByteSize, int& Parity, int& StopBits);


/************************ ���ڶ�д ************************/

// ���ܣ��򴮿�д�����ݡ�
// ���룺hCom����ComOpen��õĴ��ھ����Data[nData]��Ҫд�봮�ڵ����ݣ�nData�������ֽ�����
// ���������д�봮�ڡ�
// ����ֵ��ʵ��д�봮�ڵ������ֽ�����
// ˵��������ͬ�����������������غ�û�й���ĺ�̨������
WinComPortExport int __stdcall ComWrite(HANDLE hCom, char* Data, int nData);

// ���ܣ��Ӵ��ڶ�ȡ���ݡ�
// ���룺hCom����ComOpen��õĴ��ھ����Data[nData]�Ǵ�ŴӴ��ڶ�ȡ�����ݵĻ�������nData�����ɶ�ȡ���ֽ�����
// ������Ӵ��ڶ�ȡ�����ݱ�����Data[nData]�С�
// ����ֵ��ʵ�ʴӴ��ڶ�ȡ�������ֽ�����
// ˵��������ͬ�����������������غ�û�й���ĺ�̨������
WinComPortExport int __stdcall ComRead(HANDLE hCom, char* Data, int nData);


#endif // #ifndef WINCOMPORT_H
