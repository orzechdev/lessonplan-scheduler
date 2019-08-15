import setuptools # important DO NOT REMOVE IT, EVEN IF UNUSED IMPORT IS SHOWN BY IDE!!!! -
#                             (it prevents "Unable to find vcvarsall.bat" error)
from distutils.core import setup
from Cython.Build import cythonize

setup(name='Hello world app',
      ext_modules=cythonize("algorithm.pyx", language_level=3),
      # zip_safe=False,
      requires=['Cython'])

