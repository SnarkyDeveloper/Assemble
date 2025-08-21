; MACROS FOR EASY ASSEMBLY PROGRAMMING

; %define NEWLINE 0x0A

; -- FUNCTIONS --

    ; -- very cool macro :3 
    %macro func 1
    ; just to make it more readable
        %ifidn %1, main():
            section .text
                global _start
            _start:
        %else
            section .text
            global %1
            %1:
        %endif
    %endmacro

    %macro end 0
        ; just to make it more readable
        ret
    %endmacro


; -- INTERNAL MACROS (For internal use mainly) --
%macro escapeString 1
    ; literally just escapes a string :sob:
    %define _s %1
    %assign i 1
    %strlen len _s
    %rep len
        %substr ch _s i 1
        %ifidni ch, "\" ; handle escapes
            %assign i i+1
            %substr esc _s i 1
            %ifidni esc, "n"
                db 10
            %elifidni esc, "t"
                db 9
            %elifidni esc, "\" 
                db 92
            %else
                db "\", esc
            %endif
        %else
            db ch
        %endif
        %assign i i+1
    %endrep
%endmacro

; -- DECLARATIONS --

%macro new 1-*
    ; usage:
    ;   new string myStr, "hello", " ", "world", NEWLINE
    ;   new byte   myByte, 1, 2, 3
    ;   new word   myWord, 1234
    ;   new dword  myDword, 0xDEADBEEF
    ;   new qword  myQword, 0x1122334455667788
    ;   new int    myInt, 42 ; (the answer of life >:3)

    %push
    %define switchback 0
    %ifnidni __SECT__, .data
        section .data
        %define switchback 1
    %endif

    ; ---------- string ----------
    %ifidn %1, string
        %if %0 >= 3
            %2:
                %ifstr %3
                    escapeString %3
                %else
                    db %3
                %endif
                %rotate 3
                %rep %0-3
                    %ifstr %1
                        escapeString %1
                    %else
                        db %1
                    %endif
                    %rotate 1
                %endrep
            %2_len equ $ - %2
        %else
            %error "Not enough parameters for 'new string'"
        %endif
    %endif
    
    ; ---------- byte ----------
    %ifidn %1, byte
        %if %0 >= 3
            %2: db %3
            %rotate 3
            %rep %0-3
                db %1
                %rotate 1
            %endrep
            %2_len equ ($ - %2) / 1
        %else
            %error "Not enough parameters for 'new byte'"
        %endif
    %endif

    ; ---------- word ----------
    %ifidn %1, word
        %if %0 >= 3
            %2: dw %3
            %rotate 3
            %rep %0-3
                dw %1
                %rotate 1
            %endrep
            %2_len equ ($ - %2) / 2
        %else
            %error "Not enough parameters for 'new word'"
        %endif
    %endif

    ; ---------- dword ----------
    %ifidn %1, dword
        %if %0 >= 3
            %2: dd %3
            %rotate 3
            %rep %0-3
                dd %1
                %rotate 1
            %endrep
            %2_len equ ($ - %2) / 4
        %else
            %error "Not enough parameters for 'new dword'"
        %endif
    %endif

    ; ---------- qword ----------
    %ifidn %1, qword
        %if %0 >= 3
            %2: dq %3
            %rotate 3
            %rep %0-3
                dq %1
                %rotate 1
            %endrep
            %2_len equ ($ - %2) / 8
        %else
            %error "Not enough parameters for 'new qword'"
        %endif
    %endif

    ; ---------- int ----------
    %ifidn %1, int
        %if %0 >= 3
            %2: dd %3
            %rotate 3
            %rep %0-3
                dd %1
                %rotate 1
            %endrep
            %2_len equ ($ - %2) / 4
        %else
            %error "Not enough parameters for 'new int'"
        %endif
    %endif

    %pop
    %if switchback
        section .text
    %endif
%endmacro


; -- UTILITY MACROS --

; --- Print macro ---
%macro print 1-*
    pusha
    %assign __i 1
    %rep %0
        %ifstr %1
            jmp %%after%+__i
            %%str%+__i:
                escapeString %1
            %%str%+__i_len equ $ - %%str%+__i
            %%after%+__i:
            mov eax, 4
            mov ebx, 1
            mov ecx, %%str%+__i
            mov edx, %%str%+__i_len
            int 80h
        %elifnum %1
            mov eax, 4
            mov ebx, 1
            mov ecx, %%byte%+__i
            mov edx, 1
            int 80h
            jmp %%done%+__i
            %%byte%+__i: db %1
            %%done%+__i:
        %else
            mov eax, 4
            mov ebx, 1
            mov ecx, %1
            mov edx, %1_len
            int 80h
        %endif
        %rotate 1
        %assign __i __i+1
    %endrep
    popa
%endmacro

; -- random number gen -- 
%macro random 2
; Usage: random <outputVar> <maxValue>
; Generates a random integer in [0, maxValue] inclusive.

    %if %2 < 0
        %error "Max value must be non-negative"
    %endif

    rdtsc
    mov [%1], eax           ; store lower 32 bits of timestamp as seed
    %define LCG_MULTIPLIER 1103515245
    %define LCG_INCREMENT  12345
    %define LCG_MODULUS    0x80000000 ; 2^31 (for 32-bit unsigned)

    mov eax, [%1]          ; load seed
    imul eax, LCG_MULTIPLIER
    add eax, LCG_INCREMENT
    and eax, LCG_MODULUS - 1 ; mod

    %if %2 = 0
        mov [%1], eax       ; just use the random value directly
    %else
        %assign maxPlusOne %2 + 1
        mov ecx, maxPlusOne
        xor edx, edx
        div ecx
        mov [%1], edx       ; store (random % (maxValue+1)) into outputvar
    %endif
