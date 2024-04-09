.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC
extern __read : PROC
public _main

.data

obszar db 36 dup (?)
dziesiec dd 10
w2 dd ?
w1 dd ?
w0 dd ?
r dd ?

.code

wyswietl_96bit PROC
	pusha
	sub esp, 36
	mov ebx, esp
	mov edi, 34

	dzielenie:
		mov edx, 0
		push ebx
        mov ebx, 10

        mov eax, w2
		div ebx
        mov w2, eax

        mov eax, w1
		div ebx
        mov w1, eax

        mov eax, w0
		div ebx
        mov w0, eax

		pop ebx

		add dl, 30h
		mov [ebx][edi], dl 
		dec edi
		or eax, w1
        jnz dzielenie
        mov eax, w2
        or eax, eax
        jz zeruj
	jmp dzielenie

	zeruj:
		or edi, edi
		jz wypisz
		mov [ebx][edi], BYTE ptr ' '
		dec edi
	jmp zeruj

	wypisz:
		mov [ebx][0], BYTE ptr 10
		mov [ebx][35], BYTE ptr 10

		push dword PTR 36 
		push ebx
		push dword PTR 1
		call __write 
		add esp, 48 

	popa
	ret
wyswietl_96bit ENDP

wczytaj_96bit PROC 
	push edi
	push ebx
	push edx
    push ecx

    mov ecx, 0 
    mov edx, 0
	mov eax, 0
	mov edi, esp
	mov ebx, OFFSET obszar

	pobieraj_cyfre:
		mov cl, [ebx]

		cmp cl, 10 ;porownujemy z enterem
		je byl_enter

		sub cl, 30H
		movzx ecx, cl
		inc ebx

        mov eax, w0
		mul DWORD ptr dziesiec
		add eax, ecx
        mov w0, eax
        adc edx, 0
        mov r,edx
        
        mov eax, w1
        mul dziesiec
        add eax, r
        mov w1, eax 
        adc edx, 0
        mov r,edx

        mov eax, w2
        mul dziesiec
        add eax, r
        mov w2, eax 
      
	jmp pobieraj_cyfre

	byl_enter:

    pop ecx
	pop edx
	pop ebx
	pop edi

	ret
wczytaj_96bit ENDP

_main PROC
    
    mov w2, 0
    mov w1, 0
    mov w0, 0

    push 36
    push OFFSET obszar
    push 0
    call __read
    add esp, 12

    call wczytaj_96bit

	call wyswietl_96bit

	push dword PTR 0
	call _ExitProcess@4

_main ENDP
END