# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import grpc_files.main_pb2 as main__pb2


class EvaluateIntegralStub(object):
    """Missing associated documentation comment in .proto file."""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.Evaluate = channel.stream_stream(
                '/nm.EvaluateIntegral/Evaluate',
                request_serializer=main__pb2.Requirements.SerializeToString,
                response_deserializer=main__pb2.Integral.FromString,
                )


class EvaluateIntegralServicer(object):
    """Missing associated documentation comment in .proto file."""

    def Evaluate(self, request_iterator, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_EvaluateIntegralServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'Evaluate': grpc.stream_stream_rpc_method_handler(
                    servicer.Evaluate,
                    request_deserializer=main__pb2.Requirements.FromString,
                    response_serializer=main__pb2.Integral.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'nm.EvaluateIntegral', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))


 # This class is part of an EXPERIMENTAL API.
class EvaluateIntegral(object):
    """Missing associated documentation comment in .proto file."""

    @staticmethod
    def Evaluate(request_iterator,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.stream_stream(request_iterator, target, '/nm.EvaluateIntegral/Evaluate',
            main__pb2.Requirements.SerializeToString,
            main__pb2.Integral.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
