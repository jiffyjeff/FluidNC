// Copyright (c) 2020 -	Bart Dring
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#include <cstdint>

#include "../Configuration/Configurable.h"
#include "../Configuration/GenericFactory.h"
#include "../System.h"

namespace Displays {

    

    class Display;
    using DisplayList = std::vector<Display*>;

    // This is the base class. Do not use this as your spindle
    class Display : public Configuration::Configurable {
    protected:
        statusCounter _statusCount;

    public:
        virtual void init();
        virtual void config_message() = 0;
        virtual void status_changed();  // future pushed notification
        void         afterParse() override;
        virtual void update(statusCounter sysCounter);

        uint32_t _refresh_ms = 100;

        // Name is required for the configuration factory to work.
        virtual const char* name() const = 0;

        void group(Configuration::HandlerBase& handler) override { handler.item("refresh_ms", _refresh_ms); }

        // Virtual base classes require a virtual destructor.
        virtual ~Display() {}
    };
    using DisplayFactory = Configuration::GenericFactory<Display>;
}