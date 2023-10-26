from library.library import Library


def put_book_to_library(library: Library):
  """Вернуть книгу в библиотеку"""

  try:
    udk = int(input('Введите номер книги: '))
  except ValueError:
    raise ValueError('Указан некорректный номер книги. '
                     'Номер должен быть положительным целым числом')

  book = library.put_book_by_id(udk)
  print(f'Книга "{book}" возвращена в библиотеку')
