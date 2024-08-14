from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Vector2(_message.Message):
    __slots__ = ("y", "dy")
    Y_FIELD_NUMBER: _ClassVar[int]
    DY_FIELD_NUMBER: _ClassVar[int]
    y: float
    dy: float
    def __init__(self, y: _Optional[float] = ..., dy: _Optional[float] = ...) -> None: ...

class Requirements(_message.Message):
    __slots__ = ("a", "b", "homo_cauchy", "cauchy", "epsilon")
    A_FIELD_NUMBER: _ClassVar[int]
    B_FIELD_NUMBER: _ClassVar[int]
    HOMO_CAUCHY_FIELD_NUMBER: _ClassVar[int]
    CAUCHY_FIELD_NUMBER: _ClassVar[int]
    EPSILON_FIELD_NUMBER: _ClassVar[int]
    a: float
    b: float
    homo_cauchy: Vector2
    cauchy: Vector2
    epsilon: float
    def __init__(self, a: _Optional[float] = ..., b: _Optional[float] = ..., homo_cauchy: _Optional[_Union[Vector2, _Mapping]] = ..., cauchy: _Optional[_Union[Vector2, _Mapping]] = ..., epsilon: _Optional[float] = ...) -> None: ...

class RequirementsConst(_message.Message):
    __slots__ = ("a", "b", "homo_cauchy", "cauchy", "h0")
    A_FIELD_NUMBER: _ClassVar[int]
    B_FIELD_NUMBER: _ClassVar[int]
    HOMO_CAUCHY_FIELD_NUMBER: _ClassVar[int]
    CAUCHY_FIELD_NUMBER: _ClassVar[int]
    H0_FIELD_NUMBER: _ClassVar[int]
    a: float
    b: float
    homo_cauchy: Vector2
    cauchy: Vector2
    h0: float
    def __init__(self, a: _Optional[float] = ..., b: _Optional[float] = ..., homo_cauchy: _Optional[_Union[Vector2, _Mapping]] = ..., cauchy: _Optional[_Union[Vector2, _Mapping]] = ..., h0: _Optional[float] = ...) -> None: ...

class Point(_message.Message):
    __slots__ = ("x", "y")
    X_FIELD_NUMBER: _ClassVar[int]
    Y_FIELD_NUMBER: _ClassVar[int]
    x: float
    y: float
    def __init__(self, x: _Optional[float] = ..., y: _Optional[float] = ...) -> None: ...

class TabFunc(_message.Message):
    __slots__ = ("points",)
    POINTS_FIELD_NUMBER: _ClassVar[int]
    points: _containers.RepeatedCompositeFieldContainer[Point]
    def __init__(self, points: _Optional[_Iterable[_Union[Point, _Mapping]]] = ...) -> None: ...

class TabFuncWithH(_message.Message):
    __slots__ = ("points", "h")
    POINTS_FIELD_NUMBER: _ClassVar[int]
    H_FIELD_NUMBER: _ClassVar[int]
    points: _containers.RepeatedCompositeFieldContainer[Point]
    h: _containers.RepeatedScalarFieldContainer[float]
    def __init__(self, points: _Optional[_Iterable[_Union[Point, _Mapping]]] = ..., h: _Optional[_Iterable[float]] = ...) -> None: ...
