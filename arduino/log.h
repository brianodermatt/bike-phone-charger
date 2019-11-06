#ifndef LOG
#define LOG

  /*
   * Set VERBOSE to 1 for logging and to 0 for no logging
   */
  #define VERBOSE 1
  
  #if (VERBOSE)
    #define echo(...) Serial.print(__VA_ARGS__)
    #define echoln(...) Serial.println(__VA_ARGS__)
  #else
    // defined as empty when
    #define echo(...)
    #define echoln(...)
  #endif

#endif
