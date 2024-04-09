.386
rozkazy SEGMENT use16
    ASSUME cs:rozkazy

obsluga_klawiatury PROC

		push ax
		push cx
		push dx
		in al, 60h

		cmp	al, 77
		jne	nielewo
		mov	cs:kierunek, 0 ;lewo
		jmp	konieck
nielewo:
		cmp	al, 80
		jne	nieprawo
		mov	cs:kierunek, 1 ;prawo
		jmp	konieck
nieprawo:
		cmp	al, 75
		jne	niegora
		mov	cs:kierunek, 2 ;gora
		jmp	konieck
niegora:
		cmp	al, 72
		jne	konieck
		mov	cs:kierunek, 3 ;dol
konieck:
		pop dx
		pop cx
		pop ax
		jmp dword PTR cs:wektor9

kierunek db 4; 4 - nie zmieniaj
wektor9 dd ?

obsluga_klawiatury ENDP
    
linia PROC
    
    push ax
    push bx
    push cx
    push dx
    push es

    dec cs:counter
    cmp cs:counter, 0
    jne koniec

    mov ax, 0A000H
    mov es, ax
    mov al, cs:czarny
    mov bx, cs:pozycja ; x
    mov cx, cs:dl_wiersza ; petla_wiersz counter

    petla_wierszc:
    mov es:[bx], al 

    inc bx
loop petla_wierszc

    sub bx, cs:dl_wiersza
    add bx, 320
    mov cx, cs:dl_wiersza
    dec cs:wielkosc
    cmp cs:wielkosc, 0
    jne petla_wierszc

    mov cs:wielkosc, 100


    cmp cs:kierunek, 0
    jne d1
    cmp cs:lewo,0
    je d1
    add cs:pozycja, 160
    mov cs:lewo,0
    d1:
    cmp cs:kierunek, 2
    jne d2
    cmp cs:lewo,1
    je d2
    sub cs:pozycja, 160
    mov cs:lewo,1
    d2:
    cmp cs:kierunek, 1
    jne d3
    cmp cs:gora, 0
    je d3
    add cs:pozycja, 320*100
    mov cs:gora, 0
    d3:
    cmp cs:kierunek, 3
    jne d4
    cmp cs:gora, 1
    je d4
    sub cs:pozycja, 320*100
    mov cs:gora,1
    d4:
    mov cs:kierunek, 4


 mov al, cs:kolor
    mov bx, cs:pozycja ; x
    mov cx, cs:dl_wiersza ; petla_wiersz counter

petla_wiersz:
    mov es:[bx], al 

    inc bx
loop petla_wiersz

    sub bx, cs:dl_wiersza
    add bx, 320
    mov cx, cs:dl_wiersza
    dec cs:wielkosc
    cmp cs:wielkosc, 0
    jne petla_wiersz

    mov cs:wielkosc, 100

    mov cs:counter, 18

    cmp al, cs:czerwony
    jne nieczerwony
        mov al,cs:zielony
        mov cs:kolor, al
        jmp koniec
    nieczerwony:

    cmp al, cs:zielony
    jne niezielony
        mov al,cs:niebieski
        mov cs:kolor, al
        jmp koniec
    niezielony:

        mov al,cs:czerwony
        mov cs:kolor, al
        jmp koniec

koniec:
    pop es
    pop dx
    pop cx
    pop bx
    pop ax

    jmp dword PTR cs:wektor8

; zmienne
zielony db 2
niebieski db 1
czerwony db 4
kolor db 4
czarny    db 0
dlugosc_lini    dw 320
counter     dw 18
wielkosc    dw 100
dl_wiersza  dw 160
gora db 1
lewo db 1
wektor8     dd ?
pozycja dw 0

linia ENDP

; int 10h - funkcja nr 0 ustawia tryb sterownika graficznego
zacznij:
    mov ah, 0
    mov al, 13h
    int 10h
    mov bx, 0
    mov es, bx
    mov eax, es:[32]
    mov cs:wektor8, eax

    mov ax, SEG linia
    mov bx, OFFSET linia
    cli
    mov es:[32], bx
    mov es:[32+2], ax
    sti

    ; podmiana przerwan klawiatury
    mov eax,es:[36]
    mov cs:wektor9, eax

    mov ax, SEG obsluga_klawiatury ; czêœæ segmentowa adresu
    mov bx, OFFSET obsluga_klawiatury ; offset adresu

    cli ; zablokowanie przerwañ
    mov es:[36], bx ; OFFSET
    mov es:[38], ax ; cz. segmentowa
    sti ;odblokowanie przerwañ

czekaj:
    mov ah, 1
    int 16h
    jz czekaj
    mov ah, 0
    int 16H
    cmp al, 'x' ; porównanie z kodem litery 'x'
    jne czekaj ; skok, gdy inny znak
    mov ah, 0
    mov al, 3h
    int 10h
    mov eax, cs:wektor8
    cli
    mov es:[32], eax
    sti
    mov eax, cs:wektor9
    cli
    mov es:[36], eax
    sti

    mov ax, 4C00h
    int 21h
rozkazy ENDS

stosik  SEGMENT stack
    db 256 dup (?)
stosik ENDS
END zacznij