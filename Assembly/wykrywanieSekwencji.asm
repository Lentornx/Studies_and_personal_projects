.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC 
public _main

.data
	tekst dw 'A','K','O',' ','j','e','s','t',' ','m','o','j',0105H,' ','p','a','s','j',0105H
	koniec db ?
	to_replace db 'moj',0A5H
	replacement db 'XXXX-XXXX'
	koniec_replacement db ?
	replacement_length dd ?
	liczba_bajtow dd ?
	magazyn db 80 dup (?)
	magazyn2 db 80 dup (' ')
	
.code
	_main PROC

		mov eax,0
		mov ax,(OFFSET koniec) - (OFFSET tekst) 
		mov bl, 2
		mov liczba_bajtow, eax
		div bl ; w ax mamy ilosc 2bajtowych slow
		mov ecx, eax
		mov esi, 0 ; indeks tekstu
		mov edi, 0 ; indeks magazynu

		petla: mov dx, tekst[esi]

			 cmp dx, 0105H
			 jne niea
			 mov al, 0A5H
			 niea:

			 cmp dx, 0107H
			 jne niec
			 mov al, 86H
			 niec:

			 cmp dx, 0119H
			 jne niee
			 mov al, 0A9H
			 niee:

			 cmp dx, 0142H
			 jne niel
			 mov al, 88H
			 niel:

			 cmp dx, 0144H
			 jne nien
			 mov al, 0E4H
			 nien:

			 cmp dx, 00F3H
			 jne nieo
			 mov al, 0A2H
			 nieo:

			 cmp dx, 015BH
			 jne nies
			 mov al, 98H
			 nies:

			 cmp dx, 017CH
			 jne nierz
			 mov al, 0BEH
			 nierz:

			 cmp dx, 017AH
			 jne niezi
			 mov al, 0ABH
			 niezi:

			 cmp dh,0
			 jne polski
			 mov al, dl
			 polski:

			 mov magazyn[edi], al 
			 inc edi ; inkrementacja indeksu magazynu
			 add esi, 2; inkrementacja indeksu tekstu

		dec ecx
		jnz petla

		mov ecx, liczba_bajtow
		mov esi, 0
		mov edi, 0

		petla2:
			mov dl, magazyn[esi]
			cmp dl, to_replace[0] ; sprawdzamy czy to pierwsza litera ciagu
			jne nieciag 
			mov bl, magazyn[esi+1]
			cmp bl, to_replace[1]
			jne nieciag 
			mov bl, magazyn[esi+2]
			cmp bl, to_replace[2]
			jne nieciag 
			mov bl, magazyn[esi+3]
			cmp bl, to_replace[3]
			jne nieciag 

			push ecx
			push esi
			mov ecx, (OFFSET koniec_replacement) - (OFFSET replacement) 
			mov esi,0

			petla3:
				 mov dl, replacement[esi]
				 mov magazyn2[edi], dl
				 inc esi
				 inc edi
				 dec ecx
			jnz petla3

			pop esi
			pop ecx
			add esi, 4
			jnz wasReplaced

			nieciag:

			mov magazyn2[edi], dl
			inc edi
			inc esi 

			wasReplaced:
 
			dec ecx
		jnz petla2

		push 80
		push OFFSET magazyn2
		push 1
		call __write ; wyswietlenie przeksztalconego tekstu
		add esp, 12 ; usuniecie parametrow ze stosu

		push 0
		call _ExitProcess@4 ; zakonczenie programu

	_main ENDP
END