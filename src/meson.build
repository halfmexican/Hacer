hacer_sources = [
  'main.vala',
  'application.vala',
  'window.vala',
  'AgendaRow.vala',
  'utils.vala',
  'HacerPreferencesWindow.vala'
]

hacer_deps = [
  dependency('gtk4'),
  dependency('gio-2.0'),
  dependency('libadwaita-1'),
  dependency('json-glib-1.0')
]

hacer_sources += gnome.compile_resources('hacer-resources',
  'hacer.gresource.xml',
  c_name: 'hacer'
)

executable('hacer', hacer_sources,
  dependencies: hacer_deps,
       install: true,
)
