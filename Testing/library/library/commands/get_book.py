from library.library import Library


def get_book_to_reader(library: Library):
  """Выдать книгу читателю"""

  try:
    udk = int(input('Введите номер книги: '))
  except ValueError:
    raise ValueError('Указан некорректный номер книги. '
                     'Номер должен быть положительным целым числом')

  book = library.get_book_by_id(udk)
  print(f'Книга {book} успешно выдана')
