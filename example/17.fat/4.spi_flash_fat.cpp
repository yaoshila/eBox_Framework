/*
file   : *.cpp
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.
*/

//STM32 RUN IN eBox
#include "ebox.h"
#include "mmc_sd.h"
#include "wrapperdiskio.h"
#include "ff.h"
#include "w25xxx.h"






static FATFS fs;            // Work area (file system object) for logical drive
FATFS *fss;
DIR DirObject;       //Ŀ¼�ṹ
FIL fsrc;            // �ļ��ṹ
FILINFO FilInfo;
FILINFO FilInfo1;


FRESULT res;

SD sd(&PB12, &spi2);
W25x16 flash(&PA15, &spi1);

u8 mf_scan_files(const char * path)
{
    FRESULT res;
    char *fn;   /* This function is assuming non-Unicode cfg. */
	  char *p; 
#if _USE_LFN
    fileinfo.lfsize = _MAX_LFN * 2 + 1;
    fileinfo.lfname = mymalloc(SRAMIN,fileinfo.lfsize);
#endif
    uart1.printf("�鿴Ŀ¼��%s\r\n",path);

    res = f_opendir(&DirObject,path); //��һ��Ŀ¼
    if (res == FR_OK)
    {
        while(1)
        {
            res = f_readdir(&DirObject, &FilInfo);                   //��ȡĿ¼�µ�һ���ļ�
            if (res != FR_OK || FilInfo.fname[0] == 0) 
            {
                 uart1.printf("===============\r\n");
                break;  //������/��ĩβ��,�˳�
            }
 
#if _USE_LFN
            fn = *fileinfo.lfname ? fileinfo.lfname : fileinfo.fname;
#else
             fn = FilInfo.fname;				  
#endif                                               /* It is a file. */
			 
                 uart1.printf("%s\r\n",FilInfo.fname);
			 FilInfo = FilInfo1;
        }
    }
    else  
    {
        uart1.printf("����%d\r\n",res);

    }
    return res;
}


void fileOpt()
{
    u8 ret;
    u8 buf[100];
    u8 readBuf[6] ;
    u32 bw = 0;
    u32 br = 0;

    for(int i = 0; i < 100; i++)
        buf[i] = '1';
    res = f_open(&fsrc, "0:12345.txt", FA_WRITE | FA_READ | FA_CREATE_ALWAYS); //û������ļ��򴴽����ļ�
    uart1.printf("\r\n");

    if(res == FR_OK)
    {
        uart1.printf("open/make file  O(��_��)O\r\n");
        uart1.printf("file flag:%d\r\n", fsrc.flag);
        uart1.printf("file size��%d\r\n", fsrc.fsize);
        uart1.printf("file ptr(start location)��%d\r\n", fsrc.fptr);
        //		uart1.printf("���ļ���ʼ�غ�:%d\r\n",fsrc.org_clust);
        //		uart1.printf("���ļ���ǰ�غţ�%d\r\n",fsrc.curr_clust);
        uart1.printf("dsect num:%d\r\n", fsrc.dsect);

        f_lseek(&fsrc, 0);
        do
        {
            res = f_write(&fsrc, buf, sizeof(buf), &bw);
            if(res)
            {
                uart1.printf("write error : %d\r\n", res);
                break;
            }
            uart1.printf("write ok!\r\n");
        }
        while (bw < sizeof(buf));  //  �ж��Ƿ�д��(bw > 100����ʾд�����)
    }
    else if(res == FR_EXIST)
        uart1.printf("file exist\r\n");
    else
        uart1.printf("creat/open failed~~~~(>_<)~~~~ %d\r\n", res);
    f_close(&fsrc);//�ر��ļ�

    /////////////////////////////////////////////////////////////////////////////////////
    u32 readsize;
    u32 buflen;
    buflen = sizeof(readBuf);
    res = f_open(&fsrc, "0:12345.txt", FA_READ); //û������ļ��򴴽����ļ�
    if(res == FR_OK)
    {
        uart1.printf("file size��%d\r\n", fsrc.fsize);
    }
    readsize = 0;
    do
    {
        res = f_read(&fsrc, readBuf, buflen, &br);
        if(res == FR_OK)
        {
            uart1.write((const char *)readBuf, sizeof(readBuf));
        }
        else
        {
            uart1.printf("\r\nread failed\r\n");
        }
        readsize += buflen;
        f_lseek(&fsrc, readsize);

    }
    while(br == buflen);
    uart1.printf("\r\nread end\r\n");
    f_close(&fsrc);//�ر��ļ�
    f_mount(&fs, "0:", 0);
}
void setup()
{
    u8 ret;
    ebox_init();
    uart1.begin(115200);

    attach_sd_to_fat(0,&flash);

    res = f_mount(&fs, "0", 1);
    if(res == FR_OK)
        uart1.printf("mount ok!\r\n", res);
    else
        uart1.printf("mount err!err = %d\r\n", res);
    
    fileOpt();
    mf_scan_files("0:");

}


int main(void)
{
    setup();
    while(1)
    {

        //uart1.printf("\r\nrunning��");
        delay_ms(1000);
    }


}



