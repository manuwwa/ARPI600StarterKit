from distutils.core import setup, Extension

module1 = Extension('dht11py',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = ['/usr/local/include'],
                    libraries = ['wiringPi'],
                    library_dirs = ['/usr/local/lib'],
                    sources = ['MainLib.c'])

setup (name = 'dht11py',
       version = '1.0',
       description = 'Extension to operate dht11 sensor',
       author = 'Marcin Packo',
       author_email = 'pacek253@gmail.com',
       url = 'http://docs.python.org/extending/building',
       long_description = '''
This is a extension for python to operate with dht11 sensor.
''',
       ext_modules = [module1])