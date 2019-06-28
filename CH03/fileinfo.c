#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int ac, char *av[])
{
    struct stat info;

    if(ac>1)
        if( stat(av[1], &info) != -1){
            show_stat_info(av[1], &info);
            return 0;
        }
        else
            perror(av[1]);
    return 1;

}

show_stat_info(char *fname, struct stat *buf)
{
    printf("    mode: %o\n", buf -> st_mode);

}
