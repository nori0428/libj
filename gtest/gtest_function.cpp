// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/error.h>
#include <libj/function.h>

namespace libj {

class GTestFunctionAdd : LIBJ_FUNCTION(GTestFunctionAdd)
 public:
    Value operator()(ArrayList::Ptr args) {
        if (!args) {
            return Error::create(Error::ILLEGAL_ARGUMENT);
        }

        Int sum = 0;
        for (Size i = 0; i < args->length(); i++) {
            int x;
            if (to<Int>(args->get(i), &x)) {
                sum += x;
            } else {
                return Error::create(Error::ILLEGAL_ARGUMENT);
            }
        }
        return sum;
    }

    String::CPtr toString() const {
        return String::create();
    }

    static Ptr create() {
        return Ptr(new GTestFunctionAdd());
    }
};

TEST(GTestFunction, TestFunctor) {
    Function::Ptr add = GTestFunctionAdd::create();
    ArrayList::Ptr args = ArrayList::create();
    args->add(2);
    args->add(3);
    ASSERT_TRUE((*add)(args).equals(5));

    ASSERT_TRUE((*add)().instanceof(Type<Error>::id()));
}

TEST(GTestFunction, TestCall) {
    Function::Ptr add = GTestFunctionAdd::create();
    ASSERT_TRUE(add->call().instanceof(Type<Error>::id()));
    ASSERT_TRUE(add->call(1).equals(1));
    ASSERT_TRUE(add->call(1, 2).equals(3));
    ASSERT_TRUE(add->call(1, 2, 3).equals(6));
    ASSERT_TRUE(add->call(1, 2, 3, 4).equals(10));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5).equals(15));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5, 6).equals(21));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5, 6, 7).equals(28));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5, 6, 7, 8).equals(36));
    ASSERT_TRUE(add->call(1, 2, 3, 4, 5, 6, 7, 8, 9).equals(45));
}

#ifdef LIBJ_USE_SP
TEST(GTestFunction, TestUseCount) {
    Function::CPtr p = GTestFunctionAdd::create();
    ASSERT_EQ(1, p.use_count());
}
#endif

}  // namespace libj
