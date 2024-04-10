#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#define WIDTHBYTES(bits) (((bits)+31)/32*4) // ºñÆ®¸Ê ÆÄÀÏ ±Ô°Ý¿¡¼±, °¡·Î¹æÇâ µ¥ÀÌÅÍ Å©±â´Â 4ÀÇ ¹è¼ö(¹ÙÀÌÆ®´ÜÀ§)·Î ÇÑ´Ù.
// ¿Ö?? -> ÀÌÀ¯¸¦ Ã£¾Æ¼­ ·¹Æ÷Æ®¿¡ Ã·ºÎ
#define BYTE unsigned char
FILE* file;// ÆÄÀÏ Æ÷ÀÎÅÍ ¼±¾ð
int rwsize, rwsize2;// °¡·Î ¶óÀÎ ´ç ¹ÙÀÌÆ® ¼ö
BYTE* lpImg;// ÀÔ·Â µ¥ÀÌÅÍ°¡ ÀúÀåµÇ´Â ¸Þ¸ð¸® ÁÖ¼Ò¸¦ Áö½ÃÇÏ´Â Æ÷ÀÎÅÍ
BYTE* lpOutImg;// Ãâ·Â µ¥ÀÌÅÍ°¡ ÀúÀåµÇ´Â ¸Þ¸ð¸® ÁÖ¼Ò¸¦ Áö½ÃÇÏ´Â Æ÷ÀÎÅÍ
RGBQUAD* pRGB;// Lookup Table
BITMAPFILEHEADER hf;// ºñÆ®¸Ê ÆÄÀÏ ÇØ´õ
BITMAPINFOHEADER hinfo;// ºñÆ®¸Ê Á¤º¸ Çì´õ

//void bitof24_to_8bit_gray(void);
void egdt(void); // 5x5 °úÁ¦!!
//void rgbdis();
//void paletteswap();
//int crop();
//void clearinputbuffer();
// ÇÁ·Î±×·¥ ³»ÀÇ ÇÔ¼ö¿¡ ´ëÇÑ ¼±¾ð

