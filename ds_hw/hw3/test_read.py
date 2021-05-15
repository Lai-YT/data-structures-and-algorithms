import unittest
from typing import List

from poly import *
from read import *
from strategy import *


class ReadTestCase(unittest.TestCase):

    def test_read_string(self):
        poly1 = read_string('4x^3-2x+1')
        self.assertEqual('4x^3-2x+1', str(poly1))

        poly2 = read_string('-3x^2+x+4')
        self.assertEqual('-3x^2+x+4', str(poly2))


if __name__ == '__main__':
    unittest.main()
