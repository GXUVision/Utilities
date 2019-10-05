// WinComPort.hpp
//
// Functions for serial ports on Windows, C++ version
// by Lin, Jingyu, linjy02@hotmail.com, 2017.9
//
// ����ͨ������������ʣ�#include "WinComPort.h"����Ҳ����ͨ��WinComPort������ʣ�#include "WinComPort.hpp"����
// WinComPort����ʹ�÷�����
// 1. �����Ҫ���þ�̬����SearchPorts()��ѯϵͳ��װ�Ĵ��ڣ�Ȼ����GetPortName()�鿴�������ƺͱ�š�
// 2. ����WinComPort����
// 3. ��Open()��ָ�����ڡ���Close()�رմ��ڡ�WinComPort�������ʱ�Զ��رմ��ڡ�
// 4. ���ô��ڣ���ConfigDlg()�����öԻ��򣻻���SetState()/GetState()��ȡ�����ô��ڡ�
// 5. �շ����ݣ���Write()ͨ�����ڷ������ݣ���Read()��ȡ���ڽ��յ������ݡ�
//

#ifndef WINCOMPORT_HPP
#define WINCOMPORT_HPP

class __declspec(dllexport) WinComPort
{
public:
	WinComPort();
	~WinComPort();

	/************************ ���ڲ�ѯ ************************/

	// ���ܣ���ѯ�豸�������еĴ��ڡ���ѯ�����GetPortName()��ȡ���ڵ����ƺͶ˿ںš�
	// ����ֵ��ϵͳ�д��ڵ�������
	static int __stdcall SearchPorts();

	// ���ܣ���ȡ�豸�������д��ڵ����ƺͶ˿ںš������ȵ���SearchPorts()��
	// ���룺idx - ������š�
	// �����ComNo - ���ڶ˿ںţ���COMx�е�x������Ч���ڵĶ˿ں�Ϊ-1��
	// ����ֵ�����������ַ���ָ�롣NULL��ʾ��ų�������������
	static char* __stdcall GetPortName(int idx, int& ComNo);

	// ���ܣ����ϵͳ�д������������δ���ù�SearchPorts()�򷵻�-1���޴����򷵻�0��
	static int __stdcall GetPortTotal();


	/************************ ���ڴ򿪺͹ر� ************************/

	// ���ܣ��򿪴��ڡ�
	// ���룺ComNo�Ǵ��ڶ˿ںţ�szInBuf��szOutBuf�����������������С��Ĭ��Ϊ4096�ֽڡ�
	// ����ֵ������1��ʾ�ɹ���0��ʾʧ�ܡ�
	int __stdcall Open(int ComNo, int szInBuf = 4096, int szOutBuf = 4096);

	// ���ܣ��رմ��ڡ�
	void __stdcall Close();


	/************************ �������� ************************/

	// ���ܣ��ô������öԻ������ô��ڲ�����
	// ���룺hCom����ComOpen��õĴ��ھ����pTitle�����������õĴ������ƣ�COMx����
	// ��������ڲ������޸ġ�
	// ����ֵ��1��ʾ�ɹ���0��ʾʧ�ܡ�
	int __stdcall ConfigDlg();

	// ���ܣ�ֱ�����ô��ڲ�����
	// ���룺BaudRate�ǲ����ʣ�ByteSize��ÿ���ֽ�bit����Parity����żУ��λ: 0(��)��1(��)��2(ż)��
	//       StopBits��ֹͣλ: 0(1 bit), 1(1.5 bits), 2(2 bits)������ֵ-1��ʾ���ı䡣
	// ������ޡ�
	// ����ֵ��1��ʾ�ɹ���0��ʾʧ�ܡ�
	int __stdcall SetState(int BaudRate = -1, int ByteSize = -1, int Parity = -1, int StopBits = -1);

	// ���ܣ���ȡ���ڲ�����
	// ���룺�ޡ�
	// �����BaudRate�ǲ����ʣ�ByteSize��ÿ���ֽ�bit����Parity����żУ��λ: 0(��)��1(��)��2(ż)��
	//       StopBits��ֹͣλ: 0(1 bit), 1(1.5 bits), 2(2 bits)��
	// ����ֵ��1��ʾ�ɹ���0��ʾʧ�ܡ�
	int __stdcall GetState(int& BaudRate, int& ByteSize, int& Parity, int& StopBits);


	/************************ ���ڶ�д ************************/

	// ���ܣ��򴮿�д�����ݡ�
	// ���룺Data[nData]��Ҫд�봮�ڵ����ݡ�nData�������ֽ�����
	// ���������д�봮�ڡ�
	// ����ֵ��ʵ��д�봮�ڵ������ֽ�����
	// ˵��������ͬ�����������������غ�û�й���ĺ�̨������
	int __stdcall Write(char* Data, int nData);

	// ���ܣ��Ӵ��ڶ�ȡ���ݡ�
	// ���룺Data[nData]�Ǵ�ŴӴ��ڶ�ȡ�����ݵĻ�������nData�����ɶ�ȡ���ֽ�����
	// ������Ӵ��ڶ�ȡ�����ݱ�����Data[nData]�С�
	// ����ֵ��ʵ�ʴӴ��ڶ�ȡ�������ֽ�����
	// ˵��������ͬ�����������������غ�û�й���ĺ�̨������
	int __stdcall Read(char* Data, int nData);

	// ���ܣ�������ڶ�д��������
	void __stdcall Purge();

	/************************ �˿���Ϣ ************************/

	// ���ܣ��жϴ����Ƿ�򿪡�����1��ʾ�����Ѵ򿪣�0��ʾ�ѹرա�
	int __stdcall IsOpened();

	// ���ܣ���ô򿪵Ĵ��ڶ˿ںš�����-1��ʾ����δ�򿪡�
	int __stdcall GetActiveComNo();

	// ���ܣ���ô򿪵Ĵ��ھ��������NULL��ʾ����δ�򿪡�
	HANDLE __stdcall GetComHandle();

private:
	HANDLE hWinCom;      // handle of opened port
	INT32 ActiveComNo;   // Com No of opened port
};

#endif // #ifndef WINCOMPORT_HPP
