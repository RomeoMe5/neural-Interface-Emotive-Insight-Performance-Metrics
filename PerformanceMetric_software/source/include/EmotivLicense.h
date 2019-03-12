/**
* Emotiv SDK
* Copyright (c) 2016 Emotiv Inc.
*
* This file is part of the Emotiv SDK.
*
* Header file for license related API.
*
*/

#ifndef EMOTIVLICENSE_H
#define EMOTIVLICENSE_H

#ifdef __cplusplus
extern "C" {
#endif

#if (!EDK_STATIC_LIB)
#   ifdef EDK_EXPORTS
#       ifdef _WIN32
#           define EDK_API __declspec(dllexport)
#       else
#           if (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER || defined __clang__
#               define EDK_API __attribute__ ((visibility("default")))
#           else
#               define EDK_API
#           endif
#       endif
#   else
#       ifdef _WIN32
#           define EDK_API __declspec(dllimport)
#       else
#           define EDK_API
#       endif
#   endif
#else
#   define EDK_API extern
#endif

    typedef enum IEE_LicenseType_enum {
        IEE_EEG = 0x001,      // Enable EEG data
        IEE_PM  = 0x002,      // Enable Performance Metric detection   
        IEE_EEG_PM = IEE_EEG | IEE_PM   // Enable EEG data and Performance Metric detection   
    } IEE_LicenseType_t;
    //! License information structure
    typedef struct IEE_LicenseInfos_struct {
        unsigned int scopes;            // license type
        unsigned int date_from;         // License is valid from the date
        unsigned int date_to;           // License is valid to  the date

        // need authorize the license, then your current quota will be reset to the debit number.
        // if not, you can still use current quota to hard_limit_date. 
        unsigned int soft_limit_date;   

        // After this date. Your current quota will be reset to 0 and stop using the library.
        unsigned int hard_limit_date;
        unsigned int seat_count;        // number of seat
        unsigned int usedQuota;         // total number of used session.
        unsigned int quota;             // total number of session of current actived license.

    } IEE_LicenseInfos_t;
    //! Debit information structure
    typedef struct IEE_DebitInfos_struct {
        unsigned int remainingSessions;   // number of remain session of the license.
        unsigned int daily_debit_limit;   // the maximum session can be debitable per day.
        unsigned int total_debit_today;   // the number of debited session today.
        unsigned int time_reset;          // the remain time to reset number of daily limit debit (seconds) to 0. 
    } IEE_DebitInfos_t;

    //! Get Debit information of the license
    /*!
        \param remainingSessions -  
        \return EDK_ERROR_CODE
                                 - EDK_OK if the command succeeded

        \sa IedkErrorCode.h
    */
    EDK_API int
        IEE_GetDebitInformation(const char* licenseID, 
                                IEE_DebitInfos_t * debit_info);


    //! Check information of the current license
    /*!    
        \param licenseID   - License key
        \param licenseInfo - License Information    
        \return EDK_ERROR_CODE
                           - EDK_OK if the command succeeded

        \sa IedkErrorCode.h
    */
    EDK_API int
        IEE_LicenseInformation(IEE_LicenseInfos_t * licenseInfo);


    //! Authorize a license with a session debit number
    /*!
        \param licenseID - License key
        \param debitNum  - Indicates number of sessions will be deducted from license
        
        \return EDK_ERROR_CODE
                         - EDK_OK if the command succeeded

        \sa IedkErrorCode.h
    */
    EDK_API int 
        IEE_AuthorizeLicense(const char* licenseID, 
                             unsigned int debitNum);


    //! Set a license to be active
    /*!
        \param licenseID - License key

        \return EDK_ERROR_CODE
                         - EDK_OK if the command succeeded

        \sa IedkErrorCode.h
    */
    EDK_API int
        IEE_SetActiveLicense(const char* licenseID);


#ifdef __cplusplus
}
#endif
#endif // EMOTIVLICENSE_H
