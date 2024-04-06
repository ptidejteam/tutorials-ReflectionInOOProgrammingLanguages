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
package net.ptidej.reflection.java.scenario2;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;

public class Main {
	public static void main(final String[] args) throws NoSuchMethodException,
			SecurityException, IllegalAccessException,
			IllegalArgumentException, InvocationTargetException,
			InstantiationException, NoSuchFieldException {

		final C o1 = new C(42);

		System.out.println("Save on disk the complete state of o");
		final Class<?> classOfO = o1.getClass();
		final Field[] fieldsOfC = classOfO.getDeclaredFields();
		for (int i = 0; i < fieldsOfC.length; i++) {
			final Field field = fieldsOfC[i];
			field.setAccessible(true);
			System.out.print('\t');
			System.out.print(field.getName());
			System.out.print(" = ");
			System.out.println(field.getInt(o1));
		}

		System.out.println("Restore from disk the object o at a later time");
		final C o2 = (C) classOfO.newInstance();
		final Field fieldiOfC = classOfO.getDeclaredField("i");
		fieldiOfC.setAccessible(true);
		fieldiOfC.setInt(o2, 43);
		o2.foo("\tThis is foo on o2: ");
	}
}
