/** ls1.c
 ** 目的是列出一个或多个目录的内容
 ** 如果没有 args ，那就，在 args 中列出其他文件
 **/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

void do_ls(char[]);

int main(int ac, char *av[])
{
    if (ac == 1)
        do_ls(".");
    else
        while( --ac  ){
            printf("%s:\n:, *++av");
            do_ls(*av);
        }
}

void do_ls(char dirname[])
/*
 * 列出目录中名为 dirname 的文件
 */
{
    DIR *dir_ptr;                            /* 这个目录 */
    struct dirent *direntp;                  /* 每个条目 */

    if((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls1: cannot open %s\n", dirname);
    else
    {
        while((direntp = readdir(dir_ptr)) != NULL)
            printf("%s\n", direntp -> d_name);
        closedir(dir_ptr);
    }
}
