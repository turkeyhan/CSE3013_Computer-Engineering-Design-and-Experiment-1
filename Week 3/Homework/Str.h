// Str 클래스 선언
class Str
{
	// 외부 접근 어려운 부분
	private :
		// string의 내용
		char *str;
		// string의 길이
		int len;
	// 외부 접근 가능 부분
	public :
		// leng은 string의 길이
		Str(int leng);
		// neyong은 초기화할 내용이 들어감, 인자에 const선언 안할 시 변경될 수 있다는 경고 뜸
		Str(const char *neyong);
		// 소멸자
		~Str();
		// string의 길이를 리턴하는 함수
		int length(void);
		// string의 내용을 리턴하는 함수
		char *contents(void);
		// a의 내용과 strcmp
		int compare(class Str& a);
		// a의 내용과 strcmp, 인자에 const선언 안할 시 변경될 수 있다는 경고 뜸
		int compare(const char *a);
		// string의 값을 대입, 인자에 const선언 안할 시 변경될 수 있다는 경고 뜸
		void operator=(const char *a);
		// Str의 내용을 대입
		void operator=(class Str& a);
};
