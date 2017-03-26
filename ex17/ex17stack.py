#! /usr/bin/env python

class Stack(list):

    def push(self, item):
        self.append(item)
        print(self)

    def pop(self):
        try:
            super().pop()
            print(self)
        except IndexError:
            print("stack is empty")
    
    def peek(self):
        try:
            print(self[-1])
        except IndexError:
            print("stack is empty")
	




if __name__ == "__main__":

    stack = Stack()

    stack.push(10)
    stack.push(23)
    stack.push(88)

    stack.peek()
    
    stack.pop()
    stack.pop()
    stack.pop()
