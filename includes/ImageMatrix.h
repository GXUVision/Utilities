// ImageMatrix.h
//
// Tools for matrix of images
// by Lin, Jingyu, linjy02@hotmail.com, 2016.08
//
#ifndef ImageMatrix_H
#define ImageMatrix_H

#include <windows.h>

#define ImageMatrixExport extern "C" __declspec(dllexport)

/****************************************************************/
/*                     File IO                                  */
/****************************************************************/
// ���ܣ�����ά���󱣴�Ϊ�ı��ļ���һ�������ö��ŷָ�������������MATLAB�н�һ��������
// ���룺filename - �ı��ļ�����mat[height][width] - Դ������������ȡ����mat_type��
//       mat_type - �������ͣ�0~9: double (ȱʡ����), int, unsigned int, char (8 bit), unsigned char(8 bit), 
//                  short (16 bit), unsigned short (16 bit), long (32 bit), unsigned long (32 bit), float��
// ���������д���ı��ļ���
/* ˵������һ��ͼ��h*w*c�����б���Ϊ�����ı�����MATLAB��ȡ����������
dat = importdata('test24bit.txt'); % �������ݣ�h*cw��
c = 3; % ����ͼ���ͨ����
[h, w] = size(dat); w = w/c; % ����ͼ��Ŀ�Ⱥ͸߶�
dat = reshape(dat,h,c,w); % ת��Ϊ��ά����
img = permute(dat,[1 3 2])/255; % ת��Ϊh*w*c����һ��ǿ�ȡ�
img = img(end:-1:1,:,end:-1:1); % BGRת��ΪRGB�������·�תʹ�õ�һ������
figure(1); image(img)
*/
ImageMatrixExport void __stdcall SaveMatrixToText(char *filename, void *mat, int width, int height, int mat_type);
ImageMatrixExport void __stdcall SaveDoubleMatrixToText(char *filename, double *mat, int width, int height);
ImageMatrixExport void __stdcall SaveIntMatrixToText(char *filename, int *mat, int width, int height);
ImageMatrixExport void __stdcall SaveByteMatrixToText(char *filename, BYTE *mat, int width, int height);

// ���ܣ����ı��ļ���ȡ��ά�����ı��ļ���һ��Ϊ������У�һ�������ö��š��ֺš���|����հ׷ָ���
// ���룺filename - �ı��ļ�����mat[height][width] - Դ���󻺳�������������ȡ����mat_type��
//       mat_type - �������ͣ�0~9: double (ȱʡ����), int, unsigned int, char (8 bit), unsigned char(8 bit), 
//                  short (16 bit), unsigned short (16 bit), long (32 bit), unsigned long (32 bit), float��
// �����mat[height][width] - ���ı��ļ���ȡ�ľ���
// ����ֵ��ʵ�ʶ�ȡ��������������height��
/* ˵������MATLAB��ȡͼ��Ȼ�󱣴�Ϊ�����ı�����������
img = double(imread('test24bit.bmp'))/255; % ��ȡͼ�񲢹�һ��ǿ��
img = permute(img,[1 3 2]); % ת��Ϊh*c*w��
img = img(end:-1:1,end:-1:1,:); % RGBת��ΪBGR�������·�תʹ�õ�һ������
[h, c, w] = size(img);  % ����ͼ��ĸ߶ȡ���Ⱥ�ͨ����
dat = reshape(img,h,c*w)*255; % ת��Ϊ��ά����
save('test24bit2.txt','dat','-ascii')
*/
ImageMatrixExport int __stdcall ReadMatrixFromText(char *filename, void *mat, int width, int height, int mat_type);
ImageMatrixExport int __stdcall ReadDoubleMatrixFromText(char *filename, double *mat, int width, int height);
ImageMatrixExport int __stdcall ReadIntMatrixFromText(char *filename, int *mat, int width, int height);
ImageMatrixExport int __stdcall ReadByteMatrixFromText(char *filename, BYTE *mat, int width, int height);

// ���ܣ���ȡһ��BMP�ļ�����֧�ֲ�ɫ��16~32bit���ͺڰף�8bit��ͼ��
// ���룺filename - BMP�ļ�����bmi - ͼ��ͷ��������40Bͼ��ͷ+4*256B��ɫ�壩��Dib[szDib] - ͼ����󻺳�����
// �����bmi - ͼ��ͷ��Ϣ��Dib[szDib] - ͼ��������ݡ�
// ����ֵ��ʵ�ʶ�ȡ��ͼ������ֽ�����������szDib��-1��ʾ��ȡʧ�ܣ�0��ʾֻ��ȡͼ��ͷ��
// ˵����ͼ����ļ�ͷ��ʽΪ��BITMAPINFOHEADER�ṹ��40B��+��ɫ�壨4*256B����
//       8bitͼ��ĵ�ɫ����256ɫ��ÿ����ɫ��һ��4�ֽڵ�RGBQUAD�ṹ��16~32bitͼ��û�е�ɫ�塣
//       ���DibΪNULL����ֻ��ȡͼ��ͷbi[szBI]��ͼ������ֽ���pixelBytes�����Dib[szDib]�ռ䲻�������������
ImageMatrixExport int __stdcall ReadBmpFile(char *filename, BITMAPINFO* bmi, BYTE *Dib, int szDib);

