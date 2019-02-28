    
很难受 这个程序并没有排上用场，因为只能他能做的只是打开目录内的全部文件 ， 而我们只需要当前目录的文件。所以要做一些修改。
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <dirent.h>
    
    int main(int argc, char * argv[])
    {
        DIR *dp;
        struct dirent *dirp;
        if (argc != 2) 
        {
            printf("Usage: ls directory_name");
            exit(1);
        }
        
        //打开指定的目录
        if ((dp = opendir(argv[1])) == NULL)
        {
            printf("can't open %s", argv[1]);
            exit(1);
        }
        
        //遍历目录
        while ((dirp = readdir(dp)) != NULL)
        {
            printf("%s\n", dirp->d_name);
        }
        
        //关闭目录
        closedir(dp);
        return 0;
    }


细节说明：

    struct __dirstream{
        void *__fd;
        char *__data;
        int  __entry_data;
        char *__ptr;
        int __entry_ptr;
        size_t __allocation;
        size_t __size;
        __libc_lock_define (, __lock)
    };
    typedef struct __dirstream DIR;


    struct _finddata_t{
        unsigned attrib; //文件属性（可读可写。。。。）
        time_t time_create;
        time_t time_access; //最后一次访问
        time_t time_write; //最后一次修改
        _fsize_t size;
        char name[_MAX_FNAME]; //文件名
    };

    long _findfirst(char * filespec , struct _finddata_t * fileinfo);
     查找成功返回long 型句柄 ， filespec 表明文件的字符串， 可支持通配符
     fileinfo 存放文件信息的指针

     int _findnext(long handle , struct _finddata_t * fileinfo );
     成功返回 0  ， 否则返回-1
    handle 由_findfirst 返回的句柄。
    fileinfo 存放文件信息的指针

    int _findclose(long handle);
    成功返回0  ， 失败返回-1
    关闭文件句柄。

    DIR * opendir(const char * pathname);
    打开文件

    closedir(dir); 关闭文件

    struct dirent * readdir (dir); //读文件

    struct dirent {
            ino_t          d_ino;       /* inode number */
            off_t          d_off;       /* offset to the next dirent */
            unsigned short d_reclen;    /* length of this record */
            unsigned char  d_type;      /* type of file; not supported by all file system types */
            char           d_name[256]; /* filename */
         }; 
    
    void rewinddir(dir); 用来设置参数dir 目录流目前的读取位置位原来开头的读取位置， 没有返回值的函数
    
    void seekdir(dir , long offset); 设置参数dir目录流当前的读取位置。
    
    示例代码  ：
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <dirent.h>
    #include <string.h>
    #include <sys/types.h>
    #include <algorithm>
    using namespace std;
    bool cmp(string a, string b){
        return a < b;
    }
    int main(){
        //struct __dirstream  typedef struct __dirstream DIR;  
        DIR *dir;
        char str[100];
        string res[100];
        struct dirent *rent;//struct
        dir = opendir(".");
        int cnt = 0;
        while((rent=readdir(dir))){
            strcpy(str, rent->d_name);
            if(str[0] == '.')
                continue;
            if(!str)
                continue;
            //printf("%s  ", str);
            res[cnt++] = str;
        }
        //cout<<"cnt = "<<cnt<<endl;
        sort(res, res+cnt, cmp);
        for(int i=0; i<cnt; i++)
            cout<<res[i]<<"  ";
        puts("");
        closedir(dir);
        return 0;

    }




