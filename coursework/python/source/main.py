from utility import send, Requirements
from analyze import analyze


print("Шаблоны ввода записаны в конце файла main.py")

while True:
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
            epsilon=10**i
        ))

    response = send(request)
    analyze(response)

# Templates
# 0 1 -13 -2
