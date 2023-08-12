#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "Pythia8/Pythia.h"

int main() {
    // Record the start time
    auto start = std::chrono::high_resolution_clock::now();

    Pythia8::Pythia pythia;
    pythia.readString("Beams:eCM = 5020."); // Set initial energy to 5020GeV
    pythia.readString("HardQCD:all = on");
    pythia.readString("PhaseSpace:pTHatMin = 20");
    pythia.readString("Print:quiet = on"); // Disable standard output
    pythia.init();

    int nEvents = 10000;
    std::ofstream outFile("parton.dat");

    for (int iEvent = 0; iEvent < nEvents; ++iEvent) {
        if (!pythia.next()) continue;

        const Pythia8::Event& event = pythia.event;

        int particleCount = 0; // Count of final state parton-level particles

        outFile << "#" << iEvent + 1 << "\n";

        for (int i = 0; i < event.size(); ++i) {
            if (event[i].isFinalPartonLevel()) {
                outFile << particleCount + 1 << " " << event[i].id() << " " << event[i].name() << " "
                        << event[i].px() << " " << event[i].py() << " " << event[i].pz() << " " << event[i].e() << "\n";
                ++particleCount;
            }
        }

        outFile << "#" << iEvent + 1 << " " << particleCount << " end\n";
    }

    outFile.close();

    // Record the end time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    std::chrono::duration<double> duration = end - start;

    // Convert time points to time_t and then to a string
    std::time_t start_time_t = std::chrono::system_clock::to_time_t(start);
    std::time_t end_time_t = std::chrono::system_clock::to_time_t(end);

    std::cout << "Start time: " << std::ctime(&start_time_t);
    std::cout << "End time: " << std::ctime(&end_time_t);
    std::cout << "Total time elapsed: " << duration.count() << " seconds" << std::endl;

    return 0;
}
