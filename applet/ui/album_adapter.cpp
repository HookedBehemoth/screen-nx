#include "album_adapter.hpp"

#include "../translation/translation.hpp"
#include "album_thumb.hpp"

#include <album.hpp>
#include <cmath>
#include <fmt/core.h>
#include <switch.h>

namespace album {

    namespace {

        constexpr size_t workSize = 0x10000;
        constexpr size_t imgSize  = 320 * 180 * 4;
        u8 workBuffer[workSize];
        u8 imgBuffer[imgSize];

    }

    ThumbnailAdapter::ThumbnailAdapter() {
        applyFilter();
    }

    size_t ThumbnailAdapter::getItemCount() {
        return albumFilterList.size();
    }

    brls::View *ThumbnailAdapter::createView() {
        return new Thumbnail(albumFilterList[0]);
    }

    void ThumbnailAdapter::bindView(brls::View *view, int index) {
        auto imageHolder = static_cast<album::Thumbnail *>(view);

        auto &fileId = albumFilterList[index];

        u64 w, h;
        CapsScreenShotDecodeOption opts;
        CapsScreenShotAttribute attrs;

        Result rc = capsLoadAlbumScreenShotThumbnailImageEx0(&w, &h, &attrs, &fileId.get(), &opts, imgBuffer, imgSize, workBuffer, workSize);

        if (R_FAILED(rc))
            return brls::Logger::error("Failed to load image with: 0x%x", rc);

        if (fileId.get().content == CapsAlbumFileContents_Movie) {
            /* Round video length to nearest full number. */
            u8 seconds               = std::round(static_cast<float>(attrs.length_x10) / 1000);
            imageHolder->frameCount  = attrs.frame_count / 1000;
            imageHolder->videoLength = fmt::format(~LENGTH_FMT, seconds);
        } else {
            imageHolder->frameCount  = 0;
            imageHolder->videoLength = "";
        }

        /* TODO: async loading with deko3d */
        imageHolder->setRGBAImage(imgBuffer, ThumbnailWidth, ThumbnailHeight);
    }

    bool ThumbnailAdapter::applyFilter() {
        auto &entries = getAllEntries();
        albumFilterList.reserve(std::size(entries));
        /* TODO */
        for (auto &entry : entries)
            albumFilterList.emplace_back(entry.file_id);

        return true;
    }

}
