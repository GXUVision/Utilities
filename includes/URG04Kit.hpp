// URG04Kit.HPP
//
// Tool kit for URG04 laser range finder, C++ version.
// by Lin, Jingyu, linjy02@hotmail.com, 2019.9
//
// ʹ�÷�����
// 1. ����URG04Device����
// 2. ��StartScan()ѡ���豸���ڴ��ڲ������������ǡ����ڿ���ֱ��ָ��������SearchURG04Device()��ѯ��
//    ��Close()�ر������ļ������ǡ�URG04Device�������ʱ�Զ��ر������ļ������ǡ�
// 3. ��ReadScanAngle()��ȡ������ݶ�Ӧ��ɨ������顣�����鲻��
// 4. ��ʱ������100ms������ReadRange()��ȡ������ݼ���ʱ�����������δȥ�������������
// 5. ���в�����ݴ����������ֵ̫С��<20mm��˵��������෶Χ����Ծ��档
// 6. �����Ҫ������RangeToMap()���������ת��Ϊ��ά��ͼ�Ա���ʾ��
//

// �޸ļ�¼
// 20190907���ϲ����ڹ��ܣ�������ҪWinComPort.dll��
//

#ifndef URG04Kit_HPP
#define URG04Kit_HPP

class __declspec(dllexport) URG04Device
{
public:
	URG04Device();
	~URG04Device();

	/************************ ��ѯ�豸 ************************/

	// ���ܣ���ѯ���ӵļ������ǡ�
	// ����ֵ��ϵͳ�м������ǵ�������
	// ˵�����β��豸����Ҫ�ٴε��ô˺������п���������USB�豸ʶ��Ϊ�������ǡ�
	static int SearchURG04Device();

	// ���ܣ���ȡ�������ǵ����ƺʹ��ںš�����SearchURG04Device()����Ч��
	// ���룺idx - �������ǵ���š�
	// �����ComNo - ���ڶ˿ںţ���COMx�е�x������Ч���ڵĶ˿ں�Ϊ-1��
	// ����ֵ�������ַ���ָ�롣NULL��ʾ��ų����豸������
	static char* GetURG04Port(int idx, int& ComNo);

	// ���ܣ����ϵͳ�м������ǵ����������δ���ù�SearchURG04Device()�򷵻�-1���޼��������򷵻�0��
	static int GetURG04Total();


	/************************ �����豸 ************************/

	// ���ܣ�����ָ�������ϵ�URG�������ǡ��ɹ�������ɼ�������ݣ�ÿ�����ݲɼ�ʱ��Ϊ100ms��
	//       ��ReadRange()������ʱ��ȡ������ݡ�
	// ���룺ComNo - �������ǵĴ��ںš�
	// ������ޡ�
	// ����ֵ��1��ʾ�ɹ������������ǡ�0��ʾ�Ǽ������ǡ�
	int StartScan(int ComNo);

	// ���ܣ��ر�URG�������ǣ�ֹͣ�ɼ�������ݡ�
	// ˵����URG04Device�������ʱ�Զ����ô˺�����
	void Close();

	/************************ ��ȡ���� ************************/

	// ���ܣ���ȡ������ݶ�Ӧ��ɨ��ǣ�rad����������szTheta�����thetaΪNULL�������ɨ��ǵ�����szTheta��
	// ���룺theta[] - ɨ��ǻ���������СΪszTheta��
	// �����theta[] - ɨ������顣
	// ����ֵ��ɨ��ǵ�����szTheta����������ݵ�����������Ч��ɨ��ķ�Χ��
	// ˵��������ǽ�һ�ܣ�360�㣩��Ϊ1024�������ɨ��ǵĵ�λΪ360��/1024=0.3516�㡣
	//       ��������ҶԳ�ɨ�衣����������ǰ����ɨ���Ϊ0����ʱ�뷽��Ϊ����
	//       ���szTheta=0�����ұߣ�szTheta/2-1����ǰ����szTheta-1������ߡ�
	int ReadScanAngle(double* theta);

	// ���ܣ���ȡ������ݣ�m������ʱ��������szRange�����������ΪNULL�򲻷�����Ӧ���ݡ�
	// ���룺range[], range0[] - ������ݻ���������СΪszRange��
	//       timeStamp, timeStamp0 - ���ڻ�ȡʱ����
	// �����range[], range0[] - �������ϴεĲ�����ݣ�ÿ��ɨ��Ƕ�Ӧһ������ֵ��
	//       *timeStamp, *timeStamp0 - ������ݵ�ʱ����
	// ����ֵ��������ݵ�����szRange������ɨ��ǵ�������
	// ˵��������ǽ�һ�ܣ�360�㣩��Ϊ1024�������ɨ��ǵĵ�λΪ360��/1024=0.3516�㡣
	//       ��������ҶԳ�ɨ�衣������ǰ����ɨ���Ϊ0����ʱ�뷽��Ϊ����
	//       ���szRange=0�����ұߣ�szRange/2����ǰ����szRange-1������ߡ�
	int ReadRange(double* range, int* timeStamp, double* range0 = NULL, int* timeStamp0 = NULL);

	/************************ �豸��Ϣ ************************/

	// ���ܣ��ж��豸�Ƿ�������
	// ����ֵ������1��ʾ��������0��ʾ�ѹرա�
	int IsActive();

	// ���ܣ�����������豸�Ĵ��ڶ˿ںš�����-1��ʾδ������
	int GetActiveURGComNo();

	// ���ܣ��������ݼ�¼״̬��log�ļ�ΪurgRange.txt��
	void SetDataLog(int bLog);
	int GetDataLog();

	/************************ �������� ************************/

	// ���ܣ����������ת��Ϊ��ά��ͼ��
	// ���룺map[mapRow][mapCol] - ��ά��ͼ��������r_front - ��ͼ���ĵ���ͼ�������е�������루m�������ڳ߶ȱ任��
	//       steering - ת��ǣ����ȣ�����ͼ���Ϸ�Ϊ0����������ʱ��Ϊ����˳ʱ��Ϊ����
	//       range[szRange] - ��ReadRange()��ȡ�Ĳ�����ݻ򾭹�����Ĳ�����ݣ�m����szRange=-1��ʾ��ϵͳȱʡֵ��
	//       stepAngle - ɨ��ǲ��������ȣ���stepAngle=-1��ʾ��ϵͳȱʡֵ��
	// �����map - ��ά��ͼ�������������У�ÿ������ȡֵ0��ʾ������0xFF��ʾ���ڵ���
	// ˵���������λ�ڵ�ͼ���ģ�r_front��Ӧ�����ͼ��mapRow/2���ľ��롣
	//       ����ReadScanAngle()���Ի��szRangeֵ���������ڵ�ɨ���֮�����stepAngle��
	static void RangeToMap(unsigned char *map, int mapRow, int mapCol, double r_front, double steering,
		double* range, int szRange = -1, double stepAngle = -1);

private:
	char privatedata[24]; // 24 bytes for x64, 12 bytes for Win32
};
#endif // #ifndef URG04Kit_HPP
