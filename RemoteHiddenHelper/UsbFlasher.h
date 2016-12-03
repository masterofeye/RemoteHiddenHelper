#pragma once
#include "BasicWrapper.h"

namespace RW{
    namespace CORE{

        class UsbFlasher :
            public BasicWrapper
        {
        public:
            UsbFlasher();
            ~UsbFlasher();
        };
    }
}
