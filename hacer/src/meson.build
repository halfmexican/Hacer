pkgdatadir = join_paths(get_option('prefix'), get_option('datadir'), meson.project_name())
moduledir = join_paths(pkgdatadir, 'hacer')
gnome = import('gnome')

gnome.compile_resources('hacer',
  'hacer.gresource.xml',
  gresource_bundle: true,
  install: true,
  install_dir: pkgdatadir,
)

python = import('python')

conf = configuration_data()

#conf.set('PYTHON', '/home/joshunter/pypy3.9-v7.3.9-linux64/bin')
conf.set('PYTHON', python.find_installation('python3').path())
conf.set('VERSION', meson.project_version())
conf.set('localedir', join_paths(get_option('prefix'), get_option('localedir')))
conf.set('pkgdatadir', pkgdatadir)

configure_file(
  input: 'hacer.in',
  output: 'hacer',
  configuration: conf,
  install: true,
  install_dir: get_option('bindir')
)

hacer_sources = [
  '__init__.py',
  'main.py',
  'window.py',
  'agendaTask.py',
  'prefWindow.py',
  'linkedListBox.py',
  'window.ui'
]

install_data(hacer_sources, install_dir: moduledir)
