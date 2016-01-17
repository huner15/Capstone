/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-17-2016
 */

#include <adsb.pb.h>
#include <ownship.pb.h>
#include <radar.pb.h>
#include <tcas.pb.h>

#include "ServerSocket.h"

/** Expected number of command line arguments. */
const int EXPECTED_ARGUMENTS = 2;

int main(int argc, char *argv[]) {
    if (argc != EXPECTED_ARGUMENTS) {
        std::cout << "usage: run_sim port" << std::endl;
    }
    else {
        const in_port_t port = (in_port_t) atoi(argv[1]);

        try {
            // Create a server to start listening for connections on the port.
            ServerSocket server(port);
            std::cout << "Listening on " << port << std::endl;

            while (true) {
                ServerSocket client;
                server.accept(client);
                std::cout << "Client has connected." << std::endl;

                // Fork or thread would probably happen here.

                // Declare reports outside of the send loop.
                OwnshipReport ownshipReport;
                AdsBReport adsbReport;
                RadarReport radarReport;
                TcasReport tcasReport;

                while (true) {
                    // Set Ownship report data fields.
                    ownshipReport.set_timestamp(0);
                    ownshipReport.set_ownship_latitude(1);
                    ownshipReport.set_ownship_longitude(2);
                    ownshipReport.set_ownship_altitude(3);
                    ownshipReport.set_north(4);
                    ownshipReport.set_east(5);
                    ownshipReport.set_down(6);

                    // Set ADS-B report data fields.
                    adsbReport.set_timestamp(7);
                    adsbReport.set_latitude(8);
                    adsbReport.set_longitude(9);
                    adsbReport.set_altitude(10);
                    adsbReport.set_tail_number("11");
                    adsbReport.set_north(12);
                    adsbReport.set_east(13);
                    adsbReport.set_down(14);

                    // Set Radar report data fields.
                    radarReport.set_timestamp(15);
                    radarReport.set_range(16);
                    radarReport.set_azimuth(17);
                    radarReport.set_elevation(18);
                    radarReport.set_id(19);
                    radarReport.set_north(20);
                    radarReport.set_east(21);
                    radarReport.set_down(22);
                    radarReport.set_latitude(23);
                    radarReport.set_longitude(24);
                    radarReport.set_altitude(25);

                    // Set TCAS report data fields.
                    tcasReport.set_id(26);
                    tcasReport.set_range(27);
                    tcasReport.set_altitude(28);
                    tcasReport.set_bearing(29);

                    // Send the reports to the client.
                    client << ownshipReport;
                    client << adsbReport;
                    client << radarReport;
                    client << tcasReport;

                    // Wait one second before sending the next reports.
                    sleep(1);
                }
            }
        }
        catch (SocketException &e) {
            std::cout << "Exception caught: " << e.description() << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Deallocate any global objects allocated by the protobuf library.
    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
