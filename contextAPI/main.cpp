#include <iostream>
#include <zmq.hpp>
#include <thread>
#include <chrono>

#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;

json make_randomWeatherUpdate(int seed);
string get_weatherUpdates();

int main() {
    std::cout << endl << "Pushing weather updates on localhost:5577" << endl;
    this_thread::sleep_for(chrono::milliseconds(500));

    zmq::context_t ctx;
    zmq::socket_t sock(ctx, zmq::socket_type::pub);
    sock.bind("tcp://*:5577");

    auto i {0};
    for(;;){
        cout << endl << "Sending weather updates: " << ++i << endl;

        sock.send(zmq::buffer(get_weatherUpdates()), zmq::send_flags::dontwait);
        this_thread::sleep_for(chrono::milliseconds(500));

    }

    return 0;
}

json make_randomWeatherUpdate(int seed){

//This function will randomise the weather updates and return corresponding JSON object
//
    json obj_json;
    int option = 1 + seed%4;
    auto r = ((float) rand() / (RAND_MAX)) + 1;

    switch (option) {
        case 1:
            obj_json = json({
                                {"location", "Oldervik"},
                                {"temperature", "14"},
                                {"humidity", "60%"},
                                {"wind", "5"},
                                {"precipitation", "20%"},
                                {"road-condition", "dry roads"},
                                {"mesurementUnits", {
                                    {"temperature", "Celsius"},
                                    {"wind", "m/s"}
                                }}
                         });
            break;
        case 2:
            obj_json = json({
                                {"location", "Sommarøy"},
                                {"temperature", "11"},
                                {"humidity", "60%"},
                                {"wind", "7"},
                                {"precipitation", "75%"},
                                {"road-condition", "wet roads"},
                                {"mesurementUnits", {
                                    {"temperature", "Celsius"},
                                    {"wind", "m/s"}
                                }}
                         });
            break;
        case 3:
            obj_json = json({
                                {"location", "Tromsø"},
                                {"temperature", "13"},
                                {"humidity", "50%"},
                                {"wind", "3"},
                                {"precipitation", "10%"},
                                {"road-condition", "dry roads"},
                                {"mesurementUnits", {
                                    {"temperature", "Celsius"},
                                    {"wind", "m/s"}
                                }}
                         });
            break;

        case 4:
            obj_json = json({
                                {"location", "Tromvik"},
                                {"temperature", "-4"},
                                {"humidity", "30%"},
                                {"wind", "7"},
                                {"precipitation", "85%"},
                                {"road-condition", "hard-packed snow"},
                                {"mesurementUnits", {
                                    {"temperature", "Celsius"},
                                    {"wind", "m/s"}
                                }}
                         });
            break;
    }

    return obj_json;
}

string get_weatherUpdates(){
    //JSON Operations
    //
    // create an empty structure (null)get_weatherUpdatesnversion of j to an object)
    json j;
    j["weatherUpdates"] = json::array();

    srand((unsigned) time(0));
    int numberOfWeatherUpdates = 1 + rand()%4;

    cout << endl << "Generating "
         << numberOfWeatherUpdates << " weather updates..." << endl;

    while (numberOfWeatherUpdates != 0){

        json obj_weatherUpdate = make_randomWeatherUpdate(numberOfWeatherUpdates);
        j["weatherUpdates"] .push_back(obj_weatherUpdate);
        --numberOfWeatherUpdates;
    }

    stringstream ss;
    ss << j.dump() ;

    cout << endl << j.dump(4) << endl;

    return ss.str();
}
