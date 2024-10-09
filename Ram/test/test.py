from subprocess import Popen, PIPE, STDOUT
import subprocess
from pathlib import Path
from os import listdir
from os.path import isfile, join

def runApp(app, input_data):
    pipe = Popen([app], stdout=PIPE, stdin=PIPE)
    out = pipe.communicate(input=bytes(input_data, "UTF-8"))
    return out[0].decode()


def get_file_list(path):
    file_list = [f for f in listdir(path) if isfile(join(path, f))]
    return file_list

if __name__ == "__main__":
    files = get_file_list(str(Path.cwd()) + "/test/data/")
    files.sort()
    in_files = ["../test/data/"+filename for filename in files if filename.endswith('.in')]

    out_files = [str(Path.cwd()) + "/test/data/" + filename for filename in files if filename.endswith('.out')]
    app = str(Path.cwd())+"/build/Ram"
    
    ram_out = [subprocess.run([app, file], capture_output=True, text=True).stdout for file in in_files]
    print(ram_out)
    # ram_out = [i.replace('\n', '') for i in ram_out]
    # print(ram_out)
    # files_out = []
    # for file in out_files:
    #     with open(file, 'r') as f:
    #         files_out.append(f.read())

    # files_out = [i.replace('\n', '') for i in files_out]


    # RED = '\033[31m'
    # GREEN = '\033[32m'
    # BLUE = '\033[34m'
    # RESET = '\033[0m'

    # print(f'{GREEN}[------------]{RESET}')
    # passed = True
    # for ram, answer, in_file, out_file in zip(ram_out, files_out, in_files, out_files):
    #     print(ram)
    #     print(f'{GREEN}[ RUN        ]{RESET}' + f'{in_file}')
    #     if ram == answer:
    #         print(f'{GREEN}[         OK ]{RESET}' + f' {ram} == {answer}')
    #     else:
    #         passed = False
    #         print(f'{RED}[   FAILED   ]{RESET}')

    # if passed:
    #     print(f'{GREEN}[   PASSED   ]{RESET}')
    # else:
    #     print(f'{RED}[   FAILED   ]{RESET}')
    # print(f'{GREEN}[------------]{RESET}')