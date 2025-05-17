from setuptools import find_packages
from setuptools import setup

setup(
    name='wpr_simulation2',
    version='1.0.0',
    packages=find_packages(
        include=('wpr_simulation2', 'wpr_simulation2.*')),
)
