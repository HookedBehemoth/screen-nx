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
#include "ui/MainApplication.hpp"

#include "util/set.hpp"

extern Settings g_Settings;

namespace ui {

	MainApplication *mainApp;

	void MainApplication::OnLoad() {
		mainApp = this;
		g_Settings.Initialize();

		this->Load();
	}

	void MainApplication::Load() {
		printf("Creating UploadLayout\n");
		this->uploadLayout = UploadLayout::New();
		this->uploadLayout->SetOnInput(std::bind(&UploadLayout::onInput, this->uploadLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		printf("Creating ListLayout\n");
		this->listLayout = ListLayout::New();
		this->listLayout->SetOnInput(std::bind(&ListLayout::onInput, this->listLayout, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		this->LoadLayout(this->listLayout);
	}

}
