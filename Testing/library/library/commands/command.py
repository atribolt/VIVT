class Command:
  name = 'Пустая команда'

  def handle(self, library):
    raise NotImplementedError(f'Для команды "{self.name}" не определен обработчик')
