//Sebastan Nicholas Outram
#ifndef AZURE_CLOUD_CREDENTIALS_H
#define AZURE_CLOUD_CREDENTIALS_H

namespace azure_cloud {
    namespace credentials {
        /*
        * Primary Connecion String
        */

        // Use https://dpsgen.z8.web.core.windows.net/ to obtain YOUR connection string
        // This one will not work, but I guess you knew that ;)
        const char iothub_connection_string[] = "HostName=iotc-62ca09bb-103b-4a06-b5cf-4ba149b0b414.azure-devices.net;DeviceId=l0zk9e1knz;SharedAccessKey=IOrlmSqVKu+SHCIpybolPE3Y4tfPeOFbinnBenmKZSU=";
    }
}
#endif
