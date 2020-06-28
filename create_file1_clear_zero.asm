; NASM
; int open(user_addr_t path, int flags, int mode);
; write(int fd, const void *buffer, size_t nbytes)
; exit(int status)
        global  _start
        section .text
_start:
		;mov     eax, 5             ; open系统调用号为5
		xor	eax,eax
		mov 	al,5		    ;eax32位，ax是eax的低16位
        mov     ebx, message1       ; 文件名
        ;mov     ecx, 0102o         ; 文件不存在则创建该文件，O_CREAT 0100
				    ; 读和写的方式打开文件，O_RDWR 02
		xor	ecx,ecx
		mov	cl,0102o
        ;mov     edx, 0666o    	    ; 设置文件权限可写,110110110 rw-rw-rw-
				    ; 即对于用户、组、其他均为可读写不执行
		xor	edx,edx
		mov	dx,0666o
        int     0x80        

	
        mov     ebx, eax            ; 文件描述符1：open返回的eax
		;mov     eax, 4             ; write系统调用号为4
		xor	eax,eax
		mov 	al,4
        mov     ecx, message2       ; 要输出的信息
        ;mov     edx, message2.len2 ; 要输出的长度
		xor	edx,edx
		mov	dl,message2.len2
        int     0x80

        ;mov     eax, 1             ; exit系统调用号为1
		xor	eax,eax
		mov 	al,1
        ;mov     ebx, 0             ; 状态码0：正常退出
		xor	ebx,ebx
        int     0x80

        section .data

message1:
        db      "wangzepeng.txt", 0
.len1   equ     $ - message1

message2:
        db      "2017301510036"
.len2   equ     $ - message2

