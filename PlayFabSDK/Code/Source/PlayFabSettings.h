#pragma once

#include "PlayFabError.h"

namespace PlayFab
{
    class PlayFabSettings
    {
    public:
        static const Aws::String playFabSDKVersion;
        static const Aws::String playFabVersionString;

        static bool useDevelopmentEnvironment;
        static Aws::String developmentEnvironmentURL;
        static Aws::String productionEnvironmentURL;
        static Aws::String titleId; // You must set this value for PlayFabSdk to work properly (Found in the Game Manager for your title, at the PlayFab Website)
        static ErrorCallback globalErrorHandler;
        static Aws::String developerSecretKey; // You must set this value for PlayFabSdk to work properly (Found in the Game Manager for your title, at the PlayFab Website)
        static Aws::String logicServerURL; // Assigned by GetCloudScriptUrl, used by RunCloudScript
        static Aws::String advertisingIdType; // Set this to the appropriate AD_TYPE_X constant below
        static Aws::String advertisingIdValue; // Set this to corresponding device value

        // DisableAdvertising is provided for completeness, but changing it is not suggested
        // Disabling this may prevent your advertising-related PlayFab marketplace partners from working correctly
        static bool disableAdvertising;
        static const Aws::String AD_TYPE_IDFA;
        static const Aws::String AD_TYPE_ANDROID_ID;

        static Aws::String getURL(const Aws::String& callPath)
        {
            if (callPath == "/Client/RunCloudScript")
                return getLogicURL(callPath);
            if (serverURL.length() == 0)
                serverURL = "https://"+titleId+(useDevelopmentEnvironment ? developmentEnvironmentURL : productionEnvironmentURL);
            return serverURL + callPath;
        }

    private:
        static Aws::String serverURL; // A cache of the constructed url string

        static Aws::String getLogicURL(const Aws::String& callPath)
        {
            return logicServerURL + callPath;
        }
    };
}
