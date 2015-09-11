/*
 * Copyright (c) 2011-2015, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#include "ElementBuilder.h"

namespace detail
{
/** Part of the implementation of `TNamedElementBuilderTemplate`
 * that does not need to be template.
 *
 * If this was implemented in this header, the xmlElement implementation
 * would leak to sources including this header.
 *
 * Plugins are including this header. As a result they would include
 * the xmlElement implementation if it was not hidden in a cpp.
 *
 * FIXME: The xml concept (forward declared) is still leaked to the plugin.
 *        A solution would be have two level of builders:
 *         - a PluginBuilder that wraps the plugin
 *         - and an ElementBuilder that wraps the PluginBuilder
 *        This way the plugin can only see the PluginBuilder and is not
 *        contaminated by any core specific concept.
 *
 * @param[in] xmlElement the XML element
 * @return the "Name" attribute value of an xml element or
 * empty string if attribute is not present
 *
 */
std::string getName(const CXmlElement& xmlElement);
}

template <class ElementType>
class TNamedElementBuilderTemplate : public CElementBuilder
{
public:
    CElement* createElement(const CXmlElement& xmlElement) const override
    {
        return new ElementType(detail::getName(xmlElement));
    }
};
