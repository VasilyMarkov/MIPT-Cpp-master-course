import numpy as np
from subprocess import Popen, PIPE, STDOUT
import random
import string


def runApp(app, data):
    pipe = Popen([app], stdout=PIPE, stdin=PIPE)
    print(data)
    out = pipe.communicate(input=bytes(data, "UTF-8"))
    return out[0].decode()

def generate_random_string(length=10):
    letters = string.ascii_letters + string.digits
    return ''.join(random.choice(letters) for _ in range(length))

def generate_random_strings(num_strings=5, string_length=10):
    random_strings = [generate_random_string(string_length) + '\n' for _ in range(num_strings)]
    return random_strings

def concatenate_strings(strings_list):
    return ''.join(strings_list)

def run_cpp_app(input_data):
    process = Popen(['./stringTwine'], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    stdout, stderr = process.communicate(input=input_data.encode())
    if process.returncode == 0:
        print("C++ App Output:")
        print(stdout.decode())
    else:
        print("C++ App Error:")
        print(stderr.decode())

if __name__ == "__main__":
    num_strings = 5 
    string_length = 10  

    random_strings = generate_random_strings(num_strings, string_length)
    big_string = concatenate_strings(random_strings)

    print("Generated Strings:")
    print(big_string)

    run_cpp_app(big_string)

