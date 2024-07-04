## 1. 读取BMP文件的头信息
BMP文件包含一个文件头（包括文件类型、文件大小和偏移量等信息），一个信息头（包括图像宽度、高度和颜色深度等信息），以及随后的像素数据。

## 2. 修改像素数据以添加水印
我们可以选择一个简单的方式来添加水印，比如改变特定区域的像素值来形成文字或者图案。

## 3. 保存修改后的图像
最后，将修改后的像素数据写回到BMP文件中，保存修改。

下面是一个基本的代码框架，展示如何实现这一过程：

``` c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1) // 确保结构体按1字节对齐

// 定义位图文件头结构体
typedef struct {
    unsigned short type; // 文件类型，必须是0x4D42
    unsigned int size; // 文件大小
    unsigned short reserved1; // 保留，必须为0
    unsigned short reserved2; // 保留，必须为0
    unsigned int offset; // 从文件头到实际位图数据的偏移
} BITMAPFILEHEADER;

// 定义位图信息头结构体
typedef struct {
    unsigned int size; // 信息头的大小
    int width; // 图像宽度
    int height; // 图像高度
    unsigned short planes; // 颜色平面数，必须为1
    unsigned short bitCount; // 每像素位数
    unsigned int compression; // 压缩类型
    unsigned int sizeImage; // 图像大小，可以为0
    int xPelsPerMeter; // 水平分辨率
    int yPelsPerMeter; // 垂直分辨率
    unsigned int clrUsed; // 使用的颜色数，如果为0，则颜色数为2的bitCount次方
    unsigned int clrImportant; // 重要颜色数，如果为0，则所有颜色都是重要的
} BITMAPINFOHEADER;

// 读取和写入BMP文件的简单函数
void AddWatermarkToBMP(const char *inputFile, const char *outputFile) {
    FILE *file = fopen(inputFile, "rb");
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    if (file) {
        // 读取文件头和信息头
        fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
        fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

        if (fileHeader.type == 0x4D42) { // 检查是否为BMP文件
            int width = infoHeader.width;
            int height = abs(infoHeader.height);
            int row_padded = (width * 3 + 3) & (~3);
            unsigned char* data = (unsigned char*)malloc(row_padded);

            fseek(file, fileHeader.offset, SEEK_SET);
            FILE *output = fopen(outputFile, "wb");

            if (output) {
                // 写入原始的文件头和信息头
                fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, output);
                fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, output);

                // 处理每一行像素
                for (int i = 0; i < height; i++) {
                    fread(data, row_padded, 1, file);
                    // 这里可以修改data来添加水印
                    // 例如，可以改变每行的开始几个像素为特定颜色
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

这个代码只是一个框架，实际添加水印的逻辑（比如在图像中添加文字或者图案）需要你根据具体需求进一步开发。你可以通过修改像素数据来创建简单的图案或者文字作为水印。






