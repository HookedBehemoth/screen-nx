/*
 * Copyright (c) 2019-2020 ShareNX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <pu/Plutonium>

#include "ui/elm_FixedMenu.hpp"

using namespace pu::ui::elm;
namespace ui {

	class ListLayout : public pu::ui::Layout {
	public:
		ListLayout();
		PU_SMART_CTOR(ListLayout)
		void onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos);

	private:
		void onItemClick();
		TextBlock::Ref topText;
		TextBlock::Ref infoText;
		Rectangle::Ref topRect;
		FixedMenu::Ref menu;
		Image::Ref image;
	};

}
