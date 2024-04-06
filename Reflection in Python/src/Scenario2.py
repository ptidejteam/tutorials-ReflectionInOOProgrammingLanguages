# Copyright Yann-Gaël Guéhéneuc, 2024
# This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License

class C:
    def __init__(self, i:int):
        self._i = i
    def foo(self, s:str):
        print(s + str(self._i))

o = C(42)

print("Save on disk the complete state of o")
for name in vars(o): 
    print("o." + str(name) + " = " + str(getattr(o, name)) + " (" + type(getattr(o, name)).__name__ + ")")

print("Restore from disk the object o at a later time")
o = C.__new__(C)
# print(o._i) # o doesn't have an attribute _i yet!
setattr(o, "_i", 43)
print(f"o._i = {o._i}")
