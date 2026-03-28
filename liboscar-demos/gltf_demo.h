#pragma once

#include <liboscar/platform/widget.h>
#include <liboscar/utilities/c_string_view.h>

namespace osc
{
    class GLTFDemo final : public Widget {
    public:
        static CStringView id();

        explicit GLTFDemo(Widget*);

    private:
        void impl_on_draw() final;

        class Impl;
        OSC_WIDGET_DATA_GETTERS(Impl);
    };
}
