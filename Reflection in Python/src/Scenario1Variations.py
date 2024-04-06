# Copyright Yann-Gaël Guéhéneuc, 2024
# This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License

from asyncio import __main__
from _operator import methodcaller
class C:
    def __init__(self, i:int):
        self._i = i
    def fooNoArg(self):
        print("This is foo")
    def fooWithString(self, s:str):
        print(s + str(self._i))

def barNoArg():
    print("This is bar")
def barWithString(s:str):
    print(s + "42")


o = C(42)



# With a string
eval("o.fooNoArg()")                     # Or exec("o.fooNoArg()")
eval("o.fooWithString('This is foo: ')") # Or exec("o.fooWithString('This is foo: ')")
eval("barNoArg()")                       # Or exec("barNoArg()")
eval("barWithString('This is bar')")     # Or exec("barWithString()")


# With a bound method
thefoo = getattr(o, "fooNoArg")
thefoo() # Or thefoo.__call__()
thefoo = getattr(o, "fooWithString")
thefoo("This is foo: ") # Or thefoo.__call__("This is foo: ")
# Not applicable to functions, like barNoArg and barWithString

# With a function
thefoo = C.fooNoArg 
thefoo = C.__dict__['fooNoArg'] 
thefoo = list(C.__dict__.values())[2]
thefoo(o) # Or thefoo.__call__(o)
thefoo = C.fooWithString
thefoo = C.__dict__['fooWithString'] 
thefoo = list(C.__dict__.values())[3]
thefoo(o, "This is foo: ") # Or thefoo.__call__(o, "This is foo: ")
thebar = barNoArg
thebar = locals()['barNoArg']
tehbar = list(locals().values())[10]
thebar()
thebar = barWithString
thebar = locals()['barWithString']
tehbar = list(locals().values())[11]
thebar("This is bar: ") # Or thebar.__call__("This is bar: ")

# Specials!
from operator import attrgetter

special = attrgetter("fooWithString")
special(o)("This is foo: ")

special = methodcaller("fooWithString", "This is foo: ")
special(o)

special = compile("""
def barNoArg():
    print("This is bar")
barNoArg()""", "<string>", "exec")
exec(special)

import gc
print(gc.get_referents(C))
print(gc.get_referents(o))