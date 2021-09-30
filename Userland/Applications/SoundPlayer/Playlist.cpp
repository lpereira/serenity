/*
 * Copyright (c) 2021, Cesar Torres <shortanemoia@protonmail.com>
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Playlist.h"

#include <AK/LexicalPath.h>
#include <AK/Random.h>
#include <LibAudio/Loader.h>
#include <LibGUI/MessageBox.h>

bool Playlist::load(StringView path)
{
    auto parser = M3UParser::from_file(path);
    auto items = parser->parse(true);

    if (items->size() <= 0)
        return false;

    try_fill_missing_info(*items, path);
    for (auto& item : *items)
        m_model->items().append(item);
    m_model->invalidate();

    return true;
}

void Playlist::try_fill_missing_info(Vector<M3UEntry>& entries, StringView path)
{
    LexicalPath playlist_path(path);
    Vector<M3UEntry*> to_delete;

    for (auto& entry : entries) {
        if (!LexicalPath(entry.path).is_absolute())
            entry.path = String::formatted("{}/{}", playlist_path.dirname(), entry.path);

        if (!Core::File::exists(entry.path)) {
            GUI::MessageBox::show(nullptr, String::formatted("The file \"{}\" present in the playlist does not exist or was not found. This file will be ignored.", entry.path), "Error reading playlist", GUI::MessageBox::Type::Warning);
            to_delete.append(&entry);
            continue;
        }

        if (!entry.extended_info->track_display_title.has_value())
            entry.extended_info->track_display_title = LexicalPath::title(entry.path);

        if (!entry.extended_info->track_length_in_seconds.has_value()) {
            //TODO: Implement embedded metadata extractor for other audio formats
            if (auto reader = Audio::Loader::create(entry.path); !reader->has_error())
                entry.extended_info->track_length_in_seconds = reader->total_samples() / reader->sample_rate();
        }

        //TODO: Implement a metadata parser for the uncomfortably numerous popular embedded metadata formats

        if (!entry.extended_info->file_size_in_bytes.has_value()) {
            FILE* f = fopen(entry.path.characters(), "r");
            VERIFY(f != nullptr);
            fseek(f, 0, SEEK_END);
            entry.extended_info->file_size_in_bytes = ftell(f);
            fclose(f);
        }
    }

    for (M3UEntry* entry : to_delete)
        entries.remove_first_matching([&](M3UEntry& e) { return &e == entry; });
}

StringView Playlist::next()
{
    if (m_next_index_to_play >= size()) {
        if (!looping())
            return {};
        m_next_index_to_play = 0;
    }
    auto next = m_model->items().at(m_next_index_to_play).path;
    if (shuffling())
        m_next_index_to_play = get_random_uniform(size());
    else
        m_next_index_to_play++;
    return next;
}

StringView Playlist::previous()
{
    m_next_index_to_play--;
    if (m_next_index_to_play < 0) {
        m_next_index_to_play = 0;
        return {};
    }
    return m_model->items().at(m_next_index_to_play).path;
}
