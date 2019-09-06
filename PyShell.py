import sys
import os
import string
import re
import signal



def parseString(input):
        i = 0
        tokens = list()
        tokens = input.split()
        executeCommand(tokens)

def changeDirectory(tokens):
                os.chdir(tokens[1])
                exit(0)

def redirects(tokens, redirectPoint):
        redirectTokens = list()
        for i in range(redirectPoint):
                redirectTokens.append(tokens[i])
        filename = tokens[len(tokens) - 1]
        child_process = os.fork()
        if(child_process == 0):
                 fd = os.open(filename, os.O_WRONLY|os.O_CREAT|os.O_TRUNC);
                 os.dup2(fd, 1)
                 os.close(fd)
                 os.execvp(redirectTokens[0], redirectTokens)
        elif child_process < 0:
                print("Error")

        else:
                os.wait()
        

def executeCommand(tokens):

        if(tokens[0] == "cd"):
                changeDirectory(tokens)
        

        redir1 = ">"
        for index in range(len(tokens)):
                if tokens[index] == redir1:
                        redirects(tokens, index)
                        return

        pid = os.fork()
        if pid == 0:
                os.execvp(tokens[0], tokens)
        else:
                os.wait()
                      
def main(argv):
    while(1):
        sys.stdout.write("> ")
        s = sys.stdin.readline()
        parseString(s)
        



main(sys.argv)
