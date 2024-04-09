.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC
extern __read : PROC
public _main

.data
	przesuniecie db 2
	magazyn db 80 dup (?)
	ilosc_zn dd ?
.code
_main PROC

	push 80
	push OFFSET magazyn
	push 0
	call __read
	add esp, 12
	dec eax ;odejmujemy entera
	mov ilosc_zn, eax
	mov ecx, eax
	mov esi, 0

	petla:
		cmp magazyn[esi], 32
		jb zly_przedzial
		cmp magazyn[esi], 125
		ja zly_przedzial

		mov al, magazyn[esi]
		add al, przesuniecie
		cmp al, 125
		jna zawiera_sie_w_przedziale
		sub al, 92
		zawiera_sie_w_przedziale:
		zly_przedzial: 
		mov magazyn[esi], al
		inc esi
	loop petla

	push ilosc_zn
	push OFFSET magazyn
	push 1
	call __write
	add esp, 12

	push dword PTR 0
	call _ExitProcess@4
_main ENDP
END