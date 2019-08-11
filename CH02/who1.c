/* who1.c - who 的第一个版本
 * 打开、读取 UTMP文件，并显示结果
 */

#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define SHOWHOST                                /* 包含远程机器的输出*/


int main()
{
    struct utmp current_record;                 /* 在此读信息 */
    int utmpfd;                                 /* 从描述符读取 */
    int reclen = sizeof(current_record);

    if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
        perror( UTMP_FILE );                    /* UTMP_FILE is in utmp.h */
        exit(1);
    }
    while(read(utmpfd, &current_record, reclen) == reclen)
        show_info(&current_record);
    close(utmpfd);
    return 0;                                   /* 进展顺利 */
}

/* 
 * show info()
 * 以人们可读的形式显示 utmp 结构的内容
 * 注意，这些 siezes 不应该使用硬链接
 */

int show_info(struct utmp *utbufp)
{
    printf("%-8.8s", utbufp -> ut_name);      /* 登录名 */
    printf(" ");                                /* 一个空格 */
    printf("%-8.8s", utbufp -> ut_line);      /* 终端设备 */
    printf(" ");
    printf("%10ld", utbufp -> ut_time);      /* 登录时间 */
    printf(" ");
#ifdef SHOWHOST
    printf("(%s)", utbufp -> ut_host);          /* 主机 */
#endif
    printf("\n");                               /* 换行 */
}






















