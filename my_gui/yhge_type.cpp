#ifdef WIN32
#include <float.h> // for ::_isnan()
#else
#include <stdlib.h>
#endif
#include <ctype.h>
//#include <math.h>
#include "yhge_type.h"

namespace YHGE {

    namespace Numeric {

        const float big_float = 1e10f;
        const float small_float = 1e-10f;
        const double big_double = 1e20;
        const double smallis_nan_double = 1e-20;


        bool is_nan(float32 x) {
  #ifdef WIN32
              return (_isnan(x) != 0) || (_finite(x) == 0) ;
  #else
              return isnan(x) || !finite(x);
  #endif
          }

          bool is_nan(float64 x) {
  #ifdef WIN32
              return (_isnan(x) != 0) || (_finite(x) == 0) ;
  #else
              return isnan(x) || !finite(x);
  #endif
          }


        int32 random_int32() {
            return rand();
        }

        float64 random_float64() {
            return float64(rand()) / double(RAND_MAX);
        }


        float32 random_float32() {

            return (float32)(float32(rand()) / double(RAND_MAX));
        }


    }

    namespace Memory {

        long used_memory() {
#ifdef WIN32
            // Note: this returns the amount of virtual memory used
            // by the system (we should replace that by a function
            // that returns the amount of virtual mem used by the
            // *process* ...)
            MEMORYSTATUS stat ;
            GlobalMemoryStatus(&stat) ;
            return (long)(stat.dwTotalVirtual - stat.dwAvailVirtual) ;
#else
            return (long)sbrk(0) ;
#endif
        }

    }

    namespace String {

        void split_string(
            const std::string& in,
            char separator,
            std::vector<std::string>& out,
            bool skip_empty_fields
            ) {
            int length = (int)in.length();
            int start = 0;
            int end = 0;

            while (start < length) {

                end = (int)in.find(separator, start);
                if (end < 0) {
                    end = length;
                }

                if (!skip_empty_fields || (end - start > 0)) {
                    out.push_back(in.substr(start, end - start));
                }
                start = end + 1;
            }
        }


        void join_strings(
            const std::vector<std::string>& in,
            char separator,
            std::string& out
            ) {
            out = "";
            for (unsigned int i = 0; i<in.size(); i++) {
                if (out.length() != 0) {
                    out += separator;
                }
                out += in[i];
            }
        }

        void join_strings(
            const std::vector<std::string>& in,
            const std::string& separator,
            std::string& out
            ) {
            out = "";
            for (unsigned int i = 0; i<in.size(); i++) {
                if (out.length() != 0) {
                    out += separator;
                }
                out += in[i];
            }
        }

        std::string join_strings(
            const std::vector<std::string>& in,
            char separator
            ) {
            std::string result;
            join_strings(in, separator, result);
            return result;
        }

        std::string join_strings(
            const std::vector<std::string>& in,
            const std::string& separator
            ) {
            std::string result;
            join_strings(in, separator, result);
            return result;
        }

        void to_lowercase(std::string& in) {
            for (unsigned int i = 0; i<in.length(); i++) {
                if (isupper(in[i])) {
                    in[i] = tolower(in[i]);
                }
            }
        }

        void to_uppercase(std::string& in) {
            for (unsigned int i = 0; i<in.length(); i++) {
                if (islower(in[i])) {
                    in[i] = toupper(in[i]);
                }
            }
        }

        std::string quote(const std::string& s, char quotes) {
            return char_to_string(quotes) + s + char_to_string(quotes);
        }


        bool string_starts_with(const std::string& haystack, const std::string& needle) {
            unsigned int l1 = haystack.length();
            unsigned int l2 = needle.length();
            if (l2 > l1) { return false; }
            return (haystack.substr(0, l2) == needle);
        }

        bool string_ends_with(const std::string& haystack, const std::string& needle) {
            unsigned int l1 = haystack.length();
            unsigned int l2 = needle.length();
            if (l2 > l1) { return false; }
            return (haystack.substr(l1 - l2, l2) == needle);
        }

    }
}
