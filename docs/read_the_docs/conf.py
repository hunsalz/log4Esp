import sys
import os
import shlex
import subprocess

read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

if read_the_docs_build:
    subprocess.call('doxygen', shell=True)

extensions = ['breathe']
breathe_projects = { 'log4Esp': 'xml' }
breathe_default_project = "log4Esp"
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
project = u'log4Esp'
copyright = u'2018, log4Esp'
author = u'log4Esp'
version = '1.0.0'
release = '1.0.0'
language = None
exclude_patterns = ['_build']
pygments_style = 'sphinx'
todo_include_todos = False
html_static_path = ['_static']
htmlhelp_basename = 'log4Espdoc'
latex_elements = {
}
latex_documents = [
  (master_doc, 'log4Esp.tex', u'log4Esp Documentation',
   u'log4Esp', 'manual'),
]
