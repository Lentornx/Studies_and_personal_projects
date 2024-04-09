.386
rozkazy SEGMENT use16
ASSUME CS:rozkazy
;============================================================
obsluga_zegara PROC
												
			push ax
			push bx
			push es
			
			dec cs:counter
			cmp cs:counter, 0
			jne koniec
												
			mov ax, 0B800h						
			mov es, ax
												
			mov bx, cs:licznik
												
			mov byte PTR es:[bx], '*'			; kod ASCII
			mov byte PTR es:[bx+1], 00000101B	; kolor

			dec cs:wirszC
			cmp cs:wirszC, 0
			jne ten_sam_wiersz
				sub bx, 160*23
				add bx, 2
				mov cs:wirszC, 23
			ten_sam_wiersz:

			add bx, 160
												
			cmp bx, 4000
			jb wysw_dalej						
												
			mov bx, 0
									
wysw_dalej:
			mov cs:licznik,bx
			mov cs:counter,2		
			koniec:
			pop es
			pop bx
			pop ax
												
			jmp dword PTR cs:wektor8
				
			counter dw 2
			wirszC dw 23
			licznik dw 320						
			wektor8 dd ?
obsluga_zegara ENDP

;============================================================

zacznij:
			mov al, 0
			mov ah, 5
			int 10
			mov ax, 0
			mov ds,ax							
												
			mov eax,ds:[32]						
			mov cs:wektor8, eax

												
			mov ax, SEG obsluga_zegara			
			mov bx, OFFSET obsluga_zegara		; offset adresu
			cli									
												
			mov ds:[32], bx						; OFFSET
			mov ds:[34], ax						; cz. segmentowa
			sti									
												
aktywne_oczekiwanie:
			mov ah, 1
			int 16H
												
			jz aktywne_oczekiwanie

												
			mov ah, 0
			int 16H
			cmp al, 'x'							
			jne aktywne_oczekiwanie				; skok, gdy inny znak


												
			mov eax, cs:wektor8
			cli
			mov ds:[32], eax					
												
			sti
												
			mov al, 0
			mov ah, 4CH
			int 21H
rozkazy ENDS

nasz_stos SEGMENT stack
			db 128 dup (?)
nasz_stos ENDS

END zacznij
