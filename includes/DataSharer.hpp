// DataSharer.hpp
//
// DataSharer���ṩ���̼����ݹ������
// 
// ʹ�÷�����
// 1. ����DataSharer����
// 2. ����OpenSharedBlock()�����������ݿ飬�������ơ���źʹ�С�����ƺ���ű�ʶ���ݿ飬���ݿ��СӦ������������Ϣ���������ݡ�
//    ��GetBlockName()��GetBlockSN()���Բ�ѯ���ݿ����ƺ���š�
// 3. ����WriteData()д����������Ϣ������ReadData()��ȡ��������Ϣ��
// 4. ����WriteImage()д��ͼ����������Ϣ������ReadImage()��ȡͼ����������Ϣ��
// 5. �������ݿ鴴�����С���ܸı䡣�����Ҫ���������OpenSharedBlock()���ı����ݿ����ƻ���š�
// ע�⣺����ǰ׺"Global\\"��ʾ�����������ʡ�
//
// by Jingyu Lin, linjy02@hotmail.com, 2019.02

#ifndef DataSharer_H
#define DataSharer_H

// ͼ�����ݵ���Ϣ�ṹ��ͼ�����ݵ��ֽ���ΪStride*Height��
struct InfoImage {
	INT32 Width;
	INT32 Height;			
	INT32 Channel;			// ÿ�����ص��ֽ�����
	INT32 Stride;			// ͼ��һ���ֽ�����������4�ı�������Stride=(Width*Channel+3)/4*4��
	double secPerFrame;		// ����ͼ������ʱ����ͼ��֮���ʱ�������룩
};

class __declspec(dllexport) DataSharer
{
public:
	DataSharer();
	~DataSharer();

	// ���ܣ������������ݿ飬���ͷ�֮ǰ�����Ĺ������ݿ顣
	// ���룺BlockName - ���ݿ����ƣ��255�ֽڡ�snBlock - ���ݿ���š�szBlock - ���ݿ��ֽ�����Ӧ������������Ϣ���������ݡ�
	// ����ֵ���ɹ��򷵻ع����ڴ��С�����򷵻�0��
	// ˵�������ݿ����ƺ�������ڱ�ʶ�������ݿ顣�������ͬ�����ݿ鲢���ֽ���С��szBlock��ʧ�ܡ�
	int OpenSharedBlock(const char* BlockName, INT32 snBlock, INT32 szBlock);

	// ���ܣ������ݼ�����Ϣд�빲�����ݿ顣
	// ���룺infoSrc[szInfo] - ��д���������Ϣ��dataSrc[szData] - ��д����������ݡ�type - �������ͣ�0��һ�����ݣ�1��ͼ��
	// ����ֵ��д����ֽ�����������Ϣ�����ݣ���0��ʾд��ʧ�ܡ�
	// ˵������д��Ϣ��д���ݡ�infoSrcΪNULL��szInfoΪ0����������Ϣ��ֻд�����ݡ�dataSrcΪNULL��szDataΪ0��д��ʧ�ܡ�
	int WriteData(BYTE* infoSrc, INT32 szInfo, BYTE* dataSrc, INT32 szData, INT32 type);

	// ���ܣ��ӹ������ݿ��ȡ���ݼ�����Ϣ��
	// ���룺dest[szDest] - ���ڱ������ݼ�����Ϣ�Ļ�������
	// �����dest - ���������ݼ�����Ϣ����Ϣ��ǰ�����ں�byteInfo - ������Ϣ���ֽ�����byteData - �������ݵ��ֽ������������ݽ���������Ϣ��
	//       type - �������͡�0��һ�����ݣ�1��ͼ��secStamp - ���ݸ��µ�ʱ�����룩��updated - 1��ʾ�ϴε���Read֮�������Ѿ����¡�
	// ����ֵ���������ֽ�����������Ϣ�����ݣ���0��ʾ��ȡʧ�ܡ�
	// ˵����destΪNULL��szDestΪ0�����ȡ���ݿ���Ϣ������ֵ�ǿɶ�ȡ�������ֽ�����
	int ReadData(BYTE* dest, INT32 szDest, INT32& byteInfo, INT32& byteData, INT32& type, double& secStamp, INT32& updated);

	// ���ܣ���ͼ������Ϣд�빲�����ݿ顣
	// ���룺imgSrc[szSrcImg] - ��д���ͼ��Width��Height��Channel - ͼ��Ŀ��ߺ���ɫͨ����
	//       secPerFrame - ����ͼ������ʱ����ͼ��֮���ʱ�������룩��
	// ����ֵ��ͼ�������ֽ�����0��ʾд��ʧ�ܡ�
	// ˵����ͼ�������ֽ���ΪChannel��Width��Height������Channel��WidthӦΪ4�ı�����
	int WriteImage(BYTE* imgSrc, INT32 szImgSrc, INT32 Width, INT32 Height, INT32 Channel, double secPerFrame);

	// ���ܣ��ӹ������ݿ��ȡͼ������Ϣ��
	// ���룺imgDest[szImgDest] - ���ڱ���ͼ��Ļ�������
	// �����imgDest - ������ͼ�����ݡ�infoImg - ͼ����Ϣ��secStamp - ���ݸ��µ�ʱ�����룩��updated - 1��ʾ�ϴε���Read֮�������Ѿ����¡�
	// ����ֵ��������ͼ�������ֽ�����0��ʾʧ�ܡ�
	// ˵����imgDestΪNULL��szImgDestΪ0�����ȡͼ����Ϣ������ֵ�ǿɶ�ȡ���ֽ�����headerData.typeDataӦΪ1�������ȡʧ�ܡ�
	int ReadImage(BYTE* imgDest, INT32 szImgDest, InfoImage& infoImg, double& secStamp, INT32& updated);

	// ���ܣ���ȡ�������ݿ�����ơ���źʹ�С��NULL��-1��ʾδ�ɹ�����Openxxx()��
	const char* GetBlockName();
	int GetBlockSN();
	int GetBlockBytes();

private:
	BYTE privatedata[296]; 
};

#endif // #ifndef DataSharer_H
