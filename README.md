![Build and Upload Artifacts](https://github.com/3vilM33pl3/hexgrpc/workflows/Build%20and%20Upload%20Artifacts/badge.svg)
## Build & Run
1. Build base image
    ```bash
    docker build -f Dockerfile.base -t gcr.io/robot-motel/hexbase:v0.1.0 .
   ```

2. Build (small) application image
    ```bash
    docker build -t hexagon:1.0 .
   ```

3. Run container
   ```bash
   docker run -p 8080:8080 hexagon:1.0
   ```

## Usage

1. Create gRPC channel
    ```c++
    shared_ptr<Channel> channel = grpc::CreateChannel(ServerAddress, grpc::InsecureChannelCredentials());
    ```
2. Connect to server
    ```c++
    channel->WaitForConnected(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_seconds(10, GPR_TIMESPAN))))
    ```
3. Create client
    ```c++
    HexagonClient hexagonClient(channel);
    ```
4.  Send a request
    ```c++
    auto result = hexagonClient->GetHexagonRing(new Hexagon(x, y, z), r);
    ```
5. Process result
    ```c++
    for(auto hex: result) {
       cout << "x: " << hex.q << " y: " << hex.r << " z: " << hex.r << endl;
    }    
    ```

## Full code example
```c++
shared_ptr<Channel> channel = grpc::CreateChannel(ServerAddress, grpc::InsecureChannelCredentials());
auto ChannelStatus = channel->GetState(true);

if(channel->WaitForConnected(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_seconds(10, GPR_TIMESPAN)))) {
    if(ChannelStatus == GRPC_CHANNEL_READY || ChannelStatus == GRPC_CHANNEL_IDLE) {
        HexagonClient hexagonClient(channel);
        
    } else {
        fmt::print("Channel not ready");
    }
} else {
    fmt::print("Channel connection timeout");
}
```

## Check status connection
```c++
switch (hexagonClient->GetConnectionStatus()) {
    case GRPC_CHANNEL_IDLE:
        out << "gRPC channel idle" << endl;
        break;
    case GRPC_CHANNEL_READY:
        out << "gRPC channel ready" << endl;
        break;
    case GRPC_CHANNEL_CONNECTING:
        out << "gRPC channel connecting" << endl;
        break;
    case GRPC_CHANNEL_TRANSIENT_FAILURE:
        out << "gRPC channel failure, recovering connection" << endl;
        break;
    case GRPC_CHANNEL_SHUTDOWN:
        out<< "gRPC channel shutdown after unrecoverable failure" << endl;
        break;
}
```
## Push Image
1. Login to service account:
```
gcloud auth activate-service-account github-deployer@robot-motel.iam.gserviceaccount.com --key-file=robot-motel-b6b89404bd6e.json
```

2. Docker login:
```bash
docker-credential-gcr configure-docker
gcloud auth print-access-token | docker login -u oauth2accesstoken --password-stdin https://gcr.io
docker-credential-gcr gcr-login
```



FROM alpine:3.11

COPY --from=build /src/_deps/grpc-build/third_party/protobuf/libprotobuf-lite.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/third_party/protobuf/libprotobuf.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/third_party/protobuf/libprotoc.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/third_party/protobuf/protobuf-lite.pc /usr/lib/
COPY --from=build /src/_deps/grpc-build/third_party/protobuf/protobuf.pc /usr/lib/

COPY --from=build /src/_deps/grpc-build/libaddress_sorting.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgpr.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpc++.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpc++_alts.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpc++_error_details.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpc++_reflection.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpc++_unsecure.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpc.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpc_cronet.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpc_plugin_support.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpc_unsecure.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libgrpcpp_channelz.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libupb.a /usr/lib/
COPY --from=build /src/_deps/grpc-build/libs/opt/pkgconfig/ /usr/lib/
COPY --from=build /src/_deps/grpc-build/libs/opt/pkgconfig/ /opt/pkgconfig/

COPY --from=build /src/_deps/grpc-build/third_party/protobuf/protoc /usr/bin/
COPY --from=build /src/_deps/grpc-build/grpc_cpp_plugin /usr/bin/

COPY --from=build /src/_deps/grpc-src/third_party/protobuf/src/google/ /usr/include/google/
COPY --from=build /src/_deps/grpc-src/include/ /usr/include/


