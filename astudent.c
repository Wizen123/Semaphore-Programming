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

    /*创建并打开信号量集合*/
    semid= semget(key,1,IPC_CREAT);

    /*初始化信号量为1*/
    semctl(semid,0,SETVAL,1);

    //0.打开文件
    fd=open("./board.txt",O_RDWR|O_APPEND);

    /*获取信号量*/
    sops.sem_num=0;
    sops.sem_op=-1;
    semop(semid,&sops,1);

    //1.向公告文件里写入“数学课”
    write(fd,"class math ",11);

    //2.暂停休息
    sleep(10);

    //3.向公告文件里写入“取消”
    write(fd,"is cancel.",11);

    /*释放信号量*/
    sops.sem_num=0;
    sops.sem_op=1;
    semop(semid,&sops,1);

    close(fd);
}
