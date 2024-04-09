.686
.model flat
public _rozmiar
extern _malloc : PROC

.code

_rozmiar PROC
	push ebp
	mov ebp, esp
	sub esp, 64 ; bufor
	push ebx
	push edi
	push esi
	

	pop esi 
	pop edi
	pop ebx
	add esp, 64
	pop ebp
	ret
_rozmiar ENDP

END