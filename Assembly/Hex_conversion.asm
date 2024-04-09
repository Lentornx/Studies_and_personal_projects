.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC
extern __read : PROC
public _main

.data

obszar db 12 dup (?)
dziesiec dd 10
dekoder db '0123456789ABCDEF'

.code

wczytaj_do_EAX PROC 
	push edi
	push ebx
	push ecx

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

		mul DWORD ptr dziesiec
		add eax, ecx
		jmp pobieraj_cyfre

	byl_enter:

	pop ecx
	pop ebx
	pop edi

	ret
wczytaj_do_EAX ENDP

wyswietl_EAX_hex PROC
	pusha

	sub esp, 12
	mov edi, esp
	mov ecx, 8
	mov esi, 1

	konwersja:
		rol eax, 4
		mov ebx, eax
		and ebx, 0000000Fh
		mov dl, dekoder[ebx]
		mov [edi][esi], dl
		inc esi
	loop konwersja

	mov esi, 1
	zerowanie:
		cmp BYTE ptr [edi][esi], '0'
		jnz koniec_zerowania
		mov [edi][esi], BYTE ptr ' '
		bez_zmian:
		inc esi
	jmp zerowanie

	koniec_zerowania:
	mov [edi][0], BYTE ptr 10
	mov [edi][9], BYTE ptr 10

	push 10
	push edi
	push 1
	call __write
	add esp, 24

	popa
	ret
wyswietl_EAX_hex ENDP

_main PROC

	push 12
	push OFFSET obszar
	push 0
	call __read
	add esp, 12

	call wczytaj_do_EAX
	call wyswietl_EAX_hex

	push dword PTR 0
	call _ExitProcess@4

_main ENDP
END