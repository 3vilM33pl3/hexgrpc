![Build and Deploy to Cloud Run](https://github.com/3vilM33pl3/hexgrpc/workflows/Build%20and%20Deploy%20to%20Cloud%20Run/badge.svg?branch=master)

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


