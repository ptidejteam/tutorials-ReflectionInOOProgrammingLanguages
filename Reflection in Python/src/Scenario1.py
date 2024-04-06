# Copyright Yann-Gaël Guéhéneuc, 2024
# This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License

class C:
    def __init__(self, i:int):
        self._i = i
    def foo(self, s:str):
        print(s + str(self._i))

o = C(42)

print("Identify all the methods available on o")
for name in dir(o): 
    if callable(getattr(o, name)):
        print(name)

print("Invoke a method using its name foo")
thefoo = getattr(o, "foo")
thefoo("This is foo: ")
