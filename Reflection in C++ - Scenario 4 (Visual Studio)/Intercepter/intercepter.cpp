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

#include "Intercepter.h"

void(ptidej::C::*pfn_foo)(const std::string) = &ptidej::C::foo;
class proxy
{
public:
	void my_foo(const std::string s)
	{
		std::cout << "Function foo() is patched!" << std::endl << std::flush;
		(reinterpret_cast<ptidej::C*>(this)->*pfn_foo)(s);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	CPatch patch_aclass_doSomething(pfn_foo, &proxy::my_foo);
	ptidej::C o(42);
	o.foo(std::string("This is o: "));
	return 0;
}
