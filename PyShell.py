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
        if sys.getsizeof(tokens) == 1:
                os.chdir("..")
                exit(0)
        else:
                os.chdir(tokens[1])
                exit(0)

def executeCommand(tokens):

        if(tokens[0] == "cd"):
                changeDirectory(tokens)
        
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
