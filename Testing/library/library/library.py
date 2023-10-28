import yaml
import tabulate
from pathlib import Path


class Book(yaml.YAMLObject):
  yaml_tag = u'Book'

  def __init__(self,
               udk: int,
               author: str,
               title: str,
               year: int):
    self.udk = udk
    self.author = author
    self.title = title
    self.year = year

  def __eq__(self, other):
    if isinstance(other, Book):
      return (self.udk == other.udk and self.title == other.title
              and self.author == other.author and self.year == other.year)
    return super().__eq__(other)

  def __str__(self):
    return f'Книга({self.udk}, {self.title}, {self.author})'


class LibraryNode(yaml.YAMLObject):
  yaml_tag = u'LibraryNode'

  def __init__(self, book: Book, available: int, count: int):
    self.book = book
    self.count = count
    self.available = available

  def available_increment(self):
    if self.available < self.count:
      self.available += 1
    else:
      raise ValueError('Книг становится больше, чем зарегистрировано')

  def available_decrement(self):
    if self.available:
      self.available -= 1
    else:
      raise ValueError('Книги нет в наличии')

  def __iter__(self):
    for item in (self.book, self.available, self.count):
      yield item


class Library(yaml.YAMLObject):
  yaml_tag = u'Library'

  @staticmethod
  def load(file: Path):
    if file.exists():
      with file.open('r') as db:
        try:
          library = yaml.full_load(db)
        except yaml.YAMLError as err:
          raise RuntimeError(f'Ошибка чтения БД: {err}')
    else:
      library = Library()

    return library

  def dump(self, file: Path):
    with file.open('w') as f:
      yaml.dump(self, f, allow_unicode=True)

  def __init__(self, books: dict = None):
    # Список книг и кол-во книг в наличии
    self.books: dict[int, LibraryNode] = books or {}

  def available_count(self, book_id: int) -> int:
    count = 0
    if info := self.books.get(book_id):
      count = info.available
    return count

  def get_book_by_id(self, book_id: int) -> Book:
    if book_id not in self.books:
      raise IndexError('Неизвестный номер книги')

    node = self.books[book_id]
    node.available_decrement()

    return node.book

  def put_book_by_id(self, book_id: int) -> Book:
    if book_id not in self.books:
      raise IndexError('Неизвестный номер книги')

    node = self.books[book_id]
    node.available_increment()
    return node.book

  def add_new_book(self, book: Book):
    if item := self.books.get(book.udk):
      if item.book == book:
        item.count += 1
      else:
        raise IndexError('Книга с таким номером уже есть в библиотеке')
    else:
      self.books[book.udk] = LibraryNode(book, 0, 1)
    self.books[book.udk].available_increment()

  def catalog_info(self):
    data = self.books.values()
    return tabulate.tabulate(data, ('Книга', 'В наличии (шт)', 'Общее кол-во (шт)'), "rounded_grid")

  def __str__(self):
    return self.catalog_info()
