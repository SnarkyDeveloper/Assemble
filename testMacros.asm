%include "map.inc"
%include "macros.inc"
new string, outside, "This variable is defined outside any section", newline 
new string, example, "print ", doublequote, "yay newlines with escapes \\n", DOUBLEQUOTE


class cats
    value cats.calico, "A calico cat is a domestic cat with a coat that is typically three colors: white, black, and orange.\n"
    method cat, grey
        print cats.calico
    end

func main():
    print "Code ran: \n", example, newline, newline

    call cat.grey
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