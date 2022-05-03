/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   tailonly_png;
    const int            tailonly_pngSize = 2412;

    extern const char*   erapf_png;
    const int            erapf_pngSize = 1908;

    extern const char*   direct_png;
    const int            direct_pngSize = 530;

    extern const char*   erfilter_png;
    const int            erfilter_pngSize = 654;

    extern const char*   er_png;
    const int            er_pngSize = 657;

    extern const char*   erapffiltersoft_png;
    const int            erapffiltersoft_pngSize = 1657;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
