.386
rozkazy SEGMENT use16
	ASSUME cs:rozkazy

obsluga_klawiatury PROC

		push ax
		push cx
		push dx
		in al, 60h

		cmp	al, 77
		jne	dalej1
		mov	cs:kierunek, 0 ;lewo
		jmp	koniec
dalej1:
		cmp	al, 80
		jne	dalej2
		mov	cs:kierunek, 1 ;prawo
		jmp	koniec
dalej2:
		cmp	al, 75
		jne	dalej3
		mov	cs:kierunek, 2 ;gora
		jmp	koniec
dalej3:
		cmp	al, 72
		jne	koniec_klaw
		mov	cs:kierunek, 3 ;dol
koniec_klaw:
		pop dx
		pop cx
		pop ax
		jmp dword PTR cs:wektor9

kierunek db 0
wektor9 dd ?

obsluga_klawiatury ENDP

linia PROC
		push ax
		push bx
		push cx
		push dx
		push di
		push si
		push es

		mov	ax, 0A000H
		mov	es, ax

		mov	bx, cs:pozycja
		cmp	cs:kierunek, 0
		jne	pomin1
		add	bx, 1
pomin1:
		cmp	cs:kierunek, 1
		jne	pomin2
		add	bx, 320
pomin2:
		cmp	cs:kierunek, 2
		jne	pomin3
		sub	bx, 1
pomin3:
		cmp	cs:kierunek, 3
		jne	pomin4
		sub	bx, 320
pomin4:
		mov	al, cs:kolor
		mov	es:[bx], al
		mov	cs:pozycja, bx

		pop es
		pop	si
		pop di
		pop dx
		pop cx
		pop bx
		pop ax

		jmp dword PTR cs:wektor8

pozycja	dw 0
kolor db 14
wektor8 dd ?

linia ENDP

zacznij:

	mov	ah, 0
	mov	al, 13h
	int	10h
	mov	bx, 0
	mov	es, bx

	mov	eax, es:[32]
	mov	cs:wektor8, eax

	mov	ax, SEG linia
	mov	bx, OFFSET linia
	cli
	mov	es:[32], bx
	mov	es:[34], ax
	sti

	mov	eax, es:[36]
	mov	cs:wektor9, eax

	mov ax, SEG obsluga_klawiatury 
    mov bx, OFFSET obsluga_klawiatury

	cli 
    mov es:[36], bx 
    mov es:[38], ax
    sti 

aktywne_oczekiwanie:
	mov	ah, 1
	int	16h

	jz	aktywne_oczekiwanie

	mov	ah, 0
	int	16h
	cmp	al, 'x'
	jne	aktywne_oczekiwanie

	mov	ah, 0
	mov	al, 3
	int	10h
	mov	eax, cs:wektor8
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