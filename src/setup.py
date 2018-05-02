from distutils.core import setup, Extension

setup(name = 'PyMyomag', ext_modules = [ Extension('PyMyomag', sources = ['AccelerationMagnitude.c', 'DataLoader.c'])])


