from file import RequirementsP1DTO, RequirementsP2DTO, write_to_file_p1, write_to_file_p2


def read_input_p1() -> RequirementsP1DTO:
    requirements = RequirementsP1DTO()

    print(
        "Формат ввода данных: \n"
        "<конец отрезка> <шаг по отрезку>\n"
        "0 для остановки"
    )
    while True:
        args: list[float] = list(map(float, input().split()))

        if args[0] == 0:
            return requirements
        requirements.requirements.append(RequirementsP1DTO.SingleRequirement(
            end_x=args[0], h0=args[1]
        ))


def read_input_p2() -> RequirementsP2DTO:
    requirements = RequirementsP2DTO()

    print(
        "Формат ввода данных: \n"
        "<конец отрезка> <min точность> <max точность>\n"
    )
    args: list[str] = input().split()
    end_x = float(args[0])

    for e_deg in range(int(args[1]), int(args[2])):
        epsilon = 10 ** e_deg
        requirements.requirements.append(RequirementsP2DTO.SingleRequirement(
            end_x=end_x, epsilon=epsilon
        ))

    return requirements


print("Номер параграфа: ")
p = int(input())

if p == 1:
    write_to_file_p1(read_input_p1())
elif p == 2:
    write_to_file_p2(read_input_p2())
