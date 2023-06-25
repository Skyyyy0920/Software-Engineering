import unittest
from test import *
# from mock import patch
from unittest.mock import patch
import io
import sys


class TestMaxProductSubarray(unittest.TestCase):

    # @patch('builtins.input', return_value='1 2 3 4 5\n')
    def test_get_input(self):
        # expected_output = [1, 2, 3, 4, 5]
        # self.assertEqual(get_input(), expected_output)
        # 测试正常情况
        with patch('builtins.input', return_value='1 2 3 4 5\n'):
            expected_output = [1, 2, 3, 4, 5]
            self.assertEqual(get_input(), expected_output)

        # 测试空输入
        with patch('builtins.input', return_value='\n'):
            expected_output = []
            self.assertEqual(get_input(), expected_output)
    #     测试异常输入
        with patch('builtins.input', return_value='1 a 3\n'):
            with self.assertRaises(ValueError) as cm:
                get_input()
            self.assertEqual(str(cm.exception), "Invalid input, please input valid numbers separated by space.")

    def test_read_input_file(self):
        file_path = 'test_input.txt'
        with open(file_path, 'w') as f:
            f.write('1\n2\n3\n4\n5\n')
        expected_output = [1, 2, 3, 4, 5]
        self.assertEqual(read_input_file(file_path), expected_output)

        self.assertEqual(read_input_file(""), [], "Should return an empty list for empty file path")

    def test_calculate_max_product(self):
        arr = [2, 3, -2, 4]
        expected_output = 6
        self.assertEqual(calculate_max_product(arr), expected_output)

        arr = [2, 3, 0, 4]
        expected_output = 6
        self.assertEqual(calculate_max_product(arr), expected_output)

        arr = [-2, -3, -4, -1]
        expected_output = 24
        self.assertEqual(calculate_max_product(arr), expected_output)

    @patch('sys.stdout', new_callable=io.StringIO)
    def test_print_result(self, mock_stdout):
        result = 6
        print_result(result)
        self.assertEqual(mock_stdout.getvalue().strip(), 'The maximum product of subarray is: 6')

    def test_write_output_file(self):
        file_path = 'test_output.txt'
        write_output_file(file_path, 6)
        with open(file_path, 'r') as f:
            self.assertEqual(f.read().strip(), '6')

if __name__ == '__main__':
    unittest.main()