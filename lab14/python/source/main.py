from utility import send, send_const, Requirements, RequirementsConst, Vector2
from analyze import analyze, analyze_const

print("Шаблоны ввода записаны в конце файла main.py")

homo_cauchy = Vector2(y=0, dy=0)
cauchy = Vector2(y=0, dy=-1)

while True:
    print("No параграфа: ")

    try:
        p = int(input())
    except ValueError:
        print("Неверный ввод")
        continue

    if p == 1:
        print("<left> <right> <h01> <h02> ...")
        try:
            args = list(map(float, input().split()))
        except ValueError as e:
            print(f"Неверный ввод")
            continue

        if len(args) < 3:
            if len(args) == 0:
                exit(0)
            print("Неверное число аргументов")
            continue

        request: list[RequirementsConst] = list()

        h0 = args[2:]
        for i in range(len(h0)):
            request.append(RequirementsConst(
                a=args[0],
                b=args[1],
                homo_cauchy=homo_cauchy,
                cauchy=cauchy,
                h0=h0[i]
            ))

        response = send_const(request)
        analyze_const(response)
    elif p == 2:
        print("<left> <right> <e_min> <e_max>")

        try:
            args = list(map(float, input().split()))
        except ValueError as e:
            print(f"Неверный ввод")
            continue

        if len(args) != 4:
            if len(args) == 0:
                exit(0)
            print("Неверное число аргументов")
            continue

        request: list[Requirements] = list()

        for i in range(int(args[2]), int(args[3])):
            request.append(Requirements(
                a=args[0],
                b=args[1],
                homo_cauchy=homo_cauchy,
                cauchy=cauchy,
                epsilon=10**i
            ))

        response = send(request)
        analyze(response)
    else:
        print("Неверный ввод")

# Templates
# 0 1 0.1 0.05
# 0 1 -12 -2

