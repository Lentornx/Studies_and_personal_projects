.686
.model flat
public _convert_to_array
extern _malloc : PROC

.code

_convert_to_array PROC
	push ebp
	mov ebp, esp
	sub esp, 64 ; bufor
	push ebx
	push edi
	push esi

	mov esi, [ebp + 8] ; adres tekst[0]
	lea ebx, [ebp - 64]; baza dla bufora
	mov edi, 0; index dla bufora
	xor edx, edx
	xor ecx, ecx
	xor eax, eax
	jmp konwersja

	do_bufora:
		mov [ebx + 4*edi], eax
		inc edi
		xor eax, eax

		cmp cl, 10
		je alokacja_tab
	konwersja:
		mov cl, [esi] ; pobranie znaku
		inc esi

		cmp cl, ' '
		je do_bufora
		cmp cl, 10
		je do_bufora

		sub cl, 30h
		push ebx
		mov ebx,10
		mul ebx
		add eax, ecx
		pop ebx

	jmp konwersja

	alokacja_tab:
		mov ecx, [ebp + 12]
		mov [ecx], edi
		mov ecx, edi
		lea edi, [edi*4]
		push ecx
		push edi 
		call _malloc ; adres w eax
		add esp, 4
		pop ecx
		
		xor edi, edi ; lecimy do pocz¹tku bufora

	kopiowanie_bufora_do_tab:
		mov edx, [ebx + 4*edi]
		mov [eax + 4*edi], edx
		inc edi
	loop kopiowanie_bufora_do_tab
	

	pop esi 
	pop edi
	pop ebx
	add esp, 64
	pop ebp
	ret
_convert_to_array ENDP

END