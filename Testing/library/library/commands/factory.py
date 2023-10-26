from tabulate import tabulate
from library.library import Library
from typing import Dict, Callable, TypeAlias


CommandHandler: TypeAlias = Callable[[Library], None]


class CommandFactory:
  class Factory:
    def __init__(self):
      self.commands: Dict[str, CommandHandler] = {}

    def add_command(self, op, cmd):
      self.commands[op] = cmd

    def get_command(self, op) -> CommandHandler:
      if op not in self.commands:
        raise KeyError('Неизвестная команда')
      return self.commands[op]

    def help(self) -> str:
      cmd_table = []
      for opcode, handler in self.commands.items():
        cmd_table.append((opcode, getattr(handler, '__doc__', '')))
      return tabulate(cmd_table, ('Код команды', 'Описание команды'), "rounded_grid")

  _instance = None

  def __new__(cls, *args, **kwargs):
    if cls._instance is None:
      cls._instance = cls.Factory()
    return cls._instance
