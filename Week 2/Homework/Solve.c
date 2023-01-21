// 헤더파일 인클루드 해 solve 함수 또한 선언
// C언어 표준 입출력 라이브러리 함수 인클루드
#include "Header.h"

// 1부터 N까지 각 자리 숫자 인자로 받은 포인터 배열에 카운트
void solve(int *cnt_pointer, int N)
{
	// 1부터 N까지 순환
	for(int i = 1; i <= N; i++)
	{
		// i값을 저장할 임시 변수 선언 및 저장
		int temp = i;
		// 저장한 i값이 0이 아닐 때, 반복
		// 자릿수 나누다 마지막에 0이되며 루프 탈출
		while(temp)
		{
			// 10으로 나눈 나머지 저장할 임시 변수 선언 및 저장
			int tmp = temp % 10;
			// cnt 배열에 10으로 나눈 나머지 인덱스의 값을 1 카운트
			cnt_pointer[tmp]++;
			// 하나의 자릿수를 세었으므로 다음 자릿수 알아보기위해
			// while 조건문 안의 임시 변수 temp를 10으로 나눔
			temp /= 10;
		}
	}
	// 함수 종료
	return;
}
