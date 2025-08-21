
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