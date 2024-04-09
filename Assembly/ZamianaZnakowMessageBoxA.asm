.686
.model flat
extern _ExitProcess@4 : PROC
extern _MessageBoxA@16 : PROC
extern _MessageBoxW@16 : PROC
extern __write : PROC 
extern __read : PROC 
public _main

.data
tytulA db 'MessageBoxA', 0
tytulW dw 'M','e','s','s','a','g','e','B','o','x','W', 0
tekst_pocz db 10, 'Prosze napisac jakis tekst '
db 'i nacisnac Enter', 10
koniec_t db ?
magazynA db 80 dup (0)
magazynW dw 80 dup (0)
nowa_linia db 10
liczba_znakow dd ?

.code
_main PROC

	 mov ecx,(OFFSET koniec_t) - (OFFSET tekst_pocz)
	 push ecx
	 push OFFSET tekst_pocz ; adres tekstu
	 push 1 
	 call __write 
	 add esp, 12 

	 push 80 ; maksymalna liczba znakow
	 push OFFSET magazynA
	 push 0 
	 call __read 
	 add esp, 12 

	 mov liczba_znakow, eax

	 mov ecx, eax
	 mov ebx, 0 ; indeks poczatkowy dla MessageBoxA
	 mov edi, 0 ; indeks poczatkowy dla MessageBoxW

	 ptl: mov dl, magazynA[ebx] ; pobranie kolejnego znaku

		 mov ah, 0 ; ustawiamy starsze bity na 00 dla utf-16

		 cmp dl, 0A5H
		 jne niea
		 mov dl, 0A5H
		 mov ax, 0104H
		 niea:

		 cmp dl, 86H
		 jne niec
		 mov dl, 0C6H
		 mov ax, 0106H
		 niec:

		 cmp dl, 0A9H
		 jne niee
		 mov dl, 0CAH
		 mov ax, 0118H
		 niee:

		 cmp dl, 88H
		 jne niel
		 mov dl, 0A3H
		 mov ax, 0141H
		 niel:

		 cmp dl, 0E4H
		 jne nien
		 mov dl, 0D1H
		 mov ax, 0143H
		 nien:

		 cmp dl, 0A2H
		 jne nieo
		 mov dl, 0D3H
		 mov ax, 00D3H
		 nieo:

		 cmp dl, 98H
		 jne nies
		 mov dl, 8CH
		 mov ax, 015AH
		 nies:

		 cmp dl, 0BEH
		 jne nierz
		 mov dl, 0AFH
		 mov ax, 017BH
		 nierz:

		 cmp dl, 0ABH
		 jne niezi
		 mov dl, 8FH
		 mov ax, 0179H
		 niezi:

		 cmp dl, 127 ; sprawdzamy czy kod nale¿y do podstawowego ascii
		 ja nieASCII

			 cmp dl, 'a'
			 jb dalej ; skok, gdy znak nie wymaga zamiany
			 cmp dl, 'z'
			 ja dalej ; skok, gdy znak nie wymaga zamiany
			 sub dl, 20H ; zamiana na wielkie litery
			 dalej:
		 
			mov al, dl ; kopiuje wartosc dla MessageBoxW (ah puste bo to ascii)
		 nieASCII:

		 mov magazynA[ebx], dl 
		 mov magazynW[edi], ax 
		 inc ebx ; inkrementacja indeksu MessageBoxA
		 add edi, 2; inkrementacja indeksu MessageBoxW

		 dec ecx
	 jnz ptl
 
	 ;push liczba_znakow
	 ;push OFFSET magazynA
	 ;push 1
	 ;call __write ; wyswietlenie przeksztalconego tekstu
	 ;add esp, 12 ; usuniecie parametrow ze stosu

	 push 0 
	 push OFFSET tytulA
	 push OFFSET magazynA
	 push 0 ; NULL
	 call _MessageBoxA@16

	  push 0 
	 push OFFSET tytulW
	 push OFFSET magazynW
	 push 0 ; NULL
	 call _MessageBoxW@16

	 push 0
	 call _ExitProcess@4 ; zakonczenie programu
_main ENDP
END