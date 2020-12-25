/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include <cppuhelper/implbase.hxx>
#include <cppuhelper/supportsservice.hxx>

#include <com/sun/star/util/XBinaryDataContainer.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>

#include <vcl/BinaryDataContainer.hxx>

using namespace css;

namespace
{
typedef ::cppu::WeakImplHelper<util::XBinaryDataContainer, css::lang::XServiceInfo>
    BinaryDataContainer_BASE;

class UnoBinaryDataContainer : public BinaryDataContainer_BASE
{
private:
    BinaryDataContainer maBinaryDataContainer;

public:
    explicit UnoBinaryDataContainer() {}

    BinaryDataContainer const& getBinaryDataContainer() { return maBinaryDataContainer; }

    void setBinaryDataContainer(BinaryDataContainer const& rBinaryDataContainer)
    {
        maBinaryDataContainer = rBinaryDataContainer;
    }

    // XBinaryDataContainer
    css::uno::Sequence<sal_Int8> SAL_CALL getCopyAsByteSequence() override
    {
        if (maBinaryDataContainer.isEmpty())
            return css::uno::Sequence<sal_Int8>();

        size_t nSize = maBinaryDataContainer.getSize();

        css::uno::Sequence<sal_Int8> aData(nSize);

        std::copy(maBinaryDataContainer.cbegin(), maBinaryDataContainer.cend(), aData.getArray());

        return aData;
    }

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName() override
    {
        return "com.sun.star.util.BinaryDataContainer";
    }

    virtual sal_Bool SAL_CALL supportsService(OUString const& rServiceName) override
    {
        return cppu::supportsService(this, rServiceName);
    }

    virtual css::uno::Sequence<OUString> SAL_CALL getSupportedServiceNames() override
    {
        return uno::Sequence<OUString>{ "com.sun.star.util.BinaryDataContainer" };
    }
};

} // end anonymous namespace

extern "C" SAL_DLLPUBLIC_EXPORT css::uno::XInterface*
com_sun_star_comp_util_BinaryDataContainer_get_implementation(
    SAL_UNUSED_PARAMETER uno::XComponentContext*,
    SAL_UNUSED_PARAMETER uno::Sequence<uno::Any> const&)
{
    return cppu::acquire(new UnoBinaryDataContainer());
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
