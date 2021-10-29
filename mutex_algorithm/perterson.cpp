/* 
  Peterson 알고리즘
  - Dekker와 유사하지만, 상대방 프로세스/스레드에게 진입 기회를 양보함.
*/
#include <stdio.h>
using namespace std;

bool flag[2];
int i, j, turn;
int main(){
  while(true) {
    flag[i] = true;
    turn = j;
    while(flag[j] && turn == j) {
      // j 프로세스 실행중 ~.~
    }
  }
  
  //------------- CRITICAL SECTION -------------- //
  
  flag[i] = false;  // 임계구역 사용 완료
  return 0;
}
