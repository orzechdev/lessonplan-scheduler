# Algorithm

## Setup

1. Install Visual Studio Build Tools (it will solve the error `Unable to find vcvarsall.bat` and error `Microsoft Visual C++ 14.0 is required.`) - make sure you have installed Windows 10 SDK as mentioned here https://github.com/benfred/implicit/issues/76, but probably the whole C++ compilation tools (select workloads/packs --> Visual C++ compile/build tools) will be needed. Also make sure you have VS version similar to that after running in `python` console e.g. `Python 3.7.4 (tags/v3.7.4:e09359112e, Jul  8 2019, 20:34:20) [MSC v.1916 64 bit (AMD64)] on win32` - `MSC v.1916`. Link to download MS VS build tools:
https://visualstudio.microsoft.com/downloads/
2. Build algorithm by running:
    ```
    python setup.py build_ext --inplace
    ```
    http://docs.cython.org/en/latest/src/quickstart/build.html
    http://docs.cython.org/en/latest/src/userguide/wrapping_CPlusPlus.html
3. Then simply start a Python session and do `from algorithm import run_algorithm` and use the imported function as you see fit
