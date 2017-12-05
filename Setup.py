from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext


#fill in the source files here
sourcefiles = ['mySmbus.pyx']
ext_modules = [Extension("mySmbus", sourcefiles)]


setup(name = 'mySmbus',
      cmdclass = {'build_ext':build_ext},
      ext_modules = ext_modules
      )