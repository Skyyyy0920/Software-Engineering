import sys


def get_input():
    """
    获取用户输入的数字列表
    """
    print("Please input numbers:")
    num = input()
    if not num.strip():
        return []

    # 使用正则表达式判断输入是否合法
    now_arr = num.strip().split(' ')
    try:
        now_arr = [int(num) for num in now_arr]
    except ValueError:
        raise ValueError("Invalid input, please input valid numbers separated by space.")
    return now_arr


def read_input_file(file_path):
    """
    从文件中读取数据
    """
    try:
        with open(file_path, 'r') as f:
            lines = f.readlines()
    except FileNotFoundError:
        print("Error: File not found.")
        return []
    # print(len(lines))
    now_arr = []
    # print(lines)

    for line in lines:
        # print(line)
        new_line = line.strip().split(' ')
        # print(now_arr)
        try:
            now_arr += [int(num) for num in new_line]
        except ValueError:
            raise ValueError("Invalid input, please input valid numbers separated by space.")

    return now_arr


def calculate_max_product(now_arr):
    """
    计算数组的最大乘积子数组
    """
    max_product = -sys.maxsize
    min_product = sys.maxsize
    final_result = -sys.maxsize

    for num in now_arr:
        new_max_product = num if max_product == -sys.maxsize else \
            max(max_product * num, min_product * num, num)
        new_min_product = num if min_product == sys.maxsize else \
            min(min_product * num, max_product * num, num)
        max_product = new_max_product
        min_product = new_min_product
        final_result = max(max_product, final_result)

    return final_result


def print_result(final_result):
    """
    打印结果
    """
    print("The maximum product of subarray is: {}".format(final_result))


def write_output_file(file_path, final_result):
    """
    将结果写入文件中
    """
    with open(file_path, 'w') as f:
        f.write(str(final_result))


if __name__ == '__main__':
    # 从控制台输入数据
    nums = get_input()
    # for i in range(10):
    result = calculate_max_product(nums)
    print_result(result)

    # 从文件中读取数据
    arr = read_input_file('C://Users//26937//Desktop//软件工程//input.txt')
    print(arr)
    result = calculate_max_product(arr)
    write_output_file('C://Users//26937//Desktop//软件工程//output.txt', result)
