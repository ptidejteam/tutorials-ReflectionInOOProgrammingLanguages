# Copyright Yann-Gaël Guéhéneuc, 2024
# This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License

class C:
    def __init__(self):
        self._x = 42
        
    @property
    def x(self):
        return self._x

o = C()

print(o.x)
o.x = 0
print(o.x)
