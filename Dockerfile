FROM gcr.io/robot-motel/hexbase:v0.1.0 AS build
COPY . /src
WORKDIR /src
RUN cmake --parallel 3 .
RUN make

FROM alpine:3.11
RUN apk update && \
    apk upgrade && \
    apk --update add \
        libstdc++
COPY --from=build /src/apps/hexgrpc_server ./
CMD ["./hexgrpc_server"]
