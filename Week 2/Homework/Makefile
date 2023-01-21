#컴파일러 gcc로 cc변수에 저장
cc=gcc
#사용할 컴파일 옵션 -W -g를 cflags 변수에 저장
cflags = -W -g
#make할 실행파일을 target변수에 저장
target = main

#컴파일할 대상 파일들을 objects 변수에 저장
objects = main.o Io.o Solve.o

#make 시 컴파일러와  옵션, 그리고 make결과 실행파일, 목적파일들을 구문으로 만듦
$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

#.c파일의 .o파일 생성과정까지 컴파일
%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

#헤더를 포함하는 파일들 명시
main.o Io.o Solve.o : Header.h

#make .PHONY나 makr clean 으로 모든 오브젝트 파일 및 make된 실행파일 제거가능
.PHONY : clean
clean :
	rm $(target) $(objects)
