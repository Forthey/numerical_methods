from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class Requirements(_message.Message):
    __slots__ = ("a", "b", "epsilon")
    A_FIELD_NUMBER: _ClassVar[int]
    B_FIELD_NUMBER: _ClassVar[int]
    EPSILON_FIELD_NUMBER: _ClassVar[int]
    a: float
    b: float
    epsilon: float
    def __init__(self, a: _Optional[float] = ..., b: _Optional[float] = ..., epsilon: _Optional[float] = ...) -> None: ...

class Integral(_message.Message):
    __slots__ = ("value", "iter_cnt", "h", "a", "b")
    VALUE_FIELD_NUMBER: _ClassVar[int]
    ITER_CNT_FIELD_NUMBER: _ClassVar[int]
    H_FIELD_NUMBER: _ClassVar[int]
    A_FIELD_NUMBER: _ClassVar[int]
    B_FIELD_NUMBER: _ClassVar[int]
    value: float
    iter_cnt: int
    h: float
    a: float
    b: float
    def __init__(self, value: _Optional[float] = ..., iter_cnt: _Optional[int] = ..., h: _Optional[float] = ..., a: _Optional[float] = ..., b: _Optional[float] = ...) -> None: ...
