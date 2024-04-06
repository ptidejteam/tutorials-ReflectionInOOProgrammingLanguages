# tutorials-ReflectionInOOProgrammingLanguages

A tutorial on reflection, with a particular emphasis on Java, with a comparison with C++, Python, and Smalltalk. It describes different scenarios in which reflection is useful, a brief history of reflection and MOPs, a comparison with C++, Python, and Smalltalk, and some particulars about Java. The source code of the examples in <a href="Reflection in Java v1.5.rar">Java (Eclipse project)</a>, <a href="Reflection in Smalltalk v1.5.rar">Smalltalk (Squeak image v3.10.6)</a>, <a href="Reflection in Python v1.6.rar">Python (Eclipse project)</a>, and C++ (<a href="Reflection in Cplusplus v1.5.rar">Eclipse projects</a> and <a href="Reflection in Cplusplus v1.5 - Scenario 4 (Visual Studio).rar">Visual Studio solution</a>) are available. (C++ Eclipse projects require <a href="//kifri.fri.uniza.sk/~chochlik/mirror-lib/html/index.html#introduction">Mirror</a>.) Big thanks to <a href="//kifri.fri.uniza.sk/~chochlik/mirror-lib/html/">Matúš Chochlík</a> and <a href="//rmod.lille.inria.fr/web/pier/team/Marcus-Denker">Marcus Denker</a> for their kind and precious help with C++ and Smalltalk.

The tutorial focuses on four common problems:

* Avoid using instanceof when code must bypass the compiler and virtual machine’s choice of the method to call.

* Create external, user-defined pieces of code loaded, used, and unloaded at run-time.

* Translate data structures or object states into a format that can be stored (file, network...).

* Monitor the execution of a program to understand its behaviour, and measure its space and time complexity.

It shows working examples of Java, Smalltalk, Python, and C++ code solving the four common problems through four scenarios:

* Scenario 1: invoke an arbitrary method on an object (see the problems with instanceof and plugins).

* Scenario 2: access the complete (including private) state of an object (see the problem with serialisation).

* Scenario 3: count the number of instances of a class created at runtime (see the problem with debugging/profiling).

* Scenario 4: patch the method of a class to change its behaviour (see the problem with patching).

It also discusses the different kinds of interconnections among objects that are available in common programming languages (linking, forking, subclassing, inter-process communication, and dynamic loading/invoking), a bit of theory about reflection, and specifically the class-loading mechanism of Java.