/****************************************************************/
/*                     Bitmap Display                           */
/****************************************************************/
// ShowBmp��ShowBmp2��ʾ����ͼ�񣬱���ͼ���߱ȡ�ǰ��ռ���������ڣ����߿��Ըı���ʾλ�á�
// ShowBmpEx��ʵ�ֶ�����ʾ��ʽ��

// ���ܣ���ָ�����ڵ���������������ʾ����ͼ�񣨱���ͼ���߱ȣ���
// ���룺hwnd - ������ʾͼ��Ĵ��ڡ�bmi - ͼ��ͷ�ṹ��pixels - ͼ�����
ImageMatrixExport void __stdcall ShowBmp(HWND hwnd, const BITMAPINFO* bmi, const BYTE* pixels);

// ���ܣ���ָ�����ڵ�ָ��������ʾ����ͼ�񣨱���ͼ���߱ȣ���
// ���룺hwnd - ������ʾͼ��Ĵ��ڡ�rectDest - ������������ʾ������bmi - ͼ��ͷ�ṹ��pixels - ͼ�����
ImageMatrixExport void __stdcall ShowBmp2(HWND hwnd, const RECT& rectDest, const BITMAPINFO* bmi, const BYTE* pixels);

// ���ܣ���ָ�����ڵ�ָ��������ʾͼ���ָ����Χ��
// ���룺hwnd - ������ʾͼ��Ĵ��ڡ�rectDest - ������������ʾ������
//       bmi - ͼ��ͷ�ṹ��pixels - ͼ�����rectSrc - ͼ����������ʾ������
//       mirror - ������ʾ��0��ʾԭͼ��1���Ҿ���2���¾���3�������Ҿ���
//       dwRop - ��դ�����룬ȡֵ����BitBlt������ֵ���£�
//BLACKNESS: Fills the destination rectangle using the color associated with index 0 in the physical palette. (This color is black for the default physical palette.)
//CAPTUREBLT: Includes any windows that are layered on top of your window in the resulting image.By default, the image only contains your window.Note that this generally cannot be used for printing device contexts.
//DSTINVERT: Inverts the destination rectangle.
//MERGECOPY: Merges the colors of the source rectangle with the brush currently selected in hdcDest, by using the Boolean AND operator.
//MERGEPAINT: Merges the colors of the inverted source rectangle with the colors of the destination rectangle by using the Boolean OR operator.
//NOMIRRORBITMAP: Prevents the bitmap from being mirrored.
//NOTSRCCOPY: Copies the inverted source rectangle to the destination.
//NOTSRCERASE: Combines the colors of the source and destination rectangles by using the Boolean OR operator and then inverts the resultant color.
//PATCOPY: Copies the brush currently selected in hdcDest, into the destination bitmap.
//PATINVERT: Combines the colors of the brush currently selected in hdcDest, with the colors of the destination rectangle by using the Boolean XOR operator.
//PATPAINT: Combines the colors of the brush currently selected in hdcDest, with the colors of the inverted source rectangle by using the Boolean OR operator. The result of this operation is combined with the colors of the destination rectangle by using the Boolean OR operator.
//SRCAND: Combines the colors of the source and destination rectangles by using the Boolean AND operator.
//SRCCOPY: Copies the source rectangle directly to the destination rectangle.
//SRCERASE: Combines the inverted colors of the destination rectangle with the colors of the source rectangle by using the Boolean AND operator.
//SRCINVERT: Combines the colors of the source and destination rectangles by using the Boolean XOR operator.
//SRCPAINT: Combines the colors of the source and destination rectangles by using the Boolean OR operator.
//WHITENESS: Fills the destination rectangle using the color associated with index 1 in the physical palette. (This color is white for the default physical palette.)
ImageMatrixExport void __stdcall ShowBmpEx(HWND hwnd, const RECT& rectDest,
	const BITMAPINFO* bmi, const BYTE* pixels, const RECT& rectSrc, int mirror, DWORD dwRop = SRCCOPY);

/****************************************************************/
/*                     Matrix Display                           */
/****************************************************************/
// ShowMatrix��ShowMatrix2��ʾ����ͼ�񣬱���ͼ���߱ȡ�ǰ��ռ���������ڣ����߿��Ըı���ʾλ�á�
// ShowMatrixEx��ʵ�ֶ�����ʾ��ʽ��

