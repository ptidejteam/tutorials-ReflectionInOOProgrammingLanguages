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
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Proxy;
import junit.framework.Assert;

public class Main {
	public static void main(final String[] args) throws InstantiationException,
			IllegalAccessException, IllegalArgumentException,
			InvocationTargetException, NoSuchMethodException, SecurityException {

		final I o = new C(42);
		o.foo("This is o: ");

		final InvocationHandler handler = new InvokationHandler(o);
		final I proxy =
			(I) Proxy.newProxyInstance(
				I.class.getClassLoader(),
				new Class[] { I.class },
				handler);

		Assert.assertTrue(proxy instanceof I);
		Assert.assertFalse(proxy instanceof C);
		Assert.assertTrue(proxy.equals(o));

		proxy.foo("This is o: ");
	}
}

// Also correct but longer...
//	final Class<?> proxyClass =
//		Proxy.getProxyClass(
//			I.class.getClassLoader(),
//			new Class[] { I.class });
//	final I proxy =
//		(I) proxyClass.getConstructor(
//			new Class[] { InvocationHandler.class }).newInstance(
//			new Object[] { handler });
