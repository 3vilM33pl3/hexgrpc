
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <hexlib/HexagonClient.hpp>

using namespace cli;
using namespace std;

void Print(vector<HexAxial> vha)
{
    for(auto item: vha) {
        cout << "U: " << item.u() << " V: " << item.v() << endl;
    }
}

int main(int ac, char** av) {
    HexagonClient hexagonClient;

    auto rootMenu = make_unique< Menu >( "cli" );
    rootMenu -> Insert(
            "connect", {"server address:port"},
            [](std::ostream& out, const string& address)
            {
                out << "Connecting to server " << address << endl;
            },
            "Connect to server" );
    rootMenu -> Insert(
            "hex", {"x y z"},
            [&hexagonClient](std::ostream& out, int x, int y, int z)
            {
                out << "Adding [ " << x << " , " << y << " , " << z << " ]" << endl;
                HexCube hc;
                hc.set_x(x);
                hc.set_y(y);
                hc.set_z(z);

                hexagonClient.Add(hc);
            },
            "Add hexagon to stack" );
    rootMenu -> Insert(
            "send",
            [&hexagonClient](ostream& out)
            {
                vector<HexAxial> vha;
                hexagonClient.Send(vha);
                Print(vha);
            },
            "Send hexagon stack");

    Cli cli( std::move(rootMenu) );
    // global exit action
    cli.ExitAction( [](auto& out){ out << "Goodbye and thanks for all the fish.\n"; } );

    CliFileSession input(cli);
    input.Start();

    return 0;
}