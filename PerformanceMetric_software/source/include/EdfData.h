/**
* Emotiv SDK
* Copyright (c) 2016 Emotiv Inc.
*
* This file is part of the Emotiv SDK.
*
*/


#ifndef EDFDATA_H
#define EDFDATA_H


#ifdef __cplusplus
extern "C" {
#endif

#if (!EDK_STATIC_LIB)
#    ifdef EDK_EXPORTS
#        ifdef _WIN32
#            define EDK_API __declspec(dllexport)
#        else
#            if (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER || defined __clang__
#                define EDK_API __attribute__ ((visibility("default")))
#            else
#                define EDK_API
#            endif
#        endif
#    else
#        ifdef _WIN32
#            define EDK_API __declspec(dllimport)
#        else
#            define EDK_API
#        endif
#    endif
#else
#    define EDK_API extern
#endif

    typedef enum FileType {
        UNKNOW = 0,
        INSIGHT,
        EPOC, 
        EPOCPLUS
    } FileType_t;
    //! eeg data file information
    typedef struct FileInfos {
        char* eegFilePath;            // eeg file path
        unsigned int EEGSampleRate;    // eeg sample rate
        unsigned int motionSampleRate; // motion sample rate
        unsigned int duration;         // duration of the file
    } FileInfos_t;


    //! Start saving EEG to EDF file for a particular user.
    /*!

        \param userID    - engine user ID
        \param filename  - name of EDF file
        \param patientID - patient ID embedded in the EDF file
        \param recordID  - record ID embedded in the EDF file
        \param date      - record date embedded in the EDF file
        \param time      - record time embedded in the EDF file
        \return EDK_ERROR_CODE
                         - EDK_OK if the command succeeded

        \sa IEE_EdfStopSaving()
    */
    EDK_API int
        IEE_EdfStartSaving(int userID,
                           const char * filename,
                           const char * patientID,
                           const char * recordID,
                           const char * date,
                           const char * time);


    //! Stop saving EEG for a particular user.
    /*!

        \param userID    - engine user ID
        \return EDK_ERROR_CODE
                         - EDK_OK if the command succeeded

        \sa IEE_EdfStartSaving()
    */
    EDK_API void
        IEE_EdfStopSaving(int userID);


    //! Stop saving EEG from all user.
    /*!

        \param userID    - engine user ID
        \return EDK_ERROR_CODE
                         - EDK_OK if the command succeeded

        \sa IEE_EdfStartSaving(), IEE_EdfStopSaving()
    */
    EDK_API void
        IEE_EdfStopSavingAll();


    //! Initializes file stream which reads data from a pre-recorded session file.
    /*!

        \param userID            - engine user ID
        \param strFilePath       - File path to the pre-recorded EEG data file.
        \param strMotionFilePath - File path to the pre-recorded motion data file.

        \return EDK_ERROR_CODE
                                 - EDK_OK if an instance is created successfully

        \sa IedkErrorCode.h
    */
    EDK_API int
        IEE_EngineLocalConnect(const char * strFilePath,
                               const char * strMotionFilePath = "");


    //! Remove the file stream out of stream list.
    /*!

        \param userID   - engine user ID
        
        \return EDK_ERROR_CODE
                        - EDK_OK if the command succeeded

        \sa IedkErrorCode.h
    */
    EDK_API int
        IEE_EngineLocalDisconnect(unsigned int userID);


    //! Start playback of the EDF file.
    /*!
        This function should only be involved after calling IEE_EngineLocalConnect() successfully.

        \param userID    - engine user ID
        \return EDK_ERROR_CODE
                         - EDK_OK if the command succeeded

        \sa IEE_EngineLocalConnect(), IEE_EdfStop()
    */
    EDK_API int
        IEE_EdfStart(unsigned int userID);


    //! Stop playback of EDF.
    /*!

        \param userID    - engine user ID
        \return EDK_ERROR_CODE
                         - EDK_OK if the command succeeded

        \sa IEE_EdfStart()
    */
    EDK_API int
        IEE_EdfStop(unsigned int userID);


    //! Seek current EDF file.
    /*!

        \param userID    - engine user ID
        \param sec       - time position to seek in seconds
        \return EDK_ERROR_CODE
                         - EDK_OK if the command succeeded

        \sa IEE_EdfStart()
    */
    EDK_API int
        IEE_EdfSeek(unsigned int userID, 
                    unsigned sec);


    //! Seek current EDF file.
    /*!

        \param userID      - engine user ID
        \param sampleIndex - sample index position to seek in sample
        \return EDK_ERROR_CODE
                           - EDK_OK if the command succeeded

        \sa IEE_EdfStart()
    */
    EDK_API int
        IEE_EdfSampleSeek(unsigned int userID, 
                          unsigned int sampleIndex);


    //! Get total time of EDF file.
    /*!

        \param userID        - engine user ID
        \param pTotalTimeOut - received total time of EDF File in seconds
        \return EDK_ERROR_CODE
                             - EDK_OK if the command succeeded

        \sa IEE_EngineLocalConnect()
    */
    EDK_API int
        IEE_EdfGetTotalTime(unsigned int userID, int * pTotalTimeOut);


    //! Get information of the file
    /*!

        \param userID        - engine user ID
        \param fileType      - type of the file
        \param fileInfos     - information of the file
        \return EDK_ERROR_CODE
                             - EDK_OK if the command succeeded

        \sa IEE_EngineLocalConnect()
    */
    EDK_API int
        IEE_EdfGetInfomation(unsigned int userID, 
                             FileType_t* fileType,
                             FileInfos_t* fileInfos);

#ifdef __cplusplus
}
#endif
#endif // EDFDATA_H
