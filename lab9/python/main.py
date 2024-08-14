# This is a sample Python script.
# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import p2
import p3
import p4
import dop
from utility import send, Spline


print("Шаблоны ввода записаны в конце файла main.py")

while True:
    print("<Номер параграфа> <id функции> <left> <right> <Число экспериментов> <min узлов> <шаг>")
    args = list(map(float, input().split()))
    if len(args) != 7:
        if len(args) == 0:
            exit(0)
        print("Неверное число аргументов")
        continue

    if args[0] == 5:
        result: list[Spline] = dop.send_for_dop(int(args[1]), int(args[2]), int(args[3]))
        dop.analyze(int(args[1]), result)
    elif args[0] == 4:
        result: list[Spline] = p4.send_for_4(int(args[1]), int(args[2]), int(args[3]), int(args[4]), int(args[5]), args[6])
        p4.analyze(int(args[1]), result)
    else:
        result: list[Spline] = send(int(args[1]), args[2], args[3], int(args[4]), int(args[5]), int(args[6]))

        print(f"Send {len(result)} to analyze")
        print(f"Analyze for {args[0]} paragraph")
        if args[0] == 2:
            p2.analyze(int(args[1]), result)
        elif args[0] == 3:
            p3.analyze(int(args[1]), result)
        elif args[0] == 4:
            p4.analyze(int(args[1]), result)

# Templates
# p2
# 2 1 -1 1 3 6 2
# 2 2 0.1 2 3 6 2
#
# p3
# 3 1 -1 1 40 6 3
# 3 2 0.1 2 40 6 3
#
# p4
# 4 1 -1 1 50 20 0.0001
# 4 2 0.1 2 50 20 0.0001
#
# dop
# 5 1 2 4 0 0 0
# 5 2 0.1 2 0 0 0
