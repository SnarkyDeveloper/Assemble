; MACROS FOR EASY ASSEMBLY PROGRAMMING

%ifndef MACROS_INC
%define MACROS_INC
; Ensure this file is only included once


; -- INTERNAL USE MACROS (Marked with __) --

%macro __addVar 2 ; for classes later on, to define everything on a global scope so you can access outside macro only
    ; Usage: N/a. Use new keyword instead
    section .data
        %1: dd %2
    section .text
%endmacro

; -- FUNCTIONS --

; -- very cool macro :3 
%macro func 1-* ; ADD MULTI-PARAM FUNCTIONS. USE RUN MACRO TO RUN WITH PARAMS
    ; just to make it more readable
    %ifidn %1, main():
        section .text
            global _start
        _start:
    %elifidn %1, main
        section .text
            global _start
        _start:

    ; TODO: fix multiparam functions
    ; IDEA: Create end_func label to jmp at end for both funcs multiparam or not
    %elif %0 > 1
        ; multiparam here. using cdecl
        %ifdef endFunc 
            %undef endFunc
        %endif
        section .data
            global %1_PARAM_COUNT
            %1_PARAM_COUNT: equ %0-1 ; remove funcname
        section .text
            global %1
        %1:
            %define endFunc %%endFunc ; so we can undef later
            endFunc:
                popad
                ret
            %%main:
                pushad
                ; user code here
            ; params are at [esp + 4bit] 
            ; call getParam to get specfic param
    %else
        section .text
            global %1
        %1:
            %define endFunc %%endFunc 
            endFunc:
                ret
            %%main:
    %endif
%endmacro

%macro getParam 2
    ; Usage: getParam <storeVar>, <paramIndex>
    ; paramIndex starts from 0
    %if %2 < 0
        %error "Parameter index must be non-negative"
    %endif
    %ifndef %1
        new dword, %1, 0
    %endif
    mov eax, [esp + 4 + (%2) * 4] ; esp+4 is ret addr, +4 per param
    mov [%1], eax
%endmacro

%macro runFunc 1-*
    ; Usage: runFunc <funcname>, <param1>, <param2>, ...
    ; Calls a function with the given parameters.
    %define __funcname %1
    %if %0 > 1
        %assign __i %0-1
        %rep %0-1
            push %{__i+1}
            %assign __i __i-1
        %endrep
    %endif
    call __funcname
    %if %0 > 1
        ; clean up stack (cdecl)
        add esp, (%0-1)*4
    %endif
    %undef __funcname
%endmacro

; -- Loops --

%macro for 2
    ; Usage: for <varname>, <count>
    pushad ; save registers :3
    new dword, %1, 0     ; loop var 
    mov ecx, %2          ; iter count
    xor eax, eax         ; clear eax for the loop start
    mov [%1], eax        ; init loop
%1_loop:
%endmacro

%macro while 3
    ; Usage: while <varname>, mode (>, <, ==), <value>
    new dword, %1, 0
    pushad
    %1_loop:
    mov eax, [%1]
    cmp eax, %3
    ; default to ==
    %ifidni %2, >
        jle %1_loop_end
    %elifidni %2, <
        jge %1_loop_end
    %else
        jne %1_loop_end
    %endif
%endmacro

%macro break 1
    jmp %1_loop_end
%endmacro

%macro end 0-2
    ; Usage: end <loopType>, <varname> OR `end` to end a function
    ; loopType is either 'for' or 'while'
    %if %0 = 2
        %ifidni %1, for
            inc eax
            mov [%2], eax
            dec ecx
            jnz %2_loop
            popad ; YIPPIE RESTORE REGISTERS
        %elifidni %1, while
            inc eax
            mov [%2], eax
            jmp %2_loop
        %2_loop_end:
            popad
        %else
            %error "Unknown loop type for 'end' macro. Use 'for' or 'while'."
        %endif
    %elif %0 = 0
        ; func end
        jmp endFunc
    %else
        %error "Too many parameters for 'end' macro"
    %endif
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

%macro new 1-* ; add class support later
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
    pushad
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
    popad
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

; Reserve space on stack
%macro reserve 2
    ; Usage: reserve <bufname>, <numBytes>
    section .bss
        %1 resb %2
    section .text
%endmacro

; -- Print C-style string macro --
%macro printC 1
    pushad
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
    popad
%endmacro

%macro syscall 0 ; just to map like x64 syscalls
    int 80h
%endmacro


; -- Runtime Ifs --

%macro mod 3
    ; Usage: mod <var>, <val1> <val2>
    ; Sets <var> to <val1> % <val2>
    %ifndef %1
        new dword, %1, 0
    %endif

    %ifidni %2, eax || %ifidni %2, ebx || %ifidni %2, ecx || %ifidni %2, edx
        mov eax, %2
    %else
        mov eax, [%2]
    %endif

    xor edx, edx
    mov ebx, %3
    div ebx
    mov [%1], edx
%endmacro

%macro if 3
    ; Usage: if <var>, mode (>, <, ==), <val>
    ; Doesn't use %if because that is compile-time
    mov eax, [%1]
    cmp eax, %3
    %ifidni %2, >
        jle %1_loop.endif_%1_%3
    %elifidni %2, <
        jge %1_loop.endif_%1_%3
    %else
        jne %1_loop.endif_%1_%3
    %endif
%endmacro

%macro endif 2
    %1_loop.endif_%1_%2:
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

; TODO: Add file i/o to my own std lib 

; -- Classes (WIP) --

; -- TODO: Implement class inheritance, `new class <classname>`, static and class methods --
; Workarounds of how to implement classes in assembly
; Create a helper macro to check if class exists before allowing to run, fail at compile time if not
; Use a global variable to store class instances, and a method to create new instances


; class storage

%macro class 1
    ; Usage: class <classname>
    ; Example: class MyClass
    ; Defines a new class with the given name.

    %ifidn __CLASS_NAME__, %1
        %error "Class '%1' is already defined"
    %endif

    section .data
    global CLASS_%1
    CLASS_%1:
        %define __CLASS_NAME__ %1
        %define __CLASS_STORAGE__ CLASS_%1
%endmacro

%macro method 3
    ; Usage: method <classname>, <methodname>, <static/clsMethod>
    ; Example: method MyClass, myMethod, static
    ; alias of func pretty much
    
    %define __METHOD_NAME__ %2
    %define __METHOD_CLASS__ %1
    %define __METHOD_TYPE__ %3
    %define __METHOD_STORAGE__ CLASS_%1.%2
    func CLASS_%1.%2
%endmacro

%macro value 2-*
    ; Usage: value <classname>.<valuename>, <value>
    ; declare val as symbol

    %ifidn __CLASS_NAME__, %1
        %error "Class '%1' is not defined"
    %endif
    %ifidn __VALSYM__, %1
        %if __VALNAME__, %2 ; check to make sure redefinition is not allowed
            %error "Value '%2' is already defined in class '%1'"
        %endif
    %endif
    %define __VALSYM__ %1
    %define __VALNAME__ %2
    %if %0 >= 2
        %1:
            %ifstr %2
                escapeString %2
            %else
                db %2
            %endif
            %rotate 2
            %rep %0-2
                %ifstr %1
                    escapeString %1
                %else
                    db %1
                %endif
                %rotate 1
            %endrep
        %1_len equ $ - %1
    %else
        %error "Not enough parameters for 'value'"
    %endif

%endmacro

%macro run 1
    ; Usage: run <classname>.<methodname>
    ; Calls a method of the class.
    %ifidn %1, main
        call _start
    %else
        call CLASS_%1
    %endif
%endmacro

%endif