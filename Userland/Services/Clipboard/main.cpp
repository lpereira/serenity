/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Clipboard/ClientConnection.h>
#include <Clipboard/Storage.h>
#include <LibCore/EventLoop.h>
#include <LibCore/LocalServer.h>
#include <LibCore/System.h>
#include <LibIPC/ClientConnection.h>
#include <LibMain/Main.h>

ErrorOr<int> serenity_main(Main::Arguments)
{
    TRY(Core::System::pledge("stdio recvfd sendfd accept"));
    Core::EventLoop event_loop;
    TRY(Core::System::unveil(nullptr, nullptr));

    auto server = TRY(Core::LocalServer::try_create());
    bool ok = server->take_over_from_system_server();
    VERIFY(ok);

    server->on_accept = [&](auto client_socket) {
        static int s_next_client_id = 0;
        int client_id = ++s_next_client_id;
        (void)IPC::new_client_connection<Clipboard::ClientConnection>(move(client_socket), client_id);
    };

    Clipboard::Storage::the().on_content_change = [&] {
        Clipboard::ClientConnection::for_each_client([&](auto& client) {
            client.notify_about_clipboard_change();
        });
    };

    return event_loop.exec();
}
