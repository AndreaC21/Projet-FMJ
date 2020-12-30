// main.cpp

// Allow log messages.
#define _LOG_

#include "log.h"
#include "scene.h"

int main( int argc, const char * argv[] )
{
    // Return value = 0 means OK.
    int rval { 0 };
    Scene scene;

    try {
        bool success = scene.initialise( argc, argv );
        if( success )
        {
          LOG_MSG( "Scene initialisation succeeded.\n" );
          scene.run_loop();
        }
        else
        {
          LOG_MSG( "Failed to initialise scene!" );
        }

    }
    catch( GuiSdlException& e )
    {
        std::cerr << "Failed to initialize! SDL Error: " << e.what() << std::endl;
        rval = 1;
    }
    catch( GuiTtfException& e )
    {
        std::cerr << "Failed to initialize! TTF Error: " << e.what() << std::endl;
        rval = 1;
    }
    catch( std::runtime_error e )
    {
        std::cerr << "Failure! " << e.what() << std::endl;
        rval = 1;
    }
    catch( std::exception e )
    {
        std::cerr << "Failure! " << e.what() << std::endl;
        rval = 1;
    }
    catch( ... )
    {
        std::cerr << "Failure!" << std::endl;
        rval = 1;
    }

    scene.shutdown();
    LOG_MSG( "Scene shut down.\n" );

    return rval;
}
