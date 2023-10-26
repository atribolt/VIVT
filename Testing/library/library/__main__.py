from pathlib import Path
from functools import partial, wraps
from argparse import ArgumentParser
from library.library import Library, Book
from library.commands import CommandFactory


command_factory = CommandFactory()
library: Library | None


def init(file: Path):
  global library, command_factory

  library = Library.load(file)

  from library.commands import (
    get_book_to_reader,
    put_book_to_library,
    library_show_info,
    quit_command
  )

  command_factory.add_command('1', library_show_info)
  command_factory.add_command('2', get_book_to_reader)
  command_factory.add_command('3', put_book_to_library)
  command_factory.add_command('q', wraps(quit_command)(partial(quit_command, database=file)))

  if not file.exists():
    default_books = [
      Book(1, 'Джоан Роулинг', 'Гарри Поттер и узник Азкабана', 2019),
      Book(2, 'Стивен Кинг', 'Зелёная Миля', 2014),
      Book(3, 'Маргарет Митчел', 'Унесенные ветром', 2020),
      Book(4, 'Артур Конан Дойл', 'Шерлок Холмс. Все повести и рассказы о сыщике №1 (сборник)', 2019)
    ]

    [library.add_new_book(x) for x in default_books]


def main():
  parser = ArgumentParser()
  parser.add_argument('-d', '--database', help='БД библиотеки', type=Path, default='database.yaml')

  args = parser.parse_args()
  init(args.database)

  while True:
    try:
      print(command_factory.help())
      op = input('Введите номер команды: ')
      command = command_factory.get_command(op)
      command(library)

    except Exception as err:
      print('Ошибка выполнения команды:', err)
    print('\n')


if __name__ == '__main__':
  main()
