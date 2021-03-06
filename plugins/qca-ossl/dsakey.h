/*
 * Copyright (C) 2004-2007  Justin Karneges <justin@affinix.com>
 * Copyright (C) 2004-2006  Brad Hards <bradh@frogmouth.net>
 * Copyright (C) 2013-2016  Ivan Romanov <drizt@land.ru>
 * Copyright (C) 2017       Fabian Vogt <fabian@ritter-vogt.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 */

#pragma once

#include "evpkey.h"
#include "qcaprovider.h"

#include <openssl/dsa.h>

using namespace QCA;
namespace opensslQCAPlugin {

// note: DSA doesn't use SignatureAlgorithm, since EMSA1 is always assumed
class DSAKeyMaker;
class DSAKey : public DSAContext
{
    Q_OBJECT
public:
    EVPKey       evp;
    DSAKeyMaker *keymaker;
    bool         wasBlocking;
    bool         transformsig;
    bool         sec;

    DSAKey(Provider *p);
    DSAKey(const DSAKey &from);
    ~DSAKey() override;

    Provider::Context *clone() const override;

    bool       isNull() const override;
    PKey::Type type() const override;
    bool       isPrivate() const override;
    bool       canExport() const override;
    void       convertToPublic() override;
    int        bits() const override;
    void       startSign(SignatureAlgorithm, SignatureFormat format) override;
    void       startVerify(SignatureAlgorithm, SignatureFormat format) override;
    void       update(const MemoryRegion &in) override;
    QByteArray endSign() override;
    bool       endVerify(const QByteArray &sig) override;
    void       createPrivate(const DLGroup &domain, bool block) override;
    void       createPrivate(const DLGroup &domain, const BigInteger &y, const BigInteger &x) override;
    void       createPublic(const DLGroup &domain, const BigInteger &y) override;
    DLGroup    domain() const override;
    BigInteger y() const override;
    BigInteger x() const override;

private Q_SLOTS:
    void km_finished();
};

}
