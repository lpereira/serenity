/*
 * Copyright (c) 2021, L. A. F. Pereira <l@tia.mat.br>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/RefPtr.h>
#include <AK/String.h>
#include <AK/Variant.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Color.h>
#include <LibGfx/StandardCursor.h>

class Skin {
public:
    void load_from_file(String const&);

    // GUI parts
    RefPtr<Gfx::Bitmap> main() const { return m_main; }
    RefPtr<Gfx::Bitmap> cbuttons() const { return m_cbuttons; }
    RefPtr<Gfx::Bitmap> numbers() const { return m_numbers; }
    RefPtr<Gfx::Bitmap> playpaus() const { return m_playpaus; }
    RefPtr<Gfx::Bitmap> posbar() const { return m_posbar; }
    RefPtr<Gfx::Bitmap> shufrep() const { return m_shufrep; }
    RefPtr<Gfx::Bitmap> titlebar() const { return m_titlebar; }
    RefPtr<Gfx::Bitmap> volume() const { return m_volume; }
    RefPtr<Gfx::Bitmap> balance() const { return m_balance; }
    RefPtr<Gfx::Bitmap> monoster() const { return m_monoster; }
    RefPtr<Gfx::Bitmap> text() const { return m_text; }

    // Cursors
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> cur_volbal() const
    {
        return m_cur_volbal;
    }
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> cur_titlebar() const
    {
        return m_cur_titlebar;
    }
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> cur_psize() const
    {
        return m_cur_psize;
    }
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> cur_posbar() const
    {
        return m_cur_posbar;
    }
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> cur_mainmenu() const
    {
        return m_cur_mainmenu;
    }
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> cur_eqtitle() const
    {
        return m_cur_eqtitle;
    }
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> cur_eqslid() const
    {
        return m_cur_eqslid;
    }
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> cur_close() const
    {
        return m_cur_close;
    }

    Color viscolor(int index) const
    {
        return (index >= 0 && index <= 23) ? m_viscolor[index] : Gfx::Color(Gfx::Color::NamedColor::Black);
    }

private:
    // GUI parts
    RefPtr<Gfx::Bitmap> m_main;
    RefPtr<Gfx::Bitmap> m_cbuttons;
    RefPtr<Gfx::Bitmap> m_numbers;
    RefPtr<Gfx::Bitmap> m_playpaus;
    RefPtr<Gfx::Bitmap> m_posbar;
    RefPtr<Gfx::Bitmap> m_shufrep;
    RefPtr<Gfx::Bitmap> m_titlebar;
    RefPtr<Gfx::Bitmap> m_volume;
    RefPtr<Gfx::Bitmap> m_balance;
    RefPtr<Gfx::Bitmap> m_monoster;
    RefPtr<Gfx::Bitmap> m_text;

    // Cursors
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> m_cur_volbal { Gfx::StandardCursor::ResizeHorizontal };
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> m_cur_titlebar { Gfx::StandardCursor::Move };
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> m_cur_psize { Gfx::StandardCursor::Arrow };
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> m_cur_posbar { Gfx::StandardCursor::ResizeHorizontal };
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> m_cur_mainmenu { Gfx::StandardCursor::Arrow };
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> m_cur_eqtitle { Gfx::StandardCursor::Move };
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> m_cur_eqslid { Gfx::StandardCursor::ResizeVertical };
    AK::Variant<Gfx::StandardCursor, AK::NonnullRefPtr<Gfx::Bitmap>> m_cur_close { Gfx::StandardCursor::Arrow };

    Gfx::Color m_viscolor[24];
};
