project(
    'magpie',
    ['cpp'],
    version: '1.0',
    license: 'Apache-2.0',
    default_options: [
        'cpp_std=c++20',
        'warning_level=3'
    ],
)

dep_m = meson.get_compiler('cpp').find_library('m', required: false)

dep_wayland_protocols = dependency('wayland-protocols', version: '>= 1.31')
dep_wayland_scanner = dependency('wayland-scanner')
dep_wayland_server = dependency('wayland-server')
dep_wlroots = dependency('wlroots', version: ['>= 0.17', '< 0.18.0'], fallback: ['wlroots', 'wlroots_dep'])
dep_xcb = dependency('xcb')
dep_xkbcommon = dependency('xkbcommon')

wayland_protocol_dir = dep_wayland_protocols.get_variable('pkgdatadir')

wayland_scanner = find_program(
  	dep_wayland_scanner.get_variable('wayland_scanner'),
  	native: true,
)

xdg_shell_protocol = custom_target(
    'xdg_shell_server_h',
    input: join_paths(wayland_protocol_dir, 'stable', 'xdg-shell', 'xdg-shell.xml'),
    output: 'xdg-shell-protocol.h',
    command: [wayland_scanner, 'server-header', '@INPUT@', '@OUTPUT@'],
    build_by_default: false,
)

wlr_pointer_constraints_protocol = custom_target(
    'wlr_pointer_constraints_unstable_v1_protocol_h',
    input: join_paths(wayland_protocol_dir, 'unstable', 'pointer-constraints', 'pointer-constraints-unstable-v1.xml'),
    output: 'pointer-constraints-unstable-v1-protocol.h',
    command: [wayland_scanner, 'server-header', '@INPUT@', '@OUTPUT@'],
    build_by_default: false,
)

wlr_output_power_management_protocol = custom_target(
    'wlr_output_power_management_unstable_v1_protocol_h',
    input: join_paths(meson.source_root(), 'protocols', 'wlr-output-power-management-unstable-v1.xml'),
    output: 'wlr-output-power-management-unstable-v1-protocol.h',
    command: [wayland_scanner, 'server-header', '@INPUT@', '@OUTPUT@'],
    build_by_default: false,
)

wlr_layer_shell_protocol = custom_target(
    'wlr_layer_shell_unstable_v1_protocol_h',
    input: join_paths(meson.source_root(), 'protocols', 'wlr-layer-shell-unstable-v1.xml'),
    output: 'wlr-layer-shell-unstable-v1-protocol.h',
    command: [wayland_scanner, 'server-header', '@INPUT@', '@OUTPUT@'],
    build_by_default: false,
)

subdir('src')
