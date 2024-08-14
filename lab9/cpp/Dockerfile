FROM forthey/grpc

WORKDIR /protos
COPY main.proto .
WORKDIR /server
COPY . .
WORKDIR /server/build
RUN cmake ../ -DCMAKE_PREFIX_PATH=$GRPCPP_DIR
RUN make -j 4

WORKDIR /server
CMD ./lab9