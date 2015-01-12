#ifndef VERSIONINFO_H
#define VERSIONINFO_H

#ifdef _WIN32

#define VER_FILEVERSION             0,0,1,2
#define VER_FILEVERSION_STR         "0.0.1.2\0"

#define VER_PRODUCTVERSION          0,0,1,2
#define VER_PRODUCTVERSION_STR      "0.0.1\0"

#define VER_COMPANYNAME_STR         "i2p.io"
#define VER_FILEDESCRIPTION_STR     "The Abscond Bundle, Repungo launcher"
#define VER_INTERNALNAME_STR        "Repungo Launcher"
#define VER_LEGALCOPYRIGHT_STR      "Copyright © 2014 privacysolutions.no"
#define VER_LEGALTRADEMARKS1_STR    "All Rights Reserved"
#define VER_LEGALTRADEMARKS2_STR    VER_LEGALTRADEMARKS1_STR
#define VER_ORIGINALFILENAME_STR    "Repungo.exe"
#define VER_PRODUCTNAME_STR         "Repungo"

#define VER_COMPANYDOMAIN_STR       "i2p.io"
#endif

const char* version = "0.0.1.2";
const char* revison = "-rev1";

#endif // VERSIONINFO_H
