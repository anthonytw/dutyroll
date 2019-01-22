import sys

from packaging.version import LegacyVersion
from skbuild.exceptions import SKBuildError
from skbuild.cmaker import get_cmake_version
from skbuild import setup

setup_requires = []

# Require pytest-runner only when running tests.
if any(arg in sys.argv for arg in ('pytest', 'test')):
	setup_requires.append('pytest-runner>=2.0')

# Add CMake as a build requirement if cmake is not installed or is too low a version.
try:
    if LegacyVersion(get_cmake_version()) < LegacyVersion('3.10'):
        setup_requires.append('cmake')
except SKBuildError:
    setup_requires.append('cmake')

setup(
    name='dutyroll',
    version='1.0.1',
    description='Parallel implementation of rolling window duty cycle.',
    author='"Anthony Wertz"<awertz@cmu.edu>',
    license='MIT',
    packages=['dutyroll'],
    tests_require=['pytest'],
    setup_requires=setup_requires
)
