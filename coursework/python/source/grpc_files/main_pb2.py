# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: main.proto
# Protobuf Python Version: 4.25.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\nmain.proto\x12\x02nm\"5\n\x0cRequirements\x12\t\n\x01\x61\x18\x02 \x01(\x01\x12\t\n\x01\x62\x18\x03 \x01(\x01\x12\x0f\n\x07\x65psilon\x18\x01 \x01(\x01\"^\n\x08Integral\x12\x10\n\x08value_38\x18\x01 \x01(\x01\x12\x13\n\x0b\x63\x61ll_cnt_38\x18\x02 \x01(\x03\x12\x13\n\x0bvalue_gauss\x18\x03 \x01(\x01\x12\x16\n\x0e\x63\x61ll_cnt_gauss\x18\x04 \x01(\x03\x32\x42\n\x10\x45valuateIntegral\x12.\n\x08\x45valuate\x12\x10.nm.Requirements\x1a\x0c.nm.Integral(\x01\x30\x01\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'main_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _globals['_REQUIREMENTS']._serialized_start=18
  _globals['_REQUIREMENTS']._serialized_end=71
  _globals['_INTEGRAL']._serialized_start=73
  _globals['_INTEGRAL']._serialized_end=167
  _globals['_EVALUATEINTEGRAL']._serialized_start=169
  _globals['_EVALUATEINTEGRAL']._serialized_end=235
# @@protoc_insertion_point(module_scope)
