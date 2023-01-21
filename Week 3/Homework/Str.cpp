// Str 클래스 선언되어있는 Str.h 인클루드, strcpy, strcmp 함수 사용위한 string.h 인클루드
// 동적할당 위한 stdlib.h 인클루드
#include <string.h>
#include <stdlib.h>
#include "Str.h"

// Str 클래스 생성자이며 인자를  정수형으로 인식하고 가능하면 호출
Str::Str(int leng)
{
	// 길이가 0일 때
	if(leng == 0)
	{
		// str 포인터에 널포인터 저장
		str = NULL;
		// 길이는 0으로 저장
		len = 0;
		// 함수 종료
		return;
	}
	// 동적할당으로 인자로 받은 길이의 1 더한 배열 할당(NUL 문자 넣기 위해)
	str = new char[leng + 1];
	// 마지막 글자 뒤 인덱스에 NUL 문자 삽입
	str[leng] = '\0';
	// private에 선언된 변수 len에 길이  저장
	len = leng;
}

// Str클래스 생성자이며 인자를  const char* 타입으로 인식하고 가능하면  호출
Str::Str(const char *neyong)
{
	// neyong이 널포인터 즉 길이가 0인 스트링일 때
	if(neyong == NULL)
	{
		// str 포인터에 널포인터 저장
		str = NULL;
		// 길이는 0으로 저장
		len = 0;
		// 함수 종료
		return;
	}
	// len에 neyong의 길이 저장
	len = strlen(neyong);
	// 동적할당으로 len + 1 길이의 배열 할당(NUL문자 넣기 위해)
	str = new char[len + 1];
	// str에 neyong 복사
	strcpy(str, neyong);
	// 마지막 문자 뒤 인덱스에 NUL문자 삽입
	str[len] = '\0';
}

// 소멸자
Str::~Str()
{
	// 동적할당 된 str 메모리 해제
	delete []str;
}

// 길이 반환 함수
int Str::length(void)
{
	// 길이 저장된 len 반환
	return len;
}

// 저장된 문자열 내용 반환 함수
char* Str::contents(void)
{
	// 저장된 문자열 포인터 반환
	return str;
}

// 저장된str 문자열과 a가  같으면 0 반환, ASCII 코드 기준 a 문자열이 더 클 때 음수 반환
// ASCII 코드 기준 str 문자열이 a보다 더 클 때 양수 반환
// 인자로 문자열이 들어왔을 때 
int Str::compare(const char *a)
{
	// strcmp 함수 사용하면 위 주석과 같은 규칙으로 됨
	return strcmp(str, a);
}

// 인자로 Str 클래스가 들어왔을 때 compare 함수
int Str::compare(class Str& a)
{
	// 지금 이 클래스의 위에 구현한 compare함수 사용해 리턴
	// a의 private부분의 str 접근을 위한 함수로 contents를 사용해compare  인자로 문자열  전달
	return (*this).compare(a.contents());
}

// = 연산자 오버로딩
// 오른쪽에 문자열이 올때
void Str::operator=(const char *a)
{
	// 인자로 받은 문자열이 없으면 즉, NULL 포인터면
	if(a == NULL)
	{
		// str 동적할당 메모리 해제
		delete []str;
		// 길이 0으로 초기화
		len = 0;
		// str 포인터를 NULL포인터로 선언
		str = NULL;
		// 함수 종료
		return;
	}

	// 인자로 받은 문자열의 길이 저장 변수, strlen 사용
	int a_length = strlen(a);

	// str의 길이가 인자로 받은 문자열보다 짧을때
	// 왜냐하면 동적할당을 다시 해줘 크기를 늘려 복사해주기 위해
	if(a_length > len)
	{
		// str 동적할당 메모리 해제
		delete []str;
		// str a 길이의 1 더한 만큼 동적할당(마지막에 NUL문자 넣으려고)
		str = new char[a_length + 1];
	}
	
	// str에 a 복사, strcpy 사용
	strcpy(str, a);
	// str 마지막 문자 뒤에 NUL문자 추가
	str[a_length] = '\0';
	// 길이 저장
	len = a_length;
}

// = 연산자 오버로딩
// 오른쪽에 Str 클래스가 올때
void Str::operator=(class Str& a)
{
	// 위에 구현한= 연산자 오버로딩 이용
	// 인자 클래스의 contents() 메소드 이용해 문자열 받기
	// 그 문자열을 오른쪽으로 해서 클래스 = 문자열 형태 만들기
	(*this)=a.contents();
}
