.686
.model flat
public _dot_product

.code

_dot_product PROC
	push ebp
	mov ebp, esp
	sub esp, 4 ; wynik
	push ebx
	push esi
	mov ebx, [ebp + 8] ; tab1
	mov edi, [ebp + 12] ; tab2
	mov esi, 0; indeks wektorow
	mov ecx, [ebp + 16] ; n

	xor eax, eax ; bufor
	xor edx, edx ; starsza czesc mul na 0
	mov [ebp-4], dword ptr 0

	ptl:
		mov eax, [ebx + 4*esi]
		imul dword ptr [edi + 4*esi]
		add [ebp - 4], eax
		inc esi
	loop ptl

	mov eax, [ebp - 4]

	pop esi
	pop ebx
	add esp, 4
	pop ebp
	ret
_dot_product ENDP

END