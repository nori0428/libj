// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_SHARED_PTR_H_
#define LIBJ_SHARED_PTR_H_

#ifdef LIBJ_USE_CXX11

#include <memory>

namespace libj {

template<typename T>
struct SharedPtr {
    typedef std::shared_ptr<T> Type;
};

}  // namespace libj

#else  // LIBJ_USE_CXX11

#define LIBJ_DISABLE_BOOST_SP_GET_DELETER
#include "boost/shared_ptr.hpp"

namespace libj {

template<typename T>
struct SharedPtr {
    typedef boost::shared_ptr<T> Type;
};

}  // namespace libj

#endif  // LIBJ_USE_CXX11

#endif  // LIBJ_SHARED_PTR_H_
