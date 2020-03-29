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
        libunwind

FROM phase_1 AS phase_2
COPY . /src
WORKDIR /src
RUN cmake --parallel 3 .
RUN make

FROM alpine:3.11
RUN apk update && \
    apk upgrade && \
    apk --update add \
        libstdc++
COPY --from=phase_2 /src/apps/hexgrpc_server ./
CMD ["./hexgrpc_server"]
