/* (c) Copyright 2014 and following years, Yann-Gaël Guéhéneuc,
 * École Polytechnique de Montréal and 연세대학교.
 * 
 * Use and copying of this software and preparation of derivative works
 * based upon this software are permitted. Any copy of this software or
 * of any derivative work must include the above copyright notice of
 * the author, this paragraph and the one after it.
 * 
 * This software is made available AS IS, and THE AUTHOR DISCLAIMS
 * ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, AND NOT WITHSTANDING ANY OTHER PROVISION CONTAINED HEREIN,
 * ANY LIABILITY FOR DAMAGES RESULTING FROM THE SOFTWARE OR ITS USE IS
 * EXPRESSLY DISCLAIMED, WHETHER ARISING IN CONTRACT, TORT (INCLUDING
 * NEGLIGENCE) OR STRICT LIABILITY, EVEN IF THE AUTHOR IS ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 * 
 * All Rights Reserved.
 */
package net.ptidej.reflection.java.scenario1;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class Main {
	public static void main(final String[] args) throws NoSuchMethodException,
			SecurityException, IllegalAccessException,
			IllegalArgumentException, InvocationTargetException {

		final C o = new C(42);

		System.out.println("Identify all the methods available on o");
		final Class<?> classOfO = o.getClass();
		final Method[] methodsOfC = classOfO.getMethods();
		for (int i = 0; i < methodsOfC.length; i++) {
			final Method method = methodsOfC[i];
			System.out.print('\t');
			System.out.println(method.getName());
		}

		System.out.println("Invoke a method using its name foo");
		final Method fooMethod =
			classOfO.getMethod("foo", new Class[] { String.class });
		fooMethod.invoke(o, new Object[] { "\tThis is foo: " });
	}
}
