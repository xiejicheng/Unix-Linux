/* filesize.c - 打印 passwd 文件的大小 */
#include<stdio.h>
#include<sys/stat.h>

int main()
{
    struct stat infobuf;                                /* 存储信息的地方 */
    if(stat("/etc/passwd", &infobuf) == -1)             /* 获取信息 */
        perror("/etc/passwd");
    else
        printf("The size of /etc/passwd is %d\n", infobuf.st_size);
}
