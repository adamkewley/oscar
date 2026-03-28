#include "gltf_demo.h"

#include <liboscar/platform/widget_private.h>
#include <liboscar/ui/oscimgui.h>

using namespace osc;

class osc::GLTFDemo::Impl final : public WidgetPrivate {
public:
    static CStringView static_label() { return "oscar_demos/GLTF"; }

    explicit Impl(GLTFDemo& owner, Widget* parent) :
        WidgetPrivate{owner, parent}
    {
        set_name(static_label());
    }

    void on_draw()
    {
        ui::draw_text("hello");
    }
};

CStringView osc::GLTFDemo::id() { return Impl::static_label(); }
osc::GLTFDemo::GLTFDemo(Widget* parent) : Widget{std::make_unique<Impl>(*this, parent)} {}
void osc::GLTFDemo::impl_on_draw() { private_data().on_draw(); }
