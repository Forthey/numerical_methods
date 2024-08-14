from pydantic import BaseModel


# TODO DTO на 2 параграфа
# 1 - вход list(end_x, h0) -> выход list((list(x), list(y), h0))
# 2 - вход list(end_x, epsilon) -> выход list((list(x), list(y), list(h), epsilon))

class RequirementsP1DTO(BaseModel):
    class SingleRequirement(BaseModel):
        end_x: float
        h0: float

    requirements: list[SingleRequirement] = []


class ResultP1DTO(BaseModel):
    class SingleResult(BaseModel):
        x: list[float]
        y: list[float]
        h0: float

    results: list[SingleResult] = []


class RequirementsP2DTO(BaseModel):
    class SingleRequirement(BaseModel):
        end_x: float
        epsilon: float

    requirements: list[SingleRequirement] = []


class ResultP2DTO(BaseModel):
    class SingleResult(BaseModel):
        x: list[float]
        y: list[float]
        h: list[float]
        epsilon: float

    results: list[SingleResult] = []


def write_to_file_p1(request: RequirementsP1DTO):
    with open("../../data/in.data", "w") as f:
        for requirement in request.requirements:
            f.write(f"{requirement.end_x} {requirement.h0}\n")


def read_from_file_p1() -> ResultP1DTO:
    result = ResultP1DTO()

    with open("../../data/out.data", "r") as f:
        while True:
            x = list(map(float, f.readline().split()))
            if len(x) == 0:
                return result
            result.results.append(ResultP1DTO.SingleResult(
                x=x,
                y=list(map(float, f.readline().split())),
                h0=float(f.readline())
            ))


def write_to_file_p2(request: RequirementsP2DTO):
    with open("../../data/in.data", "w") as f:
        for requirement in request.requirements:
            f.write(f"{requirement.end_x} {requirement.epsilon}\n")


def read_from_file_p2() -> ResultP2DTO:
    result = ResultP2DTO()

    with open("../../data/out.data", "r") as f:
        while True:
            x = list(map(float, f.readline().split()))
            if len(x) == 0:
                return result
            result.results.append(ResultP2DTO.SingleResult(
                x=x,
                y=list(map(float, f.readline().split())),
                h=list(map(float, f.readline().split())),
                epsilon=float(f.readline())
            ))