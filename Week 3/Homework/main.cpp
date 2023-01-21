// C++ 입출력 스트림 라이브러리 include, std::cout 사용 위한 것
#include <iostream>
// Str.h에 선언된 클래스 사용 위해 include
#include "Str.h"
// std namespace 따로 std:: 선언 없이 사용
using namespace std;

// Str 클래스 test 위한 main 함수
int main()
{
	// Str 클래스의 인자가 있는 선언으로 해당 생성자 호출
	Str a("I'm a girl");
	Str b(0);
	// Str 클래스 내 구현된 contents 메소드 사용
	cout << a.contents() << endl;
	// Str 클래스 내 연산자 오버로팅 사용
	a = "I'm a boy\n";
	// 연산자 오버로딩으로 잘 바뀌었는지 출력으로  확인
	cout << a.contents();
	// Str 클래스 내 구현된 compare 메소드 사용 및 출력
	cout << a.compare("I'm a a") << endl;
	// 연산자 오버로딩 클래스와 클래스 확인
	a = b;
	// NULL 포인터로 잘 바뀌었는지 확인
	if(a.contents() == NULL)
	{
		// a의 str이 NULL 포인터면 NULL 문자열 출력
		cout << "NULL" << endl;
	}
	// a와 b값 초기화
	a = "g++";
	b = "gcc";
	// a 클래스에서 b 클래스를 인자로 받아 compare 출력
	cout << a.compare(b) << endl;
	// a 클래스와 b 클래스의 길이 출력
	cout << a.length() << ' ' << b.length() << endl;
	// main 함수 종료
	return 0;
}
