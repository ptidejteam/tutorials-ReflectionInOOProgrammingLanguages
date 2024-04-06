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

/*
 * Scenario 1
 * ----------
 *
 * Given a class C
 * Given an object o, instance of C
 * Identify all the methods available on o
 * Invoke a method using its name foo
 */

#include <iostream>
#include <mirror/invoker.hpp>
#include <mirror/meta_class.hpp>
#include <mirror/pre_registered/type/native.hpp>
#include <mirror/utils/default_suppliers.hpp>

#include "c.hpp"
#include "helpers.hpp"

template<typename O>
void identify_members(O * _o) {
	using namespace mirror;

	typedef MIRRORED_CLASS(O)meta_Class;
	std::cout << "\t(The type of o is " << meta_Class::full_name() << ")"
			<< std::endl;
	std::cout << "\t";
	mp::for_each_ii<all_member_variables<meta_Class>>(info_printer());
	std::cout << std::endl << "\t";
	mp::for_each_ii<member_functions<meta_Class>>(info_printer());
	std::cout << std::endl;
}

template<typename O>
void invoke_member_function(O * _o) {
	using namespace mirror;

	typedef MIRRORED_CLASS(ptidej::C)meta_Class;
	typedef mp::at_c<overloads<mp::at_c<member_functions<meta_Class>, 0>::type>,
			0>::type meta_foo;
	my_invoker_maker::invoker<meta_foo>::type invoker(
			std::string("\tThis is foo: "));
	invoker.call_on(*_o);
}

int main(void) {
	ptidej::C * o = new ptidej::C(42);

	std::cout << "Identify all the methods available on o" << std::endl;
	identify_members(o);

	std::cout << "Invoke a method using its name foo" << std::endl;
	invoke_member_function(o);

	return 0;
}
