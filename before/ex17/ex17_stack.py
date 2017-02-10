#!/usr/bin/env python

class Stack(list):

    def __init__(self):
        super().__init__()
        self.stack = []

    def push(self, x):
        self.stack.append(x)

    def pop(self):
        self.stack.pop()


if __name__ == '__main__':

    d = Stack()
    print(d.stack)
    d.push('s')
    d.push('t')
    d.push('o')
    d.push('p')
    print(d.stack)
    
    d.pop()

    print(d.stack)


