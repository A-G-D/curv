// Copyright 2016-2021 Doug Moen
// Licensed under the Apache License, version 2.0
// See accompanying file LICENSE or https://www.apache.org/licenses/LICENSE-2.0

#ifndef LIBCURV_TYPE_H
#define LIBCURV_TYPE_H

#include <libcurv/value.h>

namespace curv {

// A plex type is either a scalar type (Bool, Num)
// or it is one of the list types that are treated specially
// by GPU shader languages (the WGSL and SPIR-V type systems).
// Plex types are the argument and result types of SPIR-V primitive functions.
enum class Plex_Type : short
{
    missing,    // flag value: not a plex type
    Bool,
    Bool2,
    Bool3,
    Bool4,
    Bool32,
    Bool2x32,
    Bool3x32,
    Bool4x32,
    Num,
    Vec2,
    Vec3,
    Vec4,
    Mat2,
    Mat3,
    Mat4
};

extern const char* glsl_plex_type_name[];

struct Type : public Ref_Value
{
    Plex_Type plex_type_;
    Type(int st, Plex_Type pt) : Ref_Value(ty_type, st), plex_type_(pt) {}
    static Shared<const Type> Error;
    static Shared<const Type> Bool;
    static Shared<const Type> Bool32;
    static Shared<const Type> Num;

    static bool equal(const Type&, const Type&);
    unsigned rank() const;

    Shared<const Type> plex_array_base() const;
    unsigned plex_array_rank() const;
    unsigned plex_array_dim(unsigned) const;
};

struct Error_Type : public Type
{
    Error_Type() : Type(sty_error_type, Plex_Type::missing) {}
    virtual void print_repr(std::ostream&) const override;
};

struct Bool_Type : public Type
{
    Bool_Type() : Type(sty_bool_type, Plex_Type::Bool) {}
    virtual void print_repr(std::ostream&) const override;
};

struct Num_Type : public Type
{
    Num_Type() : Type(sty_num_type, Plex_Type::Num) {}
    virtual void print_repr(std::ostream&) const override;
};

struct List_Type : public Type
{
    unsigned count_;
    Shared<const Type> elem_type_;
    List_Type(unsigned c, Shared<const Type> et)
    :
        Type(sty_list_type, make_plex_type(c, et)),
        count_(c),
        elem_type_(et)
    {}
    static Plex_Type make_plex_type(unsigned, Shared<const Type>);
    virtual void print_repr(std::ostream&) const override;
};

} // namespace curv
#endif // header guard
