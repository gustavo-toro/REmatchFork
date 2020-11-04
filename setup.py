"""A setuptools based setup module.
See:
https://packaging.python.org/guides/distributing-packages-using-setuptools/
https://github.com/pypa/sampleproject
"""

# Always prefer setuptools over distutils
from setuptools import setup, find_packages, Distribution
from setuptools.command.build_py import build_py
from distutils.file_util import copy_file
import re
import codecs
import os.path
import os
from sysconfig import get_platform

try:
    from setuptools.command.build_ext import build_ext
    from setuptools import setup, Extension, Command, find_packages
except:
    from distutils.command.build_ext import build_ext
    from distutils import setup, Extension, Command, find_packages

root_dir = os.path.abspath(os.path.dirname(__file__))
libraries = []

if(get_platform().startswith('win')):
    libraries.append('ws2_32')

srcs = []
for dirpath, dirnames, filenames in os.walk(os.path.join(root_dir, 'src')):
    srcs.extend([os.path.join(dirpath, f) for f in filenames if f.endswith('.cpp') ])


filter_rgx = re.compile(r".*(main|benchmark)/[\w\-]*\.cpp|.*rematch_wrap.cpp")

srcs = [p for p in srcs if not filter_rgx.fullmatch(p)]

print(*srcs, sep='\n')

srcs.append(os.path.join(root_dir, "src/interfaces/rematch.i"))

rematch_module = Extension('_rematch',
                            sources=srcs,
                            include_dirs=[os.path.join(root_dir, 'src'),
                                          os.path.join(root_dir, 'thirdparty')],
                            libraries=libraries,
                            extra_compile_args=["-std=c++17"],
                            swig_opts=["-c++"]
                            )

# Get the long description from the README file
long_description = codecs.open(os.path.join(root_dir,'README.md'), encoding='utf8').read()

# Arguments marked as "Required" below must be included for upload to PyPI.
# Fields marked as "Optional" may be commented out.

class BinaryDistribution(Distribution):
    def has_ext_modules(self):
        return True

class CustomBuildPy(build_py):
    def run(self):
        self.run_command("build_ext")
        # copy_file(os.path.join(root_dir, 'src/interfaces/rematch.py'),
        #           os.path.join(root_dir, 'python/packages/rematchpy'))
        return super().run()

setup(
    name='rematchpy',
    version='0.0.3',
    description='An information extraction focused regex library using '\
                'constant-delay algorithms.' ,
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/REmatchChile/REmatch',
    author='Nicolás A. Van Sint Jan',
    author_email='nicovsj@uc.cl',
    # ext_modules=[rematch_module],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3'
    ],
    keywords='regex',
    packages=find_packages(where='python/packages'),
    package_dir={'':'python/packages',
                 'rematchpy': 'python/packages/rematchpy'},
    package_data={'rematchpy': ['_rematch*']},
    cmdclass={'build_py': CustomBuildPy},
    python_requires='>=3.6, <4',
    distclass=BinaryDistribution,
)
