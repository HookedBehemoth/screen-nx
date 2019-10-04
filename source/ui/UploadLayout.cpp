/*
 * Copyright (c) 2019 screen-nx
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

#include "MainApplication.hpp"
#include "ui/UploadLayout.hpp"
#include "utils.hpp"
#define COLOR(hex) pu::ui::Color::FromHex(hex)

namespace scr::ui {
    extern MainApplication *mainApp;
    extern scr::utl::hosterConfig m_config;

    UploadLayout::UploadLayout(scr::utl::entry Entry) : Layout::Layout(), m_entry(Entry) {
        this->SetBackgroundColor(COLOR(m_config.m_theme.color_background));
        this->SetBackgroundImage(m_config.m_theme.background_path);
        this->topRect = Rectangle::New(0, 0, 1280, 30, COLOR(m_config.m_theme.color_topbar));
        this->topText = TextBlock::New(10, 0, m_config.m_name, 25);
        this->topText->SetColor(COLOR(m_config.m_theme.color_text));
        if (!strcmp(m_config.m_theme.image_path, "") == 0) {
            this->image = Image::New(m_config.m_theme.image_x, m_config.m_theme.image_y, m_config.m_theme.image_path);
            this->image->SetWidth(m_config.m_theme.image_w);
            this->image->SetHeight(m_config.m_theme.image_h);
            this->Add(this->image);
            this->Add(this->image);
        }
        this->bottomText = TextBlock::New(80, 640, "Press A to upload, B to go back!", 45);
        this->bottomText->SetColor(COLOR(m_config.m_theme.color_text));
        this->preview = Image::New(10, 40, m_entry.path);
        this->preview->SetWidth(970);
        this->preview->SetHeight(545);
        this->Add(this->topRect);
        this->Add(this->topText);
        this->Add(this->bottomText);
        this->Add(this->preview);
    }

    void UploadLayout::onInput(u64 Down, u64 Up, u64 Held, pu::ui::Touch Pos) {
        if ((Down & KEY_PLUS) || (Down & KEY_MINUS)) {
            mainApp->Close();
        }
        if  (uploading) {
            std::string url = scr::utl::uploadFile(m_entry.path, m_config);
            if(url.compare("")) {
                this->bottomText->SetText(url);
            } else {
                this->bottomText->SetText("Upload failed!");
            }
            uploading = false;
        }
        if(Down & KEY_A && !uploading) {
            uploading = true;
            this->bottomText->SetText("Uploading... Please wait!");
        }

        if (Down & KEY_B) {
            mainApp->LoadLayout(mainApp->listLayout);
        }
    }
}