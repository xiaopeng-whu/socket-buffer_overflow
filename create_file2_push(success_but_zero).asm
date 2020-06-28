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
        ;mov     ebx, message1      ; 文件名
		push	0x7478
		push	0x742e676e
		push	0x6570657a
		push	0x676e6177
		mov	ebx,esp		    ; 另一种方法储存字符串变量
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
        ;mov     ecx, message2      ; 要输出的信息
	
		push	0x0036
		push	0x33303031
		push	0x35313033
		push	0x37313032
		mov	ecx,esp		    ; 同理利用堆栈存储字符串
        ;mov     edx, message2.len2 ; 要输出的长度
		xor	edx,edx
		;mov	dl,message2.len2
		mov	dl,13
        int     0x80

        ;mov     eax, 1             ; exit系统调用号为1
		xor	eax,eax
		mov 	al,1
        ;mov     ebx, 0             ; 状态码0：正常退出
		xor	ebx,ebx
        int     0x80

        section .data

