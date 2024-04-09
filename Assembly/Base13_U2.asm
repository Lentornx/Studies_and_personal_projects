.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC
extern __read : PROC
public _main

.data

obszar db 12 dup (?)
dziesiec dd 10
mnoznik dd 13 ; mnoznik bazy
p dd ?
dekoder db 'ABC'
znak db '+'
.code

wczytaj_do_EAX_13_U2 PROC 

	push ebx
	push esi
	push edx
	push ecx

	mov esi, 0 ; indeks obszaru roboczego konwersji
	mov eax, 0 ; rejestr wynikowy
	mov edx, 0 ; rejestr roboczy
	mov ecx, 0 ; 0 - dodatnia, 1 - ujemna

	;rozpatrujemy znak 
	mov dl, obszar[esi]
	cmp dl, '-'
	jne poczatek_konwersji
	mov ecx, 1
	inc esi
	poczatek_konwersji:

		mov dl, obszar[esi]

		cmp dl, 10
		je byl_enter
		push edx
		mul mnoznik ; *13
		pop edx

		; rozpatrzenie 0-9
			cmp dl, '0'
			jb niepoprawneDane
			cmp dl, '9'
			ja dalej ; moze byc litera A-C

			sub dl, 30h
			jmp wpisuj_do_eax

		dalej: ;rozpatrzenie A-B
			cmp dl, 'A'
			jb niepoprawneDane
			cmp dl, 'C'
			ja dalej2 ; moze byc litera a-c

			sub dl, 55; 'A' = 65 , A ma byc rowne 10, B = 11 itd
			jmp wpisuj_do_eax

		dalej2: ;rozpatrzenie a-b
			
			cmp dl, 'a'
			jb niepoprawneDane
			cmp dl, 'c'
			ja niepoprawneDane

			sub dl, 87; 'a' = 97 , A ma byc rowne 10, B = 11 itd
			jmp wpisuj_do_eax
			
		wpisuj_do_eax:
			add eax, edx
			inc esi 

	jmp poczatek_konwersji

	niepoprawneDane:
	mov eax, 0
	byl_enter:

	or ecx, ecx ; sprawdzamy znak
	jz dodatnia_liczba

	neg eax

	dodatnia_liczba:
	
	pop ecx
	pop edx
	pop esi
	pop ebx

	ret
wczytaj_do_EAX_13_U2 ENDP

wyswietl_EAX_U2 PROC
	pusha
	sub esp, 12
	mov ebx, esp
	mov edi, 10

	; sprawdzamy pierwszy bit, by stwierdziæ znak
	mov edx, eax
	rol edx, 1 ; przenosimy pierwszy bit na ostatni¹ pozycjê
	and edx, 1 ; zerujemy wszystkie bity oprocz pierwszego ostatniego
	jz dzielenie

	; konwersja wartosci ujemnej liczby
	mov dl, '-'
	mov znak, dl

	neg eax ; flipujemy bity

	dzielenie:
		mov edx, 0 ; zerujemy na potrzebe dzielenia samego eax
		push ebx 
		mov ebx, mnoznik
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

	dodaj_znak:
		mov dl, znak
		mov [ebx][edi], dl ; dodajemy znak
		dec edi
		
	spacjuj:
		or edi, edi
		jz wypisz
		mov [ebx][edi], BYTE ptr ' '
		dec edi
	jmp spacjuj

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
wyswietl_EAX_U2 ENDP

_main PROC

	push 12
	push OFFSET obszar
	push 0
	call __read
	add esp, 12

	call wczytaj_do_EAX_13_U2
	sub eax, 10
	call wyswietl_EAX_U2

	push dword PTR 0
	call _ExitProcess@4

_main ENDP
END