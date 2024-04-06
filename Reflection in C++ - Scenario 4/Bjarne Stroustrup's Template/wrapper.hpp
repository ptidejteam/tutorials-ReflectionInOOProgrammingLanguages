/*
 * wrapper.hpp
 *
 *  Created on: 2014-04-05
 *      Author: Yann
 */

#ifndef BS_WRAPPER_HPP_
#define BS_WRAPPER_HPP_

template<class T>
class Prefix {
	T* p;
public:
	Prefix(T * _p) :
			p(_p) {
	}
	T* operator->() {
		std::cout << "(Prefix::operator->())" << std::endl;
		return p;
	}
};

#endif /* BS_WRAPPER_HPP_ */
