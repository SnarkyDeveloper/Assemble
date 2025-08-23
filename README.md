# Assemble

## What is this?

Assemble is a programming 'language' written in 100% NASM x86_32. It uses only assembly macros, with the possible addition of a very basic lexer and compiler to make syntax slightly easier.

## Why?

Assemble was made by a bored 14 year old, SnarkyDev (me), right before starting my freshman year in high school. This project was created mostly from a lot of bordem and the hatred of oneself. Well also partly because I wanted to learn a bit more about assembly.

## How does this work?

Assemble works by creating a LOT of macros that expand during post-proccesing. These macros only expand if you use them though, making the final size extremely small and efficent.

## Examples

```asm
%include "macros.inc" ; what makes everything high level
%include "map.inc" ; this is for all chars and syscalls

func printVar ; create a new function
    new string, var, "This is from a variable!\n" ; handles creation of all types and putting it in correct section!
    print "Printing a variable works! Here look: ", var
    for num, 5
        mod number, num, 5
        if number, 0 ; runtime ifs no need for compiler time!
            print "Divisible by 5 \n" ; WIP to convert ints to ascii chars, otherwise would be here!
        endif number, 0 ; end the if statement
    end num ; auto ending for loops :)
end ; automatically handles closing functions, sorry for the lua syntax lol

func main ; start of main function
    print "Hello, world \n" ; supports \n!
    call printVar ; run also works as a keyword alias to call, run is needed in classes
    new int, exitStatus, 0 ; creating ints work too!
    random exitStatus, 1 ; set it to either 0 or 1, but you can set higher for more fun exit codes!
    exit exitStatus ; bum bum bum moment of truth!
; "Classes" exist as well, but not shown here as not fully implemented yet!

```

More inside testMacros.asm. More to come inside a /examples folder soon.

## Contributing

Please open a pull request with all changes you would like to see, I am open to all changes of any sort! Work for a STD-lib will be in progress soon, so contributors would be much appreicated.

## Credits

> None lol I wrote this all myself... in a week... someone kill me
