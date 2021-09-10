/**
 * @file
 * This file forms part of sxpsxfp
 *
 * @author Joshua Saxby <joshua.a.saxby@gmail.com>
 * @date September 2021
 *
 * @copyright Copyright Joshua Saxby <joshua.a.saxby@gmail.com> 2021
 *
 * @copyright
 * This is closed-source software and may not be used in any way without the
 * express written permission of the copyright holder. All rights reserved.
 */

#ifndef COM_SAXBOPHONE_SXPSXFP_SXPSXFP_HPP
#define COM_SAXBOPHONE_SXPSXFP_SXPSXFP_HPP

// NOTE: Blindly assuming that the PS1 environment declares itself as a freestanding implementation for this check!
#if __STDC_HOSTED__
#include <cstdint>
#else
#include <sys/types.h>
#endif

namespace com::saxbophone::sxpsxfp {
    class Fixed {
    public:
        using UnderlyingType = int32_t;
        /**
         * @brief Default constructor, creates a Fixed instance with value 0.0
         */
        Fixed();

    private:
        UnderlyingType _raw_value;
    };
}

#endif // include guard
