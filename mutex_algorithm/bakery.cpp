/* 
  Bakery 알고리즘
  - 여러 프로세스/스레드에 대한 처리가 가능한 알고리즘.
  - 가장 작은 수의 번호표를 가지고 있는 프로세스가 진입한다.
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

bool flag[5];
int bakery[5];
int i, j, turn;
int main(){
  while(true) {
    flag[i] = true;
    bakery[i] = *max_element(bakery, bakery+5) + 1; // 현재 번호표 + 1
    flag[i] = false;  // 번호표 받으면 false (번호표 수령 완료의 의미)

    for(j = 0; j < 5; j++) {
      while (flag[j]);  // 모든 프로세스의 번호표를 비교하고, 번호표를 받을 때 까지 비교
      while (bakery[j] && bakery[j] < bakery[i] && j < i);  // 프로세스 j 의 실행 조건
    }
  }
  
  //------------- CRITICAL SECTION -------------- //
  
  bakery[i] = 0;  // 임계구역 사용 완료
  return 0;
}
