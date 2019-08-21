/* ls2.c    -   ls -1
 * 目的是列出一个或多个目录的内容
 * 如果没有 args,使用。在 args 中列出其他文件
 * 使用 stat 和 pwd.h 和 grp.h
 * BUG: try ls2 /tmp
 */

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>

void do_ls(char[]);
void dostat(char* );
void show_file_info(char *, struct stat *);
void mode_to_letters(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int ac, char *av[])
{
    if(ac == 1)
        do_ls(".");
    else
        while(--ac)
        {
            printf("%s:\n", *++av);
            do_ls(*av);
        }
}

void do_ls(char dirname[])
/*
 * 列出名为dirname的文件
 */
{
    DIR *dir_ptr;                               /* 目录 */
    struct dirent *direntp;                     /* 每个条目 */

    if((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls2: cannot open %s\n", dirname);
    else
    {
        while((direntp = readdir(dir_ptr)) != NULL)
            dostat(direntp -> d_name);
        closedir(dir_ptr);
    }
}

void dostat(char *filename)
{
    struct stat info;
    if(stat(filename, &info) == -1)              /* 无法获得 stat */
        perror( filename  );                     /* 原因 */
    else
        show_file_info(filename, &info);
}

void show_file_info(char *filename, struct stat *info_p)
/*
 * 显示有关文件名的信息。 信息存储在 *info_p 结构中
 */
{
    char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
    void mode_to_letters();
    char modestr[11];

    mode_to_letters(info_p -> st_mode, modestr);

    printf("%s", modestr);
    printf("%4d ", (int)info_p -> st_nlink);
    printf("%-8s", uid_to_name(info_p -> st_uid));
    printf("%-8s", gid_to_name(info_p -> st_gid));
    printf("%8ld ", (long)info_p -> st_size);
    printf("%.12s", 4 + ctime(&info_p -> st_mtime));
    printf("%s\n", filename);
}

/*
 * 相关函数列表
 */

/*
 * 这个函数接收一个 mode 值和一个 char 数组，
 * 并将文件类型和对应于 mode 中的九个字母放到 char 数组中
 * 注意：它不编码 setuid、setgid、sticky.
 * 编码！
 */

void mode_to_letters(int mode, char str[])
{
    strcpy(str, "----------");                  /* 默认 = 不转化 */

    if( S_ISDIR(mode) ) str[0] = 'd';           /* 目录? */
    if( S_ISCHR(mode) ) str[0] = 'c';           /* 字符设备 */
    if( S_ISBLK(mode) ) str[0] = 'b';           /* 块设备 */
    
    if(mode & S_IRUSR) str[1] = 'r';            /* 用户的3个权限 */
    if(mode & S_IWUSR) str[2] = 'w';
    if(mode & S_IXUSR) str[3] = 'x';

    if(mode & S_IRUSR) str[4] = 'r';            /* 用户组的3个权限 */
    if(mode & S_IWUSR) str[5] = 'w';
    if(mode & S_IXUSR) str[6] = 'x';

    if(mode & S_IROTH) str[7] = 'r';            /* 其他用户的3个权限 */
    if(mode & S_IWOTH) str[8] = 'w';
    if(mode & S_IXOTH) str[9] = 'x';
}

#include<pwd.h>

char *uid_to_name(uid_t uid)
/*
 * 使用getpw() 返回指向与uid关联的用户名的指针
 */
{
    struct passwd *getpwuid(), *pw_ptr;
    static char numstr[10];

    if((pw_ptr = getpwuid(uid)) == NULL)
    {
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else
        return pw_ptr -> pw_name;
}


#include<grp.h>

char *gid_to_name(gid_t gid)
/*
 * 使用getgrgid(3)，返回指向组号 gid 的指针
 */
{
    struct group *getgrgid(), *grp_ptr;
    static char numstr[10];

    if((grp_ptr = getgrgid(gid)) == NULL)
    {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else
        return grp_ptr -> gr_name;
}



















