# cc 변수에 g++ 컴파일러 저장
cc = g++
# cppflags 변수에 컴파일 옵션 저장
cppflags = -W -g
# 만들 실행파일 타켓 저장
target = a.out

# 컴파일 대상들 저장
objects = main.o Str.o

# 컴파일에 옵션주고 컴파일 진행, 그리고 타겟 실행파일 생성
$(target) : $(objects)
	$(cc) $(cppflags) -o $(target) $(objects)

# 모든.cpp 파일을 .o의 오브젝트 파일 생성까지 컴파일
%.o : %.cpp
	$(cc) $(cppflags) -c -o $@ $<

# Str.h 헤더를 사용하는 오브젝트 파일 명시
main.o Str.o : Str.h

# make clean이나 make .PHONY 명령어로 모든 오브젝트 파일과 실행파일 제거 위한 코드
.PHONY : clean
clean :
	rm $(target) $(objects)

