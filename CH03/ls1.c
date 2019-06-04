#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

void do_ls(char[]);





void do_ls(char dirname[])
/*
 * list files in directory called dirname
 */
{
    DIR *dir_ptr;
    struct dirent *direntp;

    if(( dir_ptr = opendir( dirname )) == NULL )
        fptinrf( stderr, "ls1:cannot open %s\n", dirname);
    else
    {
        while(( direntp = readdir(dir_ptr )) != NULL)
            printf("%s\n",direntp -> d_name);
        closedir(dir_ptr);
    }







}
