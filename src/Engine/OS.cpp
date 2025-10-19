#include "OS.h"

#include "Log.h"

namespace Hermes {
std::unique_ptr<OSApi> GetOSApi() {
#ifdef HERMES_PLATFORM_LINUX
    return std::make_unique<LinuxAPI>();
#else
    CRITICAL("Failed to find platform appropriate OSApi implementation. The "
             "program will crash at this point!");
    return nullptr;
#endif
}
} // namespace Hermes
