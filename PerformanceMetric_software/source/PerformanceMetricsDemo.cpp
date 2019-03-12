#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <chrono>

#include "IEmoStateDLL.h"
#include "Iedk.h"
#include "IedkErrorCode.h"
#include "IEmoStatePerformanceMetric.h"
#include "EmotivLicense.h"

inline double normalize(double rawScore, double maxScale, double minScale) {
    if (rawScore < minScale) {
        return 0;
    } else if (rawScore > maxScale)	{
        return 1;
    } else {
        return (rawScore - minScale)/(maxScale - minScale);
    }
}


void writeHeader(std::ostream& os);
void miniLog(std::ostream& os, double rawScore, double maxScale, double minScale);
void logData(std::ostream &os, unsigned int userID, EmoStateHandle eState);


int main(int argc, char** argv) {

    EmoEngineEventHandle eEvent	= IEE_EmoEngineEventCreate();
    EmoStateHandle eState = IEE_EmoStateCreate();
    unsigned int userID	= 0;
    int state  = 0;

    if (IEE_EngineConnect() != EDK_OK) {
        std::cerr << "Connection failed\n";
        return -1;
    }

    IEE_LicenseInfos_t licenseInfos;
    int result = IEE_LicenseInformation(&licenseInfos);
    std::cout << "License: " << result << '\n';
    std::cout << "Press any key to stop logging..." << std::endl;
    std::ofstream ofs("PerformanceMetricData.csv");

    writeHeader(ofs);
    while (!_kbhit()) {
        state = IEE_EngineGetNextEvent(eEvent);
        if (state == EDK_OK) {
            IEE_Event_t eventType = IEE_EmoEngineEventGetType(eEvent);
            IEE_EmoEngineEventGetUserId(eEvent, &userID);
            if (eventType == IEE_EmoStateUpdated) {
                IEE_EmoEngineEventGetEmoState(eEvent, eState);
                logData(ofs, userID, eState);
            }
        }
        Sleep(0.05);
    }

    ofs.close();
    IEE_EngineDisconnect();
    IEE_EmoStateFree(eState);
    IEE_EmoEngineEventFree(eEvent);

    return 0;
}

void writeHeader(std::ostream &os) {
    os << "Time,";
    os << "UserID,";
    os << "Stress raw score,";
    os << "Stress min score,";
    os << "Stress max score,";
    os << "Stress scaled score,";
    os << "Engagement boredom raw score,";
    os << "Engagement boredom min score,";
    os << "Engagement boredom max score,";
    os << "Engagement boredom scaled score,";
    os << "Relaxation raw score,";
    os << "Relaxation min score,";
    os << "Relaxation max score,";
    os << "Relaxation scaled score,";
    os << "Excitement raw score,";
    os << "Excitement min score,";
    os << "Excitement max score,";
    os << "Excitement scaled score,";
    os << "Interest raw score,";
    os << "Interest min score,";
    os << "Interest max score,";
    os << "Interest scaled score,";
    os << std::endl;
}

void miniLog(std::ostream &os, double rawScore, double maxScale, double minScale) {
    os << rawScore << "," << minScale << "," << maxScale << ",";
    if (minScale == maxScale) {
        os << "???" << ",";
    } else {
        os << normalize(rawScore, maxScale, minScale) << ",";
    }
}

void logData(std::ostream& os, unsigned int userID, EmoStateHandle eState) {
    os << IS_GetTimeFromStart(eState) << ",";
    os << userID << ",";

    double rawScore = 0;
    double minScale = 0;
    double maxScale = 0;

    /* Stress */
    IS_PerformanceMetricGetStressModelParams(eState, &rawScore, &minScale, &maxScale);
    miniLog(os, rawScore, maxScale, minScale);

    /* Engagement */
    IS_PerformanceMetricGetEngagementBoredomModelParams(eState, &rawScore, &minScale, &maxScale);
    miniLog(os, rawScore, maxScale, minScale);

    /* Relaxation */
    IS_PerformanceMetricGetRelaxationModelParams(eState, &rawScore, &minScale, &maxScale);
    miniLog(os, rawScore, maxScale, minScale);

    /* Instantaneous */
    IS_PerformanceMetricGetInstantaneousExcitementModelParams(eState, &rawScore, &minScale, &maxScale);
    miniLog(os, rawScore, maxScale, minScale);

    /* Instantaneous */
    IS_PerformanceMetricGetInterestModelParams(eState, &rawScore, &minScale, &maxScale);
    miniLog(os, rawScore, maxScale, minScale);

    os << std::endl;
}


