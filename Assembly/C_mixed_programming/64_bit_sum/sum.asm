public sum

.code

sum PROC
push rbp
mov rbp,rsp
push rdi

xor rax, rax

cmp rcx, 0
	je koniec
	add rax, rdx

cmp rcx, 1
	je koniec
	add rax, r8

cmp rcx, 2
	je koniec
	add rax, r9

cmp rcx, 3
	je koniec

sub rcx, 3
mov rdi, 0
dodaj_kolejny:
	add rax, [rbp + 16 + 32 + 8*rdi]
	inc rdi
loop dodaj_kolejny

koniec:
	pop rdi
	pop rbp
	ret
sum ENDP

END