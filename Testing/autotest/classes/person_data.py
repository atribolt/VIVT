from datetime import date


class PersonData:
  __slots__ = [
    'name',
    'surname',
    'birth_date'
  ]

  def __init__(self, name: str, surname: str, birth_date: date):
    self.name = name
    self.surname = surname
    self.birth_date = birth_date

  def dump(self) -> dict:
    return {
      'name': self.name,
      'surname': self.surname,
      'birth_date': self.birth_date
    }

  @staticmethod
  def loads(data: dict) -> 'PersonData':
    return PersonData(
      name=data.get('name'),
      surname=data.get('surname'),
      birth_date=data.get('birth_date')
    )


def test_person_data_dump():
  person = PersonData('Test', 'Testov', date(1965, 1, 12))
  data = person.dump()

  assert data.get('name') == 'Test'
  assert data.get('surname') == 'Testov'
  assert data.get('birth_date') == date(1965, 1, 12)


def test_person_data_load():
  person = PersonData.loads({
    'name': 'Test',
    'surname': 'Testov',
    'birth_date': date(1999, 9, 19)
  })

  assert person.name == 'Test'
  assert person.surname == 'Testov'
  assert person.birth_date == date(1999, 9, 19)
