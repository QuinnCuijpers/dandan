#ifndef DANDAN_JSONREGISTERMACROS_H
#define DANDAN_JSONREGISTERMACROS_H

#include "dandan/serialization/JsonTypeRegistry.h"

#define DANDAN_JSONREGISTER_NUMBER(TypeName, JsonName, serializer,             \
                                   deserializer, representation)               \
    namespace                                                                  \
    {                                                                          \
        const bool TypeName##_registered = []                                  \
        {                                                                      \
            dandan::serialization::NumberRegistry::instance().registerType(    \
                JsonName, typeid(dandan::numbers::TypeName), serializer,       \
                deserializer, representation);                                 \
            return true;                                                       \
        }();                                                                   \
    }
#endif
