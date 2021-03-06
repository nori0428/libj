// Copyright (c) 2012 Plenluno All rights reserved.

#include <gtest/gtest.h>
#include <libj/error.h>
#include <libj/js_array.h>
#include <libj/js_function.h>

namespace libj {

class GTestJsFunctionAdd : LIBJ_JS_FUNCTION(GTestJsFunctionAdd)
 public:
    Value operator()(JsArray::Ptr args) {
        if (args->size() == 2 &&
            args->get(0).type() == Type<Int>::id() &&
            args->get(1).type() == Type<Int>::id()) {
            int x, y;
            to<Int>(args->get(0), &x);
            to<Int>(args->get(1), &y);
            return x + y;
        } else {
            return Error::create(Error::ILLEGAL_ARGUMENT);
        }
    }

    static GTestJsFunctionAdd::Ptr create() {
        return Ptr(new GTestJsFunctionAdd());
    }
};

TEST(GTestJsFunction, TestToString) {
    GTestJsFunctionAdd::Ptr add = GTestJsFunctionAdd::create();
    ASSERT_TRUE(add->toString()->equals(
        String::create("function GTestJsFunctionAdd() {}")));
}

TEST(GTestJsFunction, TestFunctor) {
    GTestJsFunctionAdd::Ptr add = GTestJsFunctionAdd::create();
    JsArray::Ptr args = JsArray::create();
    args->add(3);
    args->add(4);
    ASSERT_TRUE((*add)(args).equals(7));
}

TEST(GTestJsFunction, TestCall) {
    GTestJsFunctionAdd::Ptr add = GTestJsFunctionAdd::create();
    ASSERT_TRUE(add->call(4, 5).equals(9));
}

TEST(GTestJsFunction, TestCompreTo) {
    GTestJsFunctionAdd::Ptr add1 = GTestJsFunctionAdd::create();
    GTestJsFunctionAdd::Ptr add2 = GTestJsFunctionAdd::create();
    ASSERT_EQ(0, add1->compareTo(add1));
    ASSERT_NE(0, add1->compareTo(add2));
}

}  // namespace libj
