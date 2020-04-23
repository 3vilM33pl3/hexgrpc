FROM alpine:3.11

RUN apk upgrade && \
    apk --update --no-cache add \
        gcc \
        g++ \
        build-base \
        autoconf \
        automake \
        libtool \
        cmake \
        libstdc++ \
        git \
        boost-dev \
        boost-program_options \
        bash \
        vim \
        protobuf-dev \
        openssl-dev \
        zlib-dev \
        libunwind

COPY . /src
WORKDIR /src
RUN cmake . -DgRPC_INSTALL=ON                \
                  -DCMAKE_BUILD_TYPE=Release       \
                  -DgRPC_PROTOBUF_PROVIDER=package \
                  -DgRPC_SSL_PROVIDER=package      \
                  -DgRPC_ZLIB_PROVIDER=package
RUN make -j16
RUN make install


