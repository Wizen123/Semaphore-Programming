#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void main()
{
    int fd=0;

    key_t key;
    int semid;
    struct sembuf sops;

    /*创建键值*/
    key=ftok("/home",1);   

    /*打开信号量集合*/
    semid= semget(key,1,IPC_CREAT);

    //0.打开文件
    fd=open("./board.txt",O_RDWR|O_APPEND);

    /*获取信号量*/
    sops.sem_num=0;
    sops.sem_op=-1;
    semop(semid,&sops,1);

    //1.向公告文件里写入“英语课考试”
    write(fd,"english exam",12);

    /*释放信号量*/
    sops.sem_num=0;
    sops.sem_op=1;
    semop(semid,&sops,1);

    //2.关闭公告板文件
    close(fd);
}
