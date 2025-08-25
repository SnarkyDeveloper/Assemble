%include "macros.inc"
%include "map.inc"

class filesystem
    method filesystem, getCwd, static ; run filesystem.getCwd
        ; Return cwd into string "cwd", use printC to display
        %ifdef cwdStr
            mov eax, cwdStr
            ret
        %endif
        reserve cwdBuffer, 256
        ; String is in cwdBuffer & EDI is len
        ; --- getcwd(buf, 256) ---
        mov eax, 183           ; sys_getcwd
        mov ebx, cwdBuffer     ; char *buf
        mov ecx, 256           ; size_t size
        int 80h              

        ; --- find string length of cwd ---
        mov esi, cwdBuffer     ; ESI = buffer ptr
        xor ecx, ecx           ; ECX = length = 0

        .find_len:
            mov al, [esi]          ; load byte
            cmp al, 0              ; terminator check
            je  .len_found
            inc esi
            inc ecx
            jmp .find_len

        .len_found:
            mov edi, ecx           ; save cwd length in EDI
            new dword, cwd, 0
            mov dword [cwd], cwdBuffer
            %define cwdStr cwd
            ret
    end