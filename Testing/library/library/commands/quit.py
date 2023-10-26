import sys


def quit_command(library, database):
  """Выход"""

  library.dump(database)
  sys.exit(0)
