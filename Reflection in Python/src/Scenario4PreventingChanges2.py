# Copyright Yann-Gaël Guéhéneuc, 2024
# This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License

class C:
    def __setattr__(self, attr, value):
        if hasattr(self, attr):
            raise Exception("Attempting to alter read-only value")
        self.__dict__[attr] = value        

    def foo(self):
        print("This is foo()")

o = C()

o.foo()
def foo2():
    print("This is the new foo()")
o.foo = foo2
o.foo()
