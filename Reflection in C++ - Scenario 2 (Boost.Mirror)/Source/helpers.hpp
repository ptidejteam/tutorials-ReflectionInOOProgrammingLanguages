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

// Functors used by the for_each_ii algorithms.
template<class O>
struct info_printer_variables {
	O o;

	inline info_printer_variables(O _o) :
			o(_o) {
	}

	template<class IterInfo>
	void operator()(IterInfo) {
		using namespace mirror;
		std::cout << IterInfo::type::full_name() << " = "
				<< IterInfo::type::get(o);
		if (!IterInfo::is_last::value)
			std::cout << ", ";
	}
};

struct info_printer_others {
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
MIRROR_REG_CLASS_END //
MIRROR_QREG_GLOBAL_SCOPE_NAMESPACE(ptidej)

MIRROR_REG_CLASS_BEGIN(class, ptidej, C)
MIRROR_REG_CLASS_MEM_VARS_BEGIN//
MIRROR_REG_CLASS_MEM_VAR_GET_SET(private, _, int, i, _.get_i(), _.set_i(_i))
MIRROR_REG_CLASS_MEM_VARS_END
MIRROR_REG_CONSTRUCTORS_BEGIN
MIRROR_REG_CONSTRUCTOR_BEGIN(public, 1)
MIRROR_REG_CONSTRUCTOR_PARAM(int, _i)
MIRROR_REG_CONSTRUCTOR_END(1)
MIRROR_REG_CONSTRUCTORS_END
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
template<class Product, typename IsEnum>
struct my_base_manufacturer {
	Product x;

	struct constr_param_name_printer {
		template<class IterInfo>
		inline void operator()(IterInfo) const {
			if (!IterInfo::is_first::value)
			std::cout << ", ";
			std::cout << IterInfo::type::base_name();
		}
	};

	struct constr_context_printer {
		template<class IterInfo>
		inline void operator()(IterInfo) const {
			if (!IterInfo::is_first::value)
			std::cout << "::";
			std::cout << IterInfo::type::base_name();
		}
	};

	template<class ConstructionInfo>
	my_base_manufacturer(int tabs, ConstructionInfo construction_info,
			const Product& _x) :
	x(tabs) {
	}

	void finish(int) {
	}

	inline Product operator()(void) {
		return x;
	}
};

template<class Product, class Unused>
struct my_enumerator: my_base_manufacturer<Product, std::true_type> {
	template<class ConstructionInfo>
	inline my_enumerator(int tabs, ConstructionInfo construction_info) :
			my_base_manufacturer<Product, std::true_type>(tabs,
					construction_info, Product()) {
	}

	void finish(int) {
	}

	inline Product operator()(void) {
		return NULL;
	}
};

template<class Product, class Unused>
struct my_manufacturer {
	typedef typename mirror::factory_maker<my_manufacturer,
			mirror::default_fact_suppliers, my_enumerator, Unused> maker;
	typename maker::template factory<Product>::type f;

	template<class ConstructionInfo>
	inline my_manufacturer(int _value, ConstructionInfo construction_info) :
			f(construction_info) {
	}

	void finish(int) {
	}

	inline Product operator()(void) {
		return f();
	}
};

// For each type of the formal parameter(s) of the constructor(s).
#define MIRROR_SPECIALIZED_MANUFACTURER(TYPE, DEFAULT) \
template <class Unused>  \
struct my_manufacturer<TYPE, Unused> : my_base_manufacturer< TYPE, std::false_type > \
{ \
	template <class ConstructionInfo> \
	inline my_manufacturer(int tabs, ConstructionInfo construction_info) \
		: my_base_manufacturer<TYPE, std::false_type>( \
				tabs, \
				construction_info, \
				DEFAULT) \
 { } \
};

MIRROR_SPECIALIZED_MANUFACTURER(int, 0)
//
MIRROR_SPECIALIZED_MANUFACTURER(double, 0.0)
MIRROR_SPECIALIZED_MANUFACTURER(std::string, std::string())

/*
 * A manufacturer that picks the constructor that will be
 * used by the means of the result of the index member
 * function (i.e., the zero-th registered constructor will
 * always be used with this manager).
 */
template<class Unused>
struct my_manufacturer<void, Unused> {
	template<typename Context>
	my_manufacturer(int _value, Context) {
	}

	void finish(int) {
	}

	template<class ConstructionInfo>
	inline int add_constructor(int _value, ConstructionInfo) const {
		return _value;
	}

	inline int index(void) {
		// Choice of the registered constructor in C.
		return 0;
	}
}
;

typedef mirror::factory_maker<my_manufacturer, mirror::default_fact_suppliers,
		my_enumerator, void> my_factory_maker;

