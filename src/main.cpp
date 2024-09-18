/************************/
/*      main.cpp        */
/*    Version 1.0       */
/*     2022/06/12       */
/*  © Davide Pasca      */
/*  © Marco Azimonti    */
/************************/

#include "log/log.h"
#include "gl_app.h"

int main(int, char**)
{
    bool file_log = false;
    LOGGER_PARAM(logging::LEVELMAX, logging::INFO);
    LOGGER_PARAM(logging::LOGTIME, true);
    if (file_log)
    {
        LOGGER_PARAM(logging::FILENAME, "out_viewer.log");
        LOGGER_PARAM(logging::FILEOUT, true);
    }
    GLApp app;
    app.onInit();
    app.mainLoop();
    return 0;
}
