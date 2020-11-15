
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

# Add all .cpp files to the sources
for dirpath, dirnames, filenames in os.walk(os.path.join(root_dir, 'src')):
    srcs.extend([os.path.join(dirpath, f) for f in filenames if f.endswith('.cpp') ])

# Remove unwanted sources
filter_rgx = re.compile(r".*(main|benchmark)/[\w\-]*\.cpp|.*rematch_wrap.cpp")
srcs = [p for p in srcs if not filter_rgx.fullmatch(p)]

# print(*srcs, sep='\n')

# Adds the swig interface file
srcs.append(os.path.join(root_dir, "src/interfaces/rematch.i"))

# Set include dirs
include_dirs = [os.path.join(root_dir, 'src'),
                os.path.join(root_dir, 'thirdparty')]

# Check is BOOST_ROOT env variable is set, and include the headers
boost = os.environ.get("BOOST_ROOT")
if boost!=None:
    print("Read BOOST_ROOT env:", boost)
    include_dirs.append(os.path.join(boost, "boost"))

rematch_module = Extension('_rematch',
                            sources=srcs,
                            include_dirs=include_dirs,
                            libraries=libraries,
                            extra_compile_args=["-std=c++17"],
                            swig_opts=["-c++"]
                            )

# Get the long description from the README file
long_description = codecs.open(os.path.join(root_dir,'python/packages/pyrematch/README.md'), encoding='utf8').read()


class BinaryDistribution(Distribution):
    def has_ext_modules(self):
        return True

class CustomBuildPy(build_py):
    def run(self):
        self.run_command("build_ext")
        copy_file(os.path.join(root_dir, 'src/interfaces/rematch.py'),
                  os.path.join(root_dir, 'python/packages/pyrematch'))
        return super().run()

setup(
    name='pyrematch',
    version='0.1.3',
    description='An information extraction focused regex library that uses '\
                'constant-delay algorithms.' ,
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/REmatchChile/REmatch',
    author='Oscar Cárcamo <oscar.carcamoz@uc.cl>, Nicolás Van Sint Jan <nicovsj@uc.cl>',
    ext_modules=[rematch_module],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3'
    ],
    keywords='regex, rematch',
    license='MIT',
    packages=find_packages(where='python/packages'),
    package_dir={'':'python/packages',
                 'pyrematch': 'python/packages/pyrematch'},
    package_data={'pyrematch': ['_rematch*']},
    cmdclass={'build_py': CustomBuildPy},
    python_requires='>=3.6, <4',
    # distclass=BinaryDistribution,
)
