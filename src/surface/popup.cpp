#include "popup.hpp"

#include "surface.hpp"
#include "types.hpp"

static void popup_map_notify(wl_listener* listener, void* data) {
	(void) listener;
	(void) data;
}

static void popup_unmap_notify(wl_listener* listener, void* data) {
	(void) listener;
	(void) data;
}

static void popup_destroy_notify(wl_listener* listener, void* data) {
	Popup& popup = magpie_container_of(listener, popup, destroy);
	(void) data;

	delete &popup;
}

static void popup_commit_notify(wl_listener* listener, void* data) {
	(void) listener;
	(void) data;
}

static void popup_new_popup_notify(wl_listener* listener, void* data) {
	const Popup& popup = magpie_container_of(listener, popup, new_popup);

	new Popup(popup, *static_cast<wlr_xdg_popup*>(data));
}

Popup::Popup(const Surface& parent, wlr_xdg_popup& wlr) noexcept
	: listeners(*this), server(parent.get_server()), parent(parent), wlr(wlr) {
	this->wlr = wlr;
	auto* scene_tree = wlr_scene_xdg_surface_create(parent.scene_node->parent, wlr.base);
	scene_node = &scene_tree->node;

	scene_node->data = this;
	wlr.base->surface->data = this;

	listeners.map.notify = popup_map_notify;
	wl_signal_add(&wlr.base->surface->events.map, &listeners.map);
	listeners.unmap.notify = popup_unmap_notify;
	wl_signal_add(&wlr.base->surface->events.unmap, &listeners.unmap);
	listeners.destroy.notify = popup_destroy_notify;
	wl_signal_add(&wlr.base->events.destroy, &listeners.destroy);
	listeners.commit.notify = popup_commit_notify;
	wl_signal_add(&wlr.base->surface->events.commit, &listeners.commit);
	listeners.new_popup.notify = popup_new_popup_notify;
	wl_signal_add(&wlr.base->events.new_popup, &listeners.new_popup);
}

Popup::~Popup() noexcept {
	wl_list_remove(&listeners.map.link);
	wl_list_remove(&listeners.unmap.link);
	wl_list_remove(&listeners.destroy.link);
	wl_list_remove(&listeners.commit.link);
	wl_list_remove(&listeners.new_popup.link);
}

constexpr wlr_surface* Popup::get_wlr_surface() const {
	return wlr.base->surface;
}

constexpr Server& Popup::get_server() const {
	return server;
}

constexpr bool Popup::is_view() const {
	return false;
}
