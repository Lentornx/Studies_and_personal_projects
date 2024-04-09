.686
.model flat
extern _GetSystemDirectoryA@8 : PROC
public _check_system_dir

.code

_check_system_dir PROC
    push ebp
    mov ebp, esp

    sub esp, 100

    push ebx
    push esi
    push edi

    mov ebx, esp

    push 100
    push ebx
    call _GetSystemDirectoryA@8

    mov ecx, eax ; liczba wprowadzonych znakow
    lea esi, [ebp+8] ; znak[0] inputu
    mov edi, ebx ; znak[0] dir
    mov esi, [esi]

petla:        
    mov dl, [esi]
    cmp dl, [edi]
    jne falsz
    inc esi
    inc edi
loop petla

    mov eax, 1
    jmp koniec

falsz:       
    mov eax, 0

koniec:        
    pop edi
    pop esi
    pop ebx
    add esp, 100
    pop ebp
    ret

_check_system_dir ENDP

END