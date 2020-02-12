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
        boost-program_options \
        libunwind \
        go \
        vim

FROM phase_1 AS phase_2
COPY . /src
WORKDIR /src
RUN cmake .
RUN make

FROM phase_2
COPY --from=phase_2 /src/apps/hexgrpc_server ./
CMD ["./hexgrpc_server"]
