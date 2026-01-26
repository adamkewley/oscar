#include "liboscar/platform/app.h"
#include "liboscar/platform/app_metadata.h"
#include "liboscar/ui/oscimgui.h"
#include "liboscar/ui/tabs/tab_registry.h"
#include "liboscar-demos/oscar_demos_tab_registry.h"
#include <liboscar/utils/assertions.h>

#include "liboscar/platform/events/event.h"
#include "liboscar/platform/events/key_event.h"

#include <cstddef>
#include <memory>

#include "liboscar/platform/log.h"

using namespace osc;

namespace
{
    class OscarDemoViewer : public Widget {
    public:
        OscarDemoViewer()
        {
            register_demo_tabs(tab_registry_);
            OSC_ASSERT_ALWAYS(not tab_registry_.empty() && "the demo registry cannot be empty");
            active_tab_ = tab_registry_[active_tab_index_].construct_tab(this);
            App::upd().set_main_window_subtitle(active_tab_->name());
            App::upd().make_main_loop_polling();
        }

    private:
        bool impl_on_event(Event& e) final
        {
            if (e.type() == EventType::KeyUp) {
                const auto* kev = dynamic_cast<const KeyEvent*>(&e);
                const Key key = kev->key();
                if (key == Key::PageUp or key == Key::PageDown) {
                    const size_t offset = kev->key() == Key::PageUp ? 1 : (tab_registry_.size() - 1);
                    active_tab_index_ = (active_tab_index_ + offset) % tab_registry_.size();
                    active_tab_->on_unmount();
                    active_tab_.reset();
                    active_tab_ = tab_registry_[active_tab_index_].construct_tab(this);
                    active_tab_->on_mount();
                    App::upd().set_main_window_subtitle(active_tab_->name());
                }
                return true;
            }
            return ui_context_.on_event(e) ? true : active_tab_->on_event(e);
        }

        void impl_on_mount() final { active_tab_->on_mount(); }
        void impl_on_unmount() final { active_tab_->on_unmount(); }
        void impl_on_tick() final { active_tab_->on_tick(); }
        void impl_on_draw() final
        {
            App::upd().clear_main_window();
            ui_context_.on_start_new_frame();
            active_tab_->on_draw();
            ui_context_.render();
        }

        TabRegistry tab_registry_;
        ui::Context ui_context_{App::upd()};
        size_t active_tab_index_ = 0;
        std::unique_ptr<Tab> active_tab_;
    };
}

int main(int, char**) { return App::main<OscarDemoViewer>(AppMetadata{}); }
