
#include <fmt/core.h>
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <boost/program_options.hpp>
#include <hexlib/HexagonClient.hpp>

using namespace cli;
using namespace std;
namespace po = boost::program_options;

void Print(vector<HexAxial> vha)
{
    for(auto item: vha) {
        cout << "U: " << item.u() << " V: " << item.v() << endl;
    }
}

void StartClient(HexagonClient *hexagonClient) {
    auto rootMenu = make_unique< Menu >("cli" );
    rootMenu -> Insert(
            "status",
            [&hexagonClient](ostream& out)
            {
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
            },
            "Connectionto server (channel) status" );
    rootMenu->Insert(
            "ring", {"x y z d"},
            [&hexagonClient](ostream& out, int x, int y, int z, int r)
            {
                out << "Requesting ring for " << "[ " << x << " , " << y << " , " << z << " ] with radius " << r << endl;
                auto result = hexagonClient->GetHexagonRing(new Hexagon(x, y, z), r);
                for(auto hex: result) {
                    cout << "x: " << hex.q << " y: " << hex.r << " z: " << hex.r << endl;
                }
            },
            "Request hexagons with center [x y z] and radius [d]"
            );

    Cli cli( move(rootMenu) );
    // global exit action
    cli.ExitAction( [](auto& out){ out << "Goodbye and thanks for all the fish.\n"; } );

    CliFileSession input(cli);
    input.Start();
}

int main(int ac, char** av) {
    string ServerAddress;
    po::options_description desc("Hexagon client options");
    desc.add_options()
            ("help", "help message")
            ("address", po::value<string>(&ServerAddress)->default_value("127.0.0.1:50051"), "address to connect to [ip:port]");

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    shared_ptr<Channel> channel = grpc::CreateChannel(ServerAddress, grpc::InsecureChannelCredentials());
    auto ChannelStatus = channel->GetState(true);

    if(channel->WaitForConnected(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_seconds(10, GPR_TIMESPAN)))) {
        if(ChannelStatus == GRPC_CHANNEL_READY || ChannelStatus == GRPC_CHANNEL_IDLE) {
            HexagonClient hexagonClient(channel);
            StartClient(&hexagonClient);
        } else {
            fmt::print("Channel not ready");
        }
    } else {
        fmt::print("Channel connection timeout");
    }


    return 0;
}