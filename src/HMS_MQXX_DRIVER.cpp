#include "HMS_MQXXX_DRIVER.h"


#if defined(HMS_MQXXX_PLATFORM_STM32_HAL)
HMS_MQXXX::HMS_MQXXX(GPIO_TypeDef *port, uint32_t pin, HMS_MQXXX_Type type) : 
 port(port), pin(pin), type(type) {
    
}

HMS_MQXXX_StatusTypeDef HMS_MQXXX::init() {

}
#endif

