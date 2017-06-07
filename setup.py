from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import os
import setuptools
import subprocess

__version__ = '0.0.1'


class get_pybind_include(object):
    """Helper class to determine the pybind11 include path
    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        try:
            import pybind11
            return pybind11.get_include(self.user)
        except ImportError:
            return 'pybind11/include'


def build_osdk_libs():

    print 'building osdk library...'

    if not os.path.isdir('./Onboard-SDK/build'):
        print 'creating build directory...'
        subprocess.call(['mkdir','-p', './Onboard-SDK/build'])
    else:
        print "osdk build directory present..."
        subprocess.call(['rm', '-rf', './Onboard-SDK/build/*'])

    cmake_cmd = ['cmake', '-DCMAKE_POSITION_INDEPENDENT_CODE=TRUE', '..']
    build_dir = './Onboard-SDK/build'

    p = subprocess.Popen(cmake_cmd, cwd=build_dir)
    p.wait()

    p = subprocess.Popen(['make'], cwd=build_dir)
    p.wait()

ext_modules = [
    Extension(
        'osdkpy',
        ['src/Drone.cpp', 'src/bindings.cpp'],
        include_dirs=[
            # Path to pybind11 headers
            get_pybind_include(),
            get_pybind_include(user=True),
            'inc',
            'Onboard-SDK/osdk-core/inc',
            'Onboard-SDK/osdk-wrapper/inc',
            'Onboard-SDK/platform/linux/inc'
        ],
        #extra_compile_args=['-fPIC'],
        library_dirs=['Onboard-SDK/build/libs'],
        libraries=['djiosdk-wrapper','djiosdk-platform', 'djiosdk-core'],
        language='c++'
    ),
]


# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True


def cpp_flag(compiler):
    """Return the -std=c++[11/14] compiler flag.
    The c++14 is prefered over c++11 (when it is available).
    """
    if has_flag(compiler, '-std=c++14'):
        return '-std=c++14'
    elif has_flag(compiler, '-std=c++11'):
        return '-std=c++11'
    else:
        raise RuntimeError('Unsupported compiler -- at least C++11 support '
                           'is needed!')


class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    c_opts = {
        'msvc': ['/EHsc'],
        'unix': [],
    }

    if sys.platform == 'darwin':
        c_opts['unix'] += ['-stdlib=libc++', '-mmacosx-version-min=10.7']

    def build_extensions(self):
        build_osdk_libs()
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])
        if ct == 'unix':
            opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
            opts.append(cpp_flag(self.compiler))
            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
        elif ct == 'msvc':
            opts.append('/DVERSION_INFO=\\"%s\\"' % self.distribution.get_version())
        for ext in self.extensions:
            ext.extra_compile_args = opts
        build_ext.build_extensions(self)

setup(
    name='osdkpy',
    version=__version__,
    author='Miguel Alonso Jr',
    author_email='drmiguelalonsojr@gmail.com',
    url='https://github.com/drmaj/Onboard-SDK-python',
    description='Python module with bindings for the DJI Onboard-SDK',
    long_description='',
    ext_modules=ext_modules,
    install_requires=['pybind11>=1.7'],
    cmdclass={'build_ext': BuildExt},
    zip_safe=False,
)
