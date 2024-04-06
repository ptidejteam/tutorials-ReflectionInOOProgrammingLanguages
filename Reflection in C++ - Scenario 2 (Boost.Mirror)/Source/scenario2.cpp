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
 * Scenario 2
 * ----------
 *
 * Given an object o, instance of C
 * Save on disk the complete state of o
 * Restore from disk the object o at a later time
 */

#include <iostream>
#include <mirror/factory.hpp>
#include <mirror/meta_class.hpp>
#include <mirror/pre_registered/type/native.hpp>
#include <mirror/auxiliary/using_directive.hpp>
#include <mirror/utils/default_suppliers.hpp>

#include "c.hpp"
#include "helpers.hpp"

template<typename O>
void save_on_disk(O * _o) {
	using namespace mirror;

	typedef MIRRORED_CLASS(O)meta_Class;
	std::cout << "\t(The type of o is " << meta_Class::full_name() << ")"
			<< std::endl << "\t";
	mp::for_each_ii<all_member_variables<meta_Class>>(
			info_printer_variables<O>(*_o));
	std::cout << std::endl;
}

template<typename O>
void restore_from_disk(void) {
	using namespace mirror;

	typedef typename my_factory_maker::factory<O>::type my_factory_type;
	my_factory_type my_factory(43);
	O o(my_factory());
	std::cout << "\t" << o.get_i() << std::endl;
}

int main(void) {
	ptidej::C * o = new ptidej::C(42);

	std::cout << "Save on disk the complete state of o" << std::endl;
	save_on_disk(o);

	std::cout << "Restore from disk the object o at a later time" << std::endl;
	restore_from_disk<ptidej::C>();

	return 0;
}
