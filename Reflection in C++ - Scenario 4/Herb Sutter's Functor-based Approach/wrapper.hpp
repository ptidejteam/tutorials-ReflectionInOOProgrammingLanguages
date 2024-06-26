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

#ifndef HS_WRAPPER_HPP_
#define HS_WRAPPER_HPP_

#include <cstdlib>
#include <cxxabi.h>
#include <typeinfo.h>

template<class T> class Wrapper {
private:
	mutable T wrappedObject;
public:
	Wrapper(T o = T { }) :
			wrappedObject(o) {
	}
	template<typename F>
	auto operator()(F f) const -> decltype(f(wrappedObject)) {
		std::cout << "(Wrapper::operator()(F f))" << std::endl;
		int status;
		char *realname = abi::__cxa_demangle(typeid(f).name(), 0, 0, &status);
		std::cout << "(The type of f is " << realname << ")" << std::endl;
		free(realname);
		return f(wrappedObject);
	}
	friend std::ostream& operator<<(std::ostream &out, const Wrapper<T> &w) {
		int status;
		char *realname = abi::__cxa_demangle(typeid(w.wrappedObject).name(), 0,
				0, &status);
		std::cout << "(The type of o is " << realname << ")" << std::endl;
		free(realname);
		return out;
	}
};

#endif /* HS_WRAPPER_HPP_ */
