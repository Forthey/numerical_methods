from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Point(_message.Message):
    __slots__ = ("x", "y")
    X_FIELD_NUMBER: _ClassVar[int]
    Y_FIELD_NUMBER: _ClassVar[int]
    x: float
    y: float
    def __init__(self, x: _Optional[float] = ..., y: _Optional[float] = ...) -> None: ...

class TabFunc(_message.Message):
    __slots__ = ("points", "expand_to")
    POINTS_FIELD_NUMBER: _ClassVar[int]
    EXPAND_TO_FIELD_NUMBER: _ClassVar[int]
    points: _containers.RepeatedCompositeFieldContainer[Point]
    expand_to: int
    def __init__(self, points: _Optional[_Iterable[_Union[Point, _Mapping]]] = ..., expand_to: _Optional[int] = ...) -> None: ...

class TabFuncs(_message.Message):
    __slots__ = ("tab_funcs",)
    TAB_FUNCS_FIELD_NUMBER: _ClassVar[int]
    tab_funcs: _containers.RepeatedCompositeFieldContainer[TabFunc]
    def __init__(self, tab_funcs: _Optional[_Iterable[_Union[TabFunc, _Mapping]]] = ...) -> None: ...

class Spline(_message.Message):
    __slots__ = ("points", "base_points")
    POINTS_FIELD_NUMBER: _ClassVar[int]
    BASE_POINTS_FIELD_NUMBER: _ClassVar[int]
    points: _containers.RepeatedCompositeFieldContainer[Point]
    base_points: _containers.RepeatedCompositeFieldContainer[Point]
    def __init__(self, points: _Optional[_Iterable[_Union[Point, _Mapping]]] = ..., base_points: _Optional[_Iterable[_Union[Point, _Mapping]]] = ...) -> None: ...
