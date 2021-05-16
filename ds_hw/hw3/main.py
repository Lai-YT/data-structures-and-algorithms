# main program area

from typing import Callable, Dict, List

from node import *
from poly import *
from read import *
from strategy import *

# function to call the corresponding operation and return two polynomial
def operation_selection(operation: int, poly1: Poly_List, poly2: Poly_List) -> List[Poly_List]:
    switcher: Dict[int, Callable[[Poly_List, Poly_List], List[Poly_List, Poly_List]]] = {
        1: add,
        2: substract,
        3: multiply,
        4: divide,
    }
    # Get the function from switcher dictionary
    func = switcher.get(operation, lambda: "nothing")

    # Execute the function
    return func(poly1, poly2)

# program entry
# function for starting the task
def poly_operation(file_path: str = 'inFile/inFile.txt') -> None:
    # read the input information from the default input text file
    strings = read_lines(file_path)

    # obtain the operation: 1. add; 2. substract; 3. Multiply; 4. Divide
    # and print it out
    operation = int(strings[0])
    operations: Dict[int, str] = {
        1: 'add',
        2: 'substract',
        3: 'multiply',
        4: 'divide'
    }
    print(strings[1], operations.get(operation), strings[2])

    # parse strings 1 and 2 to derive the input polynomials and represent them with
    # linked lists
    poly1 = read_string(strings[1])
    poly2 = read_string(strings[2])

    # perform the operation and two polynomials are returned.
    r1, r2 = operation_selection(operation, poly1, poly2)

    # print out the result
    if (operation == 4):
        print("The quotient is: ", end="")
        r1.printPolynomial()
        print("The remainder is: ", end="")
        r2.printPolynomial()
    else:
        print("The result is: ", end="")
        r1.printPolynomial()


if __name__ == '__main__':
    # execute the program with the input file inFile.txt
    poly_operation('inFile/inFile.txt')
    poly_operation('inFile/inFile-0.txt')
    poly_operation('inFile/inFile-1.txt')
    poly_operation('inFile/inFile-2.txt')
    poly_operation('inFile/inFile-3.txt')
    poly_operation('inFile/inFile-4.txt')
    # 4x^3-2x+1 substract -3x^2+x+4
    # The result is: 4x^3+3x^2-3x-3
    # 4x^3-2x+1 substract 3x^2+x+4
    # The result is: 4x^3-3x^2-3x-3
    # 5x^5-8x^3+2x+10 substract 3x^8-6x^6-4x^4-6x+4
    # The result is: -3x^8+6x^6+5x^5+4x^4-8x^3+8x+6
    # 5x^5-8x^3+2x+10 add 3x^8-6x^6-4x^4-6x+4
    # The result is: 3x^8-6x^6+5x^5-4x^4-8x^3-4x+14
    # 3x^8-6x^6-4x^4-6x+4 divide 5x^5-8x^3+2x+10
    # The quotient is: 0.6x^3-0.24000000000000005x
    # The remainder is: -7.120000000000001x^4-6x^3+0.4800000000000001x^2-3.5999999999999996x+4
    # 4x^3-2x+1 multiply 3x^2+x+4
    # The result is: 12x^5+4x^4+10x^3+x^2-7x+4
