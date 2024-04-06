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
package net.ptidej.reflection.java.scenario4;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;

public class InvokationHandler implements InvocationHandler {
	private final I i;
	public InvokationHandler(final I aConcreteImplementationOfI) {
		this.i = aConcreteImplementationOfI;
	}
	public Object invoke(
		final Object aProxy,
		final Method aMethod,
		final Object[] someArgs) throws Throwable {

		if (aMethod.getName().equals("foo")) {
			final String arg = (String) someArgs[0];
			final String newArg = arg.toUpperCase();

			System.out.print("Forwarding method: \"");
			System.out.print(aMethod.getName());
			System.out.print("\"\n\tOriginal arguments: \"");
			System.out.print(arg);
			System.out.print("\"\n\tNew arguments: \"");
			System.out.print(newArg);
			System.out.println('\"');

			this.i.foo(newArg);
			return null;
		}
		else {
			return aMethod.invoke(this.i, someArgs);
		}
	}
}
