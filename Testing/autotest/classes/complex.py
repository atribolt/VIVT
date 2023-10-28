class Complex:
  __slots__ = [
    'real', 'imag'
  ]

  def __init__(self, r=0., i=0.):
    self.real = r
    self.imag = i

  def __add__(self, other: 'Complex'):
    return Complex(
      self.real + other.real,
      self.imag + other.imag
    )

  def __sub__(self, other: 'Complex'):
    return Complex(
      self.real - other.real,
      self.imag - other.imag
    )

  def __mul__(self, other: 'Complex'):
    r0, i0 = self.real, self.imag
    r1, i1 = other.real, other.imag

    return Complex(
      r0 * r1 - i0 * i1,
      i0 * r1 + r0 * i1
    )

  def __eq__(self, other: 'Complex'):
    return self.real == other.real and self.imag == other.imag

  def __str__(self):
    return "{0.real} + {0.imag}j".format(self)

  def __repr__(self):
    return f"Complex(real={self.real}, imag={self.imag})"


# ---------------------------------------------------------------------------------
# Test cases

def test_complex_eq():
  assert Complex(0, 0) == Complex(0, 0)


def test_complex_sum():
  assert Complex(0, 0) + Complex(0, 0) == Complex(0, 0)
  assert Complex(0, 0) + Complex(1, 0) == Complex(1, 0)
  assert Complex(1, 0) + Complex(1, 1) == Complex(2, 1)


def test_complex_sub():
  assert Complex(0, 0) - Complex(0, 0) == Complex(0, 0)
  assert Complex(0, 0) - Complex(1, 0) == Complex(-1, 0)
  assert Complex(1, 0) - Complex(1, 1) == Complex(0, -1)


def test_complex_mul():
  assert Complex(0, 0) * Complex(1, 0) == Complex(0, 0)
  assert Complex(0, 1) * Complex(2, 5) == Complex(-5, 2)
  assert Complex(1, 0) * Complex(2, 1) == Complex(2, 1)