%endmacro

%macro argv 2
    ; Usage: argv <storeIndex>, <index>
    ; Loads the pointer to argv[<index>] into eax and stores it in <storeIndex>.
    ; Note: index starts from 0.
    %if %2 < 0
        %error "Index must be above 0"
    %endif

    mov eax, [esp + 4 + (%2) * 4] ; esp+4 for argv[0], esp+8 for argv[1], etc.
    mov [%1], eax
%endmacro

; -- Print C-style string macro --
%macro printC 1
    pusha
    mov eax, [%1]
    test eax, eax
    jz %%done
    mov ecx, eax         ; pointer to string
    mov edx, 0
    %%find_len:
        cmp byte [ecx+edx], 0
        je %%got_len
        inc edx
        jmp %%find_len
    %%got_len:
        mov eax, 4
        mov ebx, 1
        mov ecx, [%1]
        int 80h
    %%done:
    popa
%endmacro

%macro syscall 0 ; just to map like x64 syscalls
    int 80h
%endmacro


; -- exit macro --
%macro exit 1
    ; Usage: exit <status>
    %ifidn __TYPE__ %1, "imm"
        mov eax, 1
        mov ebx, %1
        int 80h
    %elifnum %1
        mov eax, 1
        mov ebx, %1
        int 80h
    %else
        mov eax, 1
        mov ebx, [%1]
        int 80h
    %endif
%endmacro

; -- IN PROGRESS (file ops) --

%macro open 3
    ; Usage: open <buffer> <filename> <mode> 
    ; Opens a file with the specified mode and stores the file descriptor in <buffer>.
    pusha
    %ifidn %3, read
        mov eax, 5          ; sys_open
        mov ebx, %2         ; filename
        mov ecx, 0          ; O_RDONLY
    %elifidn %3, write
        mov eax, 5          ; sys_open
        mov ebx, %2         ; filename
        mov ecx, 1          ; O_WRONLY
    %elifidn %3, readwrite
        mov eax, 5          ; sys_open
        mov ebx, %2         ; filename
        mov ecx, 2          ; O_RDWR
    %else
        %error "Invalid mode for open macro. Use 'read', 'write', or 'readwrite'"
    %endif
    mov edx, 0            ; no special flags
    int 80h               ; call kernel
    mov [%1], eax         ; store file descriptor in buffer
    popa
%endmacro

%macro dynamicAlloc 1
    ; Usage: dynamicAlloc <fd>
    ; Allocates memory dynamically and stores the file descriptor in <fd>.
    pusha
    mov eax, 45          ; sys_mmap
    xor ebx, ebx         ; krnl choose addr
    mov ecx, 4096        ; length = 4096 bytes
    mov edx, 3           ; prot = PROT_READ | PROT_WRITE
    mov esi, 34          ; flags = MAP_PRIVATE | MAP_ANONYMOUS
    xor edi, edi         ; fd = -1 (no file)
    xor ebp, ebp         ; offset = 0
    int 80h              ; call kernel
    mov [%1], eax        ; store allocated memory address in <fd>
    popa
%endmacro

%macro read 2
    ; Usage: read <fd> <buffer>
    ; Reads data from file descriptor <fd> into <buffer>.
    ; Recommended usage is with dynamicAlloc to allocate buffer first.
    pusha
    %ifidn __TYPE__, "imm"
        %error "read macro does not support immediate values for file descriptor"
    %endif

    mov eax, 3          ; sys_read
    mov ebx, %1         ; file descriptor
    mov ecx, %2         ; buffer to read into
    mov edx, 4096       ; number of bytes to read
    int 80h             ; call kernel
    popa
%endmacro

%macro close 1
    ; Usage: close <fd>
    ; Closes the file descriptor <fd>.
    pusha
    %ifidn __TYPE__, "imm"
        %error "close macro does not support immediate values for file descriptor"
    %endif

    mov eax, 6          ; sys_close
    mov ebx, %1         ; file descriptor
    int 80h             ; call kernel
    popa
%endmacro


; -- Classes (WIP) --

; -- TODO: Implement class inheritance, `new class <classname>`, static and class methods --

%macro class 1
    ; Usage: class <classname>
    ; Defines a new class with the given name.
    section .data
    global %1
    %1:
        db "Class: ", `%1`, NEWLINE
        db 0 ; null terminator for string
    section .text
%endmacro

%macro method 2
    ; Usage: method <classname>, <methodname>
    ; alias of func pretty much
    func %1.%2
%endmacro

%macro value 2-*
    ; Usage: value <classname>.<valuename>, <value>
    ; Alias of new for class values
    new string, %1, %2
%endmacro

%macro run 2
    ; Usage: run <classname>, <methodname>
    ; Calls a method of the class.
    %ifidn %1, main
        call _start
    %else
        call %1.%2
    %endif
%endmacro