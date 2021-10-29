## 해당 코드는 
1. First Process가 공유메모리를 만들고 
2. 5초 후에 공유메모리에 1의 값을 써주는 작업 
3. Second Process는 First Process가 만든 공유메모리를 자신의 프로세스에 연결
4. 값을 계속 읽다가 1의 값이 읽히는 순간 종료되는 프로그램

## Shared Memory 자료구조 
 - 공유 메모리 정보 (shmid_ds)
 - Include
   #include <sys/types.h>
   #include <sys/shm.h>
``` 
  struct shmid_ds {
   struct           ipc_perm shm_perm;  // Permission
   int              shm_segsz;          // 메모리 공간의 크기
   time_t           shm_atime;          // 마지막 Attached 시간
   time_t           shm_dtime;          // 마지막 Detach 시간
   time_t           shm_ctime;          // 마지막 Change 시간
   unsigned short   shm_cpid;           // 생성프로세스의 PID
   unsigned short   shm_lpid;           // 마지막으로 작동한 프로세스의 PID
   short            shm_nattch;         // 현재 접근한 프로세스의 수
 }
```
## Shared Memory 함수
 - int shmget(key_t key, int size, int shmflg)
  : 커널에 공유 메모리 공간 할당을 요청 (shmflg : 접근권한, 생성방식)

 - void *shmat( int shmid, const void *shmaddr, int shmflg )
  : 공유 메모리 공간을 생성한 이후, 공유메모리에 접근할 수 있는 int형의 "식별자"를 얻는다
  (식별자, 메모리가 붙을 주소 (0을 사용할 경우 커널이 메모리가 붙을 주소를 명시), 읽기/쓰기 모드)

 - int shmdt( const void *shmaddr)
  : 프로세스가 더이상 공유 메모리를 사용하지 않을 경우 프로세스와 공유 메모리를 분리시키는 작업
  * 해당 시스템 호출 함수는 현재 프로세스와 공유 메모리를 분리시킬 뿐, 공유 메모리의 공간을 삭제하지 않는다
  * shmdt 가 성공적으로 수행되면 커널은 shmid_ds 의 내용을 갱신, 즉 shm_dtime, shm_lpid, shm_nattch 등의 내용을 갱신 하는데,
    * shm_dtime 는 가장 최근에 dettach (즉 shmdt 를 사용한)된 시간
    * shm_lpid 는 호출한 프로세세의 PID
    * shm_nattch 는 현재 공유 메모리를 사용하는 (shmat 를 이용해서 공유 메모리에 붙어있는) 프로세스의 수 리턴

 - int shmctl(int shmid, int cmd, struct shmid_ds *buf)
  : 공유 메모리를 제어하기 위해 사용
  * 해당 공유 메모리에 대한 소유자, 그룹 등의 허가권을 변경하거나, 공유 메모리 삭제, 공유 메모리의 잠금을 설정하거나 해제하는 작업
  * Option (cmd)
    * IPC_STAT : 공유 메모리 공간에 관한 정보를 가져오기 위해서 사용된다. 정보는 buf에 저장된다.
    * IPC_SET  : 공유 메모리 공간에 대한 사용자권한 변경을 위해서 사용된다. 사용자 권한 변경을 위해서는 슈퍼유저   
                 혹은 사용자 권한을 가지고 있어야 한다.
    * IPC_RMID : 공유 메모리 공간을 삭제하기 위해서 사용된다. 이 명령을 사용한다고 해서 곧바로 사용되는건 아니며,
                 더이상 공유 메모리 공간을 사용하는 프로세스가 없을 때, 즉 shm_nattch 가 0일때 까지 기다렸다가 삭제된다.