// Copyright (c) 2012 Plenluno All rights reserved.

#ifndef LIBJ_COLLECTION_H_
#define LIBJ_COLLECTION_H_

#include "libj/mutable.h"
#include "libj/iterator.h"

namespace libj {

class Collection : LIBJ_MUTABLE(Collection)
 public:
    virtual Size size() const = 0;
    virtual void clear() = 0;
    virtual Type<Iterator>::Ptr iterator() const = 0;
    // and so on
};

#define LIBJ_COLLECTION(T) public libj::Collection { \
    LIBJ_MUTABLE_DECLS(T, libj::Collection)

}  // namespace libj

#endif  // LIBJ_COLLECTION_H_