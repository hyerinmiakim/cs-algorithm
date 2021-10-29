struct semaphore {
	int count;
    	queueType queue;
};

/* 세마포어 값을 감소 */
void semWait (semaphore s) {
	s.count--;
    if (s.count < 0) 
    {
    	/* 
        이 구역으로 들어왔다는 것은 현재 프로세스(스레드)가 공유 자원에 접근할 수 없다는 것을 의미.
    	  현재 프로세스를 s.queue에 들어가고, 블록 상태로 락된다
       */
    }
} 
/* 세마포어 값을 증가 */
void semSignal (semaphore s) {
	s.count++;
    if (s.count <= 0) 
    {
    	/*
        대기하고 있는 프로세스(스레드)를 s.queue에서 꺼낸어 언락한다.
        꺼낸 프로세스의 상태를 실행 가능으로 변경하고 ready list에 연결
      */
    }
}

const int n = // 프로세스 개수
semaphore s = 1;

void Process (int i) {
	while (true) 
  {
     semWait(s); /* 세마포어 값 감소 */
        
     /* 임계 영역(Critical Section) */
        
     semSignal(s); /* 세마포어 값 증가 */
        
     /* 임계 영역 이후 코드 */
   }
}

void main() {
	parbegin (Process(1), Process(2), ..., Process(n));
}