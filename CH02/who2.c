/* who2.c - 读取 etc/utmp 并列出信息
 * 抑制空白记录
 * 格式化时间
 */

#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<time.h>

/* #define SHOWOST */

void showtime(long);
void show_info(struct utmp *);

int main()
{
    struct utmp utbuf;                      /* 读取信息到这里 */
    int utmpfd;                             /* 从这个描述符读取 */

    if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }

    while(read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
        show_info( &utbuf );
    close(utmpfd);
    return 0;
}

/* show_info()
 *  显示 utmp 结构的内容
 *  人们可读的
 *  如果记录没有用户名，则不显示任何内容
 */

void show_info(struct utmp *utbufp)
{
    if(utbufp -> ut_type != USER_PROCESS)
        return;

    printf("%-8.8s", utbufp -> ut_name);           /* 登录名 */
    printf(" ");
    printf("%-8.8s", utbufp -> ut_line);           /* 终端信息 */
    printf(" ");
    showtime( utbufp -> ut_time );                 /* 显示时间 */
# ifdef SHOWHOST
    if(utbufp -> ut_host[0] != '\0')
        printf("(%s)", utbufp -> ut_host);         /* 主机 */
# endif
    printf("\n");
}

void showtime(long timeval)
/*
 * 用适合人们查看的格式显示时间
 * 使用 ctime 创建一个字符串，然后从中提取部分内容
 * 注意：%12.12s 打印字符串为12字符宽和限制(LIMIT)
 */
{
    char *cp;                                   /* 获取地址时间 */
    cp = ctime(&timeval);                       /* 将时间转换成字符串 */
                                                /* 字符串的模样 */
                                                /* Mon Feb 4 00:46:40 EST 1991 */
                                                /* 0123456789012345 */
    printf("%12.12s", cp+4);                    /* 从 pos 4 中选择12个字符 */
}























