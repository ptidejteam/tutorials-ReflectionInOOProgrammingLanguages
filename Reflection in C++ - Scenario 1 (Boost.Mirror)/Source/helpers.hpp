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

// Functor used by the for_each_ii algorithm.
struct info_printer {
	template<class IterInfo>
	void operator()(IterInfo) {
		using namespace mirror;
		std::cout << IterInfo::type::full_name();
		if (!IterInfo::is_last::value)
			std::cout << ", ";
	}
};

// Registration of the ptidej name-space, of the C class, and of the members of the C class.
MIRROR_REG_BEGIN

MIRROR_QREG_GLOBAL_SCOPE_NAMESPACE(std)

	MIRROR_REG_CLASS_BEGIN(struct, std, string)
	MIRROR_REG_CLASS_END

	MIRROR_QREG_GLOBAL_SCOPE_NAMESPACE(ptidej)

		MIRROR_REG_CLASS_BEGIN(class, ptidej, C)
			MIRROR_REG_CLASS_MEM_VARS_BEGIN
				MIRROR_REG_CLASS_MEM_VAR_GET_SET(private, _, int, i, _.get_i(), _.set_i(_i))
			MIRROR_REG_CLASS_MEM_VARS_END
			MIRROR_REG_MEM_FUNCTIONS_BEGIN
				MIRROR_REG_MEM_OVLD_FUNC_BEGIN(foo)
					MIRROR_REG_MEM_FUNCTION_BEGIN(public, _, void, foo, 1)
						MIRROR_REG_MEM_FUNCTION_PARAM(std::string, _s)
					MIRROR_REG_MEM_FUNCTION_END(1, _)
				MIRROR_REG_MEM_OVLD_FUNC_END(foo)
			MIRROR_REG_MEM_FUNCTIONS_END
		MIRROR_REG_CLASS_END

MIRROR_REG_END

// Class templates used to instantiate the invoker template and instance of this invoker template.
template<class Product, class Unused>
struct my_enumerator {
	void finish(std::string) const {
	}

	inline Product operator()(void) const {
		return NULL;
	}
};

template<class Product, class Unused>
struct my_manufacturer {
	typedef typename mirror::factory_maker<my_manufacturer,
			mirror::default_fact_suppliers, my_enumerator, Unused> maker;
	typename maker::template factory<Product>::type factory;

	template<class ConstructionInfo>
	inline my_manufacturer(const std::string _s,
			const ConstructionInfo construction_info) :
			factory(_s, construction_info) {
	}

	void finish(std::string) const {
	}

	inline Product operator()(void) const {
		return factory();
	}
};

template<class Unused>
struct my_manufacturer<std::string, Unused> {
	const std::string s;

	template<class ConstructionInfo>
	inline my_manufacturer(const std::string _s,
			const ConstructionInfo construction_info) :
			s(_s) {
	}

	void finish(std::string) const {
	}

	inline std::string operator()(void) const {
		return s;
	}
};

typedef mirror::invoker_maker<my_manufacturer, mirror::default_fact_suppliers,
		my_enumerator, void> my_invoker_maker;
