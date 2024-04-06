# Copyright Yann-Gaël Guéhéneuc, 2024
# This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License

class C:
    def foo(self):
        print("This is foo()")
    def bar(self, s:str):
        print(f"This is bar() with {s}")

o = C()

o.foo()
def foo2():
    print("This is the new foo()")
o.foo = foo2
o.foo()

o.bar("1")
def bar2(s:str):
    print(f"This is the new bar() with {s}")
o.bar = bar2
o.bar("2")
