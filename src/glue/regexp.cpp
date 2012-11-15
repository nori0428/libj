// Copyright (c) 2012 Plenluno All rights reserved.

#ifdef LIBJ_USE_PCRE16
# include <pcre.h>
#else
# include <iv/aero/aero.h>
#endif
#include <vector>

#include "./regexp.h"

namespace libj {
namespace glue {

RegExp* RegExp::create(const U16String& pattern, unsigned int flags) {
    RegExp* re = new RegExp(pattern, flags);
    int error = 0;

#ifdef LIBJ_USE_PCRE16
    const char* errstr;
    int fs = (flags & IGNORE_CASE ? PCRE_CASELESS : 0)
           | (flags & MULTILINE ? PCRE_MULTILINE : 0);
    re->code_ = pcre16_compile(pattern.c_str(), fs, &errstr, &error, NULL);
#else
    iv::core::Space space;
    int fs = (flags & IGNORE_CASE ? iv::aero::IGNORE_CASE : 0)
           | (flags & MULTILINE ? iv::aero::MULTILINE : 0);
    re->code_ = iv::aero::Compile(&space, pattern, fs, &error);
#endif

    if (!error && re->code_) {
        return re;
    } else {
        delete re;
        return NULL;
    }
}

RegExp::~RegExp() {
#ifdef LIBJ_USE_PCRE16
    free(static_cast<pcre16*>(code_));
#else
    delete static_cast<iv::aero::Code*>(code_);
#endif

}

bool RegExp::global() const {
    return flags_ & GLOBAL;
}

bool RegExp::ignoreCase() const {
    return flags_ & IGNORE_CASE;
}

bool RegExp::multiline() const {
    return flags_ & MULTILINE;
}

bool RegExp::execute(
    const U16String& str,
    int offset,
    std::vector<int>& captures) const {

#ifdef LIBJ_USE_PCRE16
    pcre16* code = static_cast<pcre16*>(code_);
    captures.clear();

# define DEFAULT_OVECTOR_SIZE (32) // XXX
    captures.reserve(DEFAULT_OVECTOR_SIZE * 3);
# undef DEFAULT_OVECTOR_SIZE

    size_t n = captures.capacity();
    for (size_t i = 0; i < n; i++)
        captures.push_back(-1);
    int res = pcre16_exec(code, NULL, str.c_str(), str.length(),
                          offset, 0, captures.data(), n);
    return (res > 0);
#else
    static iv::aero::VM vm;
    iv::aero::Code* code = static_cast<iv::aero::Code*>(code_);
    captures.clear();
    size_t n = code->captures() * 2;
    for (size_t i = 0; i < n; i++)
        captures.push_back(-1);
    int res = vm.Execute(code, str, captures.data(), offset);
    return res == iv::aero::AERO_SUCCESS;
#endif
}

}  // namespace glue
}  // namespace libj
