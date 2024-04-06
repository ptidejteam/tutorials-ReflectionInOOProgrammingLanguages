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
 * Scenario 3
 * ----------
 *
 * Given a class C
 * Record the numbers of its instance ever created
 * Report this number when the program ends
 */

#include "c.hpp"

int ptidej::C::numberOfInstances = 0;

int main(void) {
	ptidej::C * o1 = new ptidej::C(42);
	ptidej::C * o2 = new ptidej::C(1);
	ptidej::C * o3 = new ptidej::C(100);

	std::cout << o1 << std::endl << o2 << std::endl << o3 << std::endl;

	std::cout << ptidej::C::getNumberOfInstances() << std::endl;

	return 0;
}
