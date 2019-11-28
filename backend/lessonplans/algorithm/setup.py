import setuptools # important DO NOT REMOVE IT, EVEN IF UNUSED IMPORT IS SHOWN BY IDE!!!! -
#                             (it prevents "Unable to find vcvarsall.bat" error)
# from skbuild import setup
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize


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
                      # "./src/LessonplanSchedulingAlgorithm.cpp",
                      # "./src/LessonplanSchedulingProblem.cpp",
                      # "./src/LessonplanSchedulingProblemProperties.cpp",
                      # "./src/LessonplanSchedulingSolution.cpp",
                      "./src/lessonplan/LessonplanIndividualDescriptor.cpp",
                      "./src/lessonplan/LessonplanIndividual.cpp",
                      "./src/lessonplan/LessonplanIndividualFactory.cpp",
                      "./src/utils/RandomNumberGenerator.cpp",
                  ],  # "algorithm.pyx" and also all ".cpp" files must be listed here !!!!
              )
          ],
          language_level=3
      ),
      # zip_safe=False,
      requires=['Cython'],
      # cmdclass={'build_ext': CMakeBuild},
)

