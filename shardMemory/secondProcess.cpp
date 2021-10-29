///////////////////////////////////////
//    Second Process Shared Memory    
////////////////////////////////////////
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define  KEY_NUM   1234
#define  MEM_SIZE  4096
using namespace std;
int shmid;
static int SharedMemoryInit();
static int SharedMemoryWrite(char *sMemory, int size);
static int SharedMemoryRead(char *sMemory);
int main(int argc, char *argv[])
{
    char buffer[MEM_SIZE] = {0,};
    SharedMemoryInit();
    
    while(1)
    {
        SharedMemoryRead(buffer);
        if(buffer[0] == 1)
        {
            cout << "Receive data from shared memory!" << endl;
            break;
        }    
    }
    return 0;
}
static int SharedMemoryInit()
{
    void *shmaddr;
    
    if((shmid = shmget((key_t)KEY_NUM, 0, 0)) == -1)
    {
        perror("Shmid failed");
    }
    
    return 0;
}
static int SharedMemoryWrite(char *sMemory, int size)
{
    void *shmaddr;
    
    if((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1)
    {
        perror("Shmat failed");
    }
    
    memcpy((char *)shmaddr, sMemory, size);
    
    if(shmdt(shmaddr) == -1)
    {
        perror("Shmdt failed");
        exit(1);
    }
    return 0;
}
static int SharedMemoryRead(char *sMemory)
{
    void *shmaddr;
    
    if((shmaddr = shmat(shmid, (void *)0, 0)) == (void *)-1)
    {
        perror("Shmat failed");
    }
    
    memcpy(sMemory, (char *)shmaddr, sizeof(sMemory));
    
    if(shmdt(shmaddr) == -1)
    {
        perror("Shmdt failed");
    }
    
    return 0;
}