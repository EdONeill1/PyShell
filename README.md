# Sea-Shell

Sea-Shell is a UNIX shell implemented within C. 

### Install
* git clone https://github.com/EdONeill1/Sea-Shell
* cd Sea-Shell
* make
* ./seashell

It can perform the majority if not all UNIX functions. It can even run vim!

```
[01/09 15:56]# vim file.txt
[01/09 15:56]# cat file.txt

hello
[01/09 15.56]# wc file.txt

       1       1       6 file.txt
       
```

There are limitations to the shell however.


(1) You can redirect output and pipe output to more than a degree of one.

```
[01/09 15:56]# ls > file.txt
[01/09 15:56]# cat file.txt

file.txt
main.c
main.o
makefile
seashell
shell-methods.c
shell-methods.h
shell-methods.o

[01/09 15:56]# ls | grep main.c

ls: grep: No such file or directory
ls: |: No such file or directory
main.c
[01/09 15:56]#
```

(2) The above example leads me to my next point. Piping is successful however an error is still thrown.

(3) Each command outputs whitespace for some reason I don't know.

