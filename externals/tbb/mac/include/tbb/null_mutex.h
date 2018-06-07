/*
    Copyright 2005-2017 Intel Corporation.

    The source code, information and material ("Material") contained herein is owned by
    Intel Corporation or its suppliers or licensors, and title to such Material remains
    with Intel Corporation or its suppliers or licensors. The Material contains
    proprietary information of Intel or its suppliers and licensors. The Material is
    protected by worldwide copyright laws and treaty provisions. No part of the Material
    may be used, copied, reproduced, modified, published, uploaded, posted, transmitted,
    distributed or disclosed in any way without Intel's prior express written permission.
    No license under any patent, copyright or other intellectual property rights in the
    Material is granted to or conferred upon you, either expressly, by implication,
    inducement, estoppel or otherwise. Any license under such intellectual property
    rights must be express and approved by Intel in writing.

    Unless otherwise agreed by Intel in writing, you may not remove or alter this notice
    or any other notice embedded in Materials by Intel or Intel's suppliers or licensors
    in any way.
*/

#ifndef __TBB_null_mutex_H
#define __TBB_null_mutex_H

#include "tbb_stddef.h"

namespace tbb {

//! A mutex which does nothing
/** A null_mutex does no operation and simulates success.
    @ingroup synchronization */
class null_mutex : internal::mutex_copy_deprecated_and_disabled {
public:
    //! Represents acquisition of a mutex.
    class scoped_lock : internal::no_copy {
    public:
        scoped_lock() {}
        scoped_lock( null_mutex& ) {}
        ~scoped_lock() {}
        void acquire( null_mutex& ) {}
        bool try_acquire( null_mutex& ) { return true; }
        void release() {}
    };

    null_mutex() {}

    // Mutex traits
    static const bool is_rw_mutex = false;
    static const bool is_recursive_mutex = true;
    static const bool is_fair_mutex = true;
};

}

#endif /* __TBB_null_mutex_H */