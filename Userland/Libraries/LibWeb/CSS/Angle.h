/*
 * Copyright (c) 2022-2023, Sam Atkins <atkinssj@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/String.h>
#include <LibWeb/Forward.h>

namespace Web::CSS {

class Angle {
public:
    enum class Type {
        Deg,
        Grad,
        Rad,
        Turn,
    };

    static Optional<Type> unit_from_name(StringView);

    Angle(int value, Type type);
    Angle(float value, Type type);
    static Angle make_degrees(float);
    Angle percentage_of(Percentage const&) const;

    ErrorOr<String> to_string() const;
    float to_degrees() const;

    bool operator==(Angle const& other) const
    {
        return m_type == other.m_type && m_value == other.m_value;
    }

private:
    StringView unit_name() const;

    Type m_type;
    float m_value { 0 };
};

}

template<>
struct AK::Formatter<Web::CSS::Angle> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, Web::CSS::Angle const& angle)
    {
        return Formatter<StringView>::format(builder, TRY(angle.to_string()));
    }
};
