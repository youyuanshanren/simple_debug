#include "debug_simple.h"

void testSimple()
{
    bFatal("bFatal:%s %d", "ssss", 12334);
    bCritica("bCritica");
    bError("bError");
    bWarning("bWarning");
    bNotice("bNotice");
    bInfo("bInfo");
    bDebug("bDebug");
    bTrace("bTrace");

    cFatal("cFatal:"
           << "ssss " << 12334);
    cCritica("cCritica"
             << " test");
    cError("cError");
    cWarning("cWarning");
    cNotice("cNotice " << 11111 << " adfa " << 1234);
    cInfo("cInfo2" << 1111);
    cDebug("cDebug");
    cTrace("cTrace");
}

int main()
{
    testSimple();
    return 0;
}
