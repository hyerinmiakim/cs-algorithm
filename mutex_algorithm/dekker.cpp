/* 
  Dekker 알고리즘
  - flag와 turn 변수를 통해 임계 구역에 들어갈 프로세스/스레드르 결정하는 방식
    - flag : 프로세스 중 누가 임계영역에 진입할 것인지 나타내는 변수 
    - turn : 누가 임계영역에 들어갈 차례인지 나타내는 변수
*/
#include <stdio.h>
using namespace std;

bool flag[2];
int i, j, turn;
int main(){
  while(true) {
    flag[i] = true;
    while(flag[j]) {
      if(turn == j) { // i 가 진입시도했을 때, j가 실행중이고 차례도 j이라면 기다린다.
        flag[i] = false;
        while(turn == j);
        flag[i] = true; // 끝나면 들어감 (turn이 i가 됨)
      }
    }
  }
  //------------- CRITICAL SECTION -------------- //
  turn = j; // 차례 넘겨줌
  flag[i] = false;
  return 0;
}
