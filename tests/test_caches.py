import subprocess
import argparse
from subprocess import Popen, PIPE, STDOUT

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

ideal_test_data = {
        (4, 13, 1, 2, 3, 4, 1, 2, 5, 5, 2, 4, 3, 4, 1)              : 8,
        (4, 10, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2)                       : 8,
        (4, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)                      : 0,
        (6, 10, 1, 2, 3, 4, 4, 1, 2, 10, 7, 11)                     : 3,
        (8, 16, 1, 2, 2, 1, 5, 4, 2, 1, 10, 6, 7, 8, 10, 11, 12, 5) : 6,
}

comp_test_data = {
        (4, 13, 1, 2, 3, 4, 1, 2, 5, 5, 2, 4, 3, 4, 1)              : (3, 8),
        (4, 10, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2)                       : (8, 8),
        (4, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)                      : (0, 0),
        (6, 10, 1, 2, 3, 4, 4, 1, 2, 10, 7, 11)                     : (3, 3),
        (8, 16, 1, 2, 2, 1, 5, 4, 2, 1, 10, 6, 7, 8, 10, 11, 12, 5) : (5, 6),
}


def check_output_data(n_test, stdout_data, right_n_hits):
        try:
                if int(stdout_data) == right_n_hits:
                        print(TERMINAL_COLORS.OKGREEN   + \
                                f"Test {n_test} Passed" + \
                        TERMINAL_COLORS.DEFAULT
                        )
                else:
                        print(TERMINAL_COLORS.ERROR                   + \
                                f"Test {n_test} NOT Passed\n"         + \
                                f"Hits: \n\t outputted={stdout_data}" + \
                                f"\n\t right={right_n_hits}"          + \
                        TERMINAL_COLORS.DEFAULT
                        )
        except:
                print(TERMINAL_COLORS.WARNING                           + \
                        f"Test {n_test} fall. Output of program is:\n'" + \
                        stdout_data + "'"                               + \
                      TERMINAL_COLORS.DEFAULT
                      )


def check_comp_output_data(n_test, stdout1_data, stdout2_data, right_1n_hits, right_2n_hits):
        print(TERMINAL_COLORS.OKBLUE    + \
                "2Q cache"              + \
              TERMINAL_COLORS.DEFAULT, end=f"\t"
        )
        check_output_data(n_test, stdout1_data, right_1n_hits);

        print(TERMINAL_COLORS.OKBLUE    + \
                "Ideal cache"           + \
              TERMINAL_COLORS.DEFAULT, end=f"\t"
        )
        check_output_data(n_test, stdout2_data, right_2n_hits);


        print(TERMINAL_COLORS.OKBLUE                                   + \
                f"\t\tDelta={int(stdout2_data) - int(stdout1_data)}\n" + \
              TERMINAL_COLORS.DEFAULT
        )


def run_cache(app2run, input_data, cmd_flags=None):
        pipe = Popen([app2run, cmd_flags], stdout=PIPE, stdin=PIPE)
        
        data_str = str()
        for data in input_data:
                data_str += str(data) + " "

        stdout_data = pipe.communicate(input=bytes(data_str, "UTF-8"))

        return stdout_data[0].decode()
        

def test_cache(input_data, cache_app_name2run, flags=None, compare2ideal_cache=False):
        n_hits = 0
        n_ideal_hits = 0
        
        if compare2ideal_cache:
                for (data, i) in zip(input_data, range(len(input_data))):
                        first_n_hits  = run_cache(cache_app_name2run, data, cmd_flags=flags[0])
                        second_n_hits = run_cache(cache_app_name2run, data, cmd_flags=flags[1])

                        check_comp_output_data(i, first_n_hits, second_n_hits, input_data[data][0], input_data[data][1])
        else:
                for (data, i) in zip(input_data, range(len(input_data))):
                        n_hits = run_cache(cache_app_name2run, data, cmd_flags=flags[0])
                        check_output_data(i, n_hits, input_data[data])


def parser_ctor(parser):
        parser.add_argument('--tq',            action="store_true", help="Run tests for 2Q cache.")
        parser.add_argument('-i', '--ideal',   action="store_true", help="Run tests for ideal cache.")
        parser.add_argument('-c', '--compare', action="store_true", help="Run tests for ideal and 2Q cache and show the difference.")


if __name__ == "__main__":
        parser = argparse.ArgumentParser(prog='2Q and ideal cache tester.')
        parser_ctor(parser)

        args = parser.parse_args()

        if args.tq:
                test_cache(two_q_test_data,   "./two_q_cache", flags=["--tq"])
        elif args.ideal:
                test_cache(ideal_test_data,   "./two_q_cache", flags=["-i"])
        elif args.compare:
                test_cache(comp_test_data, "./two_q_cache", flags=["--tq", "-i"], compare2ideal_cache=True)
        else:
                parser.print_help()