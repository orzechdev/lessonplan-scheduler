import setuptools # important DO NOT REMOVE IT, EVEN IF UNUSED IMPORT IS SHOWN BY IDE!!!! -
#                             (it prevents "Unable to find vcvarsall.bat" error)
# from skbuild import setup
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import os
import platform
import re
import subprocess
import sys
import sysconfig
from pprint import pprint
# from setuptools import Extension  # , setup
from setuptools.command.build_ext import build_ext

# # Filename for the C extension module library
# c_module_name = 'algorithm'
#
# # Parse command line flags
# options = {k: 'OFF' for k in ['--opt', '--debug', '--cuda']}
# for flag in options.keys():
#     if flag in sys.argv:
#         options[flag] = 'ON'
#         sys.argv.remove(flag)
#
# # Command line flags forwarded to CMake
# cmake_cmd_args = []
# for f in sys.argv:
#     if f.startswith('-D'):
#         cmake_cmd_args.append(f)
#
# for f in cmake_cmd_args:
#     sys.argv.remove(f)
#
#
# class CMakeExtension(Extension):
#     def __init__(self, name, cmake_lists_dir='.', sources=[], **kwa):
#         Extension.__init__(self, name, sources=sources, **kwa)
#         self.cmake_lists_dir = os.path.abspath(cmake_lists_dir)
#
#
# class CMakeBuild(build_ext):
#       def build_extensions(self):
#             # Ensure that CMake is present and working
#             try:
#                   out = subprocess.check_output(['cmake', '--version'])
#             except OSError:
#                   raise RuntimeError('Cannot find CMake executable')
#
#             for ext in self.extensions:
#
#                   extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
#                   cfg = 'Debug' if options['--debug'] == 'ON' else 'Release'
#
#                   cmake_args = [
#                         '-DCMAKE_BUILD_TYPE=%s' % cfg,
#                         # Ask CMake to place the resulting library in the directory
#                         # containing the extension
#                         '-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), extdir),
#                         # Other intermediate static libraries are placed in a
#                         # temporary build directory instead
#                         '-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), self.build_temp),
#                         # Hint CMake to use the same Python executable that
#                         # is launching the build, prevents possible mismatching if
#                         # multiple versions of Python are installed
#                         '-DPYTHON_EXECUTABLE={}'.format(sys.executable),
#                         # Add other project-specific CMake arguments if needed
#                         # ...
#                   ]
#
#                   # We can handle some platform-specific settings at our discretion
#                   if platform.system() == 'Windows':
#                         plat = ('x64' if platform.architecture()[0] == '64bit' else 'Win32')
#                         cmake_args += [
#                               # These options are likely to be needed under Windows
#                               '-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE',
#                               '-DCMAKE_RUNTIME_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), extdir),
#                         ]
#                         # Assuming that Visual Studio and MinGW are supported compilers
#                         if self.compiler.compiler_type == 'msvc':
#                               cmake_args += [
#                                     '-DCMAKE_GENERATOR_PLATFORM=%s' % plat,
#                               ]
#                         else:
#                               cmake_args += [
#                                     '-G', 'MinGW Makefiles',
#                               ]
#
#                   cmake_args += cmake_cmd_args
#
#                   if not os.path.exists(self.build_temp):
#                         os.makedirs(self.build_temp)
#
#                   # Config
#                   lists_dir = '.'
#                   if hasattr(ext, 'cmake_lists_dir'):
#                       lists_dir = ext.cmake_lists_dir
#                   subprocess.check_call(['cmake', lists_dir] + cmake_args,
#                                         cwd=self.build_temp)
#
#                   # Build
#                   subprocess.check_call(['cmake', '--build', '.', '--config', cfg],
#                                         cwd=self.build_temp)


setup(
      name='Lessonplan scheduler algorithm',
      ext_modules=cythonize(
          [
              # CMakeExtension(c_module_name),
              Extension(
                  name="algorithm",
                  include_dirs=["./include/algorithm"],
                  library_dirs=["./src"],
                  sources=[
                      "algorithm.pyx",
                      "./src/LessonplanScheduler.cpp",
                      "./src/GenAlgorithm.cpp",
                      "./src/LessonplanGenAlgorithm.cpp",
                      "./src/Individual.cpp",
                      "./src/LessonplanIndividual.cpp"
                  ],  # "algorithm.pyx" and also all ".cpp" files must be listed here !!!!
              )
          ],
          language_level=3
      ),
      # zip_safe=False,
      requires=['Cython'],
      # cmdclass={'build_ext': CMakeBuild},
)

