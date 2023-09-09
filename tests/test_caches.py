import subprocess
from subprocess import Popen, PIPE, STDOUT

# p = Popen(['myapp'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
# stdout_data = p.communicate(input='data_to_write')[0]

# hosts = subprocess.check_output("grep 'host:' /root/test.txt", shell=True)
# print hosts

class TERMINAL_COLORS:
        PURPLE    = '\033[95m'
        OKBLUE    = '\033[94m'
        OKCYAN    = '\033[96m'
        OKGREEN   = '\033[92m'
        WARNING   = '\033[93m'
        ERROR     = '\033[91m'
        DEFAULT   = '\033[0m'
        BOLD      = '\033[1m'
        UNDERLINE = '\033[4m'


two_q_test_data = {
        (4, 13, 1, 2, 3, 4, 1, 2, 5, 5, 2, 4, 3, 4, 1)              : 3,
        (4, 10, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2)                       : 8,
        (4, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)                      : 0,
        (6, 10, 1, 2, 3, 4, 4, 1, 2, 10, 7, 11)                     : 3,
        (8, 16, 1, 2, 2, 1, 5, 4, 2, 1, 10, 6, 7, 8, 10, 11, 12, 5) : 5,
}


def check_output_data(n_test, stdout_data, right_n_hits):
        if int(stdout_data) == right_n_hits:
                print(TERMINAL_COLORS.OKGREEN   + \
                        f"Test {n_test} Passed" + \
                      TERMINAL_COLORS.DEFAULT
                      )
        else:
                print(TERMINAL_COLORS.ERROR                  + \
                        f"Test {n_test} NOT Passed\n"        + \
                        f"Hits: \n\t outputed={stdout_data}" + \
                        f"\n\t right={right_n_hits}"         + \
                       TERMINAL_COLORS.DEFAULT
                       )


def run_cache(app2run, input_data):
        pipe = Popen([app2run], stdout=PIPE, stdin=PIPE)
        
        data_str = str()
        for data in input_data:
                data_str += str(data) + " "

        stdout_data = pipe.communicate(input=bytes(data_str, "UTF-8"))

        return stdout_data[0].decode()
        
        
        # check_output_data(stdout_data, right_n_hits)

def test_cache(input_data, cache_app_name2run, ideal_cache_app_name2run=None, compare2ideal_cache=False):
        n_hits = 0
        n_ideal_hits = 0
        
        if compare2ideal_cache:
                print("Can not compare to ideal cache")
        else:
                for (data, i) in zip(input_data, range(len(input_data))):
                        n_hits = run_cache(cache_app_name2run, data)
                        check_output_data(i, n_hits, input_data[data])


if __name__ == "__main__":
        test_cache(two_q_test_data, "./two_q_cache")