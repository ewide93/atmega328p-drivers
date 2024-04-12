import re
import sys


def is_testcase(line: str) -> bool:
    return ":PASS" in line or ":IGNORE" in line or ":FAIL" in line


def main() -> None:
    regex = re.compile(r"(\d+) Tests (\d+) Failures (\d+) Ignored")
    test_cnt = 0
    pass_cnt = 0
    fail_cnt = 0
    ignore_cnt = 0

    with open(sys.argv[1], mode="r") as f:
        for line in f:
            match = regex.match(line)
            if match:
                test_cnt += int(match.group(1))
                fail_cnt += int(match.group(2))
                ignore_cnt += int(match.group(3))
            else:
                if is_testcase(line):
                    print(line, end="")

    pass_cnt = test_cnt - fail_cnt - ignore_cnt
    print("----------------------------------------")
    print("              Test results              ")
    print("----------------------------------------")
    print(f"Total   : {test_cnt}")
    print(f"Passed  : {pass_cnt} ({round(pass_cnt / test_cnt * 100, 1)}%)")
    print(f"Failed  : {fail_cnt} ({round(fail_cnt / test_cnt * 100, 1)}%)")
    print(f"Skipped : {ignore_cnt} ({round(ignore_cnt / test_cnt * 100, 1)}%)")


if __name__ == "__main__":
    main()
