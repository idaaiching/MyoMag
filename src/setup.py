from distutils.core import setup, Extension

setup(name = 'PyMyomag', ext_modules = [ Extension('PyMyomag', sources = ['PyMyomag_module.c','acc.c'])])