int main()
{
	//bitof24_to_8bit_gray();
	//rgbdis();
	//crop();
	//paletteswap();
	egdt();
	return 0;
}
void egdt(void)
{
	int i, j;
	BYTE R, G, B, GRAY;
	BITMAPFILEHEADER ohf; // Ãâ·Â ÆÄÀÏÀ» À§ÇÑ ºñÆ®¸Ê ÆÄÀÏ Çì´õ
	BITMAPINFOHEADER ohinfo; // Ãâ·Â ÆÄÀÏÀ» À§ÇÑ ºñÆ®¸Ê ÆÄÀÏ Á¤º¸ Çì´õ

	// ÇÔ¼ö ½ÃÀÛÀ» ¾Ë¸®´Â Ãâ·Â¹®
	printf("RUN bitof24_to_8bit_gray()\n\n");

	// ÆÄÀÏ ¿ÀÇÂ
	file = fopen("ori.bmp", "rb");
	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}

	// BMP ÆÄÀÏÀÎÁö È®ÀÎ
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);
	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}

	// BMP Çì´õ Á¤º¸ ÀÐ±â
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	
	// BMP Á¤º¸ Ãâ·Â
	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	
	// BMP Çì´õ Á¤º¸ ¹é¾÷
	ohf = hf;
	ohinfo = hinfo;
	
	// ÀÐÀº BMP ÀÌ¹ÌÁö Å©±â °è»ê
	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(8 * ohinfo.biWidth);
	
	// BMP ÀÌ¹ÌÁö µ¥ÀÌÅÍ ¿ÀÇÁ¼Â À§Ä¡·Î ÀÌµ¿
	fseek(file, hf.bfOffBits, SEEK_SET);
	
	// BMP ÀÌ¹ÌÁö µ¥ÀÌÅÍ ¸Þ¸ð¸® ÇÒ´ç ¹× ÆÄÀÏ¿¡¼­ ÀÐ¾î¿À±â
	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	
	// ÆÄÀÏ ´Ý±â
	fclose(file);
	
	// Ãâ·ÂÇÒ ÀÌ¹ÌÁö µ¥ÀÌÅÍ ¸Þ¸ð¸® ÇÒ´ç
	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);
	
	// ¿øº» ÀÌ¹ÌÁö¿¡¼­ Èæ¹é ÀÌ¹ÌÁö·Î º¯È¯
	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++) //?????에 들어갈 반복문 조건
		{
			B = lpImg[i * rwsize + 3 * j + 0];
			G = lpImg[i * rwsize + 3 * j + 1];
			R = lpImg[i * rwsize + 3 * j + 2];
			//¾Õ¼­ ¾ð±ÞÇßµí rwsize´Â °¡·Î ÇÑÁÙÀÇ µ¥ÀÌÅÍ Å©±â´Ù. µû¶ó¼­ ¿©±â¿¡ i¸¦ °öÇÑ´Ù´Â°ÍÀº i+1¹øÂ° ÁÙÀÇ µ¥ÀÌÅÍ¸¦
			//»ç¿ëÇÔÀ» ÀÇ¹ÌÇÑ´Ù. ÇÑÆí ÄÃ·¯¿¡¼­ ÇÑ ÇÈ¼¿´ç µ¥ÀÌÅÍ´Â 3¹ÙÀÌÆ®°¡ ÇÊ¿äÇÏ¹Ç·Î 3*j¸¦ ÇØ¼­ j+1¹øÂ° ÇÈ¼¿·Î ÀÌµ¿ÇÑ´Ù.
			//Áï ¾ÕÀÇ °úÁ¤À» ÅëÇØ  i+1¹øÂ° ÁÙÀÇ j+1¹øÂ°Ä­ÀÇ ÇÈ¼¿ÀÇ µ¥ÀÌÅÍ¸¦ ÀúÀåÇÑ ¹è¿­ÀÇ °ªÀ» È®ÀÎÇÏ°Ô µÈ´Ù.
			//ÀÌ¶§ ¹è¿­ÀÇ À§Ä¡¸¦ +0,+1,+2¸¦ ÇØ¼­ µ¥ÀÌÅÍÀÇ B G R°ªÀ» °¢°¢ ÀúÀåÇÑ´Ù.
			GRAY = (BYTE)(0.299 * R + 0.587 * G + 0.114 * B);
			//°¢°¢ ÀúÀåÇÑ R,G,B°ª¿¡ Àû´çÇÑ °ªÀ» °öÇÏ°í ´õÇØ¼­ ¹à±â°ªÀ» ¸¸µç´Ù
			//ÀÌ °ªµéÀº ¾î¶»°Ô Á¤ÇØÁø°ÍÀÎ°¡? -> Ã£¾Æ¼­ ·¹Æ÷Æ® Ã·ºÎ
			lpOutImg[i * rwsize2 + j] = GRAY;
			//¸¸µç ¹à±â°ªÀ» lpOutImgÀÇ i+1¹øÂ° ÁÙÀÇ j+1¹øÂ°Ä­ÀÇ ÇÈ¼¿ÀÇ µ¥ÀÌÅÍ¸¦ ÀúÀåÇÑ ¹è¿­¿¡ ÀúÀåÇÑ´Ù.
		}
	}

	// x ¹æÇâ°ú y ¹æÇâÀÇ ¿§Áö °¨Áö¸¦ À§ÇÑ Ä¿³Î »ý¼º
	int xk[5][5] = { {2,2,4,2,2},{1,1,2,1,1},{0,0,0,0,0},{-1,-1,-2,-1,-1},{-2,-2,-4,-2,-2} };
	int yk[5][5] = { {2,1,0,-1,-2},{2,1,0,-1,-2},{4,2,0,-2,-4},{2,1,0,-1,-2},{2,1,0,-1,-2} }; //??????????에 들어갈 sobel Gy 값은?
	
	// x ¹æÇâ°ú y ¹æÇâÀÇ ¿§Áö °¨Áö °á°ú¸¦ ÀúÀåÇÒ ¹è¿­ »ý¼º
	int* xedge = (BYTE*)calloc(rwsize2 * ohinfo.biHeight, sizeof(int));
	int* yedge = (BYTE*)calloc(rwsize2 * ohinfo.biHeight, sizeof(int));
	BYTE* edgeout = (BYTE*)calloc(rwsize2 * ohinfo.biHeight, sizeof(int));
	
	// °¢ ÇÈ¼¿¿¡ ´ëÇØ ¿§Áö °¨Áö ¼öÇà
	int initx, inity, lastx, lasty;
	for (int y = 0; y < ohinfo.biHeight; y++)
	{
		for (int x = 0; x < ohinfo.biWidth; x++)
		{
			if (x == 0) //Ä¿³Î ½ÃÀÛ ÀÎµ¦½º
			{
				initx = 2;  //2·Î ÃÊ±âÈ­ ÇØ¼­ ¿¹¿ÜÃ³¸®
			}
			else if (x == 1) // Ä¿³Î ½ÃÀÛ +1 ÀÎµ¦½º
			{
				initx = 1; //1·Î ÃÊ±âÈ­ÇØ¼­ ¿¹¿ÜÃ³¸®
			}
			else
			{
				initx = 0;
			}

			if (x == hinfo.biWidth) //Ä¿³Î ³¡ ÀÎµ¦½º
			{
				lastx = 2; //2·Î ÃÊ±âÈ­ÇØ¼­ ¿¹¿ÜÃ³¸®
			}
			else if (x == hinfo.biWidth - 1) //Ä¿³Î ³¡-1 ÀÎµ¦½º
			{
				lastx = 3; //3À¸·Î ÃÊ±âÈ­ÇØ¼­ ¿¹¿ÜÃ³¸®
			}
			else
			{
				lastx = 4;
			}

			if (y == 0) //Ä¿³Î ½ÃÀÛ ÀÎµ¦½º
			{
				inity = 2; //2·Î ÃÊ±âÈ­ ÇØ¼­ ¿¹¿ÜÃ³¸®
			}
			else if (y == 1) // Ä¿³Î ½ÃÀÛ +1 ÀÎµ¦½º
			{
				inity = 1; //1·Î ÃÊ±âÈ­ÇØ¼­ ¿¹¿ÜÃ³¸®
			}
			else
			{
				inity = 0;
			}

			if (y == ohinfo.biHeight)//Ä¿³Î ³¡ ÀÎµ¦½º
			{
				lasty = 2; //2·Î ÃÊ±âÈ­ÇØ¼­ ¿¹¿ÜÃ³¸®
			}
			else if (y == ohinfo.biHeight - 1) //Ä¿³Î ³¡-1 ÀÎµ¦½º
			{
				lasty = 3; //3À¸·Î ÃÊ±âÈ­ÇØ¼­ ¿¹¿ÜÃ³¸®
			}
			else
			{
				lasty = 4;
			}

			// Ä¿³Î ³» ÇÈ¼¿ °ª°ú °¡ÁßÄ¡¸¦ °öÇØ ¿§Áö °¨Áö
			// ÀÌÁß for ·çÇÁ·Î ÀÌ¹ÌÁöÀÇ ¸ðµç ÇÈ¼¿À» ¼øÈ¸ÇÏ¸ç, ÇØ´ç ÇÈ¼¿À» Áß½ÉÀ¸·Î °¡ÁßÄ¡°¡ Àû¿ëµÈ Ä¿³ÎÀÇ °ªÀ» ±¸ÇÏ°í, xedge, yedge ¹è¿­¿¡ °¢°¢ ´õÇØÁØ´Ù
            // xedge´Â x¹æÇâÀÇ ¿§Áö °­µµ¸¦, yedge´Â y¹æÇâÀÇ ¿§Áö °­µµ¸¦ ³ªÅ¸³½´Ù.
			for (int y1 = inity; y1 <= lasty; y1++)
			{
				for (int x1 = initx; x1 <= lastx; x1++)
				{
					xedge[y * rwsize2 + x] += lpOutImg[(y + y1 - 2) * rwsize2 + (x + x1 - 2)] * (xk[y1][x1] / 3);
					yedge[y * rwsize2 + x] += lpOutImg[(y + y1 - 2) * rwsize2 + (x + x1 - 2)] * (yk[y1][x1] / 3);
				}
			}

			// °è»êµÈ xedge¿Í yedge °ªÀ» ÀÌ¿ëÇÏ¿© ¿§Áö °­µµ¸¦ °è»êÇÏ°í, 255¸¦ ³ÑÀ¸¸é 255·Î Å¬¸®ÇÎ
			if (sqrt(pow(xedge[y * rwsize2 + x], 2) + pow(yedge[y * rwsize2 + x], 2)) > 255)
			{
				edgeout[y * rwsize2 + x] = 255;
			}
			else
			{
				edgeout[y * rwsize2 + x] = sqrt(pow(xedge[y * rwsize2 + x], 2) + pow(yedge[y * rwsize2 + x], 2));
			}
		}
	}
	ohf.bfOffBits += 1024;
	//bfOffBits´Â ½ÇÁ¦ ÆÄÀÏÀÇ È­¸é µ¥ÀÌÅÍ°¡ ½ÃÀÛµÇ´Â °÷ÀÇ À§Ä¡ÀÌ´Ù.
	//ºñÆ®¸ÊÆÄÀÏ¿¡¼­ ºñÆ®¼ö°¡ ³·À¸¸é(1 ~ 8BPP)
	//ºñÆ®¼ö°¡ ³ôÀ» ¶§¿Í(8BPP ÃÊ°ú) ´Þ¸® ColorTableÀÌ ÆÄÀÏÀÇ È­¸é µ¥ÀÌÅÍ¾Õ¿¡ ÀÖ´Ù.
	//µû¶ó¼­ bfOffBits¸¦ 1024¸¸Å­ µÚ·Î ¹Ð¾î¾ß ÇÑ´Ù.
	//1024´Â RGBQUADÀÇ Å©±â(4¹ÙÀÌÆ®) * 256°³ ÆÈ·¹Æ® = 1024´Ù.
	ohinfo.biBitCount = 8;
	//8BPPÀÌ´Ï±î 8ÀÌ´Ù.
	pRGB = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
	//¾Õ¼­ ¸»ÇÑ ColorTableÀ» À§ÇÑ ¸Þ¸ð¸®¸¦ ¼³Á¤ÇÑ´Ù.
	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
		pRGB[i].rgbReserved = i;
	}
	//Èæ¹éÀÌ´Ï±î ±×³É 0ºÎÅÍ 255±îÁö ¼øÂ÷ÀûÀ¸·Î ÀúÀåÇÑ´Ù.
	file = fopen("edge.bmp", "wb"); //???에 들어갈 적당한 개방 모드? w? rb? wb? ...?
	//ÀÌÁ¦ Ãâ·ÂÇÒ ÆÄÀÏÀ» ¾²±â¸ðµå·Î ¿¬´Ù.
	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(pRGB, sizeof(RGBQUAD), 256, file);
	//ºñÆ®¸Ê ÆÄÀÏÀ» ±¸¼ºÇÏ´Â BITMAPFILEHEADER, BITMAPINFOHEADER,RGBQUAD¸¦ ±â·ÏÇÑ´Ù.
	fwrite(edgeout, sizeof(char), rwsize2 * hinfo.biHeight, file);
	//¾Õ¼­ ¿ì¸®°¡ ¸¸µç Ãâ·Â µ¥ÀÌÅÍ¸¦ ±â·ÏÇÑ´Ù.
	fclose(file);
	//ÆÄÀÏÀ» ´Ý´Â´Ù.
	free(lpImg);
	free(lpOutImg);
	free(edgeout);
	free(pRGB);
	free(xedge);
	free(yedge);
	//¸Þ¸ð¸®¸¦ ¹ÝÈ¯ÇÑ´Ù.
	printf("Check edge.bmp!!\n\n");
}
/*
void bitof24_to_8bit_gray(void)
{
	int i, j;
	BYTE R, G, B, GRAY;
	BITMAPFILEHEADER ohf; // Ãâ·Â ÆÄÀÏÀ» À§ÇÑ ºñÆ®¸Ê ÆÄÀÏ Çì´õ
	BITMAPINFOHEADER ohinfo; // Ãâ·Â ÆÄÀÏÀ» À§ÇÑ ºñÆ®¸Ê ÆÄÀÏ Á¤º¸ Çì´õ
	printf("RUN bitof24_to_8bit_gray()\n\n");
	file = fopen("ori.bmp", "rb");// ÆÄÀÏÀ» ÀÐ±â ¸ðµå·Î ¿®
	if (file == NULL)// ÆÄÀÏ ¿­±â¿¡ ½ÇÆÐÇÏ¸é
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file); // ÆÄÀÏÀ» ¿­¾î ÆÄÀÏÀÇ BITMAPFILEHEADER¸¸Å­À» hf¿¡ ÀúÀå
	if (hf.bfType != 0x4D42) // 0X4D42 == BM(¾Æ½ºÅ° ÄÚµå), ºñÆ®¸ÊÆÄÀÏÀº ¸Ç Ã³À½ ½ÃÀÛÀÌ BMÀÌ´Ù. µû¶ó¼­ Ã¹ ºÎºÐÀ» ÀÐ°í, ±× ºÎºÐÀ» ºÐ¼®ÇØ¼­ ºñÆ®¸ÊÀÌ ¾Æ´Ï¸é...
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file); // ÆÄÀÏÀ» ¿­¾î ÆÄÀÏÀÇ BITMAPINFOHEADER¸¸Å­À» hinfo¿¡ ÀúÀå
	printf("File size : %d\n", hf.bfSize); // ÀÔ·Â¹ÞÀº ºñÆ®¸Ê ÆÄÀÏÀÇ Å©±â¸¦ È­¸é¿¡ Ãâ·ÂÇÔ
	printf("offset : %d\n", hf.bfOffBits); // ÀÔ·Â¹ÞÀº ºñÆ®¸Ê ÆÄÀÏ¿¡¼­ ½ÇÁ¦ µ¥ÀÌÅÍ°¡ ½ÃÀÛÇÏ´Â ¿ÀÇÁ¼Â
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight); // ÀÔ·Â¹ÞÀº ºñÆ®¸Ê ÆÄÀÏÀÇ ÇÈ¼¿ °³¼ö¸¦ È­¸é¿¡ Ãâ·ÂÇÔ
	printf("%d BPP \n", hinfo.biBitCount); // ÀÔ·Â¹ÞÀº ºñÆ®¸Ê ÆÄÀÏÀÇ ÇÈ¼¿´ç ºñÆ®¼ö¸¦ Ãâ·Â
	ohf = hf;
	ohinfo = hinfo;
	// ¿øº» ÆÄÀÏ°ú Ãâ·Â ÆÄÀÏÀº °ÅÀÇ À¯»çÇÏ¹Ç·Î Çì´õÆÄÀÏÀ» º¹»çÇØ¼­ »ç¿ëÇÑ´Ù.
	// ´Ü, ÀÏºÎ °ªÀÌ ¹Ù²î´Â °ÍµéÀÌ ÀÖÀ¸¹Ç·Î, ³ªÁß¿¡ ¹Ýµå½Ã ¼öÁ¤ÇØÁà¾ß ÇÑ´Ù.(bfOffBits, biBitCount µî...)
	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(8 * ohinfo.biWidth);
	//ÀÔ·Â ÆÄÀÏ°ú Ãâ·Â ÆÄÀÏ¿¡¼­ °¡·Î ÇÑ ÁÙ´ç µ¥ÀÌÅÍ°¡ ¸îºñÆ®ÀÎÁö ÀúÀåÇÑ´Ù
	//ÀÌ¶§ ÀÔ·ÂÆÄÀÏ¿¡¼­ °¡·ÎÆø°ú(=°¡·ÎÆø¿¡ ÀÖ´Â ÃÑ ÇÈ¼¿ °¹¼ö)
	//ÇÑ ÇÈ¼¿´ç ¹ÙÀÌÆ® ¼ö¸¦ °öÇÏ¸é, ÇÑ ÁÙÀÌ ¸î ºñÆ®¸¦ Â÷ÁöÇÏ´ÂÁö ¾Ë ¼ö ÀÖ´Ù.
	//rwsize2¸¦ °è»êÇÒ ¶§´Â ÀÔ·Â ÆÄÀÏ°ú Ãâ·Â ÆÄÀÏÀÇ ÇÈ¼¿ »çÀÌÁî´Â µ¿ÀÏÇÏ±â ¶§¹®¿¡ ÀÔ·Â ÆÄÀÏÀÇ °¡·ÎÆøÀ» ±×´ë·Î ¾²¸ç
	//8BPP ÆÄÀÏÀÇ ÇÈ¼¿´ç ºñÆ®¼ö´Â 8ºñÆ®ÀÌ¹Ç·Î 8À» °öÇÑ´Ù.
	fseek(file, hf.bfOffBits, SEEK_SET);
	//ºñÆ®¸Ê ÆÄÀÏ¿¡¼­ ½ÇÁ¦ °ªµéÀÌ ÀúÀåµÅ ÀÖ´Â À§Ä¡·Î Æ÷ÀÎÅÍ¸¦ ÀÌµ¿ÇÑ´Ù
	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	//ÀÔ·Â ¹ÞÀº ÆÄÀÏÀ» À§ÇÑ ¸Þ¸ð¸®¸¦ ÇÒ´çÇÑ´Ù
	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	//Æ÷ÀÎÅÍ´Â ÇöÀç ½ÇÁ¦ µ¥ÀÌÅÍ °ªÀÌ ÀúÀåµÈ °÷ÀÇ ¸Ç Ã³À½À¸·Î ÀÌµ¿ÇÑ »óÈ²ÀÌ´Ù. ÀÌ¶§ ÀÌ¹ÌÁöÀÇ ¼¼·ÎÆø°ú(=°¡·ÎÆø¿¡ ÀÖ´Â ÃÑ ÇÈ¼¿ °¹¼ö)
	//ÇÑ ÁÙ´ç ºñÆ®¼ö¸¦ °öÇÏ¸é, ÀüÃ¼ µ¥ÀÌÅÍÀÇ Å©±â°¡ ³ª¿Â´Ù. freadÇÔ¼ö¸¦ ÀÌ¿ëÇØ ÀÌ¹ÌÁöÀÇ µ¥ÀÌÅÍ¸¦ charº¯¼öÀÇ Å©±â¸¸Å­
	//³ª´²¼­ ÀúÀåÇÑ´Ù.
	fclose(file);
	//ÆÄÀÏ»ç¿ëÀÌ ¿Ï·áµÇ¾úÀ¸¹Ç·Î ´Ý´Â´Ù.
	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);
	//Ãâ·ÂÇÑ ÆÄÀÏÀ» À§ÇÑ ¸Þ¸ð¸®¸¦ ÇÒ´çÇÑ´Ù
	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			B = lpImg[i * rwsize + 3 * j + 0];
			G = lpImg[i * rwsize + 3 * j + 1];
			R = lpImg[i * rwsize + 3 * j + 2];
			//¾Õ¼­ ¾ð±ÞÇßµí rwsize´Â °¡·Î ÇÑÁÙÀÇ µ¥ÀÌÅÍ Å©±â´Ù. µû¶ó¼­ ¿©±â¿¡ i¸¦ °öÇÑ´Ù´Â°ÍÀº i+1¹øÂ° ÁÙÀÇ µ¥ÀÌÅÍ¸¦
			//»ç¿ëÇÔÀ» ÀÇ¹ÌÇÑ´Ù. ÇÑÆí ÄÃ·¯¿¡¼­ ÇÑ ÇÈ¼¿´ç µ¥ÀÌÅÍ´Â 3¹ÙÀÌÆ®°¡ ÇÊ¿äÇÏ¹Ç·Î 3*j¸¦ ÇØ¼­ j+1¹øÂ° ÇÈ¼¿·Î ÀÌµ¿ÇÑ´Ù.
			//Áï ¾ÕÀÇ °úÁ¤À» ÅëÇØ  i+1¹øÂ° ÁÙÀÇ j+1¹øÂ°Ä­ÀÇ ÇÈ¼¿ÀÇ µ¥ÀÌÅÍ¸¦ ÀúÀåÇÑ ¹è¿­ÀÇ °ªÀ» È®ÀÎÇÏ°Ô µÈ´Ù.
			//ÀÌ¶§ ¹è¿­ÀÇ À§Ä¡¸¦ +0,+1,+2¸¦ ÇØ¼­ µ¥ÀÌÅÍÀÇ B G R°ªÀ» °¢°¢ ÀúÀåÇÑ´Ù.
			GRAY = (BYTE)(0.299 * R + 0.587 * G + 0.114 * B);
			//°¢°¢ ÀúÀåÇÑ R,G,B°ª¿¡ Àû´çÇÑ °ªÀ» °öÇÏ°í ´õÇØ¼­ ¹à±â°ªÀ» ¸¸µç´Ù
			//ÀÌ °ªµéÀº ¾î¶»°Ô Á¤ÇØÁø°ÍÀÎ°¡? -> Ã£¾Æ¼­ ·¹Æ÷Æ® Ã·ºÎ
			lpOutImg[i * rwsize2 + j] = GRAY;
			//¸¸µç ¹à±â°ªÀ» lpOutImgÀÇ i+1¹øÂ° ÁÙÀÇ j+1¹øÂ°Ä­ÀÇ ÇÈ¼¿ÀÇ µ¥ÀÌÅÍ¸¦ ÀúÀåÇÑ ¹è¿­¿¡ ÀúÀåÇÑ´Ù.
		}
	}
	ohf.bfOffBits += 1024;
	//bfOffBits´Â ½ÇÁ¦ ÆÄÀÏÀÇ È­¸é µ¥ÀÌÅÍ°¡ ½ÃÀÛµÇ´Â °÷ÀÇ À§Ä¡ÀÌ´Ù.
	//ºñÆ®¸ÊÆÄÀÏ¿¡¼­ ºñÆ®¼ö°¡ ³·À¸¸é(1 ~ 8BPP)
	//ºñÆ®¼ö°¡ ³ôÀ» ¶§¿Í(8BPP ÃÊ°ú) ´Þ¸® ColorTableÀÌ ÆÄÀÏÀÇ È­¸é µ¥ÀÌÅÍ¾Õ¿¡ ÀÖ´Ù.
	//µû¶ó¼­ bfOffBits¸¦ 1024¸¸Å­ µÚ·Î ¹Ð¾î¾ß ÇÑ´Ù.
	//1024´Â RGBQUADÀÇ Å©±â(4¹ÙÀÌÆ®) * 256°³ ÆÈ·¹Æ® = 1024´Ù.
	ohinfo.biBitCount = 8;
	//8BPPÀÌ´Ï±î 8ÀÌ´Ù.
	pRGB = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
	//¾Õ¼­ ¸»ÇÑ ColorTableÀ» À§ÇÑ ¸Þ¸ð¸®¸¦ ¼³Á¤ÇÑ´Ù.
	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
		pRGB[i].rgbReserved = i;
	}
	//Èæ¹éÀÌ´Ï±î ±×³É 0ºÎÅÍ 255±îÁö ¼øÂ÷ÀûÀ¸·Î ÀúÀåÇÑ´Ù.
	file = fopen("BW.bmp", "wb");
	//ÀÌÁ¦ Ãâ·ÂÇÒ ÆÄÀÏÀ» ¾²±â¸ðµå·Î ¿¬´Ù.
	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(pRGB, sizeof(RGBQUAD), 256, file);
	//ºñÆ®¸Ê ÆÄÀÏÀ» ±¸¼ºÇÏ´Â BITMAPFILEHEADER, BITMAPINFOHEADER,RGBQUAD¸¦ ±â·ÏÇÑ´Ù.
	fwrite(lpOutImg, sizeof(char), rwsize2 * hinfo.biHeight, file);
	//¾Õ¼­ ¿ì¸®°¡ ¸¸µç Ãâ·Â µ¥ÀÌÅÍ¸¦ ±â·ÏÇÑ´Ù.
	fclose(file);
	//ÆÄÀÏÀ» ´Ý´Â´Ù.
	free(lpImg);
	free(lpOutImg);
	free(pRGB);
	//¸Þ¸ð¸®¸¦ ¹ÝÈ¯ÇÑ´Ù.
	printf("Check BW.bmp!!\n\n");
}
void rgbdis(void)
{
	int i, j;
	printf("RUN rgbdis()\n\n");
	file = fopen("rgbdis.bmp", "rb");
	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);
	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	fseek(file, hf.bfOffBits, SEEK_SET);
	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	lpOutImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize + 3 * j + 0] = lpImg[i * rwsize + 3 * j + 0];  // B
			lpOutImg[i * rwsize + 3 * j + 1] = 0;  // G
			lpOutImg[i * rwsize + 3 * j + 2] = 0;  // R
		}
	}
	hinfo.biBitCount = 24;
	file = fopen("blue.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(lpOutImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	file = fopen("green.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize + 3 * j + 0] = 0;  // B
			lpOutImg[i * rwsize + 3 * j + 1] = lpImg[i * rwsize + 3 * j + 1];  // G
			lpOutImg[i * rwsize + 3 * j + 2] = 0;  // R
		}
	}
	fwrite(lpOutImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	file = fopen("red.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize + 3 * j + 0] = 0;  // B
			lpOutImg[i * rwsize + 3 * j + 1] = 0;  // G
			lpOutImg[i * rwsize + 3 * j + 2] = lpImg[i * rwsize + 3 * j + 2];  // R
		}
	}
	fwrite(lpOutImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	free(lpImg);
	free(lpOutImg);
	printf("Check blue.bmp, green.bmp, red.bmp!!!\n\n");
}
void paletteswap()
{
	int i, j;
	BYTE R, G, B, GRAY;
	RGBQUAD* oripal;
	RGBQUAD* swappal;
	BITMAPFILEHEADER ohf;
	BITMAPINFOHEADER ohinfo;
	printf("RUN paletteswap()\n\n");
	file = fopen("logo.bmp", "rb");
	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);
	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	printf("Palette has %d color \n", hinfo.biClrUsed);
	ohf = hf;
	ohinfo = hinfo;
	oripal = (RGBQUAD*)malloc(sizeof(RGBQUAD) * hinfo.biClrUsed);
	fread(oripal, sizeof(RGBQUAD), hinfo.biClrUsed, file);
	for (i = 0; i < hinfo.biClrUsed; i++)
	{
		printf("Original palette %d B : %d\n", i, oripal[i].rgbBlue);
		printf("Original palette %d G : %d\n", i, oripal[i].rgbGreen);
		printf("Original palette %d R : %d\n\n", i, oripal[i].rgbRed);
	}
	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(ohinfo.biBitCount * ohinfo.biWidth);
	fseek(file, hf.bfOffBits, SEEK_SET);
	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	lpOutImg = lpImg;
	swappal = (RGBQUAD*)malloc(sizeof(RGBQUAD) * hinfo.biClrUsed);
	int buf;
	for (i = 0; i < hinfo.biClrUsed; i++)
	{
		printf("input palette %d B : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbBlue = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		printf("input palette %d G : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbGreen = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		printf("input palette %d R : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbRed = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		printf("\n");
	}
	file = fopen("logo_swap.bmp", "wb");
	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(swappal, sizeof(RGBQUAD), hinfo.biClrUsed, file);
	fwrite(lpOutImg, sizeof(char), rwsize2 * hinfo.biHeight, file);
	fclose(file);
	free(lpImg);
	free(oripal);
	free(swappal);
	printf("logo_swap.bmp!!\n\n");
}
void clearinputbuffer() // ÀÔ·Â ¹öÆÛ Å¬¸®¾î
{
	while (getchar() != '\n');
}
int crop()
{
	int p1x, p1y, p2x, p2y, fi;
	int i, j;
	BITMAPFILEHEADER ohf;
	BITMAPINFOHEADER ohinfo;
	printf("RUN crop()\n\n");
	file = fopen("ori.bmp", "rb");
	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);
	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	printf("P1 x : ");
	scanf("%d", &p1x);
	clearinputbuffer();
	printf("P1 y : ");
	scanf("%d", &p1y);
	clearinputbuffer();
	printf("P2 x : ");
	scanf("%d", &p2x);
	clearinputbuffer();
	printf("P2 y : ");
	scanf("%d", &p2y);
	clearinputbuffer();
	printf("P1 : %4d, %4d\n", p1x, p1y);
	printf("P2 : %4d, %4d\n", p2x, p2y);
	if (p1x<0 || p1x>hinfo.biWidth || p1y<0 || p1y>hinfo.biHeight || p2x<0 || p2x>hinfo.biWidth || p2y<0 || p2y>hinfo.biHeight)
	{
		printf(" check your input!!! \n");
		return -1;
	}
	if (p1x > p2x)
	{
		fi = p1x;
		p1x = p2x;
		p2x = fi;
	}
	if (p1y > p2y)
	{
		fi = p1y;
		p1y = p2y;
		p2y = fi;
	}
	ohf = hf;
	ohinfo = hinfo;
	ohinfo.biWidth = p2x - p1x + 1;
	ohinfo.biHeight = p2y - p1y + 1;
	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(ohinfo.biBitCount * ohinfo.biWidth);
	ohf.bfSize = rwsize2 * ohinfo.biHeight + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	fseek(file, hf.bfOffBits, SEEK_SET);
	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);
	for (i = 0; i < ohinfo.biHeight; i++)
	{
		for (j = 0; j < ohinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize2 + 3 * j + 0] = lpImg[(i + p1y) * rwsize + 3 * (j + p1x) + 0];
			lpOutImg[i * rwsize2 + 3 * j + 1] = lpImg[(i + p1y) * rwsize + 3 * (j + p1x) + 1];
			lpOutImg[i * rwsize2 + 3 * j + 2] = lpImg[(i + p1y) * rwsize + 3 * (j + p1x) + 2];
		}
	}
	file = fopen("crop.bmp", "wb");
	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(lpOutImg, sizeof(char), rwsize2 * ohinfo.biHeight, file);
	fclose(file);
	free(lpImg);
	free(lpOutImg);
	printf("Check crop.bmp!!!\n\n");
}
*/