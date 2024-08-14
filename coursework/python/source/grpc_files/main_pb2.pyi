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
    __slots__ = ("value_38", "call_cnt_38", "value_gauss", "call_cnt_gauss")
    VALUE_38_FIELD_NUMBER: _ClassVar[int]
    CALL_CNT_38_FIELD_NUMBER: _ClassVar[int]
    VALUE_GAUSS_FIELD_NUMBER: _ClassVar[int]
    CALL_CNT_GAUSS_FIELD_NUMBER: _ClassVar[int]
    value_38: float
    call_cnt_38: int
    value_gauss: float
    call_cnt_gauss: int
    def __init__(self, value_38: _Optional[float] = ..., call_cnt_38: _Optional[int] = ..., value_gauss: _Optional[float] = ..., call_cnt_gauss: _Optional[int] = ...) -> None: ...
