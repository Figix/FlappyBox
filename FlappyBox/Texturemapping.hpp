#define _CRT_SECURE_NO_WARNINGS

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

static GLuint textGameStart;
static GLuint textGameOver;

using namespace std;

//��Ʈ�� ����� �� �������� �ٽ� ����ü�� �������. �Լ�ó���� ���ϰ� �Ϸ�����.
namespace BoxGame {
    typedef struct tagBITMAPHEADER {
        BITMAPFILEHEADER bf;
        BITMAPINFOHEADER bi;
        RGBQUAD hRGB[256];
    }BITMAPHEADER;

    BYTE* LoadBitmapFile(BITMAPHEADER* bitmapHeader, int* imgSize, const char* filename)
    {
        FILE* fp = fopen(filename, "rb");	//������ �����б���� ����
        if (fp == NULL)
        {
            printf("���Ϸε��� �����߽��ϴ�.\n");	//fopen�� �����ϸ� NULL���� ����
            return NULL;
        }
        else
        {
            fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);	//��Ʈ��������� �б�
            fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);	//��Ʈ��������� �б�
            fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);	//�����ȷ�Ʈ �б�

            int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;	//�̹��� ������ ���
            *imgSize = imgSizeTemp;	// �̹��� ����� ���� ������ �Ҵ�

            BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSizeTemp);	//�̹���ũ�⸸ŭ �޸��Ҵ�
            fread(image, sizeof(BYTE), imgSizeTemp, fp);//�̹��� ũ�⸸ŭ ���Ͽ��� �о����
            fclose(fp);


            return image;
        }
    }
    void init_texture_GameStart(void)
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);

        BITMAPHEADER originalHeader;	//��Ʈ���� ����κ��� ���Ͽ��� �о� ������ ����ü
        int imgSize;			//�̹����� ũ�⸦ ������ ����
        BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "GameText.bmp"); //��Ʈ�������� �о� ȭ�������� ����
        
        if (image == NULL) return;        //���� �б⿡ �����ϸ� ���α׷� ����
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &textGameStart);
        glBindTexture(GL_TEXTURE_2D, textGameStart);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_GREEN, GL_BYTE, image);
    }
    void init_texture_GameOver(void) {
        glClearColor(0.0, 0.0, 0.0, 1.0);

        BITMAPHEADER originalHeader;	//��Ʈ���� ����κ��� ���Ͽ��� �о� ������ ����ü
        int imgSize;			//�̹����� ũ�⸦ ������ ����
        BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "GameText2.bmp"); //��Ʈ�������� �о� ȭ�������� ����
        if (image == NULL) return;        //���� �б⿡ �����ϸ� ���α׷� ����

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(1, &textGameOver);
        glBindTexture(GL_TEXTURE_2D, textGameOver);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RED, GL_BYTE, image);
    }
}