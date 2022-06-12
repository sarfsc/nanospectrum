/***********************************************************************************************************************
**
** Copyright (C) 2022 Evgeny Sinelnikov. <sin@altlinux.org>
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
***********************************************************************************************************************/

#ifndef NANOSPECTRUM_PLUGIN_H
#define NANOSPECTRUM_PLUGIN_H

#include "model.h"

#include "common.h"

#include <functional>
#include <map>
#include <memory>

class QLibrary;
class QString;

namespace nanospectrum {
    class PluginPrivate;
    class PluginStorage;

    class NANOSPECTRUM_MODEL_EXPORT Plugin
    {
    public:
        virtual ~Plugin();

        const QString& getName() const;

        void setLibrary(std::unique_ptr<QLibrary> library);
        QLibrary* getLibrary() const;

        const std::map<QString, std::function<void *()> > &getPluginClasses() const;

    protected:
        explicit Plugin(const QString& name);
        explicit Plugin(const char* name);

        void registerPluginClass(const QString& name, std::function<void*()> constructor);

    private:
        Plugin(const Plugin&)            = delete;   // copy ctor
        Plugin(Plugin&&)                 = delete;   // move ctor
        Plugin& operator=(const Plugin&) = delete;   // copy assignment
        Plugin& operator=(Plugin&&)      = delete;   // move assignment

    private:
        PluginPrivate* d;
    };
}

#define NANOSPECTRUM_EXPORT_PLUGIN(name, className) \
    extern "C" NANOSPECTRUM_SYMBOL_EXPORT nanospectrum::Plugin* nanospectrum_plugin_init() \
    { \
        return new className; \
    }

#define NANOSPECTRUM_REGISTER_PLUGIN_CLASS(name, pluginClass) \
    registerPluginClass(name, [](){ return new pluginClass(); })

#endif // NANOSPECTRUM_PLUGIN_H