// ���ܣ�����ͼ��ͷ�ṹbmi��
// ���룺bmi - ����Ϊ1064�ֽڵ�ͼ��ͷ�ṹ��������chnpp��width��height - ͼ��ͨ������1��3��4�������ߡ�
//       TopDown - ����ͼ���Ƿ����϶��¡�1��ʾͼ������һ�ж�Ӧͼ�񶥲���0��ʾͼ������һ�ж�Ӧͼ��ײ���
// �����bmi - ͼ��ͷ�ṹ��Ϣ��
// ˵����bmi�ĽṹΪһ��BITMAPINFOHEADER��40�ֽڣ���256��RGBQUAD�ṹ��1024�ֽڣ���
ImageMatrixExport void __stdcall FillDibHead(BITMAPINFO* bmi, int chnpp, int width, int height, int TopDown);

// ���ܣ���ָ�����ڵ���������������ʾ������ά���󣨾���ͼ�񱣳�ͼ���߱ȣ���
// ���룺hwnd - ������ʾ����Ĵ��ڡ�mat[height][chnpp*width] - ��ά�������ݡ�chnpp - ͼ��ͨ������1��3��4����
//       minVal, maxVal - ����Ԫ�ص��½���Ͻ磬�����½����ֵת��Ϊ0�������Ͻ����ֵת��Ϊ255��
//       TopDown - ����ͼ���Ƿ����϶��¡�1��ʾ�����һ�ж�Ӧͼ�񶥲���0��ʾ�����һ�ж�Ӧͼ��ײ���
// ˵����Ƶ����ʾӦʹ��BYTE���;���
ImageMatrixExport void __stdcall ShowMatrix(HWND hwnd, const double* mat, int chnpp, int width, int height,
	double minVal, double maxVal, int TopDown);
ImageMatrixExport void __stdcall ShowByteMatrix(HWND hwnd, const BYTE* mat, int chnpp, int width, int height, 
	int TopDown);

// ���ܣ���ָ�����ڵ�ָ��������ʾ������ά���󣨾���ͼ�񱣳�ͼ���߱ȣ���
// ���룺hwnd - ������ʾ����Ĵ��ڡ�rectDest - ������������ʾ������mat[height][chnpp*width] - ��ά�������ݡ�
//       chnpp - ͼ��ͨ������1��3��4����minVal, maxVal - ����Ԫ�ص��½���Ͻ磬�����½����ֵת��Ϊ0�������Ͻ����ֵת��Ϊ255��
//       TopDown - ����ͼ���Ƿ����϶��¡�1��ʾ�����һ�ж�Ӧͼ�񶥲���0��ʾ�����һ�ж�Ӧͼ��ײ���
// ˵����Ƶ����ʾӦʹ��BYTE���;���
ImageMatrixExport void __stdcall ShowMatrix2(HWND hwnd, const RECT& rectDest, const double* mat, int chnpp, int width, int height,
	double minVal, double maxVal, int TopDown);
ImageMatrixExport void __stdcall ShowByteMatrix2(HWND hwnd, const RECT& rectDest, const BYTE* mat, int chnpp, int width, int height, 
	int TopDown);

// ���ܣ���ָ�����ڵ�ָ��������ʾ��ά�����ָ����Χ����֧��1~4ͨ�����󡣾���ͼ�����϶��£��������һ�ж�Ӧͼ�񶥲���
// ���룺hwnd - ������ʾ����Ĵ��ڡ�rectDest - ������������ʾ������mat[height][chnpp*width] - ��ά�������ݡ�
//       chnpp - ͼ��ͨ������1��3��4����minVal, maxVal - ����Ԫ�ص��½���Ͻ磬�����½����ֵת��Ϊ0�������Ͻ����ֵת��Ϊ255��
//       rectSrc - ������������ʾ������mirror - ������ʾ��0��ʾԭͼ��1���Ҿ���2���¾���3�������Ҿ���
//       dwRop - ��դ�����룬ȡֵ˵������ShowBmpEx��
// ˵����rectMat�Ǿ������������ͼ�����ꡣͼ������ԭ�������½ǣ�����Ϊ������������ԭ�������Ͻǣ�����Ϊ����
// ˵����Ƶ����ʾӦʹ��BYTE���;���
ImageMatrixExport void __stdcall ShowMatrixEx(HWND hwnd, const RECT& rectDest, const double* mat, int chnpp, int width, int height,
	double minVal, double maxVal, const RECT& rectSrc, int mirror, DWORD dwRop);
ImageMatrixExport void __stdcall ShowByteMatrixEx(HWND hwnd, const RECT& rectDest, const BYTE* mat, int chnpp, int width, int height,
	const RECT& rectSrc, int mirror, DWORD dwRop);

#endif // #ifndef ImageMatrix_H
