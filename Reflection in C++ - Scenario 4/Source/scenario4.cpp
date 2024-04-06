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
 * Scenario 4
 * ----------
 *
 * Given an object o, instance of C
 * Without changing o or C
 * Change the behaviour of o.foo()
 */

#include <iostream>

#include "../Bjarne Stroustrup's Template/wrapper.hpp"
#include "../Herb Sutter's Functor-based Approach/wrapper.hpp"
#include "../CPatcher/patcher.h"

#include "c.hpp"

void (ptidej::C::*pfn_foo)(const std::string) = &ptidej::C::foo;
class proxy {
public:
	void my_foo(const std::string _s) {
		std::cout << "patch void foo(" << _s << ")" << std::endl;

		(reinterpret_cast<ptidej::C*>(this)->*pfn_foo)(_s);
	}
};

int main(void) {
	// Herb Sutter's Functor-based Approach
	// http://channel9.msdn.com/Shows/Going+Deep/C-and-Beyond-2012-Herb-Sutter-Concurrency-and-Parallelism
	std::cout << "Herb Sutter's Functor-based Approach:" << std::endl;
	Wrapper<ptidej::C> o1(42);
	o1([](ptidej::C &o1) {
		o1.foo("This is o: ");
	});
	std::cout << std::endl;

	// Bjarne Stroustrup's Template
	// http://www.stroustrup.com/wrapper.pdf
	std::cout << "Bjarne Stroustrup's Template:" << std::endl;
	ptidej::C o2(42);
	Prefix<ptidej::C> prefixed_o2(&o2);
	prefixed_o2->foo("This is o: ");
	std::cout << std::endl;

	// armagedescu's CPatch Template
	// http://www.codeproject.com/Articles/34237/A-C-Style-of-Intercepting-Functions
	std::cout << "armagedescu's CPatch Template:" << std::endl;
	CPatch patch_C_foo(pfn_foo, &proxy::my_foo);
	ptidej::C o3(42);
	o3.foo(std::string("This is o: "));
	std::cout << std::endl;

	return 0;
}
