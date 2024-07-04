## 1. ��ȡBMP�ļ���ͷ��Ϣ
BMP�ļ�����һ���ļ�ͷ�������ļ����͡��ļ���С��ƫ��������Ϣ����һ����Ϣͷ������ͼ���ȡ��߶Ⱥ���ɫ��ȵ���Ϣ�����Լ������������ݡ�

## 2. �޸��������������ˮӡ
���ǿ���ѡ��һ���򵥵ķ�ʽ�����ˮӡ������ı��ض����������ֵ���γ����ֻ���ͼ����

## 3. �����޸ĺ��ͼ��
��󣬽��޸ĺ����������д�ص�BMP�ļ��У������޸ġ�

������һ�������Ĵ����ܣ�չʾ���ʵ����һ���̣�

``` c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1) // ȷ���ṹ�尴1�ֽڶ���

// ����λͼ�ļ�ͷ�ṹ��
typedef struct {
    unsigned short type; // �ļ����ͣ�������0x4D42
    unsigned int size; // �ļ���С
    unsigned short reserved1; // ����������Ϊ0
    unsigned short reserved2; // ����������Ϊ0
    unsigned int offset; // ���ļ�ͷ��ʵ��λͼ���ݵ�ƫ��
} BITMAPFILEHEADER;

// ����λͼ��Ϣͷ�ṹ��
typedef struct {
    unsigned int size; // ��Ϣͷ�Ĵ�С
    int width; // ͼ����
    int height; // ͼ��߶�
    unsigned short planes; // ��ɫƽ����������Ϊ1
    unsigned short bitCount; // ÿ����λ��
    unsigned int compression; // ѹ������
    unsigned int sizeImage; // ͼ���С������Ϊ0
    int xPelsPerMeter; // ˮƽ�ֱ���
    int yPelsPerMeter; // ��ֱ�ֱ���
    unsigned int clrUsed; // ʹ�õ���ɫ�������Ϊ0������ɫ��Ϊ2��bitCount�η�
    unsigned int clrImportant; // ��Ҫ��ɫ�������Ϊ0����������ɫ������Ҫ��
} BITMAPINFOHEADER;

// ��ȡ��д��BMP�ļ��ļ򵥺���
void AddWatermarkToBMP(const char *inputFile, const char *outputFile) {
    FILE *file = fopen(inputFile, "rb");
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    if (file) {
        // ��ȡ�ļ�ͷ����Ϣͷ
        fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
        fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

        if (fileHeader.type == 0x4D42) { // ����Ƿ�ΪBMP�ļ�
            int width = infoHeader.width;
            int height = abs(infoHeader.height);
            int row_padded = (width * 3 + 3) & (~3);
            unsigned char* data = (unsigned char*)malloc(row_padded);

            fseek(file, fileHeader.offset, SEEK_SET);
            FILE *output = fopen(outputFile, "wb");

            if (output) {
                // д��ԭʼ���ļ�ͷ����Ϣͷ
                fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, output);
                fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, output);

                // ����ÿһ������
                for (int i = 0; i < height; i++) {
                    fread(data, row_padded, 1, file);
                    // ��������޸�data�����ˮӡ
                    // ���磬���Ըı�ÿ�еĿ�ʼ��������Ϊ�ض���ɫ
                    fwrite(data, row_padded, 1, output);
                }
                free(data);
                fclose(output);
            }
            fclose(file);
        }
    }
}

int main() {
    AddWatermarkToBMP("input.bmp", "output.bmp");
    return 0;
}
```

�������ֻ��һ����ܣ�ʵ�����ˮӡ���߼���������ͼ����������ֻ���ͼ������Ҫ����ݾ��������һ�������������ͨ���޸����������������򵥵�ͼ������������Ϊˮӡ��






