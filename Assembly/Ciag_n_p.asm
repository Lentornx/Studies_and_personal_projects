.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC
extern __read : PROC
public _main

.data

obszar db 12 dup (?)
dziesiec dd 10
dwanascie dd 12
p dd ?
dekoder db 'AB'

.code

wczytaj_do_EAX_12 PROC 

	push ebx
	push esi
	push edx

	mov esi, 0 ; indeks obszaru roboczego konwersji
	mov eax, 0 ; rejestr wynikowy
	mov edx, 0 ; rejestr roboczy

	poczatek_konwersji:

		mov dl, obszar[esi]

		cmp dl, 10
		je byl_enter
		push edx
		mul dwanascie
		pop edx

		; rozpatrzenie 0-9
			cmp dl, '0'
			jb niepoprawneDane
			cmp dl, '9'
			ja dalej ; moze byc litera A-B

			sub dl, 30h
			jmp wpisuj_do_eax

		dalej: ;rozpatrzenie A-B
			cmp dl, 'A'
			jb niepoprawneDane
			cmp dl, 'B'
			ja dalej2 ; moze byc litera a-b

			sub dl, 55; 'A' = 65 , A ma byc rowne 10, B = 11 itd
			jmp wpisuj_do_eax

		dalej2: ;rozpatrzenie a-b
			
			cmp dl, 'a'
			jb niepoprawneDane
			cmp dl, 'b'
			ja niepoprawneDane

			sub dl, 87; 'a' = 97 , A ma byc rowne 10, B = 11 itd
			jmp wpisuj_do_eax
			
		wpisuj_do_eax:
			add eax, edx
			inc esi 

	jmp poczatek_konwersji

	niepoprawneDane:
	mov eax, 0FFFFFFFFH
	byl_enter:
	

	pop edx
	pop esi
	pop ebx

	ret
wczytaj_do_EAX_12 ENDP

wyswietl_EAX PROC
	pusha
	sub esp, 12
	mov ebx, esp
	mov edi, 10

	dzielenie:
		mov edx, 0 ; zerujemy na potrzebe dzielenia samego eax
		push ebx 
		mov ebx, 12
		div ebx
		pop ebx
		cmp dl, 9 ; sprawdzamy reszta czy jest w przedziale 0-9
		ja litery

		add dl, 30h
		jmp wypisz_do_wyniku

		litery:
		sub dl, 10; zamieniamy na indeks dekodera (dekoder[0] == 'A')
		push edi
		mov edi, edx
		mov dl, dekoder[edi]
		pop edi

		wypisz_do_wyniku:
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

	call wczytaj_do_EAX_12
	cmp eax, 0FFFFFFFFh
	je bladWczytywania
	mov ecx, eax

	;call wyswietl_EAX

	push ecx ; read podmienia wartosc ecx
	push 12
	push OFFSET obszar
	push 0
	call __read
	add esp, 12
	pop ecx

	call wczytaj_do_EAX_12
	cmp eax, 0FFFFFFFFh
	je bladWczytywania
	mov p, eax

	;call wyswietl_EAX

	mov edx, 0 ; dodajnik/odjemnik
	mov bl, 0 ; boolean 1 = dodawanie , 0 = odejmowanie
	mov eax, p

	kolejny_element_ciagu:
		
		or bl, bl
		jz odejmuj
		add eax, edx
		dec bl
		jmp wyswietl_element

		odejmuj:
		sub eax, edx
		inc bl

		wyswietl_element:
		call wyswietl_EAX
		inc edx
	
	loop kolejny_element_ciagu



	bladWczytywania:
	push dword PTR 0
	call _ExitProcess@4

_main ENDP
END