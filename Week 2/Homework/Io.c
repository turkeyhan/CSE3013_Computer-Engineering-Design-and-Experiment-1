// 헤더파일 인클루드해 Input함수, Output함수 선언
// c언어 표준 입출력  라이브러리 인클루드
#include "Header.h"

// T와 N 값을 입력받기 위한 함수
int Input()
{
	int num;
	scanf("%d", &num);
	return num;
}

// cnt 배열을 출력하기 위한 함수, 인자로 포인터 선언(배열의 시작주소 받기위해)
void Output(int *cnt_pointer)
{
	// 0~9까지 범위이기 때문에 for문의 끝이 정해져있음
	// cnt 배열의 처음부터 끝까지 순환하며 출력
	for(int i = 0; i < 10; i++)
	{
		printf("%d ", cnt_pointer[i]);
	}
	// 하나의 테스트 케이스 출력 끝나고 줄바꿈
	printf("\n");
	return;
}

