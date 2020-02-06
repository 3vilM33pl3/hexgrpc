FROM alpine:3.11 AS phase_1

RUN apk update && \
    apk upgrade && \
    apk --update add \
        curl \
        gcc \
        g++ \
        build-base \
        autoconf \
        automake \
        libtool \
        git \
        cmake \
        bash \
        libstdc++ \
        protobuf \
        protobuf-dev \
        grpc \
        grpc-dev \
        boost-dev \
        libunwind \
        go \
        vim

COPY . /src
WORKDIR /src
RUN cmake -DDOCKER_PHASE_1=TRUE -DDOCKER_PHASE_2=FALSE -DDOCKER_INSTALL_LIBS=TRUE .
RUN make

FROM phase_1 AS phase_2
COPY . /src
WORKDIR /src
RUN cmake -DDOCKER_PHASE_1=FALSE /src
RUN make

FROM phase_2
COPY --from=phase_2 /src/hexgrpc_server ./
CMD ["./hexgrpc_server"]