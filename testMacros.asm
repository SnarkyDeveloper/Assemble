%include "map.inc"
%include "macros.asm"
new string, outside, "This variable is defined outside any section", newline 
new string, example, "print ", doublequote, "yay newlines with escapes \\n", doublequote


class cats
    value cats.calico, "A calico cat is a domestic cat with a coat that is typically three colors: white, black, and orange.\n"
    value cats.siamese, "A Siamese cat is a breed of domestic cat that is known for its striking blue almond-shaped eyes and short coat with color points on the ears, face, paws, and tail.\n"
    value cats.persian, "A Persian cat is a long-haired breed of cat characterized by its round face, short muzzle, and long, flowing coat.\n"
    value cats.tabby, "tabby kittie is sillie kitty :3\n"
    
    method cats, grey, static
        print cats.calico
    end

    method cats, all, static
        ; print cats.calico
        print cats.siamese
        print cats.persian
        print cats.tabby
    end

func printHello
    while meow, <, 5
        print "hi\n"
        break meow
        print "outside the break\n"
    end while, meow
    print "outside while loop\n"
    for hello, 5
        mod helloMod, hello, 5
        if helloMod, ==, 0
            print "yes five\n"
        endif helloMod, 0
    end for, hello
end
func main():
    print "Code ran: \n", example, newline, newline
    call printHello
    run cats, grey
    run cats, all
    print "Called cat.grey function CLASSES YIPPIEEE\n"
    print "Output: \n"
    print "yay newlines with escapes \n"
    print outside
    new string, inside, "This variable was defined inside _start (.text) section :)", NEWLINE
    print inside

    new dword, firstArg, 0
    argv firstArg, 1
    print "First argument: "
    printC firstArg

    new int, exitStatus, 0
    random exitStatus, 1
    exit exitStatus