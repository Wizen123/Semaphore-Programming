#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

void main()
{

    key_t key=0;
    int semid;
    struct sembuf sops;

    /*创建键值*/
    key=ftok("/root",2);   

    /*打开信号量集合*/
    semid= semget(key,1,IPC_CREAT);

    /*获取信号量*/
    sops.sem_num=0;
    sops.sem_op=-1;
    sops.sem_flg=SEM_UNDO;
    semop(semid,&sops,1);

    //取走产品文件
    system("cp ./product.txt ./ship/");
}
