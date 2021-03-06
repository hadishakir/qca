/*
 Copyright (C) 2007 Justin Karneges <justin@affinix.com>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "tlssocket.h"

#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCA::Initializer init;
    QCoreApplication qapp(argc, argv);
    QCA::logger()->setLevel(QCA::Logger::Debug);
    QCA::logger()->registerLogDevice(new SimpleLogger(&qapp));

    TLSSocket socket;
    socket.connectToHostEncrypted(QStringLiteral("tls13.1d.pw"), 443);
    socket.write("GET / HTTP/1.0\r\n\r\n");
    while (socket.waitForReadyRead())
        printf("%s", socket.readAll().constData());

    return 0;
}
