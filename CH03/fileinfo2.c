/* fileinfo.c - 使用 stat() 获取和打印文件属性
 *            - 有限成员只是数字...
 */

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int ac, char *av[])
{
    struct stat info;                   /* 文件信息缓冲区 */

    if(ac > 1)
        if(stat(av[1], &info) != -1)
        {
            show_stat_info( av[1], &info );
            return 0;
        }
        else
        {
            perror(av[1]);              /* stat() 错误报告 */
        }
    return 1;
}

int show_stat_info(char *fname, struct stat *buf)
/*
 * 以 name = value 格式显示来自 stat 的一些信息
 */
{
    printf("    mode: %o\n", buf -> st_mode);       /* 类型 + 模式 */
    printf("    links: %d\n", buf -> st_nlink);     /* #链接 */
    printf("    user: %d\n", buf -> st_uid);        /* 用户id */
    printf("    group: %d\n", buf -> st_gid);       /* 用户组id */
    printf("    size: %d\n", buf -> st_size);       /* 文件大小 */
    printf("    modtime: %d\n", buf -> st_mtime);   /* 修改时间 */
    printf("    name: %d\n", fname);                /* 文件名 */
}
