.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC
extern __read : PROC
public _main

.data

obszar db 12 dup (?)
dziesiec dd 10

.code

wczytaj_do_EAX_hex PROC 

	push ebx
	push esi
	push edx

	mov esi, 0 ; indeks obszaru roboczego konwersji
	mov eax, 0 ; rejestr wynikowy
	mov edx, 0

	poczatek_konwersji:

		mov dl, obszar[esi]

		cmp dl, 10
		je byl_enter
		rol eax, 4

		; rozpatrzenie 0-9
			cmp dl, '0'
			jb poczatek_konwersji ; pomijamy bledny znak
			cmp dl, '9'
			ja dalej ; moze byc litera A-F

			sub dl, 30h
			jmp wpisuj_do_eax

		dalej: ;rozpatrzenie A-F
			cmp dl, 'A'
			jb poczatek_konwersji ; pomijamy bledny znak
			cmp dl, 'F'
			ja dalej2 ; moze byc litera a-f

			sub dl, 55; 'A' = 65 , A ma byc rowne 10, B = 11 itd
			jmp wpisuj_do_eax

		dalej2: ;rozpatrzenie a-f
			
			cmp dl, 'a'
			jb poczatek_konwersji ; pomijamy bledny znak
			cmp dl, 'f'
			ja poczatek_konwersji ; pomijamy bledny znak

			sub dl, 87; 'a' = 97 , A ma byc rowne 10, B = 11 itd
			jmp wpisuj_do_eax
			
		wpisuj_do_eax:
			add eax, edx
			inc esi 

	jmp poczatek_konwersji

	byl_enter:

	pop edx
	pop esi
	pop ebx

	ret
wczytaj_do_EAX_hex ENDP

wyswietl_EAX PROC
	pusha
	sub esp, 12
	mov ebx, esp
	mov edi, 10

	dzielenie:
		mov edx, 0
		push ebx
		mov ebx, 10
		div ebx
		pop ebx
		add dl, 30h
		mov [ebx][edi], dl 
		dec edi
		cmp eax, 0
	jnz dzielenie

	zeruj:
		or edi, edi
		jz wypisz
		mov [ebx][edi], BYTE ptr ' '
		dec edi
	jmp zeruj

	wypisz:
		mov [ebx][0], BYTE ptr 10
		mov [ebx][11], BYTE ptr 10

		push dword PTR 12 
		push ebx
		push dword PTR 1
		call __write 
		add esp, 24 ;12 + 12

	popa
	ret
wyswietl_EAX ENDP

_main PROC

	push 12
	push OFFSET obszar
	push 0
	call __read
	add esp, 12

	call wczytaj_do_EAX_hex
	call wyswietl_EAX

	push dword PTR 0
	call _ExitProcess@4

_main ENDP
END